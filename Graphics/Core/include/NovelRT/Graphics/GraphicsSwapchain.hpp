#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/TexelFormat.hpp>
#include <memory>

namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsSwapchainImage;

    template<typename TBackend>
    class GraphicsSwapchain : public GraphicsDeviceObject<TBackend>
    {
    public:
        GraphicsSwapchain() = delete;
        ~GraphicsSwapchain() = delete;
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsSwapchain<TBackend>> shared_from_this();

        [[nodiscard]] Graphics::TexelFormat GetFormat();

        [[nodiscard]] std::shared_ptr<GraphicsSwapchainImage<TBackend>> AcquireNextImage();
        [[nodiscard]] TexelFormat GetFormat();
        [[nodiscard]] bool Present();
    };
}
