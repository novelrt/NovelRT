// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_CATALOGUE_H
#define NOVELRT_ECS_CATALOGUE_H

#include "ComponentCache.h"
#include "ComponentView.h"
#include "EcsUtils.h"
#include "EntityCache.h"

namespace NovelRT::Ecs
{
    class Catalogue
    {
      private:
        size_t _poolId;
        ComponentCache& _componentCache;
        EntityCache& _entityCache;
        std::vector<EntityId> _createdEntitiesThisFrame;

      public:
        Catalogue(size_t poolId, ComponentCache& componentCache, EntityCache& entityCache) noexcept;

        template <typename TComponent> [[nodiscard]] auto GetComponentView()
        {
            return ComponentView<TComponent>(_poolId, _componentCache.GetComponentBuffer<TComponent>());
        }

        template <typename... TComponents> [[nodiscard]] auto GetComponentViews()
        {
            return std::make_tuple(
                ComponentView<TComponents>(_poolId, _componentCache.GetComponentBuffer<TComponents>())...);
        }

        [[nodiscard]] EntityId CreateEntity() noexcept;

        void DeleteEntity(EntityId entity) noexcept;
    };
} // namespace NovelRT::Ecs

#endif //! NOVELRT_ECS_CATALOGUE_H