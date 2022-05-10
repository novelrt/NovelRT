// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PERSISTENCE_H
#define NOVELRT_PERSISTENCE_H

// Persistence dependencies
#include "../Ecs/Ecs.h"
#include "../ResourceManagement/ResourceManagement.h"
#include <gsl/span>
#include <map>
#include <sstream>
#include <string>

namespace NovelRT::Persistence
{
    class Chapter;
    class IPersistable;
}

// clang-format off

#include "IPersistable.h"
#include "Chapter.h"

// clang-format on

#endif // NOVELRT_PERSISTENCE_H
