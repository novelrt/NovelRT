// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_INPUT_H
#define NOVELRT_EXPERIMENTAL_INPUT_H

/**
 * @Brief The experimental Input plugin API.
 */
namespace NovelRT::Experimental::Input
{
    class IInputDevice;
}

// Input dependencies
#include "../../Maths/GeoVector2F.h"
#include "../../Input/KeyCode.h"
#include "../../Input/KeyState.h"
#include "../../Input/KeyStateFrameChangeLog.h"
#include <cstdint>

// Input types
#include "IInputDevice.h"

#endif // NOVELRT_EXPERIMENTAL_INPUT_H
