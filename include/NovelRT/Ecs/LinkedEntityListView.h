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

    private:
        EntityId _begin;
        EntityId _end = std::numeric_limits<EntityId>::max();
        EntityId _tail;
        bool _hasBeenCommitted;
        SparseSet<EntityId, LinkedEntityListNodeComponent> _changes;
        std::optional<EntityId> _newTailPostDiff;
        std::optional<EntityId> _newBeginPostDiff;
        Catalogue& _catalogue;

        [[nodiscard]] EntityId& UpdateExistingChangesForAddBeforeOperation(
            EntityId& newNode,
            ConstIterator& nextIt,
            const ComponentView<LinkedEntityListNodeComponent>& nodeView,
            EntityId& existingNextNode);

        [[nodiscard]] EntityId& UpdateExistingChangesForAddAfterOperation(
            EntityId& newNode,
            ConstIterator& previousIt,
            const ComponentView<LinkedEntityListNodeComponent>& nodeView,
            EntityId& existingPreviousNode);

    public:
        LinkedEntityListView(EntityId node, Catalogue& catalogue) noexcept;
        ~LinkedEntityListView();

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

        void AddInsertBeforeIndexInstruction(size_t index, EntityId newNode);
        void AddInsertAfterIndexInstruction(size_t index, EntityId newNode);

        [[nodiscard]] inline std::optional<LinkedEntityListNodeComponent> TryGetComposedDiffInstruction(
            EntityId node) const noexcept
        {
            if (_changes.ContainsKey(node))
            {
                return _changes[node];
            }

            return std::optional<LinkedEntityListNodeComponent>{};
        }

        [[nodiscard]] inline std::optional<LinkedEntityListNodeComponent> TryGetComposedDiffInstructionAtBeginning()
            const noexcept
        {
            if (_newBeginPostDiff.has_value())
            {
                return _changes[_newBeginPostDiff.value()];
            }

            return std::optional<LinkedEntityListNodeComponent>{};
        }

        [[nodiscard]] inline std::optional<LinkedEntityListNodeComponent> TryGetComposedDiffInstructionAtEnd()
            const noexcept
        {
            if (_newTailPostDiff.has_value())
            {
                return std::optional<LinkedEntityListNodeComponent>(_changes[_newTailPostDiff.value()]);
            }

            return std::optional<LinkedEntityListNodeComponent>{};
        }

        [[nodiscard]] inline std::optional<EntityId> TryGetNewNodeAtBeginning() const noexcept
        {
            if (_newBeginPostDiff.has_value())
            {
                return _newBeginPostDiff.value();
            }

            return std::optional<EntityId>{};
        }

        [[nodiscard]] inline std::optional<EntityId> TryGetNewNodeAtEnd() const noexcept
        {
            if (_newTailPostDiff.has_value())
            {
                return _newTailPostDiff.value();
            }

            return std::optional<EntityId>{};
        }

        [[nodiscard]] inline EntityId GetOriginalBeginning() const noexcept
        {
            return _begin;
        }

        [[nodiscard]] inline EntityId GetOriginalEnd() const noexcept
        {
            if (_tail == std::numeric_limits<EntityId>::max())
            {
                return _begin;
            }
            else
            {
                return _end;
            }
        }

        void AddInsertAtBackInstruction(EntityId newNode);
        void AddInsertAtFrontInstruction(EntityId newNode);
        void AddRemoveNodeInstruction(EntityId nodeToRemove);
        void ClearAndAddRemoveNodeInstructionForAll();
        void Commit();
    };
}

#endif // NOVELRT_ECS_LINKEDENTITYLISTVIEW_H
