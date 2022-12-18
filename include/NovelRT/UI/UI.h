// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_H
#define NOVELRT_UI_H

// UI dependencies
#include <memory>
#include <cstdint>
#include "NovelRT/LoggingService.h"
#include "NovelRT/Graphics/Graphics.h"
#include "NovelRT/Windowing/Windowing.h"
#include "NovelRT/Utilities/Event.h"
//#include "NovelRT/PluginManagement/PluginManagement.h"
/**
 * @brief The experimental UI plugin API.
 */
namespace NovelRT::UI
{
    enum class UIElementState : uint32_t;
    class IUIElement;
    class IUITextbox;
    class IUIProvider;
}



// UI types
#include "UIElementState.h"
#include "IUIElement.h"
#include "IUITextbox.h"
#include "IUIProvider.h"

#endif // !NOVELRT_UI_H
