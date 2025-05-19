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
    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsSurfaceContext
    {
    public:
        using BackendSurfaceContextType = typename GraphicsBackendTraits<TBackend>::SurfaceContextType;

    private:
        std::unique_ptr<BackendSurfaceContextType> _implementation;
        std::shared_ptr<IGraphicsSurface> _surface;
        std::shared_ptr<GraphicsProvider<TBackend>> _provider;

        friend class NovelRT::PluginManagement::IGraphicsPluginProvider<TBackend>;

    public:
        GraphicsSurfaceContext(std::unique_ptr<BackendSurfaceContextType> implementation,
                               std::shared_ptr<IGraphicsSurface> surface,
                               std::shared_ptr<GraphicsProvider<TBackend>> provider)
            : _implementation(std::move(implementation))
            , _surface(std::move(surface))
            , _provider(std::move(provider))
        {
            if (_surface == nullptr)
            {
                throw Exceptions::NullPointerException("The supplied IGraphicsSurface is nullptr.");
            }

            if (_provider == nullptr)
            {
                throw Exceptions::NullPointerException("The supplied GraphicsProvider is nullptr.");
            }
        }

        [[nodiscard]] BackendSurfaceContextType* GetImplementation() const noexcept
        {
            return _implementation.get();
        }

        [[nodiscard]] IGraphicsSurface* GetSurface() const noexcept
        {
            return _surface.get();
        }
        [[nodiscard]] GraphicsProvider<TBackend>* GetProvider() const noexcept
        {
            return _provider.get();
        }

        [[nodiscard]] void* GetSurfaceContextHandleUntyped()
        {
            return _implementation->GetSurfaceContextHandleUntyped();
        }

        template<typename THandleType> [[nodiscard]] THandleType GetSurfaceContextHandleAs()
        {
            return *reinterpret_cast<THandleType*>(GetSurfaceContextHandleUntyped());
        }
    };
}
