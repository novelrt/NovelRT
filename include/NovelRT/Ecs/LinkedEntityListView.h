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
        Catalogue& _catalogue;

    public:
        using value = EntityId;

        class ConstIterator
        {
        private:
            EntityId _currentEntityNode;
            LinkedEntityListNodeComponent _currentComponentNode;
            Catalogue& _catalogue;

        public:
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
                return _catalogue.GetComponentView<LinkedEntityListNodeComponent>().GetComponentUnsafe(_currentEntityNode);
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

        LinkedEntityListView(EntityId node, Catalogue& catalogue) noexcept : _begin(node), _catalogue(catalogue)
        {
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

        /*
        inline ConstIterator InsertAtIndex(size_t index, EntityId newNode)
        {

        }
*/
    };

    /*
    class LinkedEntityListView
    {
    private:
        EntityId _begin;
        EntityId _end = std::numeric_limits<EntityId>::max();
        Catalogue& _catalogue;

    public:
        using value = EntityId;

        class ConstIterator
        {
        private:
            EntityId _currentEntityBlock;
            uint32_t _currentIndexInBlock;
            Catalogue& _catalogue;

        public:
            ConstIterator(EntityId currentEntityBlock, uint32_t currentIndexInBlock, Catalogue& catalogue) noexcept
                : _currentEntityBlock(currentEntityBlock),
                  _currentIndexInBlock(currentIndexInBlock),
                  _catalogue(catalogue)
            {
            }

            inline value operator*() const noexcept
            {
                auto component =
                    _catalogue.GetComponentView<QuadEntityBlockComponent>().GetComponentUnsafe(_currentEntityBlock);
                switch (_currentIndexInBlock)
                {
                    case 0:
                        return component.zero;
                    case 1:
                        return component.one;
                    case 2:
                        return component.two;
                    case 3:
                        return component.three;
                }
            }

            inline ConstIterator& operator++() noexcept
            {
                _currentIndexInBlock++;

                if (_currentIndexInBlock > 3)
                {
                    auto component =
                        _catalogue.GetComponentView<QuadEntityBlockComponent>().GetComponentUnsafe(_currentEntityBlock);

                    if (!std::bitset<8>(component.blockWriteMap).test(5))
                    {
                        _currentIndexInBlock = 4;
                        _currentEntityBlock = std::numeric_limits<EntityId>::max();
                    }
                    else
                    {
                        _currentIndexInBlock = 0;
                        _currentEntityBlock = component.nextBlock;
                    }
                }

                return *this;
            }

            inline ConstIterator& operator--() noexcept
            {
                _currentIndexInBlock--;

                if (_currentIndexInBlock < 0)
                {
                    auto component =
                        _catalogue.GetComponentView<QuadEntityBlockComponent>().GetComponentUnsafe(_currentEntityBlock);

                    if (!std::bitset<8>(component.blockWriteMap).test(0))
                    {
                        _currentIndexInBlock = 0;
                        _currentEntityBlock = std::numeric_limits<EntityId>::max();
                    }
                    else
                    {
                        _currentIndexInBlock = 3;
                        _currentEntityBlock = component.previousBlock;
                    }
                }

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

            [[nodiscard]] inline EntityId GetCurrentEntityBlock() const noexcept
            {
                return _currentEntityBlock;
            }

            [[nodiscard]] inline QuadEntityBlockComponent GetListBlock() const noexcept
            {
                return _catalogue.GetComponentView<QuadEntityBlockComponent>().GetComponentUnsafe(_currentEntityBlock);
            }

            [[nodiscard]] inline bool operator==(const ConstIterator& other) const noexcept
            {
                return _currentEntityBlock == other._currentEntityBlock &&
                       _currentIndexInBlock == other._currentIndexInBlock;
            }

            [[nodiscard]] inline bool operator!=(const ConstIterator& other) const noexcept
            {
                return !(*this == other);
            }
        };

        LinkedEntityListView(EntityId node, Catalogue& catalogue) noexcept : _begin(node), _catalogue(catalogue)
        {
            auto view = _catalogue.GetComponentView<QuadEntityBlockComponent>();
            auto component = view.GetComponentUnsafe(_begin);

            while (std::bitset<8>(component.blockWriteMap).test(0))
            {
                _begin = component.previousBlock;
                component = view.GetComponentUnsafe(_begin);
            }
        }

        [[nodiscard]] inline EntityId operator[](size_t index) const noexcept
        {
            size_t block = index / 4ULL;

            auto componentView = _catalogue.GetComponentView<QuadEntityBlockComponent>();
            auto currentBlock = componentView.GetComponentUnsafe(_begin);

            for (size_t i = 0; i < block; i++)
            {
                currentBlock = componentView.GetComponentUnsafe(currentBlock.nextBlock);
            }

            size_t subIndex = index % 4ULL;

            switch (subIndex)
            {
                case 0:
                    return currentBlock.zero;
                case 1:
                    return currentBlock.one;
                case 2:
                    return currentBlock.two;
                case 3:
                    return currentBlock.three;
            }
        }

        void PushAddToEndInstruction(EntityId entityElement)
        {
            auto listBlockView = _catalogue.GetComponentView<QuadEntityBlockComponent>();
            QuadEntityBlockComponent component{0, 0, 0, 0, 0, 0, 0};
            EntityId currentEntity = 0;

            for (ConstIterator it = begin(); it != end(); it++)
            {
                component = it.GetListBlock();
                currentEntity = it.GetCurrentEntityBlock();

                if (!std::bitset<8>(component.blockWriteMap).test(5))
                {
                    break;
                }
            }

            std::bitset<8> writeBits(component.blockWriteMap);

            bool newBlockNeeded = true;

            for (size_t i = 1; i < 5; i++)
            {
                if (!writeBits.test(i))
                {
                    writeBits.set(i);
                    newBlockNeeded = false;
                    switch (i - 1)
                    {
                        case 0:
                            component.zero = entityElement;
                            break;
                        case 1:
                            component.one = entityElement;
                            break;
                        case 2:
                            component.two = entityElement;
                            break;
                        case 3:
                            component.three = entityElement;
                            break;
                    }

                    break;
                }
            }

            if (!newBlockNeeded)
            {
                component.blockWriteMap = static_cast<uint8_t>(writeBits.to_ulong());
                listBlockView.PushComponentUpdateInstruction(currentEntity, component);
                return;
            }

            std::bitset<8> newWriteBits;
            newWriteBits.set(0);
            newWriteBits.set(1);

            uint8_t value = static_cast<uint8_t>(newWriteBits.to_ulong());
            EntityId max = std::numeric_limits<EntityId>::max();

            EntityId newEntity = _catalogue.CreateEntity();
            QuadEntityBlockComponent newBlock{
                value, currentEntity, entityElement, max, max, max, max,
            };

            listBlockView.AddComponent(newEntity, newBlock);

            writeBits.set(5);
            value = static_cast<uint8_t>(writeBits.to_ulong());

            component.blockWriteMap = value;
            component.nextBlock = newEntity;
            listBlockView.PushComponentUpdateInstruction(currentEntity, component);
        }

        void PushEmplaceInstruction(EntityId entityElement)
        {
            auto listBlockView = _catalogue.GetComponentView<QuadEntityBlockComponent>();
            QuadEntityBlockComponent component{0, 0, 0, 0, 0, 0, 0};
            EntityId currentEntityBlock = 0;
            bool newBlockNeeded = true;

            std::bitset<8> readBits(component.blockWriteMap);
            for (ConstIterator it = begin(); it != end(); it++)
            {
                component = it.GetListBlock();
                currentEntityBlock = it.GetCurrentEntityBlock();

                if (!readBits.test(1) || !readBits.test(2) || !readBits.test(3) || !readBits.test(4))
                {
                    newBlockNeeded = false;
                    break;
                }
            }

            if (newBlockNeeded)
            {
                PushAddToEndInstruction(entityElement);
                return;
            }

            std::bitset<8> writeBits(component.blockWriteMap);

            for (size_t i = 1; i < 5; i++)
            {
                if (!writeBits.test(i))
                {
                    writeBits.set(i);
                    switch (i - 1)
                    {
                        case 0:
                            component.zero = entityElement;
                            break;
                        case 1:
                            component.one = entityElement;
                            break;
                        case 2:
                            component.two = entityElement;
                            break;
                        case 3:
                            component.three = entityElement;
                            break;
                    }

                    break;
                }
            }

            component.blockWriteMap = static_cast<uint8_t>(writeBits.to_ulong());
            listBlockView.PushComponentUpdateInstruction(currentEntityBlock, component);
        }

        void PushRemoveInstruction(EntityId entity)
        {
            auto listBlockView = _catalogue.GetComponentView<QuadEntityBlockComponent>();
            QuadEntityBlockComponent component{0, 0, 0, 0, 0, 0, 0};
            EntityId currentEntity = 0;
            EntityId max = std::numeric_limits<EntityId>::max();

            for (ConstIterator it = begin(); it != end(); it++)
            {
                component = it.GetListBlock();
                currentEntity = it.GetCurrentEntityNode();

                if (component.zero == entity)
                {
                    component.zero = max;
                    std::bitset<8> writeBits(component.blockWriteMap);
                    writeBits.set(1, false);
                    component.blockWriteMap = static_cast<uint8_t>(writeBits.to_ulong());
                    return;
                }

                if (component.one == entity)
                {
                    component.one = max;
                    std::bitset<8> writeBits(component.blockWriteMap);
                    writeBits.set(2, false);
                    component.blockWriteMap = static_cast<uint8_t>(writeBits.to_ulong());
                    return;
                }

                if (component.two == entity)
                {
                    component.two = max;
                    std::bitset<8> writeBits(component.blockWriteMap);
                    writeBits.set(3, false);
                    component.blockWriteMap = static_cast<uint8_t>(writeBits.to_ulong());
                    return;
                }

                if (component.three == entity)
                {
                    component.three = max;
                    std::bitset<8> writeBits(component.blockWriteMap);
                    writeBits.set(4, false);
                    component.blockWriteMap = static_cast<uint8_t>(writeBits.to_ulong());
                    return;
                }
            }

            throw std::out_of_range("The specified EntityId does not exist in the entity linked list.");
        }

        [[nodiscard]] inline ConstIterator begin() const noexcept
        {
            return ConstIterator(_begin, 0, _catalogue);
        }

        [[nodiscard]] inline ConstIterator end() const noexcept
        {
            return ConstIterator(_end, 4, _catalogue);
        }

        [[nodiscard]] inline ConstIterator rbegin() const noexcept
        {
            auto view = _catalogue.GetComponentView<QuadEntityBlockComponent>();
            auto component = view.GetComponentUnsafe(_begin);
            EntityId endBlock = 0;

            while (std::bitset<8>(component.blockWriteMap).test(0))
            {
                endBlock = component.previousBlock;
                component = view.GetComponentUnsafe(_begin);
            }

            return ConstIterator(endBlock, 3, _catalogue);
        }

        [[nodiscard]] inline ConstIterator rend() const noexcept
        {
            return ConstIterator(_end, 4, _catalogue);
        }
    };
     */
}

#endif // NOVELRT_ECS_LINKEDENTITYLISTVIEW_H
