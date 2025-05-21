#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/NullPointerException.hpp>
#include <NovelRT/Graphics/GraphicsProvider.hpp>
#include <NovelRT/Graphics/IGraphicsSurface.hpp>

#include <memory>

namespace NovelRT::PluginManagement
{
    template<typename TBackend> class IGraphicsPluginProvider;
}

namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsSurfaceContext : public std::enable_shared_from_this<GraphicsSurfaceContext<TBackend>>
    {
    public:
        GraphicsSurfaceContext() = delete;

        [[nodiscard]] IGraphicsSurface* GetSurface() const noexcept;
        [[nodiscard]] std::weak_ptr<GraphicsProvider<TBackend>> GetProvider() const noexcept;
    };
}
