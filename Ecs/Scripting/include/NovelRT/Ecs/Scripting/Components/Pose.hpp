#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Maths/GeoVector2F.hpp>

#include <string>

namespace NovelRT::Ecs::Scripting::Components
{
    struct Pose
    {
        std::string* name;
        std::string* sprite;
        NovelRT::Maths::GeoVector2F position;
        NovelRT::Maths::GeoVector2F scale;

        inline Pose& operator+=(const Pose& other)
        {
            delete name;
            delete sprite;

            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const Pose& other) const noexcept
        {
            // TODO: is comparing the position/scale by value correct here?
            return name == other.name && sprite == other.sprite && position == other.position && scale == other.scale;
        }
    };
}
