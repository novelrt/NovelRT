// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/FileNotFoundException.hpp>
#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Graphics/GraphicsRenderPassDescription.hpp>

#include <NovelRT/Graphics/GraphicsAdapter.hpp>
#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/GraphicsContext.hpp>
#include <NovelRT/Graphics/GraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsFence.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/GraphicsPipeline.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInput.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElement.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElementKind.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResource.hpp>
#include <NovelRT/Graphics/GraphicsRenderPass.hpp>
#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapterSelector.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderTarget.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchainImage.hpp>

#include <NovelRT/Windowing/Glfw/GlfwWindowProvider.hpp>

#include <NovelRT/Maths/GeoVector2F.hpp>
#include <NovelRT/Maths/GeoVector3F.hpp>
#include <NovelRT/Utilities/Paths.hpp>

#include <filesystem>
#include <fstream>
#include <memory>

using namespace NovelRT::Logging;
using namespace NovelRT::Windowing::Glfw;
using namespace NovelRT::Windowing;
using namespace NovelRT::Graphics::Vulkan;
using namespace NovelRT::Graphics;

std::vector<uint8_t> LoadSpv(std::filesystem::path relativeTarget)
{
    std::filesystem::path finalPath =
        NovelRT::Utilities::GetExecutableDirPath() / "Resources" / "Shaders" / relativeTarget;
    std::ifstream file(finalPath.string(), std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw NovelRT::Exceptions::FileNotFoundException(finalPath.string());
    }

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<uint8_t> buffer(fileSize);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(buffer.data()), std::streamsize(fileSize));
    file.close();

    return buffer;
}

struct TexturedVertex
{
    NovelRT::Maths::GeoVector3F Position;
    NovelRT::Maths::GeoVector2F UV;
};

template<typename TBackend>
struct PerFrameResources
{
    uint64_t frameNumber;

    std::shared_ptr<NovelRT::Graphics::GraphicsRenderTarget<TBackend>> renderTarget{};
    std::shared_ptr<NovelRT::Graphics::GraphicsDescriptorSet<TBackend>> descriptorSet{};
    std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TBackend>> commandList{};
};

template<typename TBackend>
struct RenderingData
{
    std::shared_ptr<GraphicsBuffer<TBackend>> VertexBuffer;
    std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>> VertexBufferRegion;
    std::shared_ptr<GraphicsPipeline<TBackend>> RenderPipeline;
    std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>> TextureRegion;
    std::shared_ptr<GraphicsRenderPass<TBackend>> RenderPass;
    std::shared_ptr<GraphicsContext<TBackend>> GraphicsContext;

    std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TBackend>> DeletionSemaphore;
    std::deque<PerFrameResources<TBackend>> FrameResources;
    uint64_t RenderedFrames{0};
};

