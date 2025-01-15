#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsProvider.hpp>
#include <NovelRT/Graphics/IGraphicsSurface.hpp>

namespace NovelRT::PluginManagement
{
    template <typename TBackend>
    class IGraphicsPluginProvider;
}

namespace NovelRT::Graphics
{
    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsSurfaceContext
    {
    public:
        using BackendSurfaceContextType = typename GraphicsBackendTraits<TBackend>::SurfaceContextType;

    private:
        std::shared_ptr<BackendSurfaceContextType> _implementation;
        std::shared_ptr<IGraphicsSurface> _surface;
        std::shared_ptr<GraphicsProvider<TBackend>> _provider;

        friend class NovelRT::PluginManagement::IGraphicsPluginProvider<TBackend>;

    public:
        GraphicsSurfaceContext(std::shared_ptr<BackendSurfaceContextType> implementation,
                               std::shared_ptr<IGraphicsSurface> surface,
                               std::shared_ptr<GraphicsProvider<TBackend>> provider);

        [[nodiscard]] std::shared_ptr<IGraphicsSurface> GetSurface() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsProvider<TBackend>> GetProvider() const noexcept;

        [[nodiscard]] virtual void* GetSurfaceContextHandleUntyped();

        template<typename THandleType> [[nodiscard]] THandleType GetSurfaceContextHandleAs()
        {
            return *reinterpret_cast<THandleType*>(GetSurfaceContextHandleUntyped());
        }
    };
}
