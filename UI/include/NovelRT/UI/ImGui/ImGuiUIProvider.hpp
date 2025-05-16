#pragma once
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/UIProvider.hpp>
#include <imgui.h>
#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElement.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResourceKind.hpp>
#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>
#include <NovelRT/Graphics/ShaderProgramVisibility.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Maths/Maths.h>
#include <imgui.h>

using namespace NovelRT::Graphics;

namespace NovelRT::UI::DearImGui
{
    struct TexturedVertex
    {
        NovelRT::Maths::GeoVector3F Position;
        NovelRT::Maths::GeoVector2F UV;
    };

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

            GraphicsBufferCreateInfo bufferCreateInfo{};
            bufferCreateInfo.cpuAccessKind = GraphicsResourceAccess::Write;
            bufferCreateInfo.gpuAccessKind = GraphicsResourceAccess::Read;
            bufferCreateInfo.size = 64 * 1024;

            auto vertexStagingBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);

            bufferCreateInfo.size = 64 * 1024 * 4;

            auto textureStagingBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);

            auto vertexBuffer = memoryAllocator->CreateBuffer(bufferCreateInfo);

            std::shared_ptr<GraphicsCmdList<TBackend>> cmdList = graphicsContext->BeginFrame();

            std::vector<GraphicsPipelineInputElement> elements{
                GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector3F),
                                             GraphicsPipelineInputElementKind::Position, 12),
                GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F),
                                             GraphicsPipelineInputElementKind::TextureCoordinate, 8)};

            std::vector<GraphicsPipelineInput> inputs{GraphicsPipelineInput(elements)};
            std::vector<GraphicsPipelineResource> resources{
                GraphicsPipelineResource(GraphicsPipelineResourceKind::Texture, ShaderProgramVisibility::Pixel)};

            auto vertexBufferRegion = vertexBuffer->Allocate(sizeof(TexturedVertex) * 3, 16);
            auto stagingBufferRegion = vertexStagingBuffer->Allocate(sizeof(TexturedVertex) * 3, 16);

            auto pVertexBuffer = vertexStagingBuffer->Map<TexturedVertex>(vertexBufferRegion);

            pVertexBuffer[0] =
                TexturedVertex{NovelRT::Maths::GeoVector3F(0, 1, 0), NovelRT::Maths::GeoVector2F(0.5f, 0.0f)};
            pVertexBuffer[1] =
                TexturedVertex{NovelRT::Maths::GeoVector3F(1, -1, 0), NovelRT::Maths::GeoVector2F(1.0f, 1.0f)};
            pVertexBuffer[2] =
                TexturedVertex{NovelRT::Maths::GeoVector3F(-1, -1, 0), NovelRT::Maths::GeoVector2F(0.0f, 1.0f)};

            vertexStagingBuffer->UnmapAndWrite(vertexBufferRegion);
            cmdList->CmdCopy(vertexBufferRegion, stagingBufferRegion);

            // auto future = new FutureResult<TextureInfo>(nullptr, TextureInfo{});
            // future = defaultRenderingSystem->LoadTextureDataRaw("ImguiAtlas", gsl::span<unsigned char>(pixels, width
            // * height), width, height, gen());

            // defaultRenderingSystem->ForceVertexTextureFutureResolution(); // force the atlas to be on the GPU before
            // game launch io.Fonts->SetTexID(static_cast<void*>(texture2d));

            // auto textureStagingBuffer = graphicsDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
            //     Graphics::GraphicsBufferKind::Default, Graphics::GraphicsResourceAccess::Write,
            //     Graphics::GraphicsResourceAccess::Read, 64 * 1024 * 4);

            _texture2D = memoryAllocator->CreateTexture2DRepeatGpuWriteOnly(width, height);
            std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>> texture2DRegion =
                _texture2D->Allocate(_texture2D->GetSize(), 4);
            auto textureStagingBufferRegion = textureStagingBuffer->Allocate(_texture2D->GetSize(), 4);
            auto pTextureData = textureStagingBuffer->Map<uint32_t>(texture2DRegion);

            // _texture2D = graphicsContext->GetDevice()->GetMemoryAllocator()->CreateTextureWithDefaultArguments(
            //     Graphics::GraphicsTextureAddressMode::Repeat, Graphics::GraphicsTextureKind::TwoDimensional,
            //     Graphics::GraphicsResourceAccess::None, Graphics::GraphicsResourceAccess::Write, width, height);
            // Graphics::GraphicsMemoryRegion<Graphics::GraphicsResource> texture2DRegion;
            // texture2DRegion = _texture2D->Allocate(_texture2D->GetSize(), 4);
            // auto pTextureData = textureStagingBuffer->Map<uint32_t>(texture2DRegion);

            memcpy(pTextureData.data(), pixels, width * height);
            textureStagingBuffer->UnmapBytesAndWrite(0, textureStagingBuffer->GetSize());
            cmdList->CmdBeginTexturePipelineBarrierLegacyVersion(_texture2D);
            cmdList->CmdCopy(_texture2D, textureStagingBufferRegion);
            cmdList->CmdEndTexturePipelineBarrierLegacyVersion(_texture2D);

            graphicsContext->EndFrame();
            graphicsDevice->Signal(graphicsContext->GetFence());
            graphicsDevice->WaitForIdle();

            // auto ptr = //new Graphics::GraphicsMemoryRegion<Graphics::GraphicsResource<TBackend>>();

            io.Fonts->SetTexID(reinterpret_cast<ImTextureID>(&_texture2D));
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

        ~ImGuiUIProvider() final
        {
            ImGui::DestroyContext(_imguiContext);
        }
    };
}