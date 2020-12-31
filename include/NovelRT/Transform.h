// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NOVELWORLDOBJECT_H
#define NOVELRT_NOVELWORLDOBJECT_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT
{
    /**
     * @brief Represents a 2D position, scale and rotation.
     */
    class Transform
    {
      public:
        Maths::GeoVector2F position;
        Maths::GeoVector2F scale;
        float rotation;

        /**
    <<<<<<< HEAD
         * Creates a new Transform with the specified position, rotation and scale.
         * @param position The position which represents the position of the transform in a given space such as screen
    or
         * world space.
    =======
         * @brief Creates a new Transform with the specified position, rotation and scale.
         * @param position The position which represents the position of the transform in a given space such as screen
    or world space.
    >>>>>>> master
         * @param rotation The rotation, in degrees, which represents the rotation of the transform.
         * @param scale The scale which represents the size of the transform.
         */
        Transform(Maths::GeoVector2F position, float rotation, Maths::GeoVector2F scale) noexcept;
        /**
         * @brief Creates a new Transform with the default values.
         */
        Transform() noexcept;

        /**
         * @brief Gets the Axis Aligned Bounding Box based on the position and scale of this transform.
         */
        inline Maths::GeoBounds getAABB() const
        {
            auto maxFscale = fmaxf(scale.x, scale.y);
            return Maths::GeoBounds(position, Maths::GeoVector2F(maxFscale, maxFscale), 0);
        }

        /**
         * @brief Gets the bounds based on the position, scale and rotation of this transform.
         */
        inline Maths::GeoBounds getBounds() const
        {
            return Maths::GeoBounds(position, scale, rotation);
        }
    };
} // namespace NovelRT

#endif // NOVELRT_NOVELWORLDOBJECT_H
