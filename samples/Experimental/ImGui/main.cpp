// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <NovelRT/NovelRT.h>

#include <NovelRT/Graphics/GraphicsAdapter.hpp>
#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/GraphicsContext.hpp>
#include <NovelRT/Graphics/GraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/GraphicsPipeline.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInput.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElement.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElementKind.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResource.hpp>
#include <NovelRT/Graphics/GraphicsRenderPass.hpp>
#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapterSelector.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsCmdList.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipeline.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderPass.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>

#include <NovelRT/input/Glfw/GlfwInputDevice.hpp>
#include <NovelRT/UI/ImGui/ImGuiUIProvider.hpp>

#include <NovelRT/Windowing/Glfw/Windowing.Glfw.h>
#include <NovelRT/Windowing/Windowing.h>
#include <memory>

#include <imgui.h>

using namespace NovelRT::Windowing::Glfw;
using namespace NovelRT::Windowing;
using namespace NovelRT::Graphics::Vulkan;
using namespace NovelRT::Graphics;
using namespace NovelRT::Input;
using namespace NovelRT::Input::Glfw;
using namespace NovelRT::UI::DearImGui;

std::vector<GraphicsBuffer<VulkanGraphicsBackend>> shittyBuffer{};
NovelRT::Utilities::Event<NovelRT::Timing::Timestamp> DummyUpdateStuff;

