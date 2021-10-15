// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_RESOURCEMANAGEMENT_H
#define NOVELRT_RESOURCEMANAGEMENT_H

// ResourceManagement Dependencies
#include <filesystem>
#include "../Utilities/Misc.h"
#include <cstdint>
#include <vector>
#include <memory>

/**
 * @brief The APIs for managing assets and other resources that reside in persisted storage.
 */
namespace NovelRT::ResourceManagement
{
    class ResourceLoader;
}

// clang-format off
#include "ResourceLoader.h"
// clang-format on

#endif // NOVELRT_RESOURCEMANAGEMENT_H
