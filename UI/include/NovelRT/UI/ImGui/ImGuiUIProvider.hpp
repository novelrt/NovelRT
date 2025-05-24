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
#include <NovelRT/Input/IInputDevice.hpp>
#include <NovelRT/Input/InputAction.hpp>
#include <fstream>
#include <imgui.h>

using namespace NovelRT::Graphics;
using namespace NoveRT::Input;

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
        struct CachedBufferObject
        {
            Graphics::GraphicsBuffer<TBackend> buffer;
            uint32_t frameLifeTime;
        }

        ImGuiContext* _imguiContext;
        ImGuiIO& _io;
        LoggingService _logger;
        bool _showMetricsWindow = false;

        NovelRT::Input::InputAction mouseInputAction;

        std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>> _texture2DRegion;
        std::shared_ptr<Windowing::IWindowingDevice> _windowingDevice;
        std::shared_ptr<Input::IInputDevice> _inputDevice;
        std::shared_ptr<Graphics::GraphicsDevice<TBackend>> _graphicsDevice;
        std::shared_ptr<Graphics::GraphicsMemoryAllocator<TBackend>> _memoryAllocator;
        std::shared_ptr<GraphicsPipeline<TBackend>> _pipeline;
        std::shared_ptr<GraphicsPipelineSignature<TBackend>> _pipelineSignature;
        std::map<std::string, ImFont*> _fontCache{};
        std::vector<CachedBufferObject> _bufferCache{};

        
        inline void LoadFontFile(std::string& name, std::filesystem::path relativeFontTarget, int32_t pixelSize)
        {
            std::filesystem::path finalPath =
                NovelRT::Utilities::Misc::getExecutableDirPath() / "Resources" / "Shaders" / relativeTarget;

            ImGuiIO& io = ImGui::GetIO();
            ImFont* font = io.Fonts->AddFontFromFileTTF(finalPath.c_str(), pixelSize);
            _fontCache.emplace(std::make_pair(name, font));
        }

        inline void UploadFontData()
        {
            uint8_t* pixels;
            int32_t width, height;
            io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

            GraphicsBufferCreateInfo bufferCreateInfo{};
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::Write;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Read;
            bufferCreateInfo.size = 64 * 1024 * 4;

            // Create Texture Staging Buffer
            auto textureStagingBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);

            //Load shader files for ImGui
            auto vertImguiShader = LoadSpv("imgui_vert.spv");
            auto pixelImguiShader = LoadSpv("imgui_frag.spv");

            auto context = _graphicsDevice->GetCurrentContext();

            //Begin commands
            std::shared_ptr<Graphics::GraphicsCmdList<TBackend>> cmdList = context->BeginFrame();

            //Define elements that make up vertex shader
            std::vector<GraphicsPipelineInputElement> elements{
                GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F), GraphicsPipelineInputElementKind::Position,
                                     8),
                GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F), GraphicsPipelineInputElementKind::Normal, 8),
                GraphicsPipelineInputElement(typeid(ImU32), GraphicsPipelineInputElementKind::Colour, sizeof(ImU32))};
            
                //Because we use push constants, define them here
            std::vector<GraphicsPushConstantRange> pushConstants{
                GraphicsPushConstantRange{ShaderProgramVisibility::Vertex, 0, sizeof(float) * 4}};


            std::vector<GraphicsPipelineInput> inputs{GraphicsPipelineInput(elements)};
            std::vector<GraphicsPipelineResource> resources{
                GraphicsPipelineResource(GraphicsPipelineResourceKind::Texture, ShaderProgramVisibility::Pixel)};
            //Create pipeline signature
            auto pipelineSignature = _graphicsDevice->CreatePipelineSignature(
                GraphicsPipelineBlendFactor::SrcAlpha, GraphicsPipelineBlendFactor::OneMinusSrcAlpha, inputs, resources, pushConstants);
            _pipelineSignature = pipelineSignature;
            auto imVertProg = _graphicsDevice->CreateShaderProgram("main", ShaderProgramKind::Vertex, vertImguiShader);
            auto imPixProg = _graphicsDevice->CreateShaderProgram("main", ShaderProgramKind::Pixel, pixelImguiShader);

            //Create pipeline
            auto pipeline = _graphicsDevice->CreatePipeline(pipelineSignature, imVertProg, imPixProg, true);
            _pipeline = pipeline;

            //Create the texture
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
            std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>> texture2DRegion =
                texture2D->Allocate(texture2D->GetSize(), 4);

            // Create a staging buffer region for texture
            auto stagingBufferRegion = textureStagingBuffer->Allocate(texture2D->GetSize(), 4);
            auto textureData = textureStagingBuffer->Map<uint32_t>(texture2DRegion);

            //Write the data over before copying
            memcpy(textureData.data(), pixels, (width * height) * sizeof(char) * 4);
            textureStagingBuffer->UnmapAndWrite(texture2DRegion);
            
            //Set texture ID so that ImGui can refer back to proper id during render
            io.Fonts->SetTexID(reinterpret_cast<ImTextureID>(&texture2DRegion));
            _texture2DRegion = texture2DRegion;

            //Send the data to GPU
            cmdList->CmdBeginTexturePipelineBarrierLegacyVersion(texture2D);
            cmdList->CmdCopy(texture2D, stagingBufferRegion);
            cmdList->CmdEndTexturePipelineBarrierLegacyVersion(texture2D);
            context->EndFrame();
            _graphicsDevice->Signal(context->GetFence());
            _graphicsDevice->WaitForIdle();
            context->GetFence()->Reset();
        }

    public:
        ImGuiUIProvider()
            : _imguiContext(nullptr),
              _logger(LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_GFX))
        {
            IMGUI_CHECKVERSION();
            
            _imguiContext = ImGui::CreateContext();
            _io = ImGui::GetIO();
            ImGui::StyleColorsDark();
            LoadFontFile("default", "Raleway-Regular.ttf", 20);
            
            _io.IniFilename = NULL;
            _io.BackendPlatformUserData = (void*)this;
            _io.BackendPlatformName = "NovelRT";
            _io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
            _io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
            _io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;
            _io.ClipboardUserData = (void*)this;
            _io.GetClipboardTextFn = &ImGui_GetClipboardText;
            _io.SetClipboardTextFn = &ImGui_SetClipboardText;
            _io.BackendRendererUserData = (void*)this;
            _io.BackendRendererName = typeid(TBackend).name();
        }

        void Initialise(std::shared_ptr<Windowing::IWindowingDevice> windowingDevice,
                        std::shared_ptr<Input::IInputDevice> inputDevice,
                        std::shared_ptr<Graphics::GraphicsDevice<TBackend>> graphicsDevice,
                        std::shared_ptr<Graphics::GraphicsMemoryAllocator<TBackend>> memoryAllocator,
                        bool debugMode = false) final
        {
            _windowingDevice = windowingDevice;
            _inputDevice = inputDevice;
            _graphicsDevice = graphicsDevice;
            _memoryAllocator = memoryAllocator;

            _showMetricsWindow = debugMode;
            
            ImGui::GetMainViewport()->PlatformHandleRaw = (void*)windowingDevice->GetHandle();

            UploadFontData();

            auto mappings = _inputDevice->GetAllMappings();
            auto lmbKey = _inputDevice->GetAvailableKey("LeftMouseButton");
            for(auto& mapping : mappings)
            {
                if(mapping.pairedKey == lmbKey)
                {
                    mouseInputAction = mapping;
                    break;
                }
            }
        }

        void BeginFrame(float deltaTime) final
        {
            _io = ImGui::GetIO();
            auto windowSize = _windowingDevice->GetSize();
            _io.DisplaySize = ImVec2(windowSize.x, windowSize.y);

            if ((windowSize.x > 0) && (windowSize.y > 0))
            {
                io.DisplayFramebufferScale = ImVec2(1, 1);
            }

            io.DeltaTime = deltaTime;

            auto mousePos = _inputDevice->GetRawMousePosition();
            io.AddMousePosEvent(mousePos.x, mousePos.y);
            auto state = _inputDevice->GetKeyState(mouseInputAction.actionName);
            if (state == KeyState::KeyDown || state == KeyState::KeyDownHeld)
            {
                io.AddMouseButtonEvent(0, true);
            }
            else
            {
                io.AddMouseButtonEvent(0, false);
            }

            ImGui::NewFrame();
        }

        void EndFrame() final
        {
            ImGui::Render();
        }

        void Draw(std::shared_ptr<Graphics::GraphicsCmdList<TBackend>> currentCmdList) final
        {
            _io = ImGui::GetIO();
            ImDrawData* drawData = ImGui::GetDrawData();

            if (drawData->TotalVtxCount <= 0)
                return;

            size_t vertexSize = drawData->TotalVtxCount * sizeof(ImDrawVert);
            size_t indexSize = drawData->TotalIdxCount * sizeof(ImDrawIdx);

            // Create buffers
            GraphicsBufferCreateInfo bufferCreateInfo{};
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::Write;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Read;
            bufferCreateInfo.size = vertexSize;
            auto vertexStagingBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);
            _bufferCache.emplace_back(CachedBufferObject{*vertexStagingBuffer.get(), 10});

            bufferCreateInfo.bufferKind = GraphicsBufferKind::Vertex;
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::None;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Write;
            auto vertexBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);
            _bufferCache.emplace_back(CachedBufferObject{*vertexBuffer.get(), 10});

            // Create index buffer + staging
            bufferCreateInfo.bufferKind = GraphicsBufferKind::Default;
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::Write;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Read;
            bufferCreateInfo.size = indexSize;
            auto indexStagingBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);
            _bufferCache.emplace_back(CachedBufferObject{*indexStagingBuffer.get(), 10});

            bufferCreateInfo.bufferKind = GraphicsBufferKind::Index;
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::None;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Write;
            auto indexBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);
            _bufferCache.emplace_back(CachedBufferObject{*indexBuffer.get(), 10});

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
            vertexStagingBuffer->UnmapAndWrite(vertexBufferRegion);
            indexStagingBuffer->UnmapAndWrite(indexBufferRegion);
            currentCmdList->CmdCopy(vertexBufferRegion, vertexStageBufferRegion);
            currentCmdList->CmdCopy(indexBufferRegion, indexStageBufferRegion);

            
        }

        ~ImGuiUIProvider() final
        {
            ImGui::DestroyContext(_imguiContext);
        }
    };
}