// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_DEARIMGUI_IMGUIUIPROVIDER_H
#define NOVELRT_UI_DEARIMGUI_IMGUIUIPROVIDER_H

#ifndef NOVELRT_UI_DEARIMGUI_H
#error NovelRT does not support including types explicitly by default. Please include UI.DearImGui.h instead for the UI::DearImGui namespace subset.
#endif

namespace NovelRT::UI::DearImGui
{
    class ImGuiUIProvider final : public UIProvider
    {
    private:

        ImGuiContext* _imguiContext;
        Threading::VolatileState _state;
        LoggingService _logger;

        std::shared_ptr<Windowing::IWindowingDevice> _windowingDevice;
        std::shared_ptr<Input::IInputDevice> _inputDevice;

    public:
        ImGuiUIProvider();

        [[nodiscard]] inline ImGuiContext* GetImGuiContext() const noexcept
        {
            return _imguiContext;
        }

        void Initialise(std::shared_ptr<Windowing::IWindowingDevice> windowingDevice,
                        std::shared_ptr<Input::IInputDevice> inputDevice) final;

        void BeginFrame(double deltaTime) final;

        void EndFrame() final;

        ~ImGuiUIProvider() final;
    };
}

#endif // !NOVELRT_UI_IMGUI_IMGUIUIPROVIDER_H
