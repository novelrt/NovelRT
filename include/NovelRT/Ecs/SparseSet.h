// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_SPARSESET_H
#define NOVELRT_ECS_SPARSESET_H

#include "EcsUtils.h"
#include "../Atom.h"
#include <unordered_map>

namespace NovelRT::Ecs
{
    template<typename TKey, typename TValue, typename THashFunction = std::hash<TKey>>
    class SparseSet
    {
        private:
        std::vector<TValue> _denseBlock;
        std::unordered_map<TKey, size_t, THashFunction> _sparseMap;

        public:
        void Insert(TKey key, TValue value)
        {
            _denseBlock.push_back(value);
            _sparseMap.emplace(key, _denseBlock.size() - 1);
        }

        void Remove(TKey key)
        {
            size_t arrayIndex = _sparseMap[key];
            _denseBlock.erase(_denseBlock.begin() + arrayIndex);

            for (auto& i : _sparseMap)
            {
                if (i.second < arrayIndex)
                {
                    continue;
                }

                i.second -= 1;
            }
        }

        bool HasValue(TKey key) const noexcept
        {
            return _sparseMap.find(key) != _sparseMap.end();
        }

        TValue& operator[](TKey key)
        {
            return _denseBlock[_sparseMap[key]];
        }

        const std::vector<TValue>& GetDenseData() const noexcept
        {
            return _denseBlock;
        }
    };
}

#endif //!NOVELRT_ECS_SPARSESET_H