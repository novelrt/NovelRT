#include <NovelRT/Graphics/GraphicsSurfaceContext.hpp>

namespace NovelRT::Graphics
{
    template<typename TBackend>
    GraphicsSurfaceContext<TBackend>::GraphicsSurfaceContext(std::shared_ptr<BackendSurfaceContextType> implementation,
                                                             std::shared_ptr<IGraphicsSurface> surface,
                                                             std::shared_ptr<GraphicsProvider<TBackend>> provider)
        : _implementation(implementation), _surface(surface), _provider(provider)
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

    template<typename TBackend>
    std::shared_ptr<IGraphicsSurface> GraphicsSurfaceContext<TBackend>::GetSurface() const noexcept
    {
        return _surface;
    }

    template<typename TBackend>
    std::shared_ptr<GraphicsProvider<TBackend>> GraphicsSurfaceContext<TBackend>::GetProvider() const noexcept
    {
        return _provider;
    }

    template<typename TBackend> void* GraphicsSurfaceContext<TBackend>::GetSurfaceContextHandleUntyped()
    {
        return _implementation->GetSurfaceContextHandleUntyped();
    }
}