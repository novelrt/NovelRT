// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_RESOURCEMANAGEMENT_DESKTOP_H
#define NOVELRT_RESOURCEMANAGEMENT_DESKTOP_H

// ResourceManagement Dependencies
#include "../../Core/Core.h"
#include "../../PluginManagement/PluginManagement.h"
#include "../ResourceManagement.h"
#include <cstdio>
#include <fstream>
#include <png.h>
#include <sndfile.h>

namespace NovelRT::ResourceManagement::Desktop
{
    class DesktopResourceLoader;
    class DesktopResourceManagementPluginProvider;
    struct ImageData;
}

// clang-format off
#include "DesktopResourceLoader.h"
#include "DesktopResourceManagementPluginProvider.h"
#include "ImageData.h"
// clang-format on

#endif // NOVELRT_RESOURCEMANAGEMENT_DESKTOP_H
