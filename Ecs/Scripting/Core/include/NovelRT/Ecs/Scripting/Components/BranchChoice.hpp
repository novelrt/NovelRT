#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

namespace NovelRT::Ecs::Scripting::Components
{
    struct BranchChoice
    {
        std::size_t choiceIndex;

        inline BranchChoice& operator+=(const BranchChoice& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const BranchChoice& other) const noexcept
        {
            return choiceIndex == other.choiceIndex;
        }
    };
}
