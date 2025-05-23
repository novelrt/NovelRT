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

static const char* ImGui_GetClipboardText(void* user_data)
{
    unused(user_data);
    return "placeholder text";
}

static void ImGui_SetClipboardText(void* user_data, const char* text)
{
    unused(user_data);
    unused(text);
}

struct TexturedVertex
{
    NovelRT::Maths::GeoVector3F Position;
    NovelRT::Maths::GeoVector2F UV;
};

void imguiDrawCommands(ImDrawData* drawData,
                       std::shared_ptr<GraphicsMemoryAllocator<VulkanGraphicsBackend>> memoryAllocator,
                       std::shared_ptr<GraphicsContext<VulkanGraphicsBackend>> context,
                       std::shared_ptr<GraphicsCmdList<VulkanGraphicsBackend>> currentCmdList,
                       std::shared_ptr<GraphicsRenderPass<VulkanGraphicsBackend>> renderPass,
                       float surfaceWidth,
                       float surfaceHeight,
                       std::shared_ptr<GraphicsPipelineSignature<VulkanGraphicsBackend>> pipelineSignature,
                       std::shared_ptr<GraphicsPipeline<VulkanGraphicsBackend>> pipeline)
{
    if (drawData->TotalVtxCount <= 0)
        return;

    auto io = ImGui::GetIO();

    size_t vertexSize = drawData->TotalVtxCount * sizeof(ImDrawVert);
    size_t indexSize = drawData->TotalIdxCount * sizeof(ImDrawIdx);

    // Create buffers
    GraphicsBufferCreateInfo bufferCreateInfo{};
    bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::Write;
    bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Read;
    bufferCreateInfo.size = vertexSize;
    auto vertexStagingBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);
    shittyBuffer.emplace_back(*vertexStagingBuffer.get());

    bufferCreateInfo.bufferKind = GraphicsBufferKind::Vertex;
    bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::None;
    bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Write;
    auto vertexBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);
    shittyBuffer.emplace_back(*vertexBuffer.get());

    // Create index buffer + staging
    bufferCreateInfo.bufferKind = GraphicsBufferKind::Default;
    bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::Write;
    bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Read;
    bufferCreateInfo.size = indexSize;
    auto indexStagingBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);
    shittyBuffer.emplace_back(*indexStagingBuffer.get());

    bufferCreateInfo.bufferKind = GraphicsBufferKind::Index;
    bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::None;
    bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Write;
    auto indexBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);
    shittyBuffer.emplace_back(*indexBuffer.get());

    // Allocate buffers
    auto vertexBufferRegion = vertexBuffer->Allocate(vertexSize, 4);
    auto vertexStageBufferRegion = vertexStagingBuffer->Allocate(vertexSize, 4);
    auto indexBufferRegion = indexBuffer->Allocate(indexSize, 4);
    auto indexStageBufferRegion = indexStagingBuffer->Allocate(indexSize, 4);

    // Map vertex buffer to region
    auto pVertexBuffer = vertexStagingBuffer->Map<ImDrawVert>(vertexBufferRegion);
    auto pVertPtr = pVertexBuffer.data();
    // Map index buffer to region
    auto pIndexbuffer = indexStagingBuffer->Map<ImDrawIdx>(indexBufferRegion);
    auto pIdxPtr = pIndexbuffer.data();

    int32_t vertInitial = 0;
    int32_t indexInitial = 0;

    // Slamjam the vertex buffer and index buffer data into their regions :|
    for (int i = 0; i < drawData->CmdListsCount; i++)
    {
        ImDrawList* list = drawData->CmdLists[i];

        // Copy vertex and index data
        memcpy(pVertPtr, list->VtxBuffer.Data, list->VtxBuffer.Size * sizeof(ImDrawVert));
        memcpy(pIdxPtr, list->IdxBuffer.Data, list->IdxBuffer.Size * sizeof(ImDrawIdx));

        pVertPtr += list->VtxBuffer.Size;
        pIdxPtr += list->IdxBuffer.Size;
    }

    // Unmap the buffers and copy them into their regions for GPU-ity
    vertexStagingBuffer->UnmapAndWrite(vertexBufferRegion);
    indexStagingBuffer->UnmapAndWrite(indexBufferRegion);
    currentCmdList->CmdCopy(vertexBufferRegion, vertexStageBufferRegion);
    currentCmdList->CmdCopy(indexBufferRegion, indexStageBufferRegion);

    auto impl = currentCmdList->_implementation;
    auto cmd = impl->_commandBuffer;

    // Provided by VK_VERSION_1_0
    //
