// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_UI_H
#define NOVELRT_ECS_UI_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

#include <NovelRT/UI/UI.h>
#include <map>

namespace NovelRT::Ecs::UI
{
    class UISystem;
}

#include "UISystem.h"

#endif // NOVELRT_ECS_UI_H
