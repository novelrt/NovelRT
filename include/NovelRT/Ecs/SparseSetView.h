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
        std::weak_ptr<const std::vector<TValue>> _denseBlock;
        std::weak_ptr<const std::unordered_map<TKey, size_t, THashFunction>> _sparseMap;
        
        void VerifyViewIsValid() const
        {
            if (_denseBlock.expired() || _sparseMap.expired())
            {
                throw std::runtime_error("Immutable view outlived object it is viewing!");
            }
        }

    public:
        SparseSetView(std::weak_ptr<const std::vector<TValue>> denseBlock, std::weak_ptr<const std::unordered_map<TKey, size_t, THashFunction>> sparseMap) noexcept : _denseBlock(denseBlock),
                                                                                                                                 _sparseMap(sparseMap)
        {
        }

        TValue operator[](TKey key) const
        {
            VerifyViewIsValid();
            return _denseBlock.lock()->at(_sparseMap.lock()->at(key));
        }

        // clang-format off
        // These functions have to be named this way for a range based for loop to work
        auto begin() const
        {
            VerifyViewIsValid();
            return _denseBlock.lock()->begin();
        }

        auto end() const
        {
            VerifyViewIsValid();
            return _denseBlock.lock()->end();
        }
        // clang-format on
    };
} // namespace NovelRT::Ecs

#endif //!NOVELRT_ECS_SPARSESETVIEW_H