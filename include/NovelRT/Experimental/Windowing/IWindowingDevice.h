// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_WINDOWING_IWINDOWINGDEVICE_H
#define NOVELRT_EXPERIMENTAL_WINDOWING_IWINDOWINGDEVICE_H

#ifndef NOVELRT_EXPERIMENTAL_WINDOWING_H
#error NovelRT does not support including types explicitly by default. Please include Windowing.h instead for the Windowing namespace subset.
#endif

namespace NovelRT::Experimental::Windowing
{
    class IWindowingDevice : public Graphics::IGraphicsSurface
    {
    public:
        virtual void Initialise(NovelRT::Windowing::WindowMode windowMode, Maths::GeoVector2F desiredWindowSize) = 0;
        virtual void TearDown() noexcept = 0;
    };
} // namespace NovelRT::Experimental::Windowing

#endif // NOVELRT_EXPERIMENTAL_WINDOWING_IWINDOWINGDEVICE_H
