// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/FileNotFoundException.hpp>

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
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>

#include <NovelRT/Input/Glfw/GlfwInputProvider.hpp>

#include <NovelRT/UI/ImGui/ImGuiUIProvider.hpp>

#include <NovelRT/Maths/GeoVector2F.hpp>
#include <NovelRT/Maths/GeoVector3F.hpp>
#include <NovelRT/Timing/StepTimer.hpp>
#include <NovelRT/Utilities/Paths.hpp>

#include <NovelRT/Windowing/Glfw/GlfwWindowProvider.hpp>

#include <fstream>
#include <memory>

#include <imgui.h>

using namespace NovelRT::Graphics::Vulkan;
using namespace NovelRT::Graphics;

using namespace NovelRT::Input::Glfw;
using namespace NovelRT::Input;

using namespace NovelRT::Windowing::Glfw;
using namespace NovelRT::Windowing;

using namespace NovelRT::UI::ImGui;

std::vector<GraphicsBuffer<VulkanGraphicsBackend>> shittyBuffer{};
NovelRT::Utilities::Event<NovelRT::Timing::Timestamp::duration> DummyUpdateStuff;

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
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
    file.close();

    return buffer;
}

struct TexturedVertex
{
    NovelRT::Maths::GeoVector3F Position;
    NovelRT::Maths::GeoVector2F UV;
};

template <typename TGraphicsBackend>
std::shared_ptr<GraphicsDescriptorSet<TGraphicsBackend>> regularDrawCmds(
    std::shared_ptr<GraphicsContext<TGraphicsBackend>> context,
    std::shared_ptr<GraphicsCmdList<TGraphicsBackend>> currentCmdList,
    std::shared_ptr<GraphicsRenderPass<TGraphicsBackend>>,
    float surfaceWidth,
    float surfaceHeight,
    std::shared_ptr<GraphicsPipelineSignature<TGraphicsBackend>> pipelineSignature,
    std::shared_ptr<GraphicsPipeline<TGraphicsBackend>> pipeline,
    std::shared_ptr<GraphicsBuffer<TGraphicsBackend>> vertexBuffer,
    std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TGraphicsBackend>> vertexBufferRegion,
    std::vector<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, TGraphicsBackend>>>
        inputResourceRegions)
{

    currentCmdList->CmdBindPipeline(pipeline.get());
    currentCmdList->CmdSetScissor(NovelRT::Maths::GeoVector2F::Zero(),
                                  NovelRT::Maths::GeoVector2F(surfaceWidth, surfaceHeight));

    std::array<const GraphicsBuffer<TGraphicsBackend>*, 1> buffers{vertexBuffer.get()};
    std::array<size_t, 1> offsets{vertexBufferRegion->GetOffset()};

    currentCmdList->CmdBindVertexBuffers(0, 1, buffers, offsets);

    auto descriptorSetData = pipeline->CreateDescriptorSet();
    descriptorSetData->AddMemoryRegionsToInputs(inputResourceRegions);
    descriptorSetData->UpdateDescriptorSetData();

    std::array<const GraphicsDescriptorSet<TGraphicsBackend>*, 1> descriptorData{descriptorSetData.get()};
    currentCmdList->CmdBindDescriptorSets(descriptorData);
    context->RegisterDescriptorSetForFrame(pipelineSignature, descriptorSetData);

    currentCmdList->CmdDraw(vertexBufferRegion->GetSize() / static_cast<uint32_t>(sizeof(TexturedVertex)), 1, 0, 0);

    return descriptorSetData;
}

