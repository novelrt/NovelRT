// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_SPARSESET_H
#define NOVELRT_ECS_SPARSESET_H

#include "EcsUtils.h"
#include "../Atom.h"
#include <unordered_map>
#include <memory>
#include <iterator>
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include "../Exceptions/DuplicateKeyException.h"

namespace NovelRT::Ecs
{
    template <typename TKey, typename TValue, typename THashFunction = std::hash<TKey>>
    class SparseSet
    {
        private:
        std::vector<TKey> _sparseBlock;
        std::vector<TValue> _denseBlock;
        std::unordered_map<TKey, size_t, THashFunction> _sparseMap;

        public:
        class Iterator
        {
            public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = std::tuple<TKey, TValue>;
            using pointer = std::tuple<typename std::vector<TKey>::iterator, typename std::vector<TValue>::iterator>;
            using reference = std::tuple<TKey&, TValue&>;

            private:
            pointer _ptr;

            public:
            Iterator(pointer ptr) : _ptr(ptr) {}

            reference operator*() const
            {
                return std::tie(*std::get<0>(_ptr), *std::get<1>(_ptr));
            }

            pointer operator->()
            {
                return _ptr;
            }

            Iterator& operator++()
            {
                std::get<0>(_ptr)++;
                std::get<1>(_ptr)++;
                return *this;
            }

            Iterator operator++(int)
            {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            friend bool operator==(const Iterator& lhs, const Iterator& rhs)
            {
                return lhs._ptr == rhs._ptr;
            }

            friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
            {
                return lhs._ptr != rhs._ptr;
            }
        };

        class ConstIterator
        {
            public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = std::tuple<TKey, TValue>;
            using pointer = std::tuple<typename std::vector<TKey>::const_iterator, typename std::vector<TValue>::const_iterator>;
            using reference = std::tuple<const TKey&, const TValue&>;
        
            private:
            pointer _ptr;
        
            public:
            ConstIterator(pointer ptr) : _ptr(ptr) {}
        
            reference operator*() const
            {
                return std::tie(*std::get<0>(_ptr), *std::get<1>(_ptr));
            }
        
            const ConstIterator& operator++()
            {
                std::get<0>(_ptr)++;
                std::get<1>(_ptr)++;
                return *this;
            }
        
            ConstIterator operator++(int)
            {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }
        
            friend bool operator==(const ConstIterator& lhs, const ConstIterator& rhs)
            {
                return lhs._ptr == rhs._ptr;
            }
        
            friend bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs)
            {
                return lhs._ptr != rhs._ptr;
            }
        };

        SparseSet() noexcept : _sparseBlock(std::vector<TKey>()), _denseBlock(std::vector<TValue>()), _sparseMap(std::unordered_map<TKey, size_t, THashFunction>())
        {
        }

        void Insert(TKey key, TValue value)
        {
            if (ContainsKey(key))
            {
                throw Exceptions::DuplicateKeyException();
            }

            _denseBlock.push_back(value);
            _sparseBlock.push_back(key);
            _sparseMap.emplace(key, _denseBlock.size() - 1);
        }

        void Remove(TKey key)
        {
            size_t arrayIndex = _sparseMap.at(key);
            _denseBlock.erase(_denseBlock.begin() + arrayIndex);
            _sparseBlock.erase(_sparseBlock.begin() + arrayIndex);
            _sparseMap.erase(key);

            for (auto &i : _sparseMap)
            {
                if (i.second < arrayIndex)
                {
                    continue;
                }

                i.second -= 1;
            }
        }

        bool TryRemove(TKey key) noexcept
        {
            if (ContainsKey(key))
            {
                Remove(key);
                return true;
            }
            
            return false;
        }

        void Clear() noexcept
        {
            _sparseBlock.clear();
            _denseBlock.clear();
            _sparseMap.clear();
        }

        [[nodiscard]] bool ContainsKey(TKey key) const noexcept
        {
            return std::find(_sparseBlock.begin(), _sparseBlock.end(), key) != _sparseBlock.end();
        }

        [[nodiscard]] TKey CopyKeyBasedOnDenseIndex(size_t denseIndex) const
        {
            return _sparseBlock.at(denseIndex);
        }

        [[nodiscard]] TValue CopyValueBasedOnDenseIndex(size_t denseIndex) const
        {
            return _denseBlock.at(denseIndex);
        }

        [[nodiscard]] size_t Length() const noexcept
        {
            return _sparseBlock.size();
        }

        [[nodiscard]] TValue& operator[](TKey key)
        {
            return _denseBlock.at(_sparseMap.at(key));
        }

        [[nodiscard]] const TValue& operator[](TKey key) const
        {
            return _denseBlock.at(_sparseMap.at(key));
        }

        // clang-format off
        // These functions have to be named this way for a range based for loop to work
        [[nodiscard]] auto begin() noexcept
        {
            return Iterator(std::make_tuple(_sparseBlock.begin(), _denseBlock.begin()));
        }

        [[nodiscard]] auto end() noexcept
        {
            return Iterator(std::make_tuple(_sparseBlock.end(), _denseBlock.end()));
        }

        [[nodiscard]] auto cbegin() const noexcept
        {
            return ConstIterator(std::make_tuple(_sparseBlock.cbegin(), _denseBlock.cbegin()));
        }

        [[nodiscard]] auto cend() const noexcept
        {
            return ConstIterator(std::make_tuple(_sparseBlock.cend(), _denseBlock.cend()));
        }
        // clang-format on

    };
} // namespace NovelRT::Ecs

#endif //!NOVELRT_ECS_SPARSESET_H
