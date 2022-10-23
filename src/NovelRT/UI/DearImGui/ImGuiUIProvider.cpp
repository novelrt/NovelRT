// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/UI/DearImGui/UI.DearImGui.h"

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
          _logger(LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_UI))
    {
        IMGUI_CHECKVERSION();

        _imguiContext = ImGui::CreateContext();

        static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
    }

    void ImGuiUIProvider::Initialise(std::shared_ptr<Windowing::IWindowingDevice> windowingDevice,
                                     std::shared_ptr<Input::IInputDevice> inputDevice)
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

        // TODO: Upload font data and call io.Fonts->SetTexID();
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
