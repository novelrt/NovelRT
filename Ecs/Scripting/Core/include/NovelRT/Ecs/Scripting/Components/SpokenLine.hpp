#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <string>

namespace NovelRT::Ecs::Scripting::Components
{
    struct SpokenLine
    {
        std::string* speaker;
        std::string* message;

        inline SpokenLine& operator+=(const SpokenLine& other)
        {
            delete speaker;
            delete message;

            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const SpokenLine& other) const noexcept
        {
            return speaker == other.speaker && message == other.message;
        }
    };
}
