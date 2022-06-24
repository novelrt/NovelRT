// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_H
#define NOVELRT_UI_H

// UI dependencies
#include "NovelRT/Ecs/Ecs.h"
#include "NovelRT/Graphics/Graphics.h"
#include "NovelRT/Input/Input.h"
#include "NovelRT/Windowing/Windowing.h"
#include <memory>

/**
 * @brief The UI plugin API.
 */
namespace NovelRT::UI
{
    class UIProvider;
}

// UI types
// clang-format off

#include "UIProvider.h"

// clang-format on

#endif // !NOVELRT_UI_H
