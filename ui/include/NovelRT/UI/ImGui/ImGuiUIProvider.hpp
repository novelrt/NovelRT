#pragma once
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/UIProvider.hpp>
#include <NovelRT/Threading/Threading.h>
#include <imgui.h>

using namespace NovelRT::Graphics;
using namespace NovelRT::Graphics::Vulkan;


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
        std::shared_ptr<Graphics::GraphicsTexture<Vulkan::VulkanGraphicsBackend>> _texture2D;

    public:
        ImGuiUIProvider();

        [[nodiscard]] inline ImGuiContext* GetImGuiContext() const noexcept
        {
            return _imguiContext;
        }

        void Initialise(std::shared_ptr<Windowing::IWindowingDevice> windowingDevice,
                        std::shared_ptr<Input::IInputDevice> inputDevice,
                        std::shared_ptr<Graphics::GraphicsDevice<Vulkan::VulkanGraphicsBackend>> graphicsDevice) final;

        void BeginFrame(double deltaTime) final;

        void EndFrame() final;

        ~ImGuiUIProvider() final;
    };
}