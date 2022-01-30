// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INPUT_H
#define NOVELRT_INPUT_H

//Input Dependencies
#include "NovelRT/LoggingService.h"
#include "NovelRT/Maths/Maths.h"
#include "NovelRT/Utilities/Event.h"
#include "NovelRT/Timing/Timestamp.h"
#include <map>
#include <string>

/**
 * @Brief The input plugin API.
 */
namespace NovelRT::Input
{
    class NovelKey;
    enum class KeyState;
    struct InputAction;
    class IInputDevice;
}

//Input Types
#include "NovelKey.h"
#include "KeyState.h"
#include "InputAction.h"
#include "IInputDevice.h"


#endif // NOVELRT_INPUT_H
