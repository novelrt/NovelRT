// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs
{
    EntityGraphView::EntityGraphView(Catalogue& catalogue,
                                     EntityId owningEntity,
                                     EntityGraphComponent component) noexcept
        : _catalogue(catalogue),
          _owningEntity(owningEntity),
          _component(component),
          _childrenChanges([&]() {
              if (_component.childrenStartNode == std::numeric_limits<EntityId>::max())
              {
                  _component.childrenStartNode = _catalogue.CreateEntity();
                  EntityGraphComponent newComponent{};
                  newComponent.parent = _owningEntity;
                  _externalChanges.emplace(_component.childrenStartNode,
                                           EntityGraphView(_catalogue, _component.childrenStartNode, newComponent));
              }

              return LinkedEntityListView(_component.childrenStartNode, _catalogue);
          }),
          _hasBeenCommitted(false)
    {
    }

    EntityGraphView::~EntityGraphView()
    {
        if (!_hasBeenCommitted)
        {
            Commit();
        }
    }

    std::vector<std::reference_wrapper<EntityGraphView>> EntityGraphView::GetOriginalChildren()
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

    EntityGraphView& EntityGraphView::AddInsertChildInstruction(EntityId newChildEntity)
    {
        auto view = _catalogue.GetComponentView<EntityGraphComponent>();
        EntityGraphComponent component{};

        if (_externalChanges.find(newChildEntity) == _externalChanges.end())
        {
            component = view.TryGetComponent(newChildEntity).value();
            _externalChanges.emplace(newChildEntity, EntityGraphView(_catalogue, newChildEntity, component));
        }

        if (component.parent != std::numeric_limits<EntityId>::max() &&
            _externalChanges.find(component.parent) == _externalChanges.end())
        {
            _externalChanges.emplace(
                component.parent, EntityGraphView(_catalogue, _component.parent, view.GetComponent(component.parent)));
            auto& returnView = _externalChanges.at(component.parent);
            returnView.AddRemoveChildInstruction(newChildEntity);
            component.parent = _owningEntity;
        }

        auto& graphView = _externalChanges.at(newChildEntity);
        graphView.GetRawComponentData().parent = _owningEntity;
        _childrenChanges.getActual().AddInsertAtBackInstruction(newChildEntity);

        if (_component.childrenStartNode == std::numeric_limits<EntityId>::max())
        {
            _component.childrenStartNode = newChildEntity;
        }

        return graphView;
    }

    EntityGraphView& EntityGraphView::AddRemoveChildInstruction(EntityId childToRemove)
    {
        auto [entityGraphView, linkedListView] =
            _catalogue.GetComponentViews<EntityGraphComponent, LinkedEntityListNodeComponent>();
        EntityGraphComponent component{};

        if (_externalChanges.find(childToRemove) == _externalChanges.end())
        {
            component = entityGraphView.GetComponent(childToRemove);
            _externalChanges.emplace(childToRemove, EntityGraphView(_catalogue, childToRemove, component));
        }

        auto& childGraphView = _externalChanges.at(childToRemove);
        component = childGraphView.GetRawComponentData();

        if (component.parent != _owningEntity)
        {
            throw Exceptions::NotSupportedException(
                "The provided entity is not a child of the entity that this entityGraphView manages.");
        }

        childGraphView.GetRawComponentData().parent = std::numeric_limits<EntityId>::max();
        _childrenChanges.getActual().AddRemoveNodeInstruction(childToRemove);
        auto optionalNodeAtBeginning = _childrenChanges.getActual().TryGetNewNodeAtBeginning();

        if (_component.childrenStartNode == childToRemove)
        {
            _component.childrenStartNode = optionalNodeAtBeginning.value_or(std::numeric_limits<EntityId>::max());
        }

        return childGraphView;
    }

    void EntityGraphView::Commit()
    {
        if (_hasBeenCommitted)
        {
            return;
        }

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
}
