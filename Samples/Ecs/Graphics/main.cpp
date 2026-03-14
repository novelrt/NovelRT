// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EcsDefaultsBuilder.hpp>
#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>

#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/Components/EntityGraphComponent.hpp>

#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>
#include <NovelRT/Ecs/Graphics/EcsGraphicsBuilder.hpp>
#include <NovelRT/Ecs/Graphics/RenderOrchestratorSystem.hpp>
#include <NovelRT/Ecs/Graphics/RenderPassManager.hpp>

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>

#include <NovelRT/Graphics/GraphicsPipeline.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInput.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElement.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElementKind.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResource.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResourceKind.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapterSelector.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderTarget.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>

#include <NovelRT/ResourceManagement/Desktop/DesktopResourceLoader.hpp>

#include <NovelRT/Timing/StepTimer.hpp>

#include <NovelRT/Windowing/Glfw/GlfwWindowProvider.hpp>

#include <NovelRT/Utilities/Macros.hpp>

#include <memory>
#include <optional>

using namespace NovelRT::Ecs;
using namespace NovelRT::Ecs::Components;
using namespace NovelRT::Ecs::Graphics;
using namespace NovelRT::Ecs::Graphics::Components;
using namespace NovelRT::Logging;
using namespace NovelRT::Graphics;
using namespace NovelRT::Graphics::Vulkan;
using namespace NovelRT::Timing;
using namespace NovelRT::Windowing;
using namespace NovelRT::Utilities;
using namespace NovelRT::ResourceManagement::Desktop;
using namespace NovelRT::Timing;

struct PtrNonsense
{
    std::shared_ptr<GraphicsRenderPass<VulkanGraphicsBackend>> trianglePass;
    std::shared_ptr<IGraphicsSurface> sampleSurface;
    std::shared_ptr<GraphicsMemoryAllocator<VulkanGraphicsBackend>> memoryAllocator;
    std::shared_ptr<GraphicsDevice<VulkanGraphicsBackend>> gfxDevice;
    RenderPassId triangleRenderPassId;
};

PtrNonsense& GetPtrNonsenseStruct()
{
    static PtrNonsense storage{};
    return storage;
}

struct TexturedVertex
{
    NovelRT::Maths::GeoVector3F Position;
    NovelRT::Maths::GeoVector2F UV;
};

template<typename TBackend>
struct RenderingData
{
    std::shared_ptr<GraphicsBuffer<TBackend>> VertexBuffer;
    std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>> VertexBufferRegion;
    std::shared_ptr<GraphicsPipeline<TBackend>> RenderPipeline;
    std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>> TextureRegion;
    std::shared_ptr<GraphicsContext<TBackend>> GraphicsContext;
};

