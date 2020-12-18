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

namespace NovelRT::Ecs
{
    template <typename TKey, typename TValue, typename THashFunction = std::hash<TKey>>
    class SparseSet
    {
    private:
        std::shared_ptr<std::vector<TKey>> _sparseBlock;
        std::shared_ptr<std::vector<TValue>> _denseBlock;
        std::shared_ptr<std::unordered_map<TKey, size_t, THashFunction>> _sparseMap;

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

        SparseSet() noexcept : _sparseBlock(std::make_shared<std::vector<TKey>>()), _denseBlock(std::make_shared<std::vector<TValue>>()), _sparseMap(std::make_shared<std::unordered_map<TKey, size_t, THashFunction>>())
        {
        }

        SparseSet(const SparseSet<TKey, TValue, THashFunction>& rhs) noexcept : _sparseBlock(std::make_shared<std::vector<TKey>>()), _denseBlock(std::make_shared<std::vector<TValue>>()), _sparseMap(std::make_shared<std::unordered_map<TKey, size_t, THashFunction>>())
        {
            _denseBlock->resize(rhs._denseBlock->size());
            std::copy(rhs._denseBlock->begin(), rhs._denseBlock->end(), _denseBlock->begin());
            _sparseBlock->resize(rhs._denseBlock->size());
            std::copy(rhs._sparseBlock->begin(), rhs._sparseBlock->end(), _sparseBlock->begin());
            *_sparseMap = *(rhs._sparseMap);
        }

        bool HasValue(TKey key) const noexcept
        {
            return _sparseMap->find(key) != _sparseMap->end();
        }

        void Insert(TKey key, TValue value)
        {
            if (HasValue(key))
            {
                throw std::runtime_error("Unable to continue! Duplicate key added to SparseSet!"); // TODO: Make this a well defined exception in the future
            }

            _denseBlock->push_back(value);
            _sparseBlock->push_back(key);
            _sparseMap->emplace(key, _denseBlock->size() - 1);
        }

        void Remove(TKey key)
        {
            size_t arrayIndex = _sparseMap->at(key);
            _denseBlock->erase(_denseBlock->begin() + arrayIndex);
            _sparseBlock->erase(_sparseBlock->begin() + arrayIndex);
            _sparseMap->erase(key);

            for (auto &i : *_sparseMap)
            {
                if (i.second < arrayIndex)
                {
                    continue;
                }

                i.second -= 1;
            }
        }

        bool ContainsKey(TKey key) const noexcept
        {
            return std::find(_sparseBlock->begin(), _sparseBlock->end(), key) != _sparseBlock->end();
        }

        TKey GetKeyBasedOnDenseIndex(size_t denseIndex) const
        {
            return _sparseBlock.at(denseIndex);
        }

        TValue& operator[](TKey key)
        {
            return _denseBlock->at(_sparseMap->at(key));
        }

        const TValue& operator[](TKey key) const
        {
            return _denseBlock->at(_sparseMap->at(key));
        }

        // clang-format off
        // These functions have to be named this way for a range based for loop to work
        auto begin() noexcept
        {
            return Iterator(std::make_tuple(_sparseBlock->begin(), _denseBlock->begin()));
        }

        auto end() noexcept
        {
            return Iterator(std::make_tuple(_sparseBlock->end(), _denseBlock->end()));
        }
        // clang-format on


    };
} // namespace NovelRT::Ecs

#endif //!NOVELRT_ECS_SPARSESET_H
