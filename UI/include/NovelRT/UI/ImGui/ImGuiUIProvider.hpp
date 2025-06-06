#pragma once
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAccessMode.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElement.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResourceKind.hpp>
#include <NovelRT/Graphics/GraphicsPipelineVisibility.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>
#include <NovelRT/Graphics/ShaderProgramVisibility.hpp>
#include <NovelRT/Input/InputProvider.hpp>
#include <NovelRT/Logging/BuiltInLogSections.hpp>
#include <NovelRT/Utilities/Macros.hpp>
#include <NovelRT/Utilities/Paths.hpp>
#include <NovelRT/Utilities/Span.hpp>
#include <NovelRT/Windowing/WindowProvider.hpp>

#include <array>
#include <fstream>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include <imgui.h>

using namespace NovelRT::Graphics;
using namespace NovelRT::Input;

namespace NovelRT::UI::ImGui
{

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

    template<typename TGraphicsBackend, typename TInputBackend, typename TWindowingBackend>
    class ImGuiUIProvider final
        : public std::enable_shared_from_this<ImGuiUIProvider<TGraphicsBackend, TInputBackend, TWindowingBackend>>
    {
    private:
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

        inline void LoadFontFile(const std::string& name, std::filesystem::path relativeFontTarget, int32_t pixelSize)
        {
            std::filesystem::path finalPath =
                NovelRT::Utilities::GetExecutableDirPath() / "Resources" / "Fonts" / relativeFontTarget;
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

            ImFontConfig config{};
            config.FontDataOwnedByAtlas = false;
            config.FontData = buffer.data();
            config.FontDataSize = fileSize;
            config.SizePixels = static_cast<float>(pixelSize);
            name.copy(config.Name, std::string::npos, 0);

            ImGuiIO& io = ::ImGui::GetIO();
            ImFont* font = io.Fonts->AddFont(&config);
            _fontCache.emplace(std::make_pair(name, font));
        }

        struct CachedBufferObject
        {
            std::shared_ptr<Graphics::GraphicsBuffer<TGraphicsBackend>> buffer;
            uint32_t frameLifetime;
        };

        struct CachedDescriptorSetObject
        {
            std::shared_ptr<Graphics::GraphicsDescriptorSet<TGraphicsBackend>> descriptorSet;
            uint32_t frameLifetime;
        };

        struct TexInfo
        {
            std::shared_ptr<GraphicsTexture<TGraphicsBackend>> texture;
            std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TGraphicsBackend>> region;
        };

        std::shared_ptr<Windowing::WindowProvider<TWindowingBackend>> _windowProvider;
        std::shared_ptr<Input::InputProvider<TInputBackend>> _inputProvider;
        std::shared_ptr<Graphics::GraphicsDevice<TGraphicsBackend>> _graphicsDevice;
        std::shared_ptr<Graphics::GraphicsMemoryAllocator<TGraphicsBackend>> _memoryAllocator;
        bool _showMetricsWindow;

        std::map<std::string, ImFont*> _fontCache;
        std::unordered_map<ImTextureID, TexInfo> _textureMap;
        std::vector<CachedBufferObject> _bufferCache;
        std::vector<CachedDescriptorSetObject> _descriptorSetCache;

        std::shared_ptr<ImGuiContext> _imguiContext;
        LoggingService _logger;

        bool _drawEnabled = false;
        ImDrawData* _cachedDrawData = nullptr;

        NovelRT::Input::InputAction _mouseInputAction;

        std::shared_ptr<GraphicsPipeline<TGraphicsBackend>> _pipeline;
        std::shared_ptr<GraphicsPipelineSignature<TGraphicsBackend>> _pipelineSignature;

        std::shared_ptr<GraphicsBuffer<TGraphicsBackend>> _currentVertexBuffer;
        std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TGraphicsBackend>> _currentVertexBufferRegion;
        std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TGraphicsBackend>> _currentIndexBufferRegion;

        inline void UploadFontData()
        {
            uint8_t* pixels;
            int32_t width, height;
            auto& io = ::ImGui::GetIO();
            io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

            GraphicsBufferCreateInfo bufferCreateInfo{};
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::Write;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Read;
            bufferCreateInfo.size = 64 * 1024 * 4;

            // Create Texture Staging Buffer
            auto textureStagingBuffer = _memoryAllocator->CreateBuffer(bufferCreateInfo);

            // Load shader files for ImGui
            auto vertImguiShader = LoadSpv("imgui_vert.spv");
            auto pixelImguiShader = LoadSpv("imgui_frag.spv");

            auto context = _graphicsDevice->GetCurrentContext();

            // Begin commands
            std::shared_ptr<Graphics::GraphicsCmdList<TGraphicsBackend>> cmdList = context->BeginFrame();

            // Define elements that make up vertex shader
            std::vector<GraphicsPipelineInputElement> elements{
                GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F),
                                             GraphicsPipelineInputElementKind::Position, 8),
                GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F),
                                             GraphicsPipelineInputElementKind::Normal, 8),
                GraphicsPipelineInputElement(typeid(ImU32), GraphicsPipelineInputElementKind::Colour, sizeof(ImU32))};

            // Because we use push constants, define them here
            std::vector<GraphicsPushConstantRange> pushConstants{
                GraphicsPushConstantRange{ShaderProgramVisibility::Vertex, 0, sizeof(float) * 4}};

            std::vector<GraphicsPipelineInput> inputs{GraphicsPipelineInput(elements)};
            std::vector<GraphicsPipelineResource> resources{
                GraphicsPipelineResource(GraphicsPipelineResourceKind::Texture, ShaderProgramVisibility::Pixel)};
            // Create pipeline signature
            _pipelineSignature = _graphicsDevice->CreatePipelineSignature(GraphicsPipelineBlendFactor::SrcAlpha,
                                                                          GraphicsPipelineBlendFactor::OneMinusSrcAlpha,
                                                                          inputs, resources, pushConstants);
            auto imVertProg = _graphicsDevice->CreateShaderProgram("main", ShaderProgramKind::Vertex, vertImguiShader);
            auto imPixProg = _graphicsDevice->CreateShaderProgram("main", ShaderProgramKind::Pixel, pixelImguiShader);

            // Create pipeline
            _pipeline = _graphicsDevice->CreatePipeline(_pipelineSignature, imVertProg, imPixProg, true);

            // Create the texture
            auto textureCreateInfo = GraphicsTextureCreateInfo{GraphicsTextureAddressMode::Repeat,
                                                               GraphicsTextureKind::TwoDimensional,
                                                               GraphicsResourceAccess::None,
                                                               GraphicsResourceAccess::ReadWrite,
                                                               static_cast<uint32_t>(width),
                                                               static_cast<uint32_t>(height),
                                                               1,
                                                               GraphicsMemoryRegionAllocationFlags::None,
                                                               TexelFormat::R8G8B8A8_UNORM};
            auto texture2D = _memoryAllocator->CreateTexture(textureCreateInfo);

            // Allocate region based on size of texture
            auto texture2DRegion = texture2D->Allocate(texture2D->GetSize(), 4);

            // Create a staging buffer region for texture
            auto stagingBufferRegion = textureStagingBuffer->Allocate(texture2D->GetSize(), 4);
            auto textureData = textureStagingBuffer->template Map<uint32_t>(stagingBufferRegion.get());

            // Write the data over before copying
            memcpy(textureData.data(), pixels, (width * height) * sizeof(char) * 4);
            textureStagingBuffer->UnmapAndWrite(stagingBufferRegion.get());

            // Set texture ID so that ImGui can refer back to proper id during render
            io.Fonts->SetTexID(0);

            // Send the data to GPU
            cmdList->CmdBeginTexturePipelineBarrierLegacyVersion(texture2D.get());
            cmdList->CmdCopy(texture2D.get(), stagingBufferRegion.get());
            cmdList->CmdEndTexturePipelineBarrierLegacyVersion(texture2D.get());

            context->EndFrame();
            _graphicsDevice->Signal(context.get());
            _graphicsDevice->WaitForIdle();
            context->GetFence()->Reset();

            _textureMap[0] = {std::move(texture2D), std::move(texture2DRegion)};
        }

    public:
        ImGuiUIProvider(std::shared_ptr<Windowing::WindowProvider<TWindowingBackend>> windowProvider,
                        std::shared_ptr<Input::InputProvider<TInputBackend>> inputProvider,
                        std::shared_ptr<Graphics::GraphicsDevice<TGraphicsBackend>> graphicsDevice,
                        std::shared_ptr<Graphics::GraphicsMemoryAllocator<TGraphicsBackend>> memoryAllocator,
                        bool debugMode = false)
            : _windowProvider(std::move(windowProvider)),
              _inputProvider(std::move(inputProvider)),
              _graphicsDevice(std::move(graphicsDevice)),
              _memoryAllocator(std::move(memoryAllocator)),
              _showMetricsWindow(debugMode),

              _fontCache(),
              _bufferCache(),
              _descriptorSetCache(),

              _imguiContext(nullptr),
              _logger(LoggingService(NovelRT::Logging::CONSOLE_LOG_GFX))
        {
            ::IMGUI_CHECKVERSION();

            _imguiContext = std::shared_ptr<ImGuiContext>{::ImGui::CreateContext(), ::ImGui::DestroyContext};
            auto& io = ::ImGui::GetIO();
            ::ImGui::StyleColorsDark();
            LoadFontFile(std::string("default"), "Raleway-Regular.ttf", 20);

            io.IniFilename = NULL;
            io.BackendPlatformName = "NovelRT";
            io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
            io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
            io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;
            io.GetClipboardTextFn = &ImGui_GetClipboardText;
            io.SetClipboardTextFn = &ImGui_SetClipboardText;
            io.BackendRendererName = "NovelRT";

            ::ImGui::GetMainViewport()->PlatformHandleRaw = (void*)_windowProvider->GetHandle();
            auto windowSize = _windowProvider->GetSize();
            io.DisplaySize = ImVec2(windowSize.x, windowSize.y);

            if ((windowSize.x > 0) && (windowSize.y > 0))
            {
                io.DisplayFramebufferScale = ImVec2(1, 1);
            }

            UploadFontData();

            auto* action = _inputProvider->FindInputActionForKey("LeftMouseButton");
            if (!action)
                throw std::runtime_error("Missing input action for LMB");

            _mouseInputAction = *action;
        }

        ~ImGuiUIProvider() = default;

        void BeginFrame(float deltaTime)
        {
            auto& io = ::ImGui::GetIO();
            auto windowSize = _windowProvider->GetSize();
            io.DisplaySize = ImVec2(windowSize.x, windowSize.y);

            if ((windowSize.x > 0) && (windowSize.y > 0))
            {
                io.DisplayFramebufferScale = ImVec2(1, 1);
            }

            io.DeltaTime = deltaTime;

            auto mousePos = _inputProvider->GetRawMousePosition();
            io.AddMousePosEvent(mousePos.x, mousePos.y);
            auto state = _inputProvider->GetKeyState(_mouseInputAction.actionName);
            if (state == KeyState::KeyDown || state == KeyState::KeyDownHeld)
            {
                io.AddMouseButtonEvent(0, true);
            }
            else
            {
                io.AddMouseButtonEvent(0, false);
            }

            ::ImGui::NewFrame();
            if (_showMetricsWindow)
            {
                ::ImGui::ShowMetricsWindow(&_showMetricsWindow);
            }
        }

        void EndFrame()
        {
            ::ImGui::Render();

            for (auto it = _bufferCache.begin(); it != _bufferCache.end();)
            {
                it->frameLifetime--;
                if (it->frameLifetime <= 0)
                {
                    it = _bufferCache.erase(it);
                }
                else
                {
                    it++;
                }
            }

            for (auto it = _descriptorSetCache.begin(); it != _descriptorSetCache.end();)
            {
                it->frameLifetime--;
                if (it->frameLifetime <= 0)
                {
                    it = _descriptorSetCache.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }

        void UploadToGPU(std::shared_ptr<Graphics::GraphicsCmdList<TGraphicsBackend>> currentCmdList)
        {
            ImDrawData* drawData = ::ImGui::GetDrawData();

            if (drawData->TotalVtxCount <= 0)
            {
                _drawEnabled = false;
                return;
            }
            _drawEnabled = true;

            auto graphicsContext = _graphicsDevice->GetCurrentContext();
            auto graphicsSurface = _graphicsDevice->GetSurface();

            size_t vertexSize = drawData->TotalVtxCount * sizeof(ImDrawVert);
            size_t indexSize = drawData->TotalIdxCount * sizeof(ImDrawIdx);

            // Create buffers
            GraphicsBufferCreateInfo bufferCreateInfo{};
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::Write;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Read;
            bufferCreateInfo.size = vertexSize;
            auto vertexStagingBuffer = _memoryAllocator->CreateBuffer(bufferCreateInfo);
            _bufferCache.emplace_back(CachedBufferObject{vertexStagingBuffer, 10});

            bufferCreateInfo.bufferKind = GraphicsBufferKind::Vertex;
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::None;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Write;
            auto vertexBuffer = _memoryAllocator->CreateBuffer(bufferCreateInfo);
            _bufferCache.emplace_back(CachedBufferObject{vertexBuffer, 10});

            // Create index buffer + staging
            bufferCreateInfo.bufferKind = GraphicsBufferKind::Default;
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::Write;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Read;
            bufferCreateInfo.size = indexSize;
            auto indexStagingBuffer = _memoryAllocator->CreateBuffer(bufferCreateInfo);
            _bufferCache.emplace_back(CachedBufferObject{indexStagingBuffer, 10});

            bufferCreateInfo.bufferKind = GraphicsBufferKind::Index;
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::None;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Write;
            auto indexBuffer = _memoryAllocator->CreateBuffer(bufferCreateInfo);
            _bufferCache.emplace_back(CachedBufferObject{indexBuffer, 10});

            // Allocate buffers
            auto vertexBufferRegion = vertexBuffer->Allocate(vertexSize, 4);
            auto vertexStageBufferRegion = vertexStagingBuffer->Allocate(vertexSize, 4);
            auto indexBufferRegion = indexBuffer->Allocate(indexSize, 4);
            auto indexStageBufferRegion = indexStagingBuffer->Allocate(indexSize, 4);

            // Map vertex buffer to region
            auto pVertexBuffer = vertexStagingBuffer->template Map<ImDrawVert>(vertexBufferRegion.get());
            auto pVertPtr = pVertexBuffer.data();
            // Map index buffer to region
            auto pIndexbuffer = indexStagingBuffer->template Map<ImDrawIdx>(indexBufferRegion.get());
            auto pIdxPtr = pIndexbuffer.data();

            // Slamjam the vertex buffer and index buffer data into their regions
            for (int i = 0; i < drawData->CmdListsCount; i++)
            {
                ImDrawList* list = drawData->CmdLists[i];

                // Copy vertex and index data
                memcpy(pVertPtr, list->VtxBuffer.Data, list->VtxBuffer.Size * sizeof(ImDrawVert));
                memcpy(pIdxPtr, list->IdxBuffer.Data, list->IdxBuffer.Size * sizeof(ImDrawIdx));

                pVertPtr += list->VtxBuffer.Size;
                pIdxPtr += list->IdxBuffer.Size;
            }

            // Unmap and copy to GPU
            vertexStagingBuffer->UnmapAndWrite(vertexBufferRegion.get());
            indexStagingBuffer->UnmapAndWrite(indexBufferRegion.get());
            currentCmdList->CmdCopy(vertexBufferRegion.get(), vertexStageBufferRegion.get());
            currentCmdList->CmdCopy(indexBufferRegion.get(), indexStageBufferRegion.get());

            // Sync the commands so that we can prevent data issues
            currentCmdList->CmdPipelineBufferBarrier(vertexBuffer.get(), GraphicsMemoryAccessMode::TransferWrite,
                                                     GraphicsMemoryAccessMode::VertexAttributeRead,
                                                     GraphicsPipelineVisibility::Transfer,
                                                     GraphicsPipelineVisibility::VertexInput);
            currentCmdList->CmdPipelineBufferBarrier(
                indexBuffer.get(), GraphicsMemoryAccessMode::TransferWrite, GraphicsMemoryAccessMode::IndexRead,
                GraphicsPipelineVisibility::Transfer, GraphicsPipelineVisibility::VertexInput);

            _currentIndexBufferRegion = indexBufferRegion;
            _currentVertexBuffer = vertexBuffer;
            _currentVertexBufferRegion = vertexBufferRegion;
            _cachedDrawData = drawData;
        }

        void Draw(std::shared_ptr<Graphics::GraphicsCmdList<TGraphicsBackend>> currentCmdList)
        {
            if (!_drawEnabled)
                return;
            auto drawData = _cachedDrawData;

            auto graphicsContext = _graphicsDevice->GetCurrentContext();
            auto graphicsSurface = _graphicsDevice->GetSurface();
            float surfaceWidth = graphicsSurface->GetWidth();
            float surfaceHeight = graphicsSurface->GetHeight();

            int32_t globalVertexOffset = 0;
            int32_t globalIndexOffset = 0;

            ImVec2 clippingOffset = drawData->DisplayPos;
            ImVec2 clippingScale = drawData->FramebufferScale;

            // Bind the Vertex Buffers and the index buffer region
            std::array<const GraphicsBuffer<TGraphicsBackend>*, 1> buffers{_currentVertexBuffer.get()};
            auto currentOffset = _currentVertexBufferRegion->GetOffset();
            auto currentIndexBufferRegion = _currentIndexBufferRegion;
            std::array<size_t, 1> offsets{currentOffset};

            ViewportInfo viewportInfoStruct{};
            viewportInfoStruct.x = 0;
            viewportInfoStruct.y = 0;
            viewportInfoStruct.width = surfaceWidth;
            viewportInfoStruct.height = surfaceHeight;
            viewportInfoStruct.minDepth = 0.0f;
            viewportInfoStruct.maxDepth = 1.0f;

            currentCmdList->CmdSetViewport(viewportInfoStruct);

            currentCmdList->CmdBindPipeline(_pipeline.get());
            currentCmdList->CmdBindVertexBuffers(0, 1, buffers, offsets);
            currentCmdList->CmdBindIndexBuffer(_currentIndexBufferRegion.get(), IndexType::UInt16);

            float scale[2];
            scale[0] = 2.0f / drawData->DisplaySize.x;
            scale[1] = 2.0f / drawData->DisplaySize.y;
            float translate[2];
            translate[0] = -1.0f - drawData->DisplayPos.x * scale[0];
            translate[1] = -1.0f - drawData->DisplayPos.y * scale[1];
            NovelRT::Utilities::Span<float> scaleSpan(scale);
            NovelRT::Utilities::Span<float> translateSpan(translate);

            currentCmdList->CmdPushConstants(_pipelineSignature.get(), ShaderProgramVisibility::Vertex, 0,
                                             NovelRT::Utilities::SpanCast<uint8_t>(scaleSpan));
            currentCmdList->CmdPushConstants(_pipelineSignature.get(), ShaderProgramVisibility::Vertex,
                                             sizeof(float) * 2, NovelRT::Utilities::SpanCast<uint8_t>(translateSpan));

            currentCmdList->CmdSetScissor(
                NovelRT::Maths::GeoVector2F::Zero(),
                NovelRT::Maths::GeoVector2F(drawData->DisplaySize.x, drawData->DisplaySize.y));

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
                        currentCmdList->CmdSetScissor(NovelRT::Maths::GeoVector2F(clippingMin.x, clippingMin.y),
                                                      NovelRT::Maths::GeoVector2F((clippingMax.x - clippingMin.x),
                                                                                  (clippingMax.y - clippingMin.y)));

                        // Bind DescriptorSet with font or user texture

                        auto it = _textureMap.find(drawCommand->GetTexID());
                        if (it == _textureMap.end())
                            continue; // TODO: this should probably warn

                        std::vector<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, TGraphicsBackend>>>
                            inputResourceRegions{it->second.region};

                        // Specify the descriptor set data
                        auto descriptorSetData = _pipeline->CreateDescriptorSet();
                        descriptorSetData->AddMemoryRegionsToInputs(inputResourceRegions);
                        descriptorSetData->UpdateDescriptorSetData();
                        graphicsContext->RegisterDescriptorSetForFrame(_pipelineSignature, descriptorSetData);
                        _descriptorSetCache.emplace_back(CachedDescriptorSetObject{descriptorSetData, 10});

                        // Bind the descriptor set
                        std::array<const GraphicsDescriptorSet<TGraphicsBackend>*, 1> descriptorData{
                            descriptorSetData.get()};

                        currentCmdList->CmdBindDescriptorSets(descriptorData);

                        currentCmdList->CmdDrawIndexed(drawCommand->ElemCount, 1,
                                                       drawCommand->IdxOffset + globalIndexOffset,
                                                       drawCommand->VtxOffset + globalVertexOffset, 0);
                    }
                }
                globalIndexOffset += list->IdxBuffer.Size;
                globalVertexOffset += list->VtxBuffer.Size;
            }

            // Reset clipping rect as per imgui
            currentCmdList->CmdSetScissor(
                NovelRT::Maths::GeoVector2F::Zero(),
                NovelRT::Maths::GeoVector2F(drawData->DisplaySize.x, drawData->DisplaySize.y));
        }
    };
}
