#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <string>

namespace NovelRT::Ecs::Scripting::Components
{
    struct Pose
    {
        std::string* name;
        std::string* sprite;

        inline Pose& operator+=(const Pose& other)
        {
            delete name;
            delete sprite;

            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const Pose& other) const noexcept
        {
            return name == other.name && sprite == other.sprite;
        }
    };
}
