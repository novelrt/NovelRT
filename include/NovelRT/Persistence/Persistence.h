// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PERSISTENCE_H
#define NOVELRT_PERSISTENCE_H

// Persistence dependencies
#include <map>
#include <string>
#include <gsl/span>
#include "../Ecs/Ecs.h"
#include "../ThirdParty/jsoncons/json.hpp"
#include "../ThirdParty/jsoncons_ext/bson/bson.hpp"

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
