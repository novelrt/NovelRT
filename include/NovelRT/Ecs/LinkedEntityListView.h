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
                  _currentComponentNode(catalogue.GetComponentView<LinkedEntityListNodeComponent>().GetComponentUnsafe(
                      currentEntityNode)),
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

                _currentComponentNode =
                    _catalogue.GetComponentView<LinkedEntityListNodeComponent>().GetComponentUnsafe(_currentEntityNode);
                return *this;
            }

            inline ConstIterator& operator--() noexcept
            {
                _currentEntityNode = _currentComponentNode.previous;

                _currentComponentNode =
                    _catalogue.GetComponentView<LinkedEntityListNodeComponent>().GetComponentUnsafe(_currentEntityNode);
                return *this;
            }

            inline ConstIterator& operator--(int amount) noexcept
            {
                for (int i = 0; i < amount; i++)
                {
                    this->operator--();
                }

                return *this;
            }

            inline ConstIterator& operator++(int amount) noexcept
            {
                for (int i = 0; i < amount; i++)
                {
                    this->operator++();
                }

                return *this;
            }

            [[nodiscard]] inline EntityId GetCurrentEntityNode() const noexcept
            {
                return _currentEntityNode;
            }

            [[nodiscard]] inline LinkedEntityListNodeComponent GetListNode() const noexcept
            {
                return _catalogue.GetComponentView<LinkedEntityListNodeComponent>().GetComponentUnsafe(
                    _currentEntityNode);
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
                while (currentBeginComponent.next != std::numeric_limits<EntityId>::max()){
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

            auto it = begin();

            for (size_t i = 0; i < index; i++)
            {
                it++;
            }

            EntityId existingNode = it.GetCurrentEntityNode();

            auto nodeView = _catalogue.GetComponentView<LinkedEntityListNodeComponent>();

            if (_changes.ContainsKey(existingNode))
            {
                auto& diffInstruction = _changes[existingNode];
                EntityId oldPrevious = diffInstruction.previous;
                auto& oldPreviousDiffInstruction = _changes[oldPrevious];

                oldPreviousDiffInstruction.next = newNode;
                LinkedEntityListNodeComponent newNodeInstruction{};
                newNodeInstruction.previous = oldPrevious;
                newNodeInstruction.next = existingNode;
                oldPreviousDiffInstruction.next = newNode;
                diffInstruction.previous = newNode;

                _changes.Insert(newNode, newNodeInstruction);
            }
            else
            {
                LinkedEntityListNodeComponent nodeComponent = it.GetListNode();
                LinkedEntityListNodeComponent newNodeInstruction{};
                newNodeInstruction.next = existingNode;
                newNodeInstruction.previous = nodeComponent.previous;
                nodeComponent.previous = newNode;

                _changes.Insert(existingNode, nodeComponent);
                _changes.Insert(newNode, newNodeInstruction);
            }

            if (_newBeginPostDiff.has_value() && _newBeginPostDiff.value() == existingNode)
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

            auto it = begin();

            for (size_t i = 0; i < index; i++)
            {
                it++;
            }


            auto nodeView = _catalogue.GetComponentView<LinkedEntityListNodeComponent>();
            EntityId existingNode = it.GetCurrentEntityNode();

            if (_changes.ContainsKey(existingNode))
            {
                auto& diffInstruction = _changes[existingNode];
                EntityId oldNext = diffInstruction.next;
                auto& oldNextDiffInstruction = _changes[oldNext];
                LinkedEntityListNodeComponent newNodeInstruction{};
                newNodeInstruction.previous = existingNode;
                newNodeInstruction.next = oldNext;
                oldNextDiffInstruction.previous = newNode;
                diffInstruction.next = newNode;

                _changes.Insert(newNode, newNodeInstruction);
            }
            else
            {
                LinkedEntityListNodeComponent nodeComponent = it.GetListNode();
                LinkedEntityListNodeComponent newNodeInstruction{};
                newNodeInstruction.previous = existingNode;
                newNodeInstruction.next = nodeComponent.next;
                nodeComponent.next = newNode;

                _changes.Insert(existingNode, nodeComponent);
                _changes.Insert(newNode, newNodeInstruction);
            }

            if (_newTailPostDiff.has_value() && _newTailPostDiff.value() == existingNode)
            {
                _newTailPostDiff = newNode;
            }
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
                _changes.Insert(newNode, LinkedEntityListNodeComponent{true, _tail, std::numeric_limits<EntityId>::max()});
            }

            //nodeView.PushComponentUpdateInstruction(_tail, last);
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
                _changes.Insert(newNode, LinkedEntityListNodeComponent{true, std::numeric_limits<EntityId>::max(), _begin});
            }
        }

        inline void AddRemoveNodeInstruction(EntityId nodeEntity)
        {
            auto nodeView = _catalogue.GetComponentView<LinkedEntityListNodeComponent>();

            if (_changes.ContainsKey(nodeEntity))
            {
                auto& component = _changes[nodeEntity];
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
                    _changes.Insert(component.previous, LinkedEntityListNodeComponent{true, previousComponent.previous, component.next});
                }

                if (next.has_value())
                {
                    next.value().get().previous = component.previous;
                }
                else if (component.next != std::numeric_limits<EntityId>::max())
                {
                    auto nextComponent = nodeView.GetComponentUnsafe(component.next);
                    _changes.Insert(component.next, LinkedEntityListNodeComponent{true, component.previous, nextComponent.next});
                }

                if (_newBeginPostDiff.has_value() && _newBeginPostDiff.value() == nodeEntity)
                {
                    _newBeginPostDiff = component.next;
                }

                if (_newTailPostDiff.has_value() && _newTailPostDiff.value() == nodeEntity)
                {
                    _newTailPostDiff = component.previous;
                }

                component = nodeView.GetDeleteInstructionState();
            }
            else
            {
                auto component = nodeView.GetComponentUnsafe(nodeEntity);
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
                    _changes.Insert(component.previous, LinkedEntityListNodeComponent{true, previousComponent.previous, component.next});
                }

                if (next.has_value())
                {
                    next.value().get().previous = component.previous;
                }
                else if (component.next != std::numeric_limits<EntityId>::max())
                {
                    auto nextComponent = nodeView.GetComponentUnsafe(component.next);
                    _changes.Insert(component.next, LinkedEntityListNodeComponent{true, component.previous, nextComponent.next});
                }

                if (_newBeginPostDiff.has_value() && _newBeginPostDiff.value() == nodeEntity)
                {
                    _newBeginPostDiff = component.next;
                }

                if (_newTailPostDiff.has_value() && _newTailPostDiff.value() == nodeEntity)
                {
                    _newTailPostDiff = component.previous;
                }

                _changes.Insert(nodeEntity, nodeView.GetDeleteInstructionState());
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