#if 0
            .buffer = self.vertexBuffers[self.swapId].buffer,
            .src_access_mask = .{
                .transfer_read_bit = true,
            },
            .dst_access_mask = .{
                // .transfer_write_bit = true,
                .vertex_attribute_read_bit = true,
            },
            .src_queue_family_index = 0,
            .dst_queue_family_index = 0,
            .offset = 0,
            .size = copy.size,
    typedef struct VkBufferMemoryBarrier {
        VkStructureType    sType;
        const void*        pNext;
        VkAccessFlags      srcAccessMask;
        VkAccessFlags      dstAccessMask;
        uint32_t           srcQueueFamilyIndex;
        uint32_t           dstQueueFamilyIndex;
        VkBuffer           buffer;
        VkDeviceSize       offset;
        VkDeviceSize       size;
    } VkBufferMemoryBarrier;
#endif

    VkBufferMemoryBarrier barrierInfo = {
        VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
        nullptr,
        VK_ACCESS_TRANSFER_WRITE_BIT,
        VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT,
        VK_QUEUE_FAMILY_IGNORED,
        VK_QUEUE_FAMILY_IGNORED,
        std::static_pointer_cast<VulkanGraphicsBuffer>(vertexBufferRegion->GetImplementation()->GetOwningResource())
            ->GetVulkanBuffer(),
        0,
        VK_WHOLE_SIZE};
    vkCmdPipelineBarrier(cmd, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_VERTEX_INPUT_BIT, 0, 0, 0, 1,
                         &barrierInfo, 0, 0);

    barrierInfo.dstAccessMask = VK_ACCESS_INDEX_READ_BIT;
    barrierInfo.buffer =
        std::static_pointer_cast<VulkanGraphicsBuffer>(indexBufferRegion->GetImplementation()->GetOwningResource())
            ->GetVulkanBuffer(),

    vkCmdPipelineBarrier(cmd, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_VERTEX_INPUT_BIT, 0, 0, 0, 1,
                         &barrierInfo, 0, 0);

    // This seems terrible but I want it working before I refactor it
    int32_t globalVertexOffset = 0;
    int32_t globalIndexOffset = 0;

    ImVec2 clippingOffset = drawData->DisplayPos;
    ImVec2 clippingScale = drawData->FramebufferScale;

    // Bind the Vertex Buffers and the index buffer(s)?
    std::array<std::shared_ptr<GraphicsBuffer<VulkanGraphicsBackend>>, 1> buffers{vertexBuffer};
    auto currentOffset = vertexBufferRegion->GetOffset();
    auto currentIndexBufferRegion = indexBufferRegion;

    std::array<size_t, 1> offsets{currentOffset};

    NovelRT::Graphics::ClearValue colourDataStruct{};
    colourDataStruct.colour = NovelRT::Graphics::RGBAColour(0, 0, 255, 0);
    colourDataStruct.depth = 0.1;
    colourDataStruct.stencil = 0;

    std::vector<ClearValue> colourData{colourDataStruct};
    currentCmdList->CmdBeginRenderPass(renderPass, colourData);

    ViewportInfo viewportInfoStruct{};
    viewportInfoStruct.x = 0;
    viewportInfoStruct.y = 0;
    viewportInfoStruct.width = surfaceWidth;
    viewportInfoStruct.height = surfaceHeight;
    viewportInfoStruct.minDepth = 0.0f;
    viewportInfoStruct.maxDepth = 1.0f;

    currentCmdList->CmdSetViewport(viewportInfoStruct);

    currentCmdList->CmdBindPipeline(pipeline);
    currentCmdList->CmdBindVertexBuffers(0, 1, buffers, offsets);
    currentCmdList->CmdBindIndexBuffer(currentIndexBufferRegion, IndexType::UInt16);

    float scale[2];
    scale[0] = 2.0f / drawData->DisplaySize.x;
    scale[1] = 2.0f / drawData->DisplaySize.y;
    float translate[2];
    translate[0] = -1.0f - drawData->DisplayPos.x * scale[0];
    translate[1] = -1.0f - drawData->DisplayPos.y * scale[1];
    size_t floatSize = sizeof(float) * 2;
    NovelRT::Utilities::Misc::Span<float> scaleSpan(scale);
    NovelRT::Utilities::Misc::Span<float> translateSpan(translate);

    currentCmdList->CmdPushConstants(pipelineSignature, ShaderProgramVisibility::Vertex, 0,
                                     NovelRT::Utilities::Misc::SpanCast<uint8_t>(scaleSpan));
    currentCmdList->CmdPushConstants(pipelineSignature, ShaderProgramVisibility::Vertex, sizeof(float) * 2,
                                     NovelRT::Utilities::Misc::SpanCast<uint8_t>(translateSpan));

    for (int n = 0; n < drawData->CmdListsCount; n++)
    {
        const ImDrawList* list = drawData->CmdLists[n];
        for (int cmdIndex = 0; cmdIndex < list->CmdBuffer.Size; cmdIndex++)
        {
            const ImDrawCmd* drawCommand = &list->CmdBuffer[cmdIndex];
            if (drawCommand->UserCallback != nullptr)
            {
                drawCommand->UserCallback(list, drawCommand);
            }
            else
            {

                // Project scissor/clipping rectangles into framebuffer space
                ImVec2 clippingMin((drawCommand->ClipRect.x - clippingOffset.x) * clippingScale.x,
                                   (drawCommand->ClipRect.y - clippingOffset.y) * clippingScale.y);
                ImVec2 clippingMax((drawCommand->ClipRect.z - clippingOffset.x) * clippingScale.x,
                                   (drawCommand->ClipRect.w - clippingOffset.y) * clippingScale.y);

                // Clamp to viewport as vkCmdSetScissor() won't accept values that are off bounds
                if (clippingMin.x < 0.0f)
                {
                    clippingMin.x = 0.0f;
                }
                if (clippingMin.y < 0.0f)
                {
                    clippingMin.y = 0.0f;
                }
                if (clippingMax.x > surfaceWidth)
                {
                    clippingMax.x = surfaceWidth;
                }
                if (clippingMax.y > surfaceHeight)
                {
                    clippingMax.y = (float)surfaceHeight;
                }
                if (clippingMax.x <= clippingMin.x || clippingMax.y <= clippingMin.y)
                    continue;

                // Apply scissor/clipping rectangle
                currentCmdList->CmdSetScissor(
                    NovelRT::Maths::GeoVector2F(clippingMin.x, clippingMin.y),
                    NovelRT::Maths::GeoVector2F((clippingMax.x - clippingMin.x), (clippingMax.y - clippingMin.y)));

                // Bind DescriptorSet with font or user texture
                auto texture2DRegion = *reinterpret_cast<
                    std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, VulkanGraphicsBackend>>*>(
                    drawCommand->GetTexID());
                std::vector<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, VulkanGraphicsBackend>>>
                    inputResourceRegions{
                        std::static_pointer_cast<GraphicsResourceMemoryRegion<GraphicsResource, VulkanGraphicsBackend>>(
                            std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, VulkanGraphicsBackend>>(
                                texture2DRegion))};

                // Specify the descriptor set data
                auto descriptorSetData = pipeline->CreateDescriptorSet();
                descriptorSetData->AddMemoryRegionsToInputs(inputResourceRegions);
                descriptorSetData->UpdateDescriptorSetData();
                context->RegisterDescriptorSetForFrame(pipelineSignature, descriptorSetData);

                // Bind the descriptor set
                std::array<std::shared_ptr<GraphicsDescriptorSet<VulkanGraphicsBackend>>, 1> descriptorData{
                    descriptorSetData};

                currentCmdList->CmdBindDescriptorSets(descriptorData);

                currentCmdList->CmdDrawIndexed(drawCommand->ElemCount, 1, drawCommand->IdxOffset + globalIndexOffset,
                                               drawCommand->VtxOffset + globalVertexOffset, 0);
            }
        }
        globalIndexOffset += list->IdxBuffer.Size;
        globalVertexOffset += list->VtxBuffer.Size;
    }

    // Reset clipping rect as per imgui
    currentCmdList->CmdSetScissor(NovelRT::Maths::GeoVector2F::Zero(),
                                  NovelRT::Maths::GeoVector2F(drawData->DisplaySize.x, drawData->DisplaySize.y));

    currentCmdList->CmdEndRenderPass();
}

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

    device->Initialise(NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(1024, 768));
    inputDevice->Initialise(device);
    auto clickAction = inputDevice->AddInputAction("LeftClick", "LeftMouseButton");

    IMGUI_CHECKVERSION();

    auto imguiContext = ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = NULL;
    io.Fonts->AddFontDefault();
    ImGui::StyleColorsDark();

    io.BackendPlatformUserData = nullptr;
    io.BackendPlatformName = "NovelRT";
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    io.ClipboardUserData = nullptr;
    io.GetClipboardTextFn = &ImGui_GetClipboardText;
    io.SetClipboardTextFn = &ImGui_SetClipboardText;

    ImGui::GetMainViewport()->PlatformHandleRaw = (void*)device->GetHandle();

    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

    uint8_t* pixels;
    int32_t width, height;

    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

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

    /// IMGUI
    GraphicsBufferCreateInfo imbci{};
    imbci.cpuAccessKind = GraphicsResourceAccess::Write;
    imbci.gpuAccessKind = GraphicsResourceAccess::Read;
    imbci.size = 64 * 1024 * 4;

    // Create Texture Staging Buffer
    auto imTSB = memoryAllocator->CreateBuffer(imbci);
    /// IMGUI

    auto vertShaderData = LoadSpv("vulkanrendervert.spv");
    auto pixelShaderData = LoadSpv("vulkanrenderfrag.spv");
    auto vertImguiShader = LoadSpv("imgui_vert.spv");
    auto pixelImguiShader = LoadSpv("imgui_frag.spv");

    std::shared_ptr<GraphicsCmdList<VulkanGraphicsBackend>> cmdList = gfxContext->BeginFrame();

    std::vector<GraphicsPipelineInputElement> elements{
        GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector3F), GraphicsPipelineInputElementKind::Position,
                                     12),
        GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F),
                                     GraphicsPipelineInputElementKind::TextureCoordinate, 8)};

    std::vector<GraphicsPipelineInput> inputs{GraphicsPipelineInput(elements)};
    std::vector<GraphicsPipelineResource> resources{
        GraphicsPipelineResource(GraphicsPipelineResourceKind::Texture, ShaderProgramVisibility::Pixel)};

    /// IMGUI
    std::vector<GraphicsPipelineInputElement> elem{
        GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F), GraphicsPipelineInputElementKind::Position,
                                     8),
        GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F), GraphicsPipelineInputElementKind::Normal, 8),
        GraphicsPipelineInputElement(typeid(ImU32), GraphicsPipelineInputElementKind::Colour, sizeof(ImU32))};

    std::vector<GraphicsPushConstantRange> pushConstants{
        GraphicsPushConstantRange{ShaderProgramVisibility::Vertex, 0, sizeof(float) * 4}};

    std::vector<GraphicsPipelineInput> in{GraphicsPipelineInput(elem)};
    std::vector<GraphicsPipelineResource> res{
        GraphicsPipelineResource(GraphicsPipelineResourceKind::Texture, ShaderProgramVisibility::Pixel)};
    auto sig = gfxDevice->CreatePipelineSignature(
        GraphicsPipelineBlendFactor::SrcAlpha, GraphicsPipelineBlendFactor::OneMinusSrcAlpha, in, res, pushConstants);
    auto imVertProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Vertex, vertImguiShader);
    auto imPixProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Pixel, pixelImguiShader);
    auto pip = gfxDevice->CreatePipeline(sig, imVertProg, imPixProg, true);
    /// IMGUI

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

    /// imgui
    auto imtci = GraphicsTextureCreateInfo{GraphicsTextureAddressMode::Repeat,
                                           GraphicsTextureKind::TwoDimensional,
                                           GraphicsResourceAccess::None,
                                           GraphicsResourceAccess::ReadWrite,
                                           static_cast<uint32_t>(width),
                                           static_cast<uint32_t>(height),
                                           1,
                                           GraphicsMemoryRegionAllocationFlags::None,
                                           TexelFormat::R8G8B8A8_UNORM};
    auto im2D = memoryAllocator->CreateTexture(imtci);

    // Allocate region based on size of texture
    std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, VulkanGraphicsBackend>> im2dRegion =
        im2D->Allocate(im2D->GetSize(), 4);

    // Create a staging buffer region for texture
    auto imStageBufferRegion = imTSB->Allocate(im2D->GetSize(), 4);
    auto imTexD = imTSB->Map<uint32_t>(im2dRegion);

    memcpy(imTexD.data(), pixels, (width * height) * sizeof(char) * 4);

    imTSB->UnmapAndWrite(im2dRegion);
    io.Fonts->SetTexID(reinterpret_cast<ImTextureID>(&im2dRegion));
    /// imgui

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

    /// imgui
    cmdList->CmdBeginTexturePipelineBarrierLegacyVersion(im2D);
    cmdList->CmdCopy(im2D, imStageBufferRegion);
    cmdList->CmdEndTexturePipelineBarrierLegacyVersion(im2D);
    /// imgui

    gfxContext->EndFrame();
    gfxDevice->Signal(gfxContext->GetFence());
    gfxDevice->WaitForIdle();
    gfxContext->GetFence()->Reset();

    /// imgui
    bool demo = true;

    io = ImGui::GetIO();
    auto windowSize = device->GetSize();
    io.DisplaySize = ImVec2(windowSize.x, windowSize.y);

    if ((windowSize.x > 0) && (windowSize.y > 0))
    {
        io.DisplayFramebufferScale = ImVec2(1, 1);
    }

    io.DeltaTime = (float)(1.0f / 60.0f);
    int strIndex = 0;
    std::vector<std::string> arr{"Hello!", "I'm going to get milk, now...", "...", "...", "*30 years later*", "..."};

    /// imgui
    // ImGui::NewFrame();
    // ImGui::ShowDemoWindow(&demo);
    //// ImGui::EndFrame();
    // ImGui::Render();

    auto surface = gfxDevice->GetSurface();
    bool clicked = false;
    NovelRT::Timing::StepTimer timer(144.0f, 1.0f / 144.0f);
    DummyUpdateStuff += [&](auto delta) {
        device->ProcessAllMessages();
        inputDevice->Update(delta);
        if (device->GetIsVisible())
        {
            io = ImGui::GetIO();
            auto windowSize = device->GetSize();
            io.DisplaySize = ImVec2(windowSize.x, windowSize.y);

            if ((windowSize.x > 0) && (windowSize.y > 0))
            {
                io.DisplayFramebufferScale = ImVec2(1, 1);
            }

            io.DeltaTime = delta.getSecondsFloat();
            auto mousePos = inputDevice->GetRawMousePosition();
            io.AddMousePosEvent(mousePos.x, mousePos.y);
            auto state = inputDevice->GetKeyState(clickAction.actionName);
            if (state == KeyState::KeyDown || state == KeyState::KeyDown)
            {
                io.AddMouseButtonEvent(0, true);
            }
            else
                io.AddMouseButtonEvent(0, false);

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
            ImGui::NewFrame();
            ImGui::SetNextWindowSize(ImVec2(612, 200));
            ImGui::SetNextWindowPos(ImVec2(100, 500));
            ImGui::Begin("Test", NULL,
                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

            if (strIndex < arr.size())
            {
                ImGui::Text(arr.at(strIndex).c_str());
            }

            ImGui::End();

            ImGui::Render();
            ImDrawData* drawData = ImGui::GetDrawData();
            // imGuiProvider->BeginFrame(1.0f/60.0f);
            // imGuiProvider->EndFrame();

            auto context = gfxDevice->GetCurrentContext();
            auto currentCmdList = context->BeginFrame();
            // context->BeginDrawing(NovelRT::Graphics::RGBAColour(0, 0, 255, 255));

            float surfaceWidth = surface->GetWidth();
            float surfaceHeight = surface->GetHeight();

            // imGuiProvider->UploadImguiGpuData(context, currentCmdList);

            auto renderPass = gfxDevice->GetRenderPass();
            NovelRT::Graphics::ClearValue colourDataStruct{};
            colourDataStruct.colour = NovelRT::Graphics::RGBAColour(0, 0, 255, 255);
            colourDataStruct.depth = 0;
            colourDataStruct.stencil = 0;

            std::vector<ClearValue> colourData{colourDataStruct};
            // currentCmdList->CmdBeginRenderPass(renderPass, colourData);

            ViewportInfo viewportInfoStruct{};
            viewportInfoStruct.x = 0;
            viewportInfoStruct.y = surfaceHeight;
            viewportInfoStruct.width = surfaceWidth;
            viewportInfoStruct.height = -surfaceHeight;
            viewportInfoStruct.minDepth = 0.0f;
            viewportInfoStruct.maxDepth = 1.0f;

            currentCmdList->CmdSetViewport(viewportInfoStruct);

            // regularDrawCmds(gfxContext, currentCmdList, renderPass, surfaceWidth, surfaceHeight, signature, pipeline,
            //                vertexBuffer, vertexBufferRegion, inputResourceRegions);

            // currentCmdList->CmdEndRenderPass();

            imguiDrawCommands(drawData, memoryAllocator, gfxContext, currentCmdList, renderPass, surfaceWidth,
                              surfaceHeight, sig, pip);

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
