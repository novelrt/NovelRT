#pragma once
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElement.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResourceKind.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>
#include <NovelRT/Graphics/ShaderProgramVisibility.hpp>
#include <NovelRT/Maths/Maths.h>
#include <NovelRT/UI/UIProvider.hpp>
#include <imgui.h>
#include <fstream>

using namespace NovelRT::Graphics;

namespace NovelRT::UI::DearImGui
{
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

    static inline size_t AlignBufferSize(size_t size, size_t alignment)
    {
        return (size + alignment - 1) & ~(alignment - 1);
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
    template<typename TBackend> class ImGuiUIProvider final : public UIProvider<TBackend>
    {
    private:
        ImGuiContext* _imguiContext;
        Threading::VolatileState _state;
        LoggingService _logger;

        std::shared_ptr<Windowing::IWindowingDevice> _windowingDevice;
        std::shared_ptr<Input::IInputDevice> _inputDevice;
        std::shared_ptr<Graphics::GraphicsTexture<TBackend>> _texture2D;
        std::shared_ptr<Graphics::GraphicsDevice<TBackend>> _graphicsDevice;
        std::shared_ptr<Graphics::GraphicsMemoryAllocator<TBackend>> _memoryAllocator;
        std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>> _texture2DRegion;
        std::shared_ptr<GraphicsPipeline<TBackend>> _pipeline;
        std::shared_ptr<GraphicsPipelineSignature<TBackend>> _pipelineSignature;

    public:
        ImGuiUIProvider()
            : _imguiContext(nullptr),
              _state(Threading::VolatileState()),
              _logger(LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_GFX))
        {
            IMGUI_CHECKVERSION();

            _imguiContext = ImGui::CreateContext();

            static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
        }

        [[nodiscard]] inline ImGuiContext* GetImGuiContext() const noexcept
        {
            return _imguiContext;
        }

        void Initialise(std::shared_ptr<Windowing::IWindowingDevice> windowingDevice,
                        std::shared_ptr<Input::IInputDevice> inputDevice,
                        std::shared_ptr<Graphics::GraphicsProvider<TBackend>> graphicsProvider,
                        std::shared_ptr<Graphics::GraphicsDevice<TBackend>> graphicsDevice,
                        std::shared_ptr<Graphics::GraphicsMemoryAllocator<TBackend>> memoryAllocator) final

        {
            _windowingDevice = windowingDevice;
            _inputDevice = inputDevice;
            _graphicsDevice = graphicsDevice;
            _memoryAllocator = memoryAllocator;

            ImGuiIO& io = ImGui::GetIO();
            ImGui::StyleColorsDark();

            io.BackendPlatformUserData = (void*)this;
            io.BackendPlatformName = "NovelRT";
            io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
            io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
            io.ClipboardUserData = (void*)this;
            io.GetClipboardTextFn = &ImGui_GetClipboardText;
            io.SetClipboardTextFn = &ImGui_SetClipboardText;

            ImGui::GetMainViewport()->PlatformHandleRaw = (void*)windowingDevice->GetHandle();

            io.BackendRendererUserData = (void*)this;
            io.BackendRendererName = "NovelRT";
            io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

            uint8_t* pixels;
            int32_t width, height;

            io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

            size_t upload_size = (width * height) * sizeof(uint32_t);
            unused(upload_size);

            // Getting Jiggy Wit It - GFX-style
            auto graphicsContext = graphicsDevice->GetCurrentContext();

            // Create Vertex Staging Buffer
            GraphicsBufferCreateInfo bufferCreateInfo{};
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::Write;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Read;
            bufferCreateInfo.size = 64 * 1024;

            auto vertexStagingBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);

            bufferCreateInfo.size = 64 * 1024 * 4;

            // Create Texture Staging Buffer
            auto textureStagingBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);

            bufferCreateInfo.bufferKind = GraphicsBufferKind::Vertex;
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::None;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Write;
            bufferCreateInfo.size = 64 * 1024;

