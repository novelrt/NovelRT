// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/ImGui/ImGuiUIProvider.hpp>
#include <NovelRT/Utilities/Misc.h>

namespace NovelRT::UI::DearImGui
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

    ImGuiUIProvider::ImGuiUIProvider()
        : _imguiContext(nullptr),
          _state(Threading::VolatileState()),
          _logger(LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_GFX))
    {
        IMGUI_CHECKVERSION();

        _imguiContext = ImGui::CreateContext();

        static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
    }

    void ImGuiUIProvider::Initialise(std::shared_ptr<Windowing::IWindowingDevice> windowingDevice,
                                     std::shared_ptr<Input::IInputDevice> inputDevice,
                                     std::shared_ptr<Graphics::GraphicsDevice<VulkanGraphicsBackend>> graphicsDevice)
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

        /**
         *
        auto future = new FutureResult<TextureInfo>(nullptr, TextureInfo{});
        *future = defaultRenderingSystem->LoadTextureDataRaw("ImguiAtlas", gsl::span<unsigned char>(pixels, width * height), width, height, gen());
        io.Fonts->SetTexID(static_cast<void*>(future));
        defaultRenderingSystem->ForceVertexTextureFutureResolution(); // force the atlas to be on the GPU before game launch
         */

        auto graphicsContext = graphicsDevice->GetCurrentContext();

        graphicsContext->BeginFrame();
        auto textureStagingBuffer = graphicsDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
            Graphics::GraphicsBufferKind::Default, Graphics::GraphicsResourceAccess::Write, Graphics::GraphicsResourceAccess::Read, 64 * 1024 * 4);

        _texture2D = graphicsContext->GetDevice()->GetMemoryAllocator()->CreateTextureWithDefaultArguments(
            Graphics::GraphicsTextureAddressMode::Repeat, Graphics::GraphicsTextureKind::TwoDimensional,
            Graphics::GraphicsResourceAccess::None, Graphics::GraphicsResourceAccess::Write, width, height);
        Graphics::GraphicsMemoryRegion<Graphics::GraphicsResource> texture2DRegion;
        texture2DRegion = _texture2D->Allocate(_texture2D->GetSize(), 4);
        auto pTextureData = textureStagingBuffer->Map<uint32_t>(texture2DRegion);

        memcpy(pTextureData.data(), pixels, width * height);
        
        textureStagingBuffer->UnmapAndWrite(0, textureStagingBuffer->GetSize());


        graphicsContext->Copy(_texture2D, textureStagingBuffer);
        graphicsContext->EndFrame();
        graphicsDevice->Signal(graphicsContext->GetFence());
        graphicsDevice->WaitForIdle();

        auto ptr = new Graphics::GraphicsMemoryRegion<Graphics::GraphicsResource>();
        *ptr = texture2DRegion;

        io.Fonts->SetTexID(ptr);
    }

    void ImGuiUIProvider::BeginFrame(double deltaTime)
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
    }

    void ImGuiUIProvider::EndFrame()
    {
        ImGui::EndFrame();
    }

    ImGuiUIProvider::~ImGuiUIProvider()
    {
        ImGui::DestroyContext(_imguiContext);
    }
} // namespace NovelRT::UI::DearImGui