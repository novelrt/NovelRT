// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs
{
    EntityId& LinkedEntityListView::UpdateExistingChangesForAddBeforeOperation(
        EntityId& newNode,
        LinkedEntityListView::ConstIterator& nextIt,
        const ComponentView<LinkedEntityListNodeComponent>& nodeView,
        EntityId& existingNextNode)
    {
        auto nextDiffInstruction = _changes[existingNextNode];

        while (nextDiffInstruction == nodeView.GetDeleteInstructionState() || nextIt != begin())
        {
            nextIt--;
            existingNextNode = nextIt.GetCurrentEntityNode();

            if (_changes.ContainsKey(existingNextNode))
            {
                nextDiffInstruction = _changes[existingNextNode];
                continue;
            }

            break;
        }

        LinkedEntityListNodeComponent finalDiffInstructionForNext{};

        if (_changes.ContainsKey(existingNextNode))
        {
            finalDiffInstructionForNext = _changes[existingNextNode];
        }
        else if (!nodeView.TryGetComponent(existingNextNode, finalDiffInstructionForNext))
        {
            finalDiffInstructionForNext = nodeView.GetDeleteInstructionState();
        }

        auto previousIt = begin();
        EntityId existingPreviousNode = previousIt.GetCurrentEntityNode();

        while (existingPreviousNode != finalDiffInstructionForNext.previous && previousIt != end())
        {
            previousIt++;
        }

        if (_changes.ContainsKey(existingPreviousNode))
        {
            auto previousDiffInstruction = _changes[existingPreviousNode];

            while (previousDiffInstruction == nodeView.GetDeleteInstructionState() || previousIt != end())
            {
                previousIt++;
                existingPreviousNode = previousIt.GetCurrentEntityNode();

                if (_changes.ContainsKey(existingPreviousNode))
                {
                    previousDiffInstruction = _changes[existingPreviousNode];
                    continue;
                }

                break;
            }
        }

        LinkedEntityListNodeComponent finalDiffInstructionForPrevious{};

        if (_changes.ContainsKey(existingPreviousNode))
        {
            finalDiffInstructionForPrevious = _changes[existingPreviousNode];
        }
        else if (!nodeView.TryGetComponent(existingPreviousNode, finalDiffInstructionForPrevious))
        {
            finalDiffInstructionForPrevious = nodeView.GetDeleteInstructionState();
        }

        bool hasPrevious = finalDiffInstructionForPrevious != nodeView.GetDeleteInstructionState();
        bool hasNext = finalDiffInstructionForNext != nodeView.GetDeleteInstructionState();

        if (hasPrevious)
        {
            finalDiffInstructionForNext.next = newNode;

            if (_changes.ContainsKey(existingNextNode))
            {
                _changes.Insert(existingNextNode, finalDiffInstructionForNext);
            }
            else
            {
                _changes[existingNextNode] = finalDiffInstructionForNext;
            }
        }

        if (hasNext)
        {
            finalDiffInstructionForNext.previous = newNode;

            if (_changes.ContainsKey(existingNextNode))
            {
                _changes.Insert(existingNextNode, finalDiffInstructionForNext);

                if ((_newBeginPostDiff.has_value() && existingNextNode == _newBeginPostDiff.value()) ||
                    _begin == existingNextNode)
                {
                    _newTailPostDiff = newNode;
                }
            }
            else
            {
                _changes[existingNextNode] = finalDiffInstructionForNext;

                if (_begin == existingNextNode)
                {
                    _newTailPostDiff = newNode;
                }
            }
        }

        _changes.Insert(newNode,
                        LinkedEntityListNodeComponent{
                            true, hasPrevious ? existingNextNode : EntityId(std::numeric_limits<EntityId>::max()),
                            hasNext ? existingNextNode : EntityId(std::numeric_limits<EntityId>::max())});
        return existingNextNode;
    }

    EntityId& LinkedEntityListView::UpdateExistingChangesForAddAfterOperation(
        EntityId& newNode,
        LinkedEntityListView::ConstIterator& previousIt,
        const ComponentView<LinkedEntityListNodeComponent>& nodeView,
        EntityId& existingPreviousNode)
    {
        auto previousDiffInstruction = _changes[existingPreviousNode];

        while (previousDiffInstruction == nodeView.GetDeleteInstructionState() || previousIt != begin())
        {
            previousIt--;
            existingPreviousNode = previousIt.GetCurrentEntityNode();

            if (_changes.ContainsKey(existingPreviousNode))
            {
                previousDiffInstruction = _changes[existingPreviousNode];
                continue;
            }

            break;
        }

        LinkedEntityListNodeComponent finalDiffInstructionForPrevious{};

        if (_changes.ContainsKey(existingPreviousNode))
        {
            finalDiffInstructionForPrevious = _changes[existingPreviousNode];
        }
        else if (!nodeView.TryGetComponent(existingPreviousNode, finalDiffInstructionForPrevious))
        {
            finalDiffInstructionForPrevious = nodeView.GetDeleteInstructionState();
        }

        auto nextIt = begin();
        EntityId existingNextNode = nextIt.GetCurrentEntityNode();

        while (existingNextNode != finalDiffInstructionForPrevious.next && nextIt != end())
        {
            nextIt++;
        }

        if (_changes.ContainsKey(existingNextNode))
        {
            auto nextDiffInstruction = _changes[existingNextNode];

            while (nextDiffInstruction == nodeView.GetDeleteInstructionState() || nextIt != end())
            {
                nextIt++;
                existingNextNode = nextIt.GetCurrentEntityNode();

                if (_changes.ContainsKey(existingNextNode))
                {
                    nextDiffInstruction = _changes[existingNextNode];
                    continue;
                }

                break;
            }
        }

        LinkedEntityListNodeComponent finalDiffInstructionForNext{};

        if (_changes.ContainsKey(existingNextNode))
        {
            finalDiffInstructionForNext = _changes[existingNextNode];
        }
        else if (!nodeView.TryGetComponent(existingNextNode, finalDiffInstructionForNext))
        {
            finalDiffInstructionForNext = nodeView.GetDeleteInstructionState();
        }

        bool hasPrevious = finalDiffInstructionForPrevious != nodeView.GetDeleteInstructionState();
        bool hasNext = finalDiffInstructionForNext != nodeView.GetDeleteInstructionState();

        if (hasPrevious)
        {
            finalDiffInstructionForPrevious.next = newNode;

            if (_changes.ContainsKey(existingPreviousNode))
            {
                _changes.Insert(existingPreviousNode, finalDiffInstructionForPrevious);

                if ((_newTailPostDiff.has_value() && existingPreviousNode == _newTailPostDiff.value()) ||
                    _tail == existingPreviousNode)
                {
                    _newTailPostDiff = newNode;
                }
            }
            else
            {
                _changes[existingPreviousNode] = finalDiffInstructionForPrevious;

                if (_tail == existingPreviousNode)
                {
                    _newTailPostDiff = newNode;
                }
            }
        }

        if (hasNext)
        {
            finalDiffInstructionForNext.previous = newNode;

            if (_changes.ContainsKey(existingNextNode))
            {
                _changes.Insert(existingNextNode, finalDiffInstructionForNext);
            }
            else
            {
                _changes[existingNextNode] = finalDiffInstructionForNext;
            }
        }

        _changes.Insert(newNode,
                        LinkedEntityListNodeComponent{
                            true, hasPrevious ? existingPreviousNode : EntityId(std::numeric_limits<EntityId>::max()),
                            hasNext ? existingNextNode : EntityId(std::numeric_limits<EntityId>::max())});
        return existingPreviousNode;
    }

    LinkedEntityListView::LinkedEntityListView(EntityId node, Catalogue& catalogue) noexcept
        : _begin(node), _tail(_end), _hasBeenCommitted(false), _changes{}, _catalogue(catalogue)
    {
        if (_begin == std::numeric_limits<EntityId>::max())
        {
            return;
        }

        auto view = _catalogue.GetComponentView<LinkedEntityListNodeComponent>();
        LinkedEntityListNodeComponent currentBeginComponent{};

        if (!view.TryGetComponent(_begin, currentBeginComponent))
        {
            _changes.Insert(_begin, LinkedEntityListNodeComponent{});
        }
        else
        {
            while (currentBeginComponent.previous != std::numeric_limits<EntityId>::max())
            {
                _begin = currentBeginComponent.previous;
                currentBeginComponent = view.GetComponentUnsafe(_begin);
            }

            currentBeginComponent = view.GetComponentUnsafe(node);
            if (currentBeginComponent.next != std::numeric_limits<EntityId>::max())
            {
                auto currentEndComponent = view.GetComponentUnsafe(currentBeginComponent.next);

                while (currentEndComponent.next != std::numeric_limits<EntityId>::max())
                {
                    _tail = currentEndComponent.next;
                    currentEndComponent = view.GetComponentUnsafe(currentEndComponent.next);
                }
            }
        }
    }

    LinkedEntityListView::~LinkedEntityListView()
    {
        if (!_hasBeenCommitted)
        {
            Commit();
        }
    }

    void LinkedEntityListView::AddInsertBeforeIndexInstruction(size_t index, EntityId newNode)
    {
        if (index >= GetLength())
        {
            throw std::out_of_range("The specified index was out of range of the linked entity list.");
        }

        auto nextIt = begin();

        for (size_t i = 0; i < index; i++)
        {
            nextIt++;
        }

        auto nodeView = _catalogue.GetComponentView<LinkedEntityListNodeComponent>();
        EntityId existingPreviousNode = nextIt.GetCurrentEntityNode();

        if (_changes.ContainsKey(existingPreviousNode) || _changes.ContainsKey(nextIt.GetListNode().previous))
        {
            existingPreviousNode =
                UpdateExistingChangesForAddBeforeOperation(newNode, nextIt, nodeView, existingPreviousNode);
        }
        else
        {
            auto max = std::numeric_limits<EntityId>::max();
            auto nextNodeComponent = nextIt.GetListNode();
            auto nextEntityId = nextIt.GetCurrentEntityNode();
            nextIt--;
            auto previousNodeComponent = nextIt.GetListNode();
            auto previousEntityId = nextIt.GetCurrentEntityNode();

            LinkedEntityListNodeComponent newInstruction{true, previousEntityId, nextEntityId};
            _changes.Insert(newNode, newInstruction);

            previousNodeComponent.next = newNode;
            nextNodeComponent.previous = newNode;

            if (previousEntityId != max)
            {
                _changes.Insert(previousEntityId, previousNodeComponent);
            }

            if (nextEntityId != max)
            {
                _changes.Insert(nextEntityId, nextNodeComponent);
            }
        }

        if (_newTailPostDiff.has_value() && _newTailPostDiff.value() == existingPreviousNode)
        {
            _newTailPostDiff = newNode;
        }
    }

    void LinkedEntityListView::AddInsertAfterIndexInstruction(size_t index, EntityId newNode)
    {
        if (index >= GetLength())
        {
            throw std::out_of_range("The specified index was out of range of the linked entity list.");
        }

        auto previousIt = begin();

        for (size_t i = 0; i < index; i++)
        {
            previousIt++;
        }

        auto nodeView = _catalogue.GetComponentView<LinkedEntityListNodeComponent>();
        EntityId existingPreviousNode = previousIt.GetCurrentEntityNode();

        if (_changes.ContainsKey(existingPreviousNode) || _changes.ContainsKey(previousIt.GetListNode().next))
        {
            existingPreviousNode =
                UpdateExistingChangesForAddAfterOperation(newNode, previousIt, nodeView, existingPreviousNode);
        }
        else
        {
            auto max = std::numeric_limits<EntityId>::max();
            auto previousNodeComponent = previousIt.GetListNode();
            auto previousEntityId = previousIt.GetCurrentEntityNode();
            previousIt++;
            auto nextNodeComponent = previousIt.GetListNode();
            auto nextEntityId = previousIt.GetCurrentEntityNode();

            LinkedEntityListNodeComponent newInstruction{true, previousEntityId, nextEntityId};
            _changes.Insert(newNode, newInstruction);

            previousNodeComponent.next = newNode;
            nextNodeComponent.previous = newNode;

            if (previousEntityId != max)
            {
                _changes.Insert(previousEntityId, previousNodeComponent);
            }

            if (nextEntityId != max)
            {
                _changes.Insert(nextEntityId, nextNodeComponent);
            }
        }

        if (_newTailPostDiff.has_value() && _newTailPostDiff.value() == existingPreviousNode)
        {
            _newTailPostDiff = newNode;
        }
    }

    void LinkedEntityListView::AddInsertAtBackInstruction(EntityId newNode)
    {
        auto nodeView = _catalogue.GetComponentView<LinkedEntityListNodeComponent>();

        if (_newTailPostDiff.has_value())
        {
            auto& tailDiffComponent = _changes[_newTailPostDiff.value()];
            tailDiffComponent.next = newNode;
            LinkedEntityListNodeComponent newTailComponent{};
            newTailComponent.previous = _newTailPostDiff.value();
            _newTailPostDiff = newNode;
            _changes.Insert(newNode, newTailComponent);
        }
        else
        {
            EntityId finalPrevious = 0;

            if (_tail != std::numeric_limits<EntityId>::max())
            {
                auto last = nodeView.GetComponentUnsafe(_tail);
                last.next = newNode;
                _changes.Insert(_tail, last);
                finalPrevious = _tail;
            }
            else if (_newBeginPostDiff.has_value())
            {
                auto& newBeginComponent = _changes[_newBeginPostDiff.value()];
                newBeginComponent.next = newNode;
                finalPrevious = _newBeginPostDiff.value();
            }
            else if (_changes.ContainsKey(_begin))
            {
                auto& beginComponent = _changes[_begin];

                if (beginComponent != nodeView.GetDeleteInstructionState())
                {
                    beginComponent.next = newNode;
                    finalPrevious = _begin;
                }
                else
                {
                    finalPrevious = std::numeric_limits<EntityId>::max();
                }
            }
            else
            {
                auto beginComponentDiff = nodeView.GetComponentUnsafe(_begin);
                beginComponentDiff.next = newNode;
                _changes.Insert(_begin, beginComponentDiff);
                finalPrevious = _begin;
            }

            _newTailPostDiff = newNode;
            _changes.Insert(newNode,
                            LinkedEntityListNodeComponent{true, finalPrevious, std::numeric_limits<EntityId>::max()});
        }
    }

    void LinkedEntityListView::AddInsertAtFrontInstruction(EntityId newNode)
    {
        auto nodeView = _catalogue.GetComponentView<LinkedEntityListNodeComponent>();

        if (_newBeginPostDiff.has_value())
        {
            auto& beginDiffComponent = _changes[_newBeginPostDiff.value()];
            beginDiffComponent.previous = newNode;
            LinkedEntityListNodeComponent newBeginComponent{};
            newBeginComponent.next = _newBeginPostDiff.value();
            _newBeginPostDiff = newNode;
            _changes.Insert(newNode, newBeginComponent);
        }
        else
        {
            EntityId finalNext = 0;

            if (_newBeginPostDiff.has_value())
            {
                auto& begin = _changes[_newBeginPostDiff.value()];
                begin.previous = newNode;
                finalNext = _newBeginPostDiff.value();
            }
            else if (_changes.ContainsKey(_begin))
            {
                auto& beginComponent = _changes[_begin];

                if (beginComponent != nodeView.GetDeleteInstructionState())
                {
                    beginComponent.previous = newNode;
                    finalNext = _begin;
                }
                else
                {
                    finalNext = std::numeric_limits<EntityId>::max();
                }
            }
            else
            {
                auto beginComponentDiff = nodeView.GetComponentUnsafe(_begin);
                beginComponentDiff.previous = newNode;
                _changes.Insert(_begin, beginComponentDiff);
                finalNext = _begin;
                // throw Exceptions::InvalidOperationException("I can't do that dave.");
            }

            _newBeginPostDiff = newNode;
            _changes.Insert(newNode,
                            LinkedEntityListNodeComponent{true, std::numeric_limits<EntityId>::max(), finalNext});
        }
    }

    void LinkedEntityListView::AddRemoveNodeInstruction(EntityId nodeToRemove)
    {
        auto nodeView = _catalogue.GetComponentView<LinkedEntityListNodeComponent>();

        if (_changes.ContainsKey(nodeToRemove))
        {
            auto& component = _changes[nodeToRemove];
            std::optional<std::reference_wrapper<LinkedEntityListNodeComponent>> previous;
            std::optional<std::reference_wrapper<LinkedEntityListNodeComponent>> next;

            if (component.previous != std::numeric_limits<EntityId>::max() && _changes.ContainsKey(component.previous))
            {
                previous = _changes[component.previous];
            }

            if (component.next != std::numeric_limits<EntityId>::max() && _changes.ContainsKey(component.next))
            {
                next = _changes[component.next];
            }

            if (previous.has_value())
            {
                previous.value().get().next = component.next;
            }
            else if (component.previous != std::numeric_limits<EntityId>::max())
            {
                auto previousComponent = nodeView.GetComponentUnsafe(component.previous);
                _changes.Insert(component.previous,
                                LinkedEntityListNodeComponent{true, previousComponent.previous, component.next});
            }

            if (next.has_value())
            {
                next.value().get().previous = component.previous;
            }
            else if (component.next != std::numeric_limits<EntityId>::max())
            {
                auto nextComponent = nodeView.GetComponentUnsafe(component.next);
                _changes.Insert(component.next,
                                LinkedEntityListNodeComponent{true, component.previous, nextComponent.next});
            }

            if (_newBeginPostDiff.has_value() && _newBeginPostDiff.value() == nodeToRemove)
            {
                _newBeginPostDiff = component.next;
            }

            if (_newTailPostDiff.has_value() && _newTailPostDiff.value() == nodeToRemove)
            {
                _newTailPostDiff = component.previous;
            }

            if (!_newBeginPostDiff.has_value() && nodeToRemove == _begin)
            {
                if (component.next == std::numeric_limits<EntityId>::max() && _newTailPostDiff.has_value())
                {
                    _newBeginPostDiff = _newTailPostDiff;
                }
                else
                {
                    EntityId nextBeginCandidate = component.next;
                    EntityId currentBeginCandidate = 0;
                    while (nextBeginCandidate != std::numeric_limits<EntityId>::max())
                    {
                        currentBeginCandidate = nextBeginCandidate;
                        LinkedEntityListNodeComponent testComponent{};
                        if (_changes.ContainsKey(currentBeginCandidate))
                        {
                            testComponent = _changes[currentBeginCandidate];
                        }
                        else
                        {
                            unused(nodeView.TryGetComponent(currentBeginCandidate, testComponent));
                        }
                        nextBeginCandidate = testComponent.next;
                    }

                    _newBeginPostDiff = currentBeginCandidate;
                }
            }

            component = nodeView.GetDeleteInstructionState();
        }
        else if (nodeView.HasComponent(nodeToRemove) && ContainsNode(nodeToRemove))
        {
            auto component = nodeView.GetComponent(nodeToRemove);
            std::optional<std::reference_wrapper<LinkedEntityListNodeComponent>> previous;
            std::optional<std::reference_wrapper<LinkedEntityListNodeComponent>> next;

            if (component.previous != std::numeric_limits<EntityId>::max() && _changes.ContainsKey(component.previous))
            {
                previous = _changes[component.previous];
            }

            if (component.next != std::numeric_limits<EntityId>::max() && _changes.ContainsKey(component.next))
            {
                next = _changes[component.next];
            }

            if (previous.has_value())
            {
                previous.value().get().next = component.next;
            }
            else if (component.previous != std::numeric_limits<EntityId>::max())
            {
                auto previousComponent = nodeView.GetComponentUnsafe(component.previous);
                _changes.Insert(component.previous,
                                LinkedEntityListNodeComponent{true, previousComponent.previous, component.next});
            }

            if (next.has_value())
            {
                next.value().get().previous = component.previous;
            }
            else if (component.next != std::numeric_limits<EntityId>::max())
            {
                auto nextComponent = nodeView.GetComponentUnsafe(component.next);
                _changes.Insert(component.next,
                                LinkedEntityListNodeComponent{true, component.previous, nextComponent.next});
            }

            if (_newBeginPostDiff.has_value() && _newBeginPostDiff.value() == nodeToRemove)
            {
                _newBeginPostDiff = component.next;
            }

            if (_newTailPostDiff.has_value() && _newTailPostDiff.value() == nodeToRemove)
            {
                _newTailPostDiff = component.previous;
            }

            _changes.Insert(nodeToRemove, nodeView.GetDeleteInstructionState());
        }
        else
        {
            throw Exceptions::KeyNotFoundException();
        }
    }

    void LinkedEntityListView::Commit()
    {
        _hasBeenCommitted = true;
        auto nodeView = _catalogue.GetComponentView<LinkedEntityListNodeComponent>();

        for (auto [entity, diffInstruction] : _changes)
        {
            nodeView.PushComponentUpdateInstruction(entity, diffInstruction);
        }
    }
}