            // Create Vertex Buffer
            auto vertexBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);
            // Create Command List
            std::shared_ptr<GraphicsCmdList<TBackend>> cmdList = graphicsContext->BeginFrame();

            // Define Pipeline inputs and resources
            std::vector<GraphicsPipelineInputElement> elements{
                GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector3F),
                                             GraphicsPipelineInputElementKind::Position, 12),
                GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F),
                                             GraphicsPipelineInputElementKind::TextureCoordinate, 8)};

            std::vector<GraphicsPipelineInput> inputs{GraphicsPipelineInput(elements)};
            std::vector<GraphicsPipelineResource> resources{
                GraphicsPipelineResource(GraphicsPipelineResourceKind::Texture, ShaderProgramVisibility::Pixel)};

            // Allocate memory for vertex and staging buffers
            auto vertexBufferRegion = vertexBuffer->Allocate(sizeof(TexturedVertex) * 3, 16);
            auto stagingBufferRegion = vertexStagingBuffer->Allocate(sizeof(TexturedVertex) * 3, 16);

            // Map vertex buffer to region
            auto pVertexBuffer = vertexStagingBuffer->Map<TexturedVertex>(vertexBufferRegion);

            // Define vertices
            pVertexBuffer[0] =
                TexturedVertex{NovelRT::Maths::GeoVector3F(0, 1, 0), NovelRT::Maths::GeoVector2F(0.5f, 0.0f)};
            pVertexBuffer[1] =
                TexturedVertex{NovelRT::Maths::GeoVector3F(1, -1, 0), NovelRT::Maths::GeoVector2F(1.0f, 1.0f)};
            pVertexBuffer[2] =
                TexturedVertex{NovelRT::Maths::GeoVector3F(-1, -1, 0), NovelRT::Maths::GeoVector2F(0.0f, 1.0f)};

            // Write region to staging buffer
            vertexStagingBuffer->UnmapAndWrite(vertexBufferRegion);
            // Copy Command from staging -> vertex buffer
            cmdList->CmdCopy(vertexBufferRegion, stagingBufferRegion);

            // Create Graphics Texture
            auto textureCreateInfo = GraphicsTextureCreateInfo{GraphicsTextureAddressMode::Repeat,
                                                               GraphicsTextureKind::TwoDimensional,
                                                               GraphicsResourceAccess::None,
                                                               GraphicsResourceAccess::ReadWrite,
                                                               static_cast<uint32_t>(width),
                                                               static_cast<uint32_t>(height),
                                                               1,
                                                               GraphicsMemoryRegionAllocationFlags::None,
                                                               TexelFormat::R8G8B8A8_UNORM};
            _texture2D = memoryAllocator->CreateTexture(textureCreateInfo);
            //_texture2D = memoryAllocator->CreateTexture2DRepeatGpuWriteOnly(width, height);
            // Allocate region based on size of texture
            std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>> texture2DRegion =
                _texture2D->Allocate(_texture2D->GetSize(), 4);
            // Create a staging buffer region for texture
            auto textureStagingBufferRegion = textureStagingBuffer->Allocate(_texture2D->GetSize(), 4);
            // Map the texture staging buffer to the texture region
            auto pTextureData = textureStagingBuffer->Map<uint32_t>(texture2DRegion);

            // copy the data from Imgui's "pixels" to the memory of the texture staging buffer
            memcpy(pTextureData.data(), pixels, width * height);
            // Unmap the staging buffer and write
            textureStagingBuffer->UnmapBytesAndWrite(0, textureStagingBuffer->GetSize());
            // Copy the texture to the GPU
            cmdList->CmdBeginTexturePipelineBarrierLegacyVersion(_texture2D);
            cmdList->CmdCopy(_texture2D, textureStagingBufferRegion);
            cmdList->CmdEndTexturePipelineBarrierLegacyVersion(_texture2D);

            graphicsContext->EndFrame();
            graphicsDevice->Signal(graphicsContext->GetFence());
            graphicsDevice->WaitForIdle();

            // auto ptr = //new Graphics::GraphicsMemoryRegion<Graphics::GraphicsResource<TBackend>>();

            _texture2DRegion = texture2DRegion;

            io.Fonts->SetTexID(reinterpret_cast<ImTextureID>(&_texture2DRegion));

            auto vertShaderData = LoadSpv("imgui_vert.spv");
            auto pixelShaderData = LoadSpv("imgui_frag.spv");

            std::vector<GraphicsPipelineInputElement> elem{
                GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F), GraphicsPipelineInputElementKind::Position,
                                             8),
                GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F),
                                             GraphicsPipelineInputElementKind::Normal, 8),
                GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector4F),
                                             GraphicsPipelineInputElementKind::TextureCoordinate, 16)};
            
            std::vector<GraphicsPushConstantRange> pushConstants{
                GraphicsPushConstantRange{ShaderProgramVisibility::Vertex, 0, sizeof(float) * 4},
                //GraphicsPushConstantRange{ShaderProgramVisibility::Vertex, sizeof(float) * 2, sizeof(float)}
            };
            
        
            std::vector<GraphicsPipelineInput> in{GraphicsPipelineInput(elem)};
            std::vector<GraphicsPipelineResource> res{
                GraphicsPipelineResource(GraphicsPipelineResourceKind::Texture, ShaderProgramVisibility::Pixel)};
        
            auto signature = graphicsDevice->CreatePipelineSignature(
                GraphicsPipelineBlendFactor::SrcAlpha, GraphicsPipelineBlendFactor::OneMinusSrcAlpha, in, res, pushConstants);
            auto vertShaderProg = graphicsDevice->CreateShaderProgram("main", ShaderProgramKind::Vertex, vertShaderData);
            auto pixelShaderProg = graphicsDevice->CreateShaderProgram("main", ShaderProgramKind::Pixel, pixelShaderData);
            auto pipeline = graphicsDevice->CreatePipeline(signature, vertShaderProg, pixelShaderProg);
            _pipeline = pipeline;
            _pipelineSignature = signature;
        }

        void BeginFrame(double deltaTime) final
        {
            ImGuiIO& io = ImGui::GetIO();

            auto windowSize = _windowingDevice->GetSize();
            io.DisplaySize = ImVec2(windowSize.x, windowSize.y);

            if ((windowSize.x > 0) && (windowSize.y > 0))
            {
                io.DisplayFramebufferScale = ImVec2(1, 1);
            }

            io.DeltaTime = (float)deltaTime;

            // TODO: Update input data

            ImGui::NewFrame();
            ImGui::Begin("Hello, World!");
            ImGui::Text("I'm cooked broski");
            ImGui::End();
        }

        void EndFrame() final
        {
            ImGui::EndFrame();
        }

        void Render(std::shared_ptr<GraphicsCmdList<TBackend>> cmdList,
                    std::shared_ptr<Graphics::GraphicsPipeline<TBackend>> pipeline) final
        {
            // Trying to do this how imgui does it cuz it kinda matches up?
            ImGui::Render();
            ImDrawData* drawData = ImGui::GetDrawData();
            auto io = ImGui::GetIO();
            // Early escape
            if (drawData->TotalVtxCount <= 0)
                return;

            /* Magic number for now - TODO: figure out proper alignment value*/
            size_t vertexSize = AlignBufferSize(drawData->TotalVtxCount * sizeof(ImDrawVert), 64);
            size_t indexSize = AlignBufferSize(drawData->TotalIdxCount * sizeof(ImDrawIdx), 64);

            // Create buffers
            GraphicsBufferCreateInfo bufferCreateInfo{};
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::Write;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Read;
            bufferCreateInfo.size = vertexSize;
            auto vertexStagingBuffer = _memoryAllocator->CreateBuffer(bufferCreateInfo);

            bufferCreateInfo.bufferKind = GraphicsBufferKind::Vertex;
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::None;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Write;
            auto vertexBuffer = _memoryAllocator->CreateBuffer(bufferCreateInfo);

            // Create index buffer + staging
            bufferCreateInfo.bufferKind = GraphicsBufferKind::Default;
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::Write;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Read;
            bufferCreateInfo.size = indexSize;
            auto indexStagingBuffer = _memoryAllocator->CreateBuffer(bufferCreateInfo);

            bufferCreateInfo.bufferKind = GraphicsBufferKind::Index;
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::None;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Write;
            auto indexBuffer = _memoryAllocator->CreateBuffer(bufferCreateInfo);

            // Allocate buffers
            auto vertexBufferRegion = vertexBuffer->Allocate(vertexSize, 64);
            auto vertexStageBufferRegion = vertexStagingBuffer->Allocate(vertexSize, 64);
            auto indexBufferRegion = indexBuffer->Allocate(indexSize, 64);
            auto indexStageBufferRegion = indexStagingBuffer->Allocate(indexSize, 64);

            // Map vertex buffer to region
            auto pVertexBuffer = vertexStagingBuffer->Map<ImDrawVert>(vertexBufferRegion);
            // Map index buffer to region
            auto pIndexbuffer = indexStagingBuffer->Map<ImDrawIdx>(indexBufferRegion);

            int32_t vertInitial = 0;
            int32_t indexInitial = 0;

            // Slamjam the vertex buffer and index buffer data into their regions :|
            for (int i = 0; i < drawData->CmdListsCount; i++)
            {
                ImDrawList* list = drawData->CmdLists[i];

                // Copy vertex and index data
                memcpy(pVertexBuffer.data() + vertInitial, list->VtxBuffer.Data,
                       list->VtxBuffer.Size * sizeof(ImDrawVert));
                memcpy(pIndexbuffer.data() + indexInitial, list->IdxBuffer.Data,
                       list->IdxBuffer.Size * sizeof(ImDrawIdx));

                vertInitial += list->VtxBuffer.Size;
                indexInitial += list->IdxBuffer.Size;
            }

            // Unmap the buffers and copy them into their regions for GPU-ity
            vertexStagingBuffer->UnmapAndWrite(vertexBufferRegion);
            indexStagingBuffer->UnmapAndWrite(indexBufferRegion);
            cmdList->CmdCopy(vertexBufferRegion, vertexStageBufferRegion);
            cmdList->CmdCopy(indexBufferRegion, indexStageBufferRegion);

            // This seems terrible but I want it working before I refactor it
            int32_t globalVertexOffset = 0;
            int32_t globalIndexOffset = 0;

            ImVec2 clippingOffset = drawData->DisplayPos;
            ImVec2 clippingScale = drawData->FramebufferScale;

            // Bind the Vertex Buffers and the index buffer(s)?
            std::array<std::shared_ptr<GraphicsBuffer<TBackend>>, 1> buffers{vertexBuffer};
            std::array<size_t, 1> offsets{vertexBufferRegion->GetOffset()};

            cmdList->CmdBindVertexBuffers(0, 1, buffers, offsets);
            cmdList->CmdBindIndexBuffer(
                indexBufferRegion,
                Graphics::IndexType::UInt16); // ImGui provides Uint16, but this could work with uint32 too

            auto renderPass = _graphicsDevice->GetRenderPass();

            NovelRT::Graphics::ClearValue colourDataStruct{};
            colourDataStruct.colour = NovelRT::Graphics::RGBAColour(0, 0, 255, 255);
            colourDataStruct.depth = 0;
            colourDataStruct.stencil = 0;

            std::vector<ClearValue> colourData{colourDataStruct};
            cmdList->CmdBeginRenderPass(renderPass, colourData);

            ViewportInfo viewportInfoStruct{};
            viewportInfoStruct.x = 0;
            viewportInfoStruct.y = drawData->DisplaySize.y;
            viewportInfoStruct.width = drawData->DisplaySize.x;
            viewportInfoStruct.height = -drawData->DisplaySize.y;
            viewportInfoStruct.minDepth = 0.0f;
            viewportInfoStruct.maxDepth = 1.0f;

            cmdList->CmdSetViewport(viewportInfoStruct);

            //Setup PushConstants
            float scale[2];
            scale[0] = 2.0f / drawData->DisplaySize.x;
            scale[1] = 2.0f / drawData->DisplaySize.y;
            float translate[2];
            translate[0] = -1.0f - drawData->DisplayPos.x * scale[0];
            translate[1] = -1.0f - drawData->DisplayPos.y * scale[1];
            size_t floatSize = sizeof(float) * 2;
            Utilities::Misc::Span<float> scaleSpan(scale);
            Utilities::Misc::Span<float> translateSpan(translate);

            cmdList->CmdBindPipeline(_pipeline);
            cmdList->CmdPushConstants(_pipelineSignature, ShaderProgramVisibility::Vertex, 0, Utilities::Misc::SpanCast<uint8_t>(scaleSpan));
            cmdList->CmdPushConstants(_pipelineSignature, ShaderProgramVisibility::Vertex, sizeof(float) * 2, Utilities::Misc::SpanCast<uint8_t>(translateSpan));
            // vkCmdPushConstants(command_buffer, bd->PipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, sizeof(float) * 0, sizeof(float) * 2, scale);
            // vkCmdPushConstants(command_buffer, bd->PipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, sizeof(float) * 2, sizeof(float) * 2, translate);
            

            cmdList->CmdSetScissor(NovelRT::Maths::GeoVector2F::Zero(),
                                   NovelRT::Maths::GeoVector2F(drawData->DisplaySize.x, drawData->DisplaySize.y));
            std::vector<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>>>
                inputResourceRegions{
                        std::static_pointer_cast<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>>(
                        std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>>(
                                _texture2DRegion))}; 

            auto descriptorSetData = _pipeline->CreateDescriptorSet();
            descriptorSetData->AddMemoryRegionsToInputs(inputResourceRegions);
            descriptorSetData->UpdateDescriptorSetData();
            // Start doing the draw commands
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

                        auto texture2DRegion =
                            *reinterpret_cast<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>>*>(
                                drawCommand->GetTexID());
                        std::vector<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>>>
                            inputResourceRegions{
                                 std::static_pointer_cast<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>>(
                                 std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>>(
                                         texture2DRegion))};
                                //std::static_pointer_cast<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>>(
                                 //       vertexBufferRegion)};

                        // Specify the descriptor set - dunno what that means but I think it's right?
                        // auto descriptorSetData = _pipeline->CreateDescriptorSet();
                        // descriptorSetData->AddMemoryRegionsToInputs(inputResourceRegions);
                        // descriptorSetData->UpdateDescriptorSetData();

                        // Bind the descriptor set
                        std::array<std::shared_ptr<GraphicsDescriptorSet<TBackend>>, 1> descriptorData{
                            descriptorSetData};
                        cmdList->CmdBindDescriptorSets(descriptorData);

                        // Project scissor/clipping rectangles into framebuffer space
                        ImVec2 clippingMin((drawCommand->ClipRect.x - clippingOffset.x) * clippingScale.x,
                                           (drawCommand->ClipRect.y - clippingOffset.y) * clippingScale.y);
                        ImVec2 clippingMax((drawCommand->ClipRect.z - clippingOffset.x) * clippingScale.x,
                                           (drawCommand->ClipRect.w - clippingOffset.y) * clippingScale.y);

                        // Clamp to viewport as vkCmdSetScissor() won't accept values that are off bounds
                        // if (clippingMin.x < 0.0f) { clippingMin.x = 0.0f; }
                        // if (clippingMin.y < 0.0f) { clippingMin.y = 0.0f; }
                        // if (clippingMax.x > ) { clippingMax.x = (float)fb_width; }
                        // if (clippingMax.y > fb_height) { clippingMax.y = (float)fb_height; }
                        // if (clippingMax.x <= clippingMin.x || clippingMax.y <= clippingMin.y)
                        //     continue;

                        // Apply scissor/clipping rectangle
                        cmdList->CmdSetScissor(NovelRT::Maths::GeoVector2F::GeoVector2F(clippingMin.x, clippingMin.y),
                                               NovelRT::Maths::GeoVector2F((clippingMax.x - clippingMin.x),
                                                                           (clippingMax.y - clippingMin.y)));

                        // Bind DescriptorSet with font or user texture
                        // VkDescriptorSet desc_set = (VkDescriptorSet)drawCommand->GetTexID();
                        // vkCmdBindDescriptorSets(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, bd->PipelineLayout,
                        // 0, 1, &desc_set, 0, nullptr);

                        // Draw
                        // CmdDrawIndexed(uint32_t indexCount,
                        //     uint32_t instanceCount,
                        //     uint32_t firstIndex,
                        //     size_t vertexOffset,
                        //     uint32_t firstInstance)
                        cmdList->CmdDrawIndexed(drawCommand->ElemCount, 1, drawCommand->IdxOffset + globalIndexOffset,
                                                drawCommand->VtxOffset + globalVertexOffset, 0);
                    }
                }
                globalIndexOffset += list->IdxBuffer.Size;
                globalVertexOffset += list->VtxBuffer.Size;
            }

            // Reset clipping rect
            cmdList->CmdSetScissor(NovelRT::Maths::GeoVector2F::Zero(),
                                   NovelRT::Maths::GeoVector2F(drawData->DisplaySize.x, drawData->DisplaySize.y));
            cmdList->CmdEndRenderPass();
        }

        ~ImGuiUIProvider() final
        {
            ImGui::DestroyContext(_imguiContext);
        }
    };
}