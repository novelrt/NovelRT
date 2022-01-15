// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_LINKEDENTITYLISTVIEW_H
#define NOVELRT_ECS_LINKEDENTITYLISTVIEW_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    class LinkedEntityListView
    {
    private:
        EntityId _begin;
        EntityId _end = std::numeric_limits<EntityId>::max();
        EntityId _tail;
        bool _hasBeenCommitted;
        SparseSet<EntityId, LinkedEntityListNodeComponent> _changes;
        std::optional<EntityId> _newTailPostDiff;
        std::optional<EntityId> _newBeginPostDiff;
        Catalogue& _catalogue;

    public:
        class ConstIterator
        {
        private:
            EntityId _currentEntityNode;
            LinkedEntityListNodeComponent _currentComponentNode;
            Catalogue& _catalogue;

        public:
            using value = EntityId;
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            ConstIterator(EntityId currentEntityNode, Catalogue& catalogue) noexcept
                : _currentEntityNode(currentEntityNode),
                  _currentComponentNode(
                      currentEntityNode != std::numeric_limits<EntityId>::max()
                          ? catalogue.GetComponentView<LinkedEntityListNodeComponent>().GetComponentUnsafe(
                                currentEntityNode)
                          : catalogue.GetComponentView<LinkedEntityListNodeComponent>().GetDeleteInstructionState()),
                  _catalogue(catalogue)
            {
            }

            inline value operator*() const noexcept
            {
                return _currentEntityNode;
            }

            inline ConstIterator& operator++() noexcept
            {
                _currentEntityNode = _currentComponentNode.next;

                if (_currentEntityNode == std::numeric_limits<EntityId>::max())
                {
                    _currentComponentNode =
                        _catalogue.GetComponentView<LinkedEntityListNodeComponent>().GetDeleteInstructionState();
                }
                else
                {
                    _currentComponentNode =
                        _catalogue.GetComponentView<LinkedEntityListNodeComponent>().GetComponentUnsafe(
                            _currentEntityNode);
                }

                return *this;
            }

            inline ConstIterator& operator--() noexcept
            {
                _currentEntityNode = _currentComponentNode.previous;

                if (_currentEntityNode == std::numeric_limits<EntityId>::max())
                {
                    _currentComponentNode =
                        _catalogue.GetComponentView<LinkedEntityListNodeComponent>().GetDeleteInstructionState();
                }
                else
                {
                    _currentComponentNode =
                        _catalogue.GetComponentView<LinkedEntityListNodeComponent>().GetComponentUnsafe(
                            _currentEntityNode);
                }

                return *this;
            }

            inline ConstIterator& operator--(int) noexcept
            {
                this->operator--();
                return *this;
            }

            inline ConstIterator& operator++(int) noexcept
            {
                this->operator++();
                return *this;
            }

            [[nodiscard]] inline EntityId GetCurrentEntityNode() const noexcept
            {
                return _currentEntityNode;
            }

            [[nodiscard]] inline LinkedEntityListNodeComponent GetListNode() const noexcept
            {
                return _currentComponentNode;
            }

            [[nodiscard]] inline bool operator==(const ConstIterator& other) const noexcept
            {
                return _currentEntityNode == other._currentEntityNode;
            }

            [[nodiscard]] inline bool operator!=(const ConstIterator& other) const noexcept
            {
                return !(*this == other);
            }
        };

        LinkedEntityListView(EntityId node, Catalogue& catalogue) noexcept
            : _begin(node), _catalogue(catalogue), _tail(_end), _hasBeenCommitted(false), _changes{}
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
                _tail = _begin;
            }
            else
            {
                while (currentBeginComponent.previous != std::numeric_limits<EntityId>::max())
                {
                    _begin = currentBeginComponent.previous;
                    currentBeginComponent = view.GetComponentUnsafe(_begin);
                }

                currentBeginComponent = view.GetComponentUnsafe(node);

                _tail = _begin;
                while (currentBeginComponent.next != std::numeric_limits<EntityId>::max())
                {
                    _tail = currentBeginComponent.next;
                    currentBeginComponent = view.GetComponentUnsafe(_tail);
                }
            }
        }

        [[nodiscard]] inline ConstIterator begin() const noexcept
        {
            return ConstIterator(_begin, _catalogue);
        }

        [[nodiscard]] inline ConstIterator end() const noexcept
        {
            return ConstIterator(_end, _catalogue);
        }

        [[nodiscard]] inline EntityId operator[](size_t index) const noexcept
        {
            auto it = begin();
            for (size_t i = 0; i < index; i++)
            {
                it++;
            }

            return it.GetCurrentEntityNode();
        }

        [[nodiscard]] inline bool ContainsNode(EntityId target) const noexcept
        {
            for (auto&& node : *this)
            {
                if (node == target)
                {
                    return true;
                }
            }

            return false;
        }

        [[nodiscard]] inline size_t GetLength() const noexcept
        {
            size_t returnCount = 0;

            for (auto&& item : *this)
            {
                unused(item);
                returnCount++;
            }

            return returnCount;
        }

        inline void AddInsertBeforeIndexInstruction(size_t index, EntityId newNode)
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

        inline void AddInsertAfterIndexInstruction(size_t index, EntityId newNode)
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

        /*
         *
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
         * */

        EntityId& UpdateExistingChangesForAddBeforeOperation(
            EntityId& newNode,
            ConstIterator& nextIt,
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
                }
                else
                {
                    _changes[existingNextNode] = finalDiffInstructionForNext;
                }
            }

            _changes.Insert(newNode,
                            LinkedEntityListNodeComponent{
                                true, hasPrevious ? existingNextNode : EntityId(std::numeric_limits<EntityId>::max()),
                                hasNext ? existingNextNode : EntityId(std::numeric_limits<EntityId>::max())});
            return existingNextNode;
        }

        EntityId& UpdateExistingChangesForAddAfterOperation(
            EntityId& newNode,
            ConstIterator& previousIt,
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
                }
                else
                {
                    _changes[existingPreviousNode] = finalDiffInstructionForPrevious;
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

        inline void AddInsertAtBackInstruction(EntityId newNode)
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
                auto last = nodeView.GetComponentUnsafe(_tail);
                last.next = newNode;
                _newTailPostDiff = newNode;
                _changes.Insert(_tail, last);
                _changes.Insert(newNode,
                                LinkedEntityListNodeComponent{true, _tail, std::numeric_limits<EntityId>::max()});
            }

            // nodeView.PushComponentUpdateInstruction(_tail, last);
        }

        inline void AddInsertAtFrontInstruction(EntityId newNode)
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
                auto begin = nodeView.GetComponentUnsafe(_begin);
                begin.previous = newNode;
                _newBeginPostDiff = newNode;
                _changes.Insert(_begin, begin);
                _changes.Insert(newNode,
                                LinkedEntityListNodeComponent{true, std::numeric_limits<EntityId>::max(), _begin});
            }
        }

        inline void AddRemoveNodeInstruction(EntityId nodeToRemove)
        {
            auto nodeView = _catalogue.GetComponentView<LinkedEntityListNodeComponent>();

            if (_changes.ContainsKey(nodeToRemove))
            {
                auto& component = _changes[nodeToRemove];
                std::optional<std::reference_wrapper<LinkedEntityListNodeComponent>> previous;
                std::optional<std::reference_wrapper<LinkedEntityListNodeComponent>> next;

                if (component.previous != std::numeric_limits<EntityId>::max() &&
                    _changes.ContainsKey(component.previous))
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

                component = nodeView.GetDeleteInstructionState();
            }
            else if (nodeView.HasComponent(nodeToRemove) && ContainsNode(nodeToRemove))
            {
                auto component = nodeView.GetComponent(nodeToRemove);
                std::optional<std::reference_wrapper<LinkedEntityListNodeComponent>> previous;
                std::optional<std::reference_wrapper<LinkedEntityListNodeComponent>> next;

                if (component.previous != std::numeric_limits<EntityId>::max() &&
                    _changes.ContainsKey(component.previous))
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

        void Commit()
        {
            _hasBeenCommitted = true;
            auto nodeView = _catalogue.GetComponentView<LinkedEntityListNodeComponent>();

            for (auto [entity, diffInstruction] : _changes)
            {
                nodeView.PushComponentUpdateInstruction(entity, diffInstruction);
            }
        }

        ~LinkedEntityListView()
        {
            if (!_hasBeenCommitted)
            {
                Commit();
            }
        }
    };
}

#endif // NOVELRT_ECS_LINKEDENTITYLISTVIEW_H
