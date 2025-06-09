#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsProvider.hpp>
#include <NovelRT/Graphics/IGraphicsSurface.hpp>

#include <string>

namespace NovelRT::Windowing
{
    template<typename TBackend>
    class WindowProvider : public Graphics::IGraphicsSurface
    {
    public:
        WindowProvider() = delete;
        ~WindowProvider() = default;

        void ProcessAllMessages();

        [[nodiscard]] bool IsVisible() const noexcept;
        [[nodiscard]] bool ShouldClose() const noexcept;

        [[nodiscard]] std::string GetWindowTitle() const noexcept;
        void SetWindowTitle(const std::string& newTitle);

        template<typename TGraphicsBackend>
        std::shared_ptr<Graphics::GraphicsProvider<TGraphicsBackend>> CreateGraphicsProvider(bool enableDebugMode);
    };
}
