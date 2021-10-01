// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSADAPTERSELECTOR_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSADAPTERSELECTOR_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class IGraphicsAdapterSelector
    {
    public:
        [[nodiscard]] virtual std::shared_ptr<GraphicsAdapter> GetDefaultRecommendedAdapter(
            const std::shared_ptr<GraphicsProvider>& provider,
            const std::shared_ptr<GraphicsSurfaceContext>& surfaceContext) const = 0;

        virtual ~IGraphicsAdapterSelector() = default;
    };
} 

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSADAPTERSELECTOR_H
