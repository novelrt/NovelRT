// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

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

#include <NovelRT/Windowing/Glfw/Windowing.Glfw.h>
#include <NovelRT/Windowing/Windowing.h>
#include <memory>

using namespace NovelRT::Windowing::Glfw;
using namespace NovelRT::Windowing;
using namespace NovelRT::Graphics::Vulkan;
using namespace NovelRT::Graphics;

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

int main()
{
    NovelRT::EngineConfig::EnableDebugOutputFromEngineInternals() = true;
    NovelRT::EngineConfig::MinimumInternalLoggingLevel() = NovelRT::LogLevel::Warn;

    NovelRT::LoggingService logger = NovelRT::LoggingService();
    logger.setLogLevel(NovelRT::LogLevel::Info);

    auto window = new GlfwWindowingDevice();
    auto device = std::shared_ptr<IWindowingDevice>(window);

    device->Initialise(NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(400, 400));

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

    // auto vertexStagingBuffer = memoryAllocator->CreateBufferWithDefaultArguments(
    //     GraphicsBufferKind::Default, GraphicsResourceAccess::Write, GraphicsResourceAccess::Read, 64 * 1024);
    // auto textureStagingBuffer = gfxDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
    //     GraphicsBufferKind::Default, GraphicsResourceAccess::Write, GraphicsResourceAccess::Read, 64 * 1024 * 4);
    // auto vertexBuffer = gfxDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
    //     GraphicsBufferKind::Vertex, GraphicsResourceAccess::None, GraphicsResourceAccess::Write, 64 * 1024);

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

    auto signature = gfxDevice->CreatePipelineSignature(GraphicsPipelineBlendFactor::SrcAlpha,
                                                        GraphicsPipelineBlendFactor::OneMinusSrcAlpha, inputs,
                                                        resources, std::vector<GraphicsPushConstantRange>{});
    auto vertShaderProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Vertex, vertShaderData);
    auto pixelShaderProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Pixel, pixelShaderData);
    auto pipeline = gfxDevice->CreatePipeline(signature, vertShaderProg, pixelShaderProg);
    // auto dummyRegion = GraphicsResourceMemoryRegion<GraphicsBuffer, VulkanGraphicsBackend>(0, nullptr, gfxDevice,
    // false, 0, 0);

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

    // auto texture2D = memoryAllocator->CreateTextureWithDefaultArguments(
    //     GraphicsTextureAddressMode::Repeat, GraphicsTextureKind::TwoDimensional, GraphicsResourceAccess::None,
    //     GraphicsResourceAccess::Write, textureWidth, textureHeight);

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

    auto surface = gfxDevice->GetSurface();

    while (!device->GetShouldClose())
    {
        device->ProcessAllMessages();
        if (device->GetIsVisible())
        {
            auto context = gfxDevice->GetCurrentContext();
            auto currentCmdList = context->BeginFrame();
            // context->BeginDrawing(NovelRT::Graphics::RGBAColour(0, 0, 255, 255));

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
            currentCmdList->CmdSetScissor(NovelRT::Maths::GeoVector2F::Zero(),
                                          NovelRT::Maths::GeoVector2F(surfaceWidth, surfaceHeight));
            currentCmdList->CmdBindPipeline(pipeline);

            std::array<std::shared_ptr<GraphicsBuffer<VulkanGraphicsBackend>>, 1> buffers{vertexBuffer};
            std::array<size_t, 1> offsets{vertexBufferRegion->GetOffset()};

            currentCmdList->CmdBindVertexBuffers(0, 1, buffers, offsets);

            auto descriptorSetData = pipeline->CreateDescriptorSet();
            descriptorSetData->AddMemoryRegionsToInputs(inputResourceRegions);
            descriptorSetData->UpdateDescriptorSetData();

            std::array<std::shared_ptr<GraphicsDescriptorSet<VulkanGraphicsBackend>>, 1> descriptorData{
                descriptorSetData};
            currentCmdList->CmdBindDescriptorSets(descriptorData);

            currentCmdList->CmdDraw(vertexBufferRegion->GetSize() / sizeof(TexturedVertex), 1, 0, 0);

            currentCmdList->CmdEndRenderPass();

            // auto primitive = gfxDevice->CreatePrimitive(pipeline, vertexBufferRegion, sizeof(TexturedVertex),
            //                                             dummyRegion, 0, inputResourceRegions);
            // context->Draw(primitive);
            context->EndFrame();
            gfxDevice->PresentFrame();
            gfxDevice->WaitForIdle();
        }
    }

    return 0;
}
