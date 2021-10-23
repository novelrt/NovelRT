// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PLUGINMANAGEMENT_H
#define NOVELRT_PLUGINMANAGEMENT_H

// PluginManagement Dependencies
#include "../Experimental/Graphics/Graphics.h"
#include "../Experimental/Windowing/Windowing.h"
#include "../ResourceManagement/ResourceManagement.h"
#include "../Audio/Audio.h"

/**
 * @brief The NovelRT engine plugin system for loading modules such as Vulkan, GLFW3, OpenAL, and more.
 */
namespace NovelRT::PluginManagement
{
    class DefaultPluginSelector;
    class IResourceManagementPluginProvider;
    class IGraphicsPluginProvider;
    class IWindowingPluginProvider;
    class IAudioPluginProvider;
}

// clang-format off
#include "IResourceManagementPluginProvider.h"
#include "IGraphicsPluginProvider.h"
#include "IWindowingPluginProvider.h"
#include "IAudioPluginProvider.h"
#include "TemporaryFnPtrs.h" //TODO: THIS HEADER IS A HACK - DELETE AFTER MVP
#include "DefaultPluginSelector.h"
// clang-format on

#endif // NOVELRT_PLUGINMANAGEMENT_H
