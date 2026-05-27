#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EcsUtils.hpp>
#include <NovelRT/Maths/Constants.hpp>
#include <NovelRT/Maths/GeoVector2F.hpp>
#include <NovelRT/Maths/GeoVector3F.hpp>

#include <limits>

namespace NovelRT::Ecs::Components
{
    struct TransformComponent
    {
        Maths::GeoVector2F position = Maths::GeoVector2F::Zero();
        Maths::GeoVector2F scale = Maths::GeoVector2F::One();
        float rotationInRadians = 0.0f;

        inline TransformComponent& operator+=(const TransformComponent& other)
        {
            position += other.position;
            rotationInRadians += other.rotationInRadians;
            scale += other.scale;

            if (rotationInRadians > Maths::Tau<float>)
            {
                rotationInRadians -= Maths::Tau<float>;
            }
            else if (rotationInRadians < -Maths::Tau<float>)
            {
                rotationInRadians += Maths::Tau<float>;
            }

            return *this;
        }

        friend inline bool operator==(const TransformComponent& lhs, const TransformComponent& rhs) noexcept
        {
            return lhs.position == rhs.position && lhs.scale == rhs.scale &&
                   lhs.rotationInRadians == rhs.rotationInRadians;
        }

        friend inline bool operator!=(const TransformComponent& lhs, const TransformComponent& rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}