std::vector<uint8_t> LoadSpv(std::filesystem::path relativeTarget)
{
    std::filesystem::path finalPath =
        NovelRT::Utilities::Misc::getExecutableDirPath() / "Resources" / "Shaders" / relativeTarget;
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

void regularDrawCmds(
    std::shared_ptr<GraphicsContext<VulkanGraphicsBackend>> context,
    std::shared_ptr<GraphicsCmdList<VulkanGraphicsBackend>> currentCmdList,
    std::shared_ptr<GraphicsRenderPass<VulkanGraphicsBackend>> renderPass,
    float surfaceWidth,
    float surfaceHeight,
    std::shared_ptr<GraphicsPipelineSignature<VulkanGraphicsBackend>> pipelineSignature,
    std::shared_ptr<GraphicsPipeline<VulkanGraphicsBackend>> pipeline,
    std::shared_ptr<GraphicsBuffer<VulkanGraphicsBackend>> vertexBuffer,
    std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, VulkanGraphicsBackend>> vertexBufferRegion,
    std::vector<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, VulkanGraphicsBackend>>>
        inputResourceRegions)
{

    currentCmdList->CmdBindPipeline(pipeline);
    currentCmdList->CmdSetScissor(NovelRT::Maths::GeoVector2F::Zero(),
                                  NovelRT::Maths::GeoVector2F(surfaceWidth, surfaceHeight));

    std::array<std::shared_ptr<GraphicsBuffer<VulkanGraphicsBackend>>, 1> buffers{vertexBuffer};
    std::array<size_t, 1> offsets{vertexBufferRegion->GetOffset()};

    currentCmdList->CmdBindVertexBuffers(0, 1, buffers, offsets);

    auto descriptorSetData = pipeline->CreateDescriptorSet();
    descriptorSetData->AddMemoryRegionsToInputs(inputResourceRegions);
    descriptorSetData->UpdateDescriptorSetData();

    std::array<std::shared_ptr<GraphicsDescriptorSet<VulkanGraphicsBackend>>, 1> descriptorData{descriptorSetData};
    currentCmdList->CmdBindDescriptorSets(descriptorData);
    context->RegisterDescriptorSetForFrame(pipelineSignature, descriptorSetData);

    currentCmdList->CmdDraw(vertexBufferRegion->GetSize() / sizeof(TexturedVertex), 1, 0, 0);
}

int main()
{
    NovelRT::EngineConfig::EnableDebugOutputFromEngineInternals() = true;
    NovelRT::EngineConfig::MinimumInternalLoggingLevel() = NovelRT::LogLevel::Debug;

    NovelRT::LoggingService logger = NovelRT::LoggingService();
    logger.setLogLevel(NovelRT::LogLevel::Info);

    auto window = new GlfwWindowingDevice();
    auto device = std::shared_ptr<IWindowingDevice>(window);
    auto inputDevice = new GlfwInputDevice();
    auto sharedInputDevice = std::shared_ptr<IInputDevice>(inputDevice);

    device->Initialise(NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(1024, 768));
    inputDevice->Initialise(device);
    auto clickAction = inputDevice->AddInputAction("LeftClick", "LeftMouseButton");

    auto gfxProvider =
        std::make_shared<GraphicsProvider<VulkanGraphicsBackend>>(std::make_shared<VulkanGraphicsProvider>());

    VulkanGraphicsAdapterSelector selector{};

    auto surfaceContext = std::make_shared<GraphicsSurfaceContext<VulkanGraphicsBackend>>(
        std::make_shared<VulkanGraphicsSurfaceContext>(device, gfxProvider->GetImplementation()), device, gfxProvider);

    std::shared_ptr<GraphicsAdapter<VulkanGraphicsBackend>> adapter =
        std::make_shared<GraphicsAdapter<VulkanGraphicsBackend>>(
            selector.GetDefaultRecommendedAdapter(gfxProvider->GetImplementation(),
                                                  surfaceContext->GetImplementation()),
            gfxProvider);
    std::shared_ptr<GraphicsDevice<VulkanGraphicsBackend>> gfxDevice = adapter->CreateDevice(surfaceContext, 2);

    std::shared_ptr<GraphicsContext<VulkanGraphicsBackend>> gfxContext = gfxDevice->GetCurrentContext();
    auto memoryAllocator = std::make_shared<GraphicsMemoryAllocator<VulkanGraphicsBackend>>(
        std::make_shared<VulkanGraphicsMemoryAllocator>(gfxDevice->GetImplementation(),
                                                        gfxProvider->GetImplementation()),
        gfxDevice, gfxProvider);

    ///IMGUI
    auto uiProvider = new ImGuiUIProvider<VulkanGraphicsBackend>();
    uiProvider->Initialise(device, sharedInputDevice, gfxDevice, memoryAllocator, true);
    ///IMGUI

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

    auto pVertexBuffer = vertexStagingBuffer->Map<TexturedVertex>(vertexBufferRegion);

    pVertexBuffer[0] = TexturedVertex{NovelRT::Maths::GeoVector3F(0, 1, 0), NovelRT::Maths::GeoVector2F(0.5f, 0.0f)};
    pVertexBuffer[1] = TexturedVertex{NovelRT::Maths::GeoVector3F(1, -1, 0), NovelRT::Maths::GeoVector2F(1.0f, 1.0f)};
    pVertexBuffer[2] = TexturedVertex{NovelRT::Maths::GeoVector3F(-1, -1, 0), NovelRT::Maths::GeoVector2F(0.0f, 1.0f)};

    vertexStagingBuffer->UnmapAndWrite(vertexBufferRegion);
    cmdList->CmdCopy(vertexBufferRegion, stagingBufferRegion);

    uint32_t textureWidth = 256;
    uint32_t textureHeight = 256;
    uint32_t texturePixels = textureWidth * textureHeight;
    uint32_t cellWidth = textureWidth / 8;
    uint32_t cellHeight = textureHeight / 8;

    auto texture2D = memoryAllocator->CreateTexture2DRepeatGpuWriteOnly(textureWidth, textureHeight);

    auto texture2DRegion = texture2D->Allocate(texture2D->GetSize(), 4);
    auto pTextureData = textureStagingBuffer->Map<uint32_t>(texture2DRegion);

    for (uint32_t n = 0; n < texturePixels; n++)
    {
        auto x = n % textureWidth;
        auto y = n / textureWidth;

        pTextureData[n] = (x / cellWidth % 2) == (y / cellHeight % 2) ? 0xFF000000 : 0xFFFFFFFF;
    }

    textureStagingBuffer->UnmapAndWrite(texture2DRegion);

    std::vector<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, VulkanGraphicsBackend>>>
        inputResourceRegions{
            std::static_pointer_cast<GraphicsResourceMemoryRegion<GraphicsResource, VulkanGraphicsBackend>>(
                texture2DRegion)};

    auto textureStagingBufferRegion = textureStagingBuffer->Allocate(texture2D->GetSize(), 4);

    cmdList->CmdBeginTexturePipelineBarrierLegacyVersion(texture2D);
    cmdList->CmdCopy(texture2D, textureStagingBufferRegion);
    cmdList->CmdEndTexturePipelineBarrierLegacyVersion(texture2D);

    gfxContext->EndFrame();
    gfxDevice->Signal(gfxContext->GetFence());
    gfxDevice->WaitForIdle();
    gfxContext->GetFence()->Reset();

    /// imgui
    int strIndex = 0;
    std::vector<std::string> arr{"Hello!", "I'm going to get milk, now...", "...", "...", "*30 years later*", "..."};

    auto surface = gfxDevice->GetSurface();
    bool clicked = false;
    NovelRT::Timing::StepTimer timer(144.0f, 1.0f / 144.0f);
    DummyUpdateStuff += [&](auto delta) {
        device->ProcessAllMessages();
        inputDevice->Update(delta);

        if (device->GetIsVisible())
        {
            auto cl = inputDevice->GetCurrentChangeLog(clickAction.actionName);

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
            uiProvider->BeginFrame(delta.getSecondsFloat());
            
            ImGui::SetNextWindowSize(ImVec2(612, 200));
            ImGui::SetNextWindowPos(ImVec2(100, 500));
            ImGui::Begin("Test", NULL,
                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

            if (strIndex < arr.size())
            {
                ImGui::Text(arr.at(strIndex).c_str());
            }

            ImGui::End();
            uiProvider->EndFrame();
            
            auto context = gfxDevice->GetCurrentContext();
            auto currentCmdList = context->BeginFrame();
            
            float surfaceWidth = surface->GetWidth();
            float surfaceHeight = surface->GetHeight();

            auto renderPass = gfxDevice->GetRenderPass();
            NovelRT::Graphics::ClearValue colourDataStruct{};
            colourDataStruct.colour = NovelRT::Graphics::RGBAColour(0, 0, 255, 255);
            colourDataStruct.depth = 0;
            colourDataStruct.stencil = 0;

            std::vector<ClearValue> colourData{colourDataStruct};
            currentCmdList->CmdBeginRenderPass(renderPass, colourData);

            ViewportInfo viewportInfoStruct{};
            viewportInfoStruct.x = 0;
            viewportInfoStruct.y = surfaceHeight;
            viewportInfoStruct.width = surfaceWidth;
            viewportInfoStruct.height = -surfaceHeight;
            viewportInfoStruct.minDepth = 0.0f;
            viewportInfoStruct.maxDepth = 1.0f;

            currentCmdList->CmdSetViewport(viewportInfoStruct);

            regularDrawCmds(gfxContext, currentCmdList, renderPass, surfaceWidth, surfaceHeight, signature, pipeline,
                           vertexBuffer, vertexBufferRegion, inputResourceRegions);

            currentCmdList->CmdEndRenderPass();

            uiProvider->Draw(currentCmdList);

            context->EndFrame();
            gfxDevice->PresentFrame();
            gfxDevice->WaitForIdle();
        }
    };

    while (!device->GetShouldClose())
    {
        timer.tick(DummyUpdateStuff);
    }

    return 0;
}
