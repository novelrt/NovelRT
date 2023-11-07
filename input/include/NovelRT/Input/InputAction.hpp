#pragma once
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#include <string>
#include <NovelRT/Input/KeyState.hpp>
#include <NovelRT/Input/NovelKey.hpp>

namespace NovelRT::Input
{
    struct InputAction
    {
        std::string actionName;
        NovelKey pairedKey;
        KeyState state = KeyState::Idle;
    };
}

