// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INPUT_H
#define NOVELRT_INPUT_H

// Input Dependencies
#include "NovelRT/LoggingService.h"
#include "NovelRT/Maths/Maths.h"
#include "NovelRT/Timing/Timestamp.h"
#include "NovelRT/Utilities/Event.h"
#include <map>
#include <string>

/**
 * @Brief The input plugin API.
 */
namespace NovelRT::Input
{
    enum class KeyState;
    class IInputDevice;
    class NovelKey;
    struct InputAction;
}

// Input Types
#include "IInputDevice.h"
#include "InputAction.h"
#include "KeyState.h"
#include "NovelKey.h"

#endif // NOVELRT_INPUT_H
