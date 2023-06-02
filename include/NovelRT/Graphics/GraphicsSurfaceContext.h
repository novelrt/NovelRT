// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_GRAPHICSSURFACECONTEXT_H
#define NOVELRT_GRAPHICS_GRAPHICSSURFACECONTEXT_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
    class GraphicsSurfaceContext
    {
    private:
        std::shared_ptr<IGraphicsSurface> _surface;
        std::shared_ptr<GraphicsProvider> _provider;

    public:
        GraphicsSurfaceContext(std::shared_ptr<IGraphicsSurface> surface, std::shared_ptr<GraphicsProvider> provider)
            : _surface(std::move(surface)), _provider(std::move(provider))
        {
            if (_surface == nullptr)
            {
                throw NovelRT::Core::Exceptions::NullPointerException("The supplied IGraphicsSurface is nullptr.");
            }

            if (_provider == nullptr)
            {
                throw NovelRT::Core::Exceptions::NullPointerException("The supplied GraphicsProvider is nullptr.");
            }
        }

        [[nodiscard]] inline std::shared_ptr<IGraphicsSurface> GetSurface() const noexcept
        {
            return _surface;
        }

        [[nodiscard]] inline std::shared_ptr<GraphicsProvider> GetProvider() const noexcept
        {
            return _provider;
        }

        [[nodiscard]] virtual void* GetSurfaceContextHandleUntyped() = 0;

        template<typename THandleType>[[nodiscard]] THandleType GetSurfaceContextHandleAs()
        {
            return *reinterpret_cast<THandleType*>(GetSurfaceContextHandleUntyped());
        }

        virtual ~GraphicsSurfaceContext() = default;
    };
}

#endif // !NOVELRT_GRAPHICS_GRAPHICSSURFACECONTEXT_H
