// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PERSISTENCE_H
#define NOVELRT_PERSISTENCE_H

// Persistence dependencies
#include <map>
#include <string>
#include <gsl/span>
#include <sstream>
#include "../Ecs/Ecs.h"
//#include "../../jsoncons/json.hpp"
//#include "../../jsoncons_ext/bson/bson.hpp"

namespace NovelRT::Persistence
{
    enum class BinaryDataType : uint32_t;
    struct BinaryMemberMetadata;
    struct BinaryPackage;
    class Chapter;
    class IPersistable;
}

// clang-format off

#include "BinaryDataType.h"
#include "BinaryMemberMetadata.h"
#include "BinaryPackage.h"
#include "IPersistable.h"
#include "Chapter.h"

// clang-format on

#endif // NOVELRT_PERSISTENCE_H
