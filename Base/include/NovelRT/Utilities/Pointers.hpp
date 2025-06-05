#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>

namespace NovelRT::Utilities
{
    template<typename TTo, typename TFrom>
    std::unique_ptr<TTo> StaticPointerCast(std::unique_ptr<TFrom>&& from)
    {
        // N.B. When casting unique_ptr, the old reference must be invalidated or else we'll end up with shared
        // ownership. To handle this, we release() it first, and only accept pointers explicitly passed with std::move()
        return std::unique_ptr<TTo>{static_cast<TTo*>(from.release())};
    }
}