template<typename TBackend>
RenderingData<TBackend> SetupTriangleSample(std::shared_ptr<GraphicsDevice<TBackend>>& gfxDevice,
                                            std::shared_ptr<GraphicsMemoryAllocator<TBackend>>& memoryAllocator)
{
    GraphicsBufferCreateInfo bufferCreateInfo{};
    bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::Write;
    bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Read;
    bufferCreateInfo.size = 64 * 1024;

    auto vertexStagingBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);

    bufferCreateInfo.size = 64 * 1024 * 4; // need this to be a different size but rest of the values are unchanged.

    auto textureStagingBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);

    bufferCreateInfo.bufferKind = GraphicsBufferKind::Vertex;
    bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::None;
    bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Write;
    bufferCreateInfo.size = 64 * 1024;

    auto vertexBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);

    auto vertShaderData = LoadSpv("vulkanrendervert.spv");
    auto pixelShaderData = LoadSpv("vulkanrenderfrag.spv");

    std::vector<GraphicsPipelineInputElement> elements{
        GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector3F), GraphicsPipelineInputElementKind::Position,
                                     12),
        GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F),
                                     GraphicsPipelineInputElementKind::TextureCoordinate, 8)};

    std::vector<GraphicsPipelineInput> inputs{GraphicsPipelineInput(elements)};
    std::vector<GraphicsPipelineResource> resources{
        GraphicsPipelineResource(GraphicsPipelineResourceKind::Texture, ShaderProgramVisibility::Pixel)};

    std::vector<GraphicsPushConstantRange> dummyData{};
    auto signature = gfxDevice->CreatePipelineSignature(
        GraphicsPipelineBlendFactor::SrcAlpha, GraphicsPipelineBlendFactor::OneMinusSrcAlpha, inputs, resources,
        NovelRT::Utilities::Span<GraphicsPushConstantRange>(dummyData));
    auto vertShaderProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Vertex, vertShaderData);
    auto pixelShaderProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Pixel, pixelShaderData);

    // create the render pass and pipeline
    GraphicsRenderPassDescription passDesc{};
    GraphicsAttachmentDescription attachmentDesc{};

    attachmentDesc.texelFormat = gfxDevice->GetSwapchain()->GetFormat();

    if (attachmentDesc.texelFormat == TexelFormat::UnknownOrUndefined)
    {
        throw NovelRT::Exceptions::InitialisationFailureException("How did you get here?");
    }

    attachmentDesc.loadOp = LoadOp::Clear;
    attachmentDesc.storeOp = StoreOp::Store;
    attachmentDesc.initialLayout = ImageLayout::Undefined;
    attachmentDesc.finalLayout = ImageLayout::Present;

    passDesc.attachmentDescriptions.push_back(attachmentDesc);
    auto pass = gfxDevice->CreateRenderPass(passDesc);
    auto pipeline = gfxDevice->CreatePipeline(signature, vertShaderProg, pixelShaderProg, pass);
    auto gfxContext = gfxDevice->CreateGraphicsContext();

    auto vertexBufferRegion = vertexBuffer->Allocate(sizeof(TexturedVertex) * 3, 16);
    auto stagingBufferRegion = vertexStagingBuffer->Allocate(sizeof(TexturedVertex) * 3, 16);

    auto pVertexBuffer = vertexStagingBuffer->template Map<TexturedVertex>(vertexBufferRegion);

    pVertexBuffer[0] = TexturedVertex{NovelRT::Maths::GeoVector3F(0, 1, 0), NovelRT::Maths::GeoVector2F(0.5f, 0.0f)};
    pVertexBuffer[1] = TexturedVertex{NovelRT::Maths::GeoVector3F(1, -1, 0), NovelRT::Maths::GeoVector2F(1.0f, 1.0f)};
    pVertexBuffer[2] = TexturedVertex{NovelRT::Maths::GeoVector3F(-1, -1, 0), NovelRT::Maths::GeoVector2F(0.0f, 1.0f)};

    vertexStagingBuffer->UnmapAndWrite(vertexBufferRegion);

    uint32_t textureWidth = 256;
    uint32_t textureHeight = 256;
    uint32_t texturePixels = textureWidth * textureHeight;
    uint32_t cellWidth = textureWidth / 8;
    uint32_t cellHeight = textureHeight / 8;

    auto texture2D = memoryAllocator->CreateTexture2DRepeatGpuWriteOnly(textureWidth, textureHeight);
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
        // TODO: This is technically legacy but I can't be bothered cleaning it up even though
        // we are doing extra work for transfer queue usage, for no reason. - Matt J.
        gfxContext->BeginFrame();
        auto cmdList = gfxContext->CreateCmdList();

        cmdList->Begin();
        cmdList->CmdCopy(vertexBufferRegion, stagingBufferRegion);

        cmdList->CmdBeginTexturePipelineBarrierLegacyVersion(texture2D);
        cmdList->CmdCopy(texture2D, textureStagingBufferRegion);
        cmdList->CmdEndTexturePipelineBarrierLegacyVersion(texture2D);
        cmdList->End();

        gfxContext->EndFrame();
        std::vector<std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TBackend>>> lists{cmdList};
        gfxDevice->QueueSubmit(lists);
        gfxDevice->WaitForIdle();
    }

    RenderingData<TBackend> returnStruct{};
    returnStruct.RenderPipeline = pipeline;
    returnStruct.TextureRegion = texture2DRegion;
    returnStruct.VertexBufferRegion = vertexBufferRegion;
    returnStruct.VertexBuffer = vertexBuffer;
    returnStruct.RenderPass = pass;
    returnStruct.GraphicsContext = gfxContext;
    returnStruct.DeletionSemaphore = gfxDevice->CreateSemaphore(0);

    return returnStruct;
}