int main()
{
    // TODO: EngineConfig was here
    //NovelRT::EngineConfig::EnableDebugOutputFromEngineInternals() = true;
    //NovelRT::EngineConfig::MinimumInternalLoggingLevel() = NovelRT::LogLevel::Debug;

    NovelRT::LoggingService logger = NovelRT::LoggingService();
    logger.setLogLevel(NovelRT::LogLevel::Info);

    auto wndProvider = std::make_shared<WindowProvider<NovelRT::Windowing::Glfw::GlfwWindowingBackend>>(
        NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(1024, 768));

    auto inputProvider = std::make_shared<InputProvider<NovelRT::Input::Glfw::GlfwInputBackend>>(wndProvider);

    auto gfxProvider = wndProvider->CreateGraphicsProvider<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>();
    auto gfxSurfaceContext = std::make_shared<GraphicsSurfaceContext<VulkanGraphicsBackend>>(wndProvider, gfxProvider);

    auto clickAction = inputProvider->AddInputAction("LeftClick", "LeftMouseButton");

    VulkanGraphicsAdapterSelector selector{};
    auto gfxAdapter = selector.GetDefaultRecommendedAdapter(gfxProvider.get(), gfxSurfaceContext.get());
    auto gfxDevice = gfxAdapter->CreateDevice(gfxSurfaceContext, 2);

    std::shared_ptr<GraphicsContext<VulkanGraphicsBackend>> gfxContext = gfxDevice->GetCurrentContext();
    auto memoryAllocator = std::make_shared<GraphicsMemoryAllocator<VulkanGraphicsBackend>>(gfxDevice, gfxProvider);

    /// IMGUI
    auto uiProvider = std::make_shared<ImGuiUIProvider<
        NovelRT::Graphics::Vulkan::VulkanGraphicsBackend,
        NovelRT::Input::Glfw::GlfwInputBackend,
        NovelRT::Windowing::Glfw::GlfwWindowingBackend>>(wndProvider, inputProvider, gfxDevice, memoryAllocator, true);
    /// IMGUI

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

    std::shared_ptr<GraphicsCmdList<VulkanGraphicsBackend>> cmdList = gfxContext->BeginFrame();

    std::vector<GraphicsPipelineInputElement> elements{
        GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector3F), GraphicsPipelineInputElementKind::Position,
                                     12),
        GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F),
                                     GraphicsPipelineInputElementKind::TextureCoordinate, 8)};

    std::vector<GraphicsPipelineInput> inputs{GraphicsPipelineInput(elements)};
    std::vector<GraphicsPipelineResource> resources{
        GraphicsPipelineResource(GraphicsPipelineResourceKind::Texture, ShaderProgramVisibility::Pixel)};

    std::vector<GraphicsPushConstantRange> dummyData{};
    auto signature =
        gfxDevice->CreatePipelineSignature(GraphicsPipelineBlendFactor::SrcAlpha,
                                           GraphicsPipelineBlendFactor::OneMinusSrcAlpha, inputs, resources, dummyData);
    auto vertShaderProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Vertex, vertShaderData);
    auto pixelShaderProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Pixel, pixelShaderData);
    auto pipeline = gfxDevice->CreatePipeline(signature, vertShaderProg, pixelShaderProg);

    auto vertexBufferRegion = vertexBuffer->Allocate(sizeof(TexturedVertex) * 3, 16);
    auto stagingBufferRegion = vertexStagingBuffer->Allocate(sizeof(TexturedVertex) * 3, 16);

    auto pVertexBuffer = vertexStagingBuffer->Map<TexturedVertex>(vertexBufferRegion.get());

    pVertexBuffer[0] = TexturedVertex{NovelRT::Maths::GeoVector3F(0, 1, 0), NovelRT::Maths::GeoVector2F(0.5f, 0.0f)};
    pVertexBuffer[1] = TexturedVertex{NovelRT::Maths::GeoVector3F(1, -1, 0), NovelRT::Maths::GeoVector2F(1.0f, 1.0f)};
    pVertexBuffer[2] = TexturedVertex{NovelRT::Maths::GeoVector3F(-1, -1, 0), NovelRT::Maths::GeoVector2F(0.0f, 1.0f)};

    vertexStagingBuffer->UnmapAndWrite(vertexBufferRegion.get());
    cmdList->CmdCopy(vertexBufferRegion.get(), stagingBufferRegion.get());

    uint32_t textureWidth = 256;
    uint32_t textureHeight = 256;
    uint32_t texturePixels = textureWidth * textureHeight;
    uint32_t cellWidth = textureWidth / 8;
    uint32_t cellHeight = textureHeight / 8;

    auto texture2D = memoryAllocator->CreateTexture2DRepeatGpuWriteOnly(textureWidth, textureHeight);
    auto texture2DRegion = texture2D->Allocate(texture2D->GetSize(), 4);
    auto textureStagingBufferRegion = textureStagingBuffer->Allocate(texture2D->GetSize(), 4);
    auto pTextureData = textureStagingBuffer->Map<uint32_t>(textureStagingBufferRegion.get());

    for (uint32_t n = 0; n < texturePixels; n++)
    {
        auto x = n % textureWidth;
        auto y = n / textureWidth;

        pTextureData[n] = (x / cellWidth % 2) == (y / cellHeight % 2) ? 0xFF000000 : 0xFFFFFFFF;
    }

    textureStagingBuffer->UnmapAndWrite(textureStagingBufferRegion.get());

    std::vector<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, VulkanGraphicsBackend>>>
        inputResourceRegions{texture2DRegion};

    cmdList->CmdBeginTexturePipelineBarrierLegacyVersion(texture2D.get());
    cmdList->CmdCopy(texture2D.get(), textureStagingBufferRegion.get());
    cmdList->CmdEndTexturePipelineBarrierLegacyVersion(texture2D.get());

    gfxContext->EndFrame();
    gfxDevice->Signal(gfxContext.get());
    gfxDevice->WaitForIdle();
    gfxContext->GetFence()->Reset();

    /// imgui
    uint32_t strIndex = 0;
    std::vector<std::string> arr{"Hello!", "I'm going to get milk, now...", "...", "...", "*30 years later*", "..."};

    auto surface = gfxDevice->GetSurface();
    bool clicked = false;
    NovelRT::Timing::StepTimer timer(144, 1.0f / 144.0f);
    DummyUpdateStuff += [&](auto delta) {
        wndProvider->ProcessAllMessages();
        inputProvider->Update(delta);

        if (wndProvider->IsVisible())
        {
            auto cl = inputProvider->GetCurrentChangeLog(clickAction.actionName);

            if (cl.GetCurrentState() == KeyState::KeyDown && !clicked)
            {
                strIndex++;
                clicked = true;
            }
            else if (cl.GetCurrentState() == KeyState::KeyUp && clicked)
            {
                clicked = false;
            }

            // ImGuiiiiiiiiiiiiiiiiiiiiii
            uiProvider->BeginFrame(NovelRT::Timing::GetSeconds<float>(delta));

            ImGui::SetNextWindowSize(ImVec2(612, 200));
            ImGui::SetNextWindowPos(ImVec2(100, 500));
            ImGui::Begin("Test", NULL,
                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

            if (strIndex < arr.size())
            {
                ImGui::Text("%s", arr.at(strIndex).c_str());
            }

            ImGui::End();
            uiProvider->EndFrame();

            auto surface = gfxDevice->GetSurface();
            auto context = gfxDevice->GetCurrentContext();
            auto currentCmdList = context->BeginFrame();

            float surfaceWidth = surface->GetWidth();
            float surfaceHeight = surface->GetHeight();

            auto renderPass = gfxDevice->GetRenderPass();

            uiProvider->UploadToGPU(currentCmdList);

            NovelRT::Graphics::ClearValue colourDataStruct{};
            colourDataStruct.colour = NovelRT::Graphics::RGBAColour(0, 0, 255, 255);
            colourDataStruct.depth = 0;
            colourDataStruct.stencil = 0;

            std::vector<ClearValue> colourData{colourDataStruct};
            currentCmdList->CmdBeginRenderPass(renderPass.get(), colourData);

            ViewportInfo viewportInfoStruct{};
            viewportInfoStruct.x = 0;
            viewportInfoStruct.y = surfaceHeight;
            viewportInfoStruct.width = surfaceWidth;
            viewportInfoStruct.height = -surfaceHeight;
            viewportInfoStruct.minDepth = 0.0f;
            viewportInfoStruct.maxDepth = 1.0f;

            currentCmdList->CmdSetViewport(viewportInfoStruct);

            auto descriptorSetData = regularDrawCmds(gfxContext, currentCmdList, renderPass, surfaceWidth, surfaceHeight, signature, pipeline,
                            vertexBuffer, vertexBufferRegion, inputResourceRegions);

            uiProvider->Draw(currentCmdList);

            currentCmdList->CmdEndRenderPass();
            context->EndFrame();
            context->RegisterDescriptorSetForFrame(std::weak_ptr(signature), descriptorSetData);
            gfxDevice->PresentFrame();
        }
    };

    while (!wndProvider->ShouldClose())
    {
        timer.Tick(DummyUpdateStuff);
    }

    return 0;
}
