// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/UI/DearImGui/UI.DearImGui.h"

namespace NovelRT::UI::DearImGui
{
    ImGuiUIProvider::ImGuiUIProvider()
        : _imguiContext(nullptr),
          _state(Threading::VolatileState()),
          _logger(LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_UI))
    {
        _imguiContext = ImGui::CreateContext();

        static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
    }

    void ImGuiUIProvider::Initialise(std::shared_ptr<Windowing::IWindowingDevice> windowingDevice,
                                     std::shared_ptr<Graphics::GraphicsProvider> graphicsProvider,
                                     std::shared_ptr<Input::IInputDevice> inputDevice)
    {
        _windowingDevice = windowingDevice;
        _graphicsProvider = graphicsProvider;
        _inputDevice = inputDevice;

        // TODO: Configure various event handling using ImGui::GetIO()

        ImGui::GetMainViewport()->PlatformHandleRaw = (void*)windowingDevice->GetHandle();
    }

    void ImGuiUIProvider::BeginFrame(double deltaTime)
    {
        ImGuiIO& io = ImGui::GetIO();

        auto windowSize = _windowingDevice->GetSize();
        io.DisplaySize = ImVec2(windowSize.x, windowSize.y);

        io.DeltaTime = (float)deltaTime;

        // TODO: Update input data

        ImGui::NewFrame();
    }

    void ImGuiUIProvider::EndFrame()
    {
        ImGui::Render();

        ImDrawData* drawData = ImGui::GetDrawData();

        for (int i = 0; i < drawData->CmdListsCount; i++)
        {
        }
    }

    ImGuiUIProvider::~ImGuiUIProvider()
    {
        ImGui::DestroyContext(_imguiContext);
    }
} // namespace NovelRT::UI::DearImGui
