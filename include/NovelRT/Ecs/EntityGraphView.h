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
        Utilities::Lazy<LinkedEntityListView> _childrenChanges;
        std::map<EntityId, EntityGraphView> _externalChanges;
        bool _hasBeenCommitted;

    public:
        EntityGraphView(Catalogue& catalogue, EntityId owningEntity, EntityGraphComponent component) noexcept
            : _catalogue(catalogue),
              _owningEntity(owningEntity),
              _component(component),
              _childrenChanges(
                  [&]()
                  {
                      if (_component.childrenStartNode == std::numeric_limits<EntityId>::max())
                      {
                          _component.childrenStartNode = _catalogue.CreateEntity();
                          EntityGraphComponent newComponent{};
                          newComponent.parent = _owningEntity;
                          _externalChanges.emplace(
                              _component.childrenStartNode,
                              EntityGraphView(_catalogue, _component.childrenStartNode, newComponent));
                      }

                      return LinkedEntityListView(_component.childrenStartNode, _catalogue);
                  }),
              _hasBeenCommitted(false)
        {
        }

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

        [[nodiscard]] inline std::vector<std::reference_wrapper<EntityGraphView>> GetOriginalChildren()
        {
            auto view = _catalogue.GetComponentView<EntityGraphComponent>();

            std::vector<std::reference_wrapper<EntityGraphView>> returnVec{};

            if (_component.childrenStartNode == std::numeric_limits<EntityId>::max())
            {
                return returnVec;
            }

            for (EntityId child : _childrenChanges.getActual())
            {
                if (_externalChanges.find(child) == _externalChanges.end())
                {
                    _externalChanges.emplace(child, EntityGraphView(_catalogue, child, view.GetComponentUnsafe(child)));
                }

                returnVec.emplace_back(std::reference_wrapper<EntityGraphView>(_externalChanges.at(child)));
            }

            return returnVec;
        }

        EntityGraphView& AddInsertChildInstruction(EntityId newChildEntity)
        {
            auto view = _catalogue.GetComponentView<EntityGraphComponent>();
            EntityGraphComponent component{};

            if (_externalChanges.find(newChildEntity) == _externalChanges.end())
            {
                unused(view.TryGetComponent(newChildEntity, component));
                _externalChanges.emplace(newChildEntity, EntityGraphView(_catalogue, newChildEntity, component));
            }

            if (component.parent != std::numeric_limits<EntityId>::max() &&
                _externalChanges.find(component.parent) == _externalChanges.end())
            {
                _externalChanges.emplace(component.parent, EntityGraphView(_catalogue, _component.parent,
                                                                           view.GetComponent(component.parent)));
                auto& returnView = _externalChanges.at(component.parent);
                returnView.AddRemoveChildInstruction(newChildEntity);
                component.parent = _owningEntity;
            }

            auto& graphView = _externalChanges.at(newChildEntity);
            graphView.GetRawComponentData().parent = _owningEntity;
            _childrenChanges.getActual().AddInsertAtBackInstruction(newChildEntity);
            return graphView;
        }

        EntityGraphView& AddRemoveChildInstruction(EntityId childToRemove)
        {
            auto view = _catalogue.GetComponentView<EntityGraphComponent>();
            EntityGraphComponent component{};

            if (_externalChanges.find(childToRemove) == _externalChanges.end())
            {
                component = view.GetComponent(childToRemove);
                _externalChanges.emplace(childToRemove, EntityGraphView(_catalogue, childToRemove, component));
            }

            auto& childGraphView = _externalChanges.at(childToRemove);
            component = childGraphView.GetRawComponentData();

            if (component.parent != _owningEntity)
            {
                throw Exceptions::NotSupportedException(
                    "The provided entity is not a child of the entity that this view manages.");
            }

            childGraphView.GetRawComponentData().parent = std::numeric_limits<EntityId>::max();
            _childrenChanges.getActual().AddRemoveNodeInstruction(childToRemove);
        }

        void Commit()
        {
            _hasBeenCommitted = true;
            for (auto [entity, view] : _externalChanges)
            {
                view.Commit();
            }

            auto view = _catalogue.GetComponentView<EntityGraphComponent>();

            if (_childrenChanges.isCreated())
            {
                _childrenChanges.getActual().Commit();
            }

            view.PushComponentUpdateInstruction(_owningEntity, _component);
        }

        ~EntityGraphView()
        {
            Commit();
        }
    };
}

#endif // NOVELRT_ENTITYGRAPHVIEW_H
