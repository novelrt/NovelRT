// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_ECSUTILS_H
#define NOVELRT_ECS_ECSUTILS_H

#include <vector>
#include <cstdint>
#include "../Atom.h"

namespace NovelRT::Ecs
{
    using EntityId = Atom;
    using ComponentTypeId = Atom;
   
    template <typename TComponent>
    ComponentTypeId GetComponentTypeId()
    {
        static const Atom id = Atom::getNextComponentTypeId();
        return id;
    }
}

#endif //!NOVELRT_ECS_ECSUTILS_H