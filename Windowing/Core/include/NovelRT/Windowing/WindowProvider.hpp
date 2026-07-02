#pragma once
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsProvider.hpp>
#include <NovelRT/Graphics/IGraphicsSurface.hpp>
#include <NovelRT/Maths/GeoVector2F.hpp>
#include <NovelRT/Windowing/VideoModeData.hpp>
#include <NovelRT/Windowing/WindowMode.hpp>

#include <string>
#include <vector>

namespace NovelRT::Windowing
{
    template<typename TBackend>
    class WindowProvider final : public Graphics::IGraphicsSurface
    {
    public:
        WindowProvider() = delete;
        ~WindowProvider() noexcept final = default;

        [[nodiscard]] std::vector<VideoModeData> GetAllVideoModeData();

        void CreateWindow(NovelRT::Windowing::WindowMode windowMode, Maths::GeoVector2F desiredWindowSize);

        void ProcessAllMessages();

        [[nodiscard]] bool IsVisible() const noexcept;
        [[nodiscard]] bool ShouldClose() const noexcept;
        [[nodiscard]] std::string GetWindowTitle() const noexcept;
        [[nodiscard]] const char* GetClipboardText() const;
        [[nodiscard]] NovelRT::Maths::GeoVector2F GetWindowScale() const noexcept;
        void SetClipboardText(const std::string& text) const;
        void SetWindowTitle(const std::string& newTitle);
        void Close();

        template<typename TGraphicsBackend>
        std::shared_ptr<Graphics::GraphicsProvider<TGraphicsBackend>> CreateGraphicsProvider(bool enableDebugMode);
    };
}
