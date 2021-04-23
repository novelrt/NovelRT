// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs
{
    std::unordered_map<std::type_index, ComponentTypeId>& GetComponentTypeIds() noexcept
    {
        static std::unordered_map<std::type_index, ComponentTypeId> _componentTypeIds =
            std::unordered_map<std::type_index, ComponentTypeId>();
        return _componentTypeIds;
    }
} // namespace NovelRT::Ecs
