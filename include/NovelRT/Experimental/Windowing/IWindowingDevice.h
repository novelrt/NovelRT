// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_IWINDOWINGDEVICE_H
#define NOVELRT_IWINDOWINGDEVICE_H

#include "../../Maths/GeoVector2F.h"
#include "../../Windowing/WindowMode.h"

namespace NovelRT::Experimental::Windowing
{
    class IWindowingDevice
    {
    public:
        virtual void Initialise(NovelRT::Windowing::WindowMode windowMode,
                                const std::string& windowTitle,
                                Maths::GeoVector2F desiredWindowSize = Maths::GeoVector2F::zero()) = 0;
        virtual void TearDown() = 0;
    };
} // namespace NovelRT::Experimental::Windowing

#endif // NOVELRT_IWINDOWINGDEVICE_H
