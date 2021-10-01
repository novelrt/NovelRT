// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NOVELWORLDOBJECT_H
#define NOVELRT_NOVELWORLDOBJECT_H

#include "Maths/GeoVector2F.h"

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
         * @brief Creates a new Transform with the specified position, rotation and scale.
         * @param position The position which represents the position of the transform in a given space such as screen
         * or world space.
         * @param rotation The rotation, in degrees, which represents the rotation of the transform.
         * @param scale The scale which represents the size of the transform.
         */
        Transform(Maths::GeoVector2F position, float rotation, Maths::GeoVector2F scale) noexcept;
        /**
         * @brief Creates a new Transform with the default values.
         */
        Transform() noexcept;
    };
} 

#endif // NOVELRT_NOVELWORLDOBJECT_H