template<typename TBackend>
void Render(RenderingData<TBackend>& renderingData,
            std::shared_ptr<GraphicsDevice<TBackend>>& gfxDevice,
            std::vector<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>>> inputResourceRegions)
{
    auto lastRenderedFrame = renderingData.DeletionSemaphore->GetValue();
    if (lastRenderedFrame > 0)
        lastRenderedFrame -= 1;

    renderingData.FrameResources.erase(std::remove_if(renderingData.FrameResources.begin(),
                                                      renderingData.FrameResources.end(), [lastRenderedFrame](auto& it)
                                                      { return it.frameNumber < lastRenderedFrame; }),
                                       renderingData.FrameResources.end());

    auto surface = gfxDevice->GetSurface();
    float surfaceWidth = surface->GetWidth();
    float surfaceHeight = surface->GetHeight();
    auto swapchainImage = gfxDevice->BeginFrame();
    std::vector<VkImageView> imageViewData{swapchainImage->GetVulkanImageView()};
    auto target = std::make_shared<GraphicsRenderTarget<TBackend>>(gfxDevice, imageViewData, renderingData.RenderPass,
                                                                   static_cast<uint32_t>(surfaceWidth),
                                                                   static_cast<uint32_t>(surfaceHeight));
    {
        auto context = renderingData.GraphicsContext;
        context->BeginFrame();
        auto currentCmdList = context->CreateCmdList();

        currentCmdList->Begin();
        // auto renderPass = context->CreateRenderPass();

        auto& frameResources =
            renderingData.FrameResources.emplace_back(PerFrameResources<TBackend>{++renderingData.RenderedFrames});

        NovelRT::Graphics::ClearValue colourDataStruct{};
        colourDataStruct.colour = NovelRT::Graphics::RGBAColour(0, 0, 255, 255);
        colourDataStruct.depth = 0;
        colourDataStruct.stencil = 0;

        std::vector<ClearValue> colourData{colourDataStruct};
        currentCmdList->CmdBeginRenderPass(renderingData.RenderPass, target, colourData);

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
        currentCmdList->CmdBindPipeline(renderingData.RenderPipeline);

        std::array<std::reference_wrapper<const std::shared_ptr<GraphicsBuffer<TBackend>>>, 1> buffers{
            std::cref(renderingData.VertexBuffer)};
        std::array<size_t, 1> offsets{renderingData.VertexBufferRegion->GetOffset()};

        currentCmdList->CmdBindVertexBuffers(0, 1, buffers, offsets);

        auto descriptorSetData = renderingData.RenderPipeline->CreateDescriptorSet();
        descriptorSetData->AddMemoryRegionsToInputs(inputResourceRegions);
        descriptorSetData->UpdateDescriptorSetData();

        currentCmdList->CmdBindDescriptorSet(descriptorSetData);

        currentCmdList->CmdDraw(
            static_cast<uint32_t>(renderingData.VertexBufferRegion->GetSize() / sizeof(TexturedVertex)), 1, 0, 0);

        currentCmdList->CmdEndRenderPass();

        currentCmdList->End();

        frameResources.descriptorSet = descriptorSetData;
        frameResources.renderTarget = target;
        frameResources.commandList = currentCmdList;

        context->EndFrame();
        swapchainImage->QueueSubmit(currentCmdList, {renderingData.DeletionSemaphore, frameResources.frameNumber});
    }

    gfxDevice->EndFrame();
}

int main()
{
    // TODO: EngineConfig was here
    // NovelRT::EngineConfig::EnableDebugOutputFromEngineInternals() = true;
    // NovelRT::EngineConfig::MinimumInternalLoggingLevel() = NovelRT::LogLevel::Warn;

    LoggingService logger{};
    logger.setLogLevel(LogLevel::Info);

    auto wndProvider = std::make_shared<WindowProvider<Glfw::GlfwWindowingBackend>>();
    wndProvider->CreateWindow(NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(400, 400));

    auto gfxProvider = wndProvider->CreateGraphicsProvider<VulkanGraphicsBackend>(false);
    auto gfxSurfaceContext = std::make_shared<GraphicsSurfaceContext<VulkanGraphicsBackend>>(wndProvider, gfxProvider);

    VulkanGraphicsAdapterSelector selector{};
    auto gfxAdapter = selector.GetDefaultRecommendedAdapter(gfxProvider, gfxSurfaceContext);
    std::shared_ptr<GraphicsDevice<VulkanGraphicsBackend>> gfxDevice = gfxAdapter->CreateDevice(gfxSurfaceContext);
    auto memoryAllocator = std::make_shared<GraphicsMemoryAllocator<VulkanGraphicsBackend>>(gfxDevice, gfxProvider);

    auto renderingData = SetupTriangleSample(gfxDevice, memoryAllocator);

    std::vector<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, VulkanGraphicsBackend>>>
        inputResourceRegions{renderingData.TextureRegion};

    while (!wndProvider->ShouldClose())
    {
        wndProvider->ProcessAllMessages();
        if (wndProvider->IsVisible())
        {
            Render(renderingData, gfxDevice, inputResourceRegions);
        }
    }

    gfxDevice->WaitForIdle();
    return 0;
}
