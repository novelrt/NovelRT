// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_ECSUTILS_H
#define NOVELRT_ECS_ECSUTILS_H

#include <vector>

namespace NovelRT::Ecs
{
    using EntityId = uint64_t;
    using ComponentTypeId = uint64_t;
    using ComponentComposition = std::vector<ComponentTypeId>;
}

#endif //!NOVELRT_ECS_ECSUTILS_H