template<typename TBackend>
class SampleTriangleRenderingSystem : public IEcsSystem
{
private:
    std::shared_ptr<DesktopResourceLoader> _resourceLoader; // TODO: This is bad. Too bad! - Matt J.
    RenderingData<TBackend> _renderingData;
    std::vector<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, VulkanGraphicsBackend>>>
        _inputResourceRegions;
    std::optional<EntityId> _cmdListEntity;

public:
    SampleTriangleRenderingSystem() : _resourceLoader(std::make_shared<DesktopResourceLoader>())
    {
        GraphicsBufferCreateInfo bufferCreateInfo{};
        bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::Write;
        bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Read;
        bufferCreateInfo.size = 64 * 1024;

        auto vertexStagingBuffer = GetPtrNonsenseStruct().memoryAllocator->CreateBuffer(bufferCreateInfo);

        bufferCreateInfo.size = 64 * 1024 * 4; // need this to be a different size but rest of the values are unchanged.

        auto textureStagingBuffer = GetPtrNonsenseStruct().memoryAllocator->CreateBuffer(bufferCreateInfo);

        bufferCreateInfo.bufferKind = GraphicsBufferKind::Vertex;
        bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::None;
        bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Write;
        bufferCreateInfo.size = 64 * 1024;

        auto vertexBuffer = GetPtrNonsenseStruct().memoryAllocator->CreateBuffer(bufferCreateInfo);

        auto vertShaderData = _resourceLoader->LoadShaderSource("vulkanrendervert.spv");
        auto pixelShaderData = _resourceLoader->LoadShaderSource("vulkanrenderfrag.spv");
        auto gfxSwapchainImage = GetPtrNonsenseStruct().gfxDevice->BeginFrame();

        std::vector<GraphicsPipelineInputElement> elements{
            GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector3F),
                                         GraphicsPipelineInputElementKind::Position, 12),
            GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F),
                                         GraphicsPipelineInputElementKind::TextureCoordinate, 8)};

        std::vector<GraphicsPipelineInput> inputs{GraphicsPipelineInput(elements)};
        std::vector<GraphicsPipelineResource> resources{
            GraphicsPipelineResource(GraphicsPipelineResourceKind::Texture, ShaderProgramVisibility::Pixel)};

        std::vector<GraphicsPushConstantRange> dummyData{};
        auto signature = GetPtrNonsenseStruct().gfxDevice->CreatePipelineSignature(
            GraphicsPipelineBlendFactor::SrcAlpha, GraphicsPipelineBlendFactor::OneMinusSrcAlpha, inputs, resources,
            NovelRT::Utilities::Span<GraphicsPushConstantRange>(dummyData));
        auto vertShaderProg = GetPtrNonsenseStruct().gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Vertex,
                                                                                    vertShaderData.shaderCode);
        auto pixelShaderProg = GetPtrNonsenseStruct().gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Pixel,
                                                                                     pixelShaderData.shaderCode);

        auto pipeline = GetPtrNonsenseStruct().gfxDevice->CreatePipeline(signature, vertShaderProg, pixelShaderProg,
                                                                         GetPtrNonsenseStruct().trianglePass);
        auto gfxContext = GetPtrNonsenseStruct().gfxDevice->CreateGraphicsContext();

        auto vertexBufferRegion = vertexBuffer->Allocate(sizeof(TexturedVertex) * 3, 16);
        auto stagingBufferRegion = vertexStagingBuffer->Allocate(sizeof(TexturedVertex) * 3, 16);

        auto pVertexBuffer = vertexStagingBuffer->template Map<TexturedVertex>(vertexBufferRegion);

        pVertexBuffer[0] =
            TexturedVertex{NovelRT::Maths::GeoVector3F(0, 1, 0), NovelRT::Maths::GeoVector2F(0.5f, 0.0f)};
        pVertexBuffer[1] =
            TexturedVertex{NovelRT::Maths::GeoVector3F(1, -1, 0), NovelRT::Maths::GeoVector2F(1.0f, 1.0f)};
        pVertexBuffer[2] =
            TexturedVertex{NovelRT::Maths::GeoVector3F(-1, -1, 0), NovelRT::Maths::GeoVector2F(0.0f, 1.0f)};

        vertexStagingBuffer->UnmapAndWrite(vertexBufferRegion);

        uint32_t textureWidth = 256;
        uint32_t textureHeight = 256;
        uint32_t texturePixels = textureWidth * textureHeight;
        uint32_t cellWidth = textureWidth / 8;
        uint32_t cellHeight = textureHeight / 8;

        auto texture2D =
            GetPtrNonsenseStruct().memoryAllocator->CreateTexture2DRepeatGpuWriteOnly(textureWidth, textureHeight);
        auto texture2DRegion = texture2D->Allocate(texture2D->GetSize(), 4);
        auto textureStagingBufferRegion = textureStagingBuffer->Allocate(texture2D->GetSize(), 4);
        auto pTextureData = textureStagingBuffer->template Map<uint32_t>(textureStagingBufferRegion);

        for (uint32_t n = 0; n < texturePixels; n++)
        {
            auto x = n % textureWidth;
            auto y = n / textureWidth;

            pTextureData[n] = (x / cellWidth % 2) == (y / cellHeight % 2) ? 0xFF000000 : 0xFFFFFFFF;
        }

        textureStagingBuffer->UnmapAndWrite(textureStagingBufferRegion);
        {
            gfxContext->BeginFrame();
            auto cmdList = gfxContext->CreateCmdList();

            cmdList->Begin();
            cmdList->CmdCopy(vertexBufferRegion, stagingBufferRegion);

            cmdList->CmdBeginTexturePipelineBarrierLegacyVersion(texture2D);
            cmdList->CmdCopy(texture2D, textureStagingBufferRegion);
            cmdList->CmdEndTexturePipelineBarrierLegacyVersion(texture2D);
            cmdList->End();

            gfxContext->EndFrame();
            GetPtrNonsenseStruct().gfxDevice->QueueSubmit(cmdList);
            GetPtrNonsenseStruct().gfxDevice->WaitForIdle();
        }

        _renderingData.RenderPipeline = pipeline;
        _renderingData.TextureRegion = texture2DRegion;
        _renderingData.VertexBufferRegion = vertexBufferRegion;
        _renderingData.VertexBuffer = vertexBuffer;
        _renderingData.GraphicsContext = gfxContext;

        _inputResourceRegions = {_renderingData.TextureRegion};
    }

    void Update(Timestamp /*delta*/, Catalogue catalogue) final
    {
        float surfaceWidth = GetPtrNonsenseStruct().sampleSurface->GetWidth();
        float surfaceHeight = GetPtrNonsenseStruct().sampleSurface->GetHeight();

        auto context = _renderingData.GraphicsContext;
        context->BeginFrame();
        auto currentCmdList = context->CreateCmdList(
            std::optional<SecondaryCmdListInfo<TBackend>>({GetPtrNonsenseStruct().trianglePass, 0}));

        currentCmdList->Begin();

        NovelRT::Graphics::ClearValue colourDataStruct{};
        colourDataStruct.colour = NovelRT::Graphics::RGBAColour(0, 0, 255, 255);
        colourDataStruct.depth = 0;
        colourDataStruct.stencil = 0;

        std::vector<ClearValue> colourData{colourDataStruct};

        ViewportInfo viewportInfoStruct{};
        viewportInfoStruct.x = 0;
        viewportInfoStruct.y = surfaceHeight;
        viewportInfoStruct.width = surfaceWidth;
        viewportInfoStruct.height = -surfaceHeight;
        viewportInfoStruct.minDepth = 0.0f;
        viewportInfoStruct.maxDepth = 1.0f;

        currentCmdList->CmdSetViewport(viewportInfoStruct);
        currentCmdList->CmdSetScissor(NovelRT::Maths::GeoVector2F::Zero(),
                                      NovelRT::Maths::GeoVector2F(surfaceWidth, surfaceHeight));
        currentCmdList->CmdBindPipeline(_renderingData.RenderPipeline);

        std::array<std::reference_wrapper<const std::shared_ptr<GraphicsBuffer<TBackend>>>, 1> buffers{
            std::cref(_renderingData.VertexBuffer)};
        std::array<size_t, 1> offsets{_renderingData.VertexBufferRegion->GetOffset()};

        currentCmdList->CmdBindVertexBuffers(0, 1, buffers, offsets);

        auto descriptorSetData = _renderingData.RenderPipeline->CreateDescriptorSet();
        descriptorSetData->AddMemoryRegionsToInputs(_inputResourceRegions);
        descriptorSetData->UpdateDescriptorSetData();

        std::array<std::reference_wrapper<const std::shared_ptr<GraphicsDescriptorSet<TBackend>>>, 1> descriptorData{
            std::cref(descriptorSetData)};
        currentCmdList->CmdBindDescriptorSets(descriptorData);

        currentCmdList->CmdDraw(
            static_cast<uint32_t>(_renderingData.VertexBufferRegion->GetSize() / sizeof(TexturedVertex)), 1, 0, 0);

        currentCmdList->End();

        context->EndFrame();

        auto [renderPassView, cmdListView, graphComponentView] =
            catalogue.GetComponentViews<RenderPass<TBackend>, BuiltCommandList<TBackend>, EntityGraphComponent>();

        if (!_cmdListEntity.has_value())
        {
            _cmdListEntity = catalogue.CreateEntity();
            auto cmdListEntityLocal = _cmdListEntity.value();

            EntityGraphComponent graphComp{};
            graphComp.parent = std::numeric_limits<EntityId>::max();
            graphComp.childrenStartNode = std::numeric_limits<EntityId>::max();
            graphComponentView.AddComponent(cmdListEntityLocal, graphComp);

            RenderPass<TBackend> passComponent{};
            passComponent.descriptorSet = new std::shared_ptr<GraphicsDescriptorSet<TBackend>>(descriptorSetData);
            passComponent.renderPassIndex =
                GetPtrNonsenseStruct().triangleRenderPassId; // TODO: There's no other way to pass this through yet. I
                                                             // am just trying to get this working.
            renderPassView.AddComponent(cmdListEntityLocal, passComponent);

            BuiltCommandList<TBackend> cmdListComp{};
            cmdListComp.commandList = new std::shared_ptr<GraphicsCmdList<TBackend>>(currentCmdList);
            cmdListView.AddComponent(cmdListEntityLocal, cmdListComp);
        }
        else
        {
            RenderPass<TBackend> passComponent{};
            passComponent.descriptorSet = new std::shared_ptr<GraphicsDescriptorSet<TBackend>>(descriptorSetData);
            passComponent.renderPassIndex = GetPtrNonsenseStruct().triangleRenderPassId;
            renderPassView.PushComponentUpdateInstruction(_cmdListEntity.value(), passComponent);

            BuiltCommandList<TBackend> cmdListComp{};
            cmdListComp.commandList = new std::shared_ptr<GraphicsCmdList<TBackend>>(currentCmdList);
            cmdListView.PushComponentUpdateInstruction(_cmdListEntity.value(), cmdListComp);
        }
    }
};

