// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_IGRAPHICSSURFACE_H
#define NOVELRT_EXPERIMENTAL_IGRAPHICSSURFACE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class IGraphicsSurface
    {
    public:
        Utilities::Event<Maths::GeoVector2F> SizeChanged;

        [[nodiscard]] virtual Maths::GeoVector2F GetSize() const noexcept = 0;

        [[nodiscard]] inline float GetWidth() const noexcept
        {
            return GetSize().x;
        }

        [[nodiscard]] inline float GetHeight() const noexcept
        {
            return GetSize().y;
        }

        [[nodiscard]] virtual void* GetHandle() const noexcept = 0;
        [[nodiscard]] virtual void* GetContextHandle() const noexcept = 0;
        [[nodiscard]] virtual GraphicsSurfaceKind GetKind() const noexcept = 0;
    };
}

#endif // !NOVELRT_EXPERIMENTAL_IGRAPHICSSURFACE_H
