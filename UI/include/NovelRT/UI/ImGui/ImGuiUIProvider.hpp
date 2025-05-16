#pragma once
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/UIProvider.hpp>
#include <imgui.h>

using namespace NovelRT::Graphics;


namespace NovelRT::UI::DearImGui
{
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
        ImGuiUIProvider();

        [[nodiscard]] inline ImGuiContext* GetImGuiContext() const noexcept
        {
            return _imguiContext;
        }

        void Initialise(std::shared_ptr<Windowing::IWindowingDevice> windowingDevice,
                        std::shared_ptr<Input::IInputDevice> inputDevice,
                        std::shared_ptr<Graphics::GraphicsProvider<TBackend>> graphicsProvider,
                        std::shared_ptr<Graphics::GraphicsDevice<TBackend>> graphicsDevice,
                        std::shared_ptr<Graphics::GraphicsMemoryAllocator<TBackend>> memoryAllocator) final;

        void BeginFrame(double deltaTime) final;

        void EndFrame() final;

        ~ImGuiUIProvider() final;
    };
}