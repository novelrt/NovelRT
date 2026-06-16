#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Maths/GeoVector3F.hpp>
#include <NovelRT/Maths/GeoMatrix4x4F.hpp>
#include <NovelRT/Ecs/Graphics/Components/Viewport.hpp>
#include <NovelRT/Ecs/Components/TransformComponent.hpp>

namespace NovelRT::Ecs::Graphics::Components
{
    struct Camera
    {
        float left = -1.0f;
        float right = 1.0f;
        float bottom = -1.0f;
        float top = 1.0f;
        float nearPlane = 0.0f;
        float farPlane = 1.0f;
        int32_t referenceResolutionWidth = 100;
        int32_t referenceResolutionHeight = 100;

        bool isScreenSpace = false;

        inline Camera& operator+=(const Camera& other)
        {
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const Camera& other) const noexcept
        {
            // normally I would care more about floating point comparison but this is basically only here to handle
            // deletion, where it'll always be zero. - Matt J.
            return left == other.left && right == other.right && bottom == other.bottom && top == other.top &&
                   nearPlane == other.nearPlane && farPlane == other.farPlane && isScreenSpace == other.isScreenSpace &&
                   referenceResolutionWidth == other.referenceResolutionWidth &&
                   referenceResolutionHeight == other.referenceResolutionHeight;
        }

        [[nodiscard]] inline bool operator!=(const Camera& other) const noexcept
        {
            return !(*this == other);
        }

        [[nodiscard]] static Maths::GeoVector2F ToVector2F(float x , float y)
        {
            return Maths::GeoVector2F(x, y);
        }

        [[nodiscard]] static Maths::GeoVector2F ToVector2F(Components::Viewport &viewport)
        {
            return Maths::GeoVector2F(viewport.x, viewport.y);
        }

        [[nodiscard]] static Maths::GeoVector3F ToVector3F(float x, float y, float z)
        {
            return Maths::GeoVector3F(x, y, z);
        }

        [[nodiscard]] static Maths::GeoVector3F ToVector3F(NovelRT::Ecs::Components::TransformComponent transform, float z)
        {
            return Maths::GeoVector3F(transform.position.x , transform.position.y, z);
        }

        [[nodiscard]] static Maths::GeoVector4F ToVector4F(float x, float y, float z, float w)
        {
            return Maths::GeoVector4F(x,y,z,w);
        }

        [[nodiscard]] static Maths::GeoMatrix4x4F ToOrthographic(Camera &camera)
        {
            return Maths::GeoMatrix4x4F::CreateOrthographic(
                        camera.left, camera.right, camera.bottom,
                        camera.top, camera.nearPlane, camera.farPlane);
        }

        [[nodiscard]] static Maths::GeoMatrix4x4F GetDefaultIdentity()
        {
            return Maths::GeoMatrix4x4F::GetDefaultIdentity();
        }

        [[nodiscard]] static Maths::GeoMatrix4x4F CreateFromLookAt(Maths::GeoVector3F eye, Maths::GeoVector3F centre, Maths::GeoVector3F up)
        {
            return Maths::GeoMatrix4x4F::CreateFromLookAt(
                eye,
                centre,
                up
            );
        }
    };
}
