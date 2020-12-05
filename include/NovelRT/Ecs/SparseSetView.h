// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_SPARSESETVIEW_H
#define NOVELRT_ECS_SPARSESETVIEW_H

#include "EcsUtils.h"
#include "../Atom.h"
#include <unordered_map>

namespace NovelRT::Ecs
{
    template <typename TKey, typename TValue, typename THashFunction = std::hash<TKey>>
    class SparseSetView
    {
    private:
        const std::vector<TValue> &_denseBlock;
        const std::unordered_map<TKey, size_t, THashFunction> &_sparseMap;

    public:
        SparseSetView(const std::vector<TValue> &denseBlock, const std::unordered_map<TKey, size_t, THashFunction> &sparseMap) : _denseBlock(denseBlock),
                                                                                                                                 _sparseMap(sparseMap)
        {
        }

        TValue operator[](TKey key) const
        {
            return _denseBlock.at(_sparseMap.at(key));
        }

        // clang-format off
        // These functions have to be named this way for a range based for loop to work
        auto begin() const noexcept
        {
            return _denseBlock.begin();
        }

        auto end() const noexcept
        {
            return _denseBlock.end();
        }
        // clang-format on
    };
} // namespace NovelRT::Ecs

#endif //!NOVELRT_ECS_SPARSESETVIEW_H