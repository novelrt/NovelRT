#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <string>
#include <vector>

namespace NovelRT::Ecs::Scripting::Components
{
    struct Branch
    {
        std::string* prompt;
        std::vector<std::string>* choices;

        inline Branch& operator+=(const Branch& other)
        {
            delete prompt;
            delete choices;

            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const Branch& other) const noexcept
        {
            return prompt == other.prompt && choices == other.choices;
        }
    };
}
