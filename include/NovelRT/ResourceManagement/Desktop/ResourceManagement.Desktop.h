// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_RESOURCEMANAGEMENT_DESKTOP_H
#define NOVELRT_RESOURCEMANAGEMENT_DESKTOP_H

// ResourceManagement Dependencies
#include "../ResourceManagement.h"
#include <png.h>
#include "../../LoggingService.h"
#include "../../Exceptions/Exceptions.h"
#include <fstream>
#include <cstdio>
#include "../../PluginManagement/PluginManagement.h"

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
