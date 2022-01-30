// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PLUGINMANAGEMENT_H
#define NOVELRT_PLUGINMANAGEMENT_H

// PluginManagement Dependencies
#include "../Graphics/Graphics.h"
#include "../ResourceManagement/ResourceManagement.h"
#include "../Windowing/Windowing.h"
#include "../Input/Input.h"

/**
 * @brief The NovelRT engine plugin system for loading modules such as Vulkan, GLFW3, OpenAL, and more.
 */
namespace NovelRT::PluginManagement
{
    class DefaultPluginSelector;
    class IResourceManagementPluginProvider;
    class IGraphicsPluginProvider;
    class IWindowingPluginProvider;
    class IInputPluginProvider;
}

// clang-format off

#include "IInputPluginProvider.h"
#include "IResourceManagementPluginProvider.h"
#include "IGraphicsPluginProvider.h"
#include "IWindowingPluginProvider.h"
#include "TemporaryFnPtrs.h" //TODO: THIS HEADER IS A HACK - DELETE AFTER MVP
#include "DefaultPluginSelector.h"
// clang-format on

#endif // NOVELRT_PLUGINMANAGEMENT_H
