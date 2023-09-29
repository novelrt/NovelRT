// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INPUT_H
#define NOVELRT_INPUT_H

// Input Dependencies
#include "NovelRT/LoggingService.h"
#include "NovelRT/Maths/Maths.h"
#include "NovelRT/Timing/Timestamp.h"
#include "NovelRT/Utilities/Misc.h"
#include "NovelRT/Windowing/Windowing.h"
#include <map>
#include <string>
#include <functional>

/**
 * @brief The input plugin API.
 */
namespace NovelRT::Input
{
    enum class KeyState;
    class KeyStateFrameChangeLog;
    class IInputDevice;
    class NovelKey;
    struct InputAction;
}

// clang-format off
// Input Types
#include "KeyState.h"
#include "KeyStateFrameChangeLog.h"
#include "NovelKey.h"
#include "InputAction.h"
#include "IInputDevice.h"
// clang-format on

#endif // NOVELRT_INPUT_H
