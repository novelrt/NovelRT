// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_ECSUTILS_H
#define NOVELRT_ECS_ECSUTILS_H

#include "../Atom.h"
#include <cstdint>
#include <typeindex>
#include <unordered_map>

namespace NovelRT::Ecs
{
    using EntityId = NovelRT::Atom;
    using ComponentTypeId = NovelRT::Atom;

    std::unordered_map<std::type_index, ComponentTypeId>& GetComponentTypeIds() noexcept;

    /**
     * @brief Retrieves the ComponentTypeId for a given component type.
     *
     * This free function will create a new ID for the given type if one does not exist on the first call.
     *
     * @tparam TComponent The component type to get the ID for.
     * @return ComponentTypeId The numerical ID of the component type as an Atom.
     */
    template<typename TComponent> [[nodiscard]] ComponentTypeId GetComponentTypeId() noexcept
    {
        auto componentTypeId = GetComponentTypeIds()[typeid(TComponent)];
        return componentTypeId;
    }
} // namespace NovelRT::Ecs

#endif //! NOVELRT_ECS_ECSUTILS_H
