// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_INPUT_H
#define NOVELRT_EXPERIMENTAL_INPUT_H

//Input Dependencies
#include <map>
#include <string>
#include "../../LoggingService.h"
#include "../../PluginManagement/PluginManagement.h"
#include "../../Timing/Timestamp.h"

/**
 * @Brief The experimental input plugin API.
 */
namespace NovelRT::Experimental::Input
{
    class NovelKey;
    enum class KeyState;
    struct InputAction;
    class IInputService;
}

//Input Types
#include "NovelKey.h"
#include "KeyState.h"
#include "InputAction.h"
#include "IInputService.h"


#endif // NOVELRT_EXPERIMENTAL_INPUT_H
