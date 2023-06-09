// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ENTITYGRAPHVIEW_H
#define NOVELRT_ENTITYGRAPHVIEW_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    class EntityGraphView
    {
    private:
        Catalogue& _catalogue;
        EntityId _owningEntity;
        EntityGraphComponent _component;
        NovelRT::Core::Utilities::Lazy<LinkedEntityListView> _childrenChanges;
        std::map<EntityId, EntityGraphView> _externalChanges;
        bool _hasBeenCommitted;

    public:
        EntityGraphView(Catalogue& catalogue, EntityId owningEntity, EntityGraphComponent component) noexcept;
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

        [[nodiscard]] inline EntityGraphComponent& GetRawComponentData() noexcept
        {
            return _component;
        }

        [[nodiscard]] inline const EntityGraphComponent& GetRawComponentData() const noexcept
        {
            return _component;
        }

        [[nodiscard]] std::vector<std::reference_wrapper<EntityGraphView>> GetOriginalChildren();

        EntityGraphView& AddInsertChildInstruction(EntityId newChildEntity);
        EntityGraphView& AddRemoveChildInstruction(EntityId childToRemove);
        void Commit();
    };
}

#endif // NOVELRT_ENTITYGRAPHVIEW_H
