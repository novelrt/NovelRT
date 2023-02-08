// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_H
#define NOVELRT_UI_H

// UI dependencies
#include <memory>
#include <cstdint>
#include "../LoggingService.h"
#include "../Maths/Maths.h"
#include "../Graphics/Graphics.h"
#include "../Windowing/Windowing.h"
#include "../Utilities/Event.h"
#include "../Input/Input.h"

/**
 * @brief The experimental UI plugin API.
 */
namespace NovelRT::UI
{
    enum class UIElementState : uint32_t;
    enum class UIElementType : uint32_t;
    struct UIElement;
    struct UIPanel;
    struct UIButton;
    struct UIFontMetadata;
    class UIProvider;
}



// UI types
// clang-format off

#include "UIElementState.h"
#include "UIElementType.h"
#include "UIElement.h"
#include "UIPanel.h"
#include "UIButton.h"
#include "UIFontMetadata.h"
#include "UIProvider.h"

// clang-format on

#endif // !NOVELRT_UI_H
