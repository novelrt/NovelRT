// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_SPARSESET_H
#define NOVELRT_ECS_SPARSESET_H

#include "EcsUtils.h"
#include "../Atom.h"
#include <unordered_map>
#include "SparseSetView.h"
#include <memory>

namespace NovelRT::Ecs
{
    template <typename TKey, typename TValue, typename THashFunction = std::hash<TKey>>
    class SparseSet
    {
    private:
        std::shared_ptr<std::vector<TValue>> _denseBlock;
        std::shared_ptr<std::unordered_map<TKey, size_t, THashFunction>> _sparseMap;

    public:
        SparseSet() : _denseBlock(std::make_shared<std::vector<TValue>>()), _sparseMap(std::make_shared<std::unordered_map<TKey, size_t, THashFunction>>())
        {
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
            _sparseMap->emplace(key, _denseBlock->size() - 1);
        }

        void Remove(TKey key)
        {
            size_t arrayIndex = _sparseMap->at(key);
            _denseBlock->erase(_denseBlock->begin() + arrayIndex);
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

        SparseSetView<TKey, TValue, THashFunction> GetImmutableView() const noexcept
        {
            return SparseSetView<TKey, TValue, THashFunction>(std::weak_ptr<const std::vector<TValue>>(_denseBlock), std::weak_ptr<const std::unordered_map<TKey, size_t, THashFunction>>(_sparseMap));
        }

        TValue& operator[](TKey key)
        {
            return _denseBlock->at(_sparseMap->at(key));
        }

        // clang-format off
        // These functions have to be named this way for a range based for loop to work
        auto begin() noexcept
        {
            return _denseBlock->begin();
        }

        auto end() noexcept
        {
            return _denseBlock->end();
        }
        // clang-format on
    };
} // namespace NovelRT::Ecs

#endif //!NOVELRT_ECS_SPARSESET_H