#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsSurfaceKind.hpp>
#include <NovelRT/Maths/GeoVector2F.hpp>
#include <NovelRT/Utilities/Event.hpp>
#include <NovelRT/Windowing/WindowMode.hpp>
#include <NovelRT/Windowing/WindowProvider.hpp>

#include <memory>
#include <string>

// TODO: Figure out if this is required
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace NovelRT::Windowing::Glfw
{
    struct GlfwWindowingBackend;
}

namespace NovelRT::Windowing
{
    template<>
    class WindowProvider<Glfw::GlfwWindowingBackend> final : public Graphics::IGraphicsSurface
    {
    public:
        struct CursorPositionEventArgs
        {
            double x = 0;
            double y = 0;
        };

        struct ButtonChangeEventArgs
        {
            int32_t key = 0;
            int32_t action = 0;
        };

        Utilities::Event<CursorPositionEventArgs> CursorMoved;
        Utilities::Event<ButtonChangeEventArgs> MouseButtonClicked;
        Utilities::Event<ButtonChangeEventArgs> KeyboardButtonChanged;

    private:
        GLFWwindow* _window;
        std::string _currentTitle;

    public:
        WindowProvider(NovelRT::Windowing::WindowMode windowMode, Maths::GeoVector2F desiredWindowSize);
        ~WindowProvider() noexcept final;

        template<typename TBackend>
        std::shared_ptr<Graphics::GraphicsProvider<TBackend>> CreateGraphicsProvider(bool enableDebugMode);

        void ProcessAllMessages();

        [[nodiscard]] bool IsVisible() const noexcept;
        [[nodiscard]] bool ShouldClose() const noexcept;

        [[nodiscard]] std::string GetWindowTitle() const noexcept;
        void SetWindowTitle(const std::string& newTitle);

        [[nodiscard]] Maths::GeoVector2F GetSize() const noexcept final;
        [[nodiscard]] void* GetHandle() const noexcept final;
        [[nodiscard]] void* GetContextHandle() const noexcept final;
        [[nodiscard]] Graphics::GraphicsSurfaceKind GetKind() const noexcept final;
    };
}
