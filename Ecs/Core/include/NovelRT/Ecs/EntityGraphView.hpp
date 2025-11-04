#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Components/EntityGraphComponent.hpp>
#include <NovelRT/Ecs/EcsUtils.hpp>
#include <NovelRT/Ecs/LinkedEntityListView.hpp>
#include <NovelRT/Utilities/Lazy.hpp>

#include <limits>
#include <map>

namespace NovelRT::Ecs
{
    class Catalogue;

    class EntityGraphView
    {
    private:
        Catalogue* _catalogue;
        EntityId _owningEntity;
        Components::EntityGraphComponent _component;
        Utilities::Lazy<LinkedEntityListView> _childrenChanges;
        std::map<EntityId, EntityGraphView> _externalChanges;
        bool _hasBeenCommitted;

    public:
        EntityGraphView(Catalogue& catalogue, EntityId owningEntity, Components::EntityGraphComponent component) noexcept;

        EntityGraphView(EntityGraphView&& other) noexcept = default;
        EntityGraphView& operator=(EntityGraphView&& other) noexcept = default;

        ~EntityGraphView();

        [[nodiscard]] inline EntityId GetRawEntityId() const noexcept
        {
            return _owningEntity;
        }

        [[nodiscard]] inline bool HasParent() const noexcept
        {
            return _component.parent != std::numeric_limits<EntityId>::max();
        }

        [[nodiscard]] inline bool HasChildren() const noexcept
        {
            return _component.childrenStartNode != std::numeric_limits<EntityId>::max();
        }

        [[nodiscard]] inline Components::EntityGraphComponent& GetRawComponentData() noexcept
        {
            return _component;
        }

        [[nodiscard]] inline const Components::EntityGraphComponent& GetRawComponentData() const noexcept
        {
            return _component;
        }

        [[nodiscard]] std::vector<std::reference_wrapper<EntityGraphView>> GetOriginalChildren();

        EntityGraphView& AddInsertChildInstruction(EntityId newChildEntity);
        EntityGraphView& AddRemoveChildInstruction(EntityId childToRemove);
        void Commit();
    };
}