int main()
{
    auto wndProvider = std::make_shared<WindowProvider<Glfw::GlfwWindowingBackend>>(
        NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(400, 400));

    auto gfxProvider = wndProvider->CreateGraphicsProvider<VulkanGraphicsBackend>(true);
    auto gfxSurfaceContext = std::make_shared<GraphicsSurfaceContext<VulkanGraphicsBackend>>(wndProvider, gfxProvider);
    GetPtrNonsenseStruct().sampleSurface = gfxSurfaceContext->GetSurface();

    VulkanGraphicsAdapterSelector selector{};
    auto gfxAdapter = selector.GetDefaultRecommendedAdapter(gfxProvider, gfxSurfaceContext);
    GetPtrNonsenseStruct().gfxDevice = gfxAdapter->CreateDevice(gfxSurfaceContext);
    GetPtrNonsenseStruct().memoryAllocator =
        std::make_shared<GraphicsMemoryAllocator<VulkanGraphicsBackend>>(GetPtrNonsenseStruct().gfxDevice, gfxProvider);

    SystemSchedulerBuilder builder{};
    AddDefaults(builder);
    AddGraphics<Vulkan::VulkanGraphicsBackend>(builder)
        .WithGraphicsDevice(GetPtrNonsenseStruct().gfxDevice)
        .WithSurfaceContext(gfxSurfaceContext)
        .ConfigureRenderPasses(
            [](RenderPassManager<VulkanGraphicsBackend>& renderPassManager)
            {
                GraphicsRenderPassDescription passDesc{};
                GraphicsAttachmentDescription attachmentDesc{};

                auto vulkanFormat = GetPtrNonsenseStruct().gfxDevice->GetSwapchain()->GetVulkanFormat();
                if (vulkanFormat == VK_FORMAT_R8G8B8A8_UNORM)
                {
                    attachmentDesc.texelFormat = TexelFormat::R8G8B8A8_UNORM;
                }
                else if (vulkanFormat == VK_FORMAT_B8G8R8A8_UNORM)
                {
                    attachmentDesc.texelFormat = TexelFormat::B8G8R8A8_UNORM;
                }
                else
                {
                    throw NovelRT::Exceptions::InitialisationFailureException("How did you get here?");
                }

                attachmentDesc.loadOp = LoadOp::Clear;
                attachmentDesc.storeOp = StoreOp::Store;
                attachmentDesc.initialLayout = ImageLayout::Undefined;
                attachmentDesc.finalLayout = ImageLayout::Present;

                passDesc.attachmentDescriptions.push_back(attachmentDesc);
                GetPtrNonsenseStruct().trianglePass = GetPtrNonsenseStruct().gfxDevice->CreateRenderPass(passDesc);
                auto passId = renderPassManager.RegisterRenderPass(GetPtrNonsenseStruct().trianglePass);
                GetPtrNonsenseStruct().triangleRenderPassId = passId;
            })
        .WithDefaultOrchestrator();

    auto triangleSystem = std::make_shared<SampleTriangleRenderingSystem<VulkanGraphicsBackend>>();
    builder.Configure([triangleSystem](SystemScheduler& scheduler) { scheduler.RegisterSystem(triangleSystem); });

    SystemScheduler scheduler = builder.Build();
    StepTimer timer{};
    Event<Timestamp::duration> TimerCallback{};

    TimerCallback += [&timer, &scheduler](auto /* delta */) { scheduler.ExecuteIteration(timer.getTotalTime()); };

    while (!wndProvider->ShouldClose())
    {
        wndProvider->ProcessAllMessages();
        timer.Tick(TimerCallback);
    }

    return 0;
}
