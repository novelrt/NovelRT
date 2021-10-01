// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOBOUNDS_H
#define NOVELRT_MATHS_GEOBOUNDS_H

#include "GeoVector2F.h"
#include "NovelRT/Transform.h"

namespace NovelRT::Maths
{
    /**
     * @brief A bounding box representing in 2D space with rotation
     */
    class GeoBounds
    {
    public:
        /// @brief A point in 2D space represented by X and Y
        GeoVector2F position;
        /// @brief An extent represented by Width and Height
        GeoVector2F size;
        /// @brief Rotation represented in Degree (Internally converted to Radian)
        float rotation;

        /**
         * @brief Defines a GeoBounds representing a bounding box in 2D space with rotation in degrees
         *
         * @param position A point in 2D space represented by X and Y
         * @param size An extent represented by Width and Height
         * @param rotation A rotation for 2D bounding box that is measured in degree (Internally converted to Radian)
         * @returns Newly constructed GeoBounds object containing the position, size, and rotation components
         */
        GeoBounds(GeoVector2F position, GeoVector2F size, float rotation) noexcept;

        /**
         * @brief Determines if a given vector of 2D components are within the space of this bounding box
         * @param point Vector of 2D components to be evaluated whether or not if it's within this bounding box space
         * @returns True if the given vector is within the space of this bounding box, otherwise false
         */
        [[nodiscard]] bool pointIsWithinBounds(GeoVector2F point) const noexcept;

        /**
         * @brief Evaluate whether or not if another bounding box in 2D intersects with this bounding box (Note, this implementation does not support rotation, so only AABB intersection computation is allowed)
         * @param otherBounds External bounding object to evaluate against this bounding box
         * @exception If either bounding box have rotation set to value other than 0, Not Supported Exception is thrown
         * @returns True if the otherbounds bounding box intersects with this bounding box
         */
        [[nodiscard]] bool intersectsWith(GeoBounds otherBounds) const;

        /**
         * @brief Get rotationally transformed corner coordination in a local space that is centered in this bounding box, index represents the corner starting top left to right bottom.
         * @param index 0 for left top corner, 1 for right top corner, 2 for left bottom corner, and 3 for right bottom corner
         * @returns A rotated point representing the corner coordination centered in this bounding box from given index
         */
        [[nodiscard]] GeoVector2F getCornerInLocalSpace(int32_t index) const noexcept;

        /**
         * @brief Get rotationally transformed corner coordination with applied offset in position for this bounding box, index represents the corner starting top left to right bottom.
         * @param index 0 for left top corner, 1 for right top corner, 2 for left bottom corner, and 3 for right bottom corner
         * @returns An applied offset to rotated point representing the corner coordination centered in this bounding box from given index
         */
        [[nodiscard]] GeoVector2F getCornerInWorldSpace(int32_t index) const noexcept;

        /**
         * @brief Returns an extent that is represented by the Width and Height with X/Y components
         * @returns Returns an extent that is represented by the Width and Height with X/Y components
         */
        [[nodiscard]] GeoVector2F getExtents() const noexcept;

        /**
         * @brief Evaluates the bounding box to another bounding box whether or not if position, size, and rotation matches.
         * @returns True if all position, size, and rotation components matches between this and other bounding boxes, otherwise false
         */
        inline bool operator==(GeoBounds other) const noexcept
        {
            return position == other.position && size == other.size && rotation == other.rotation;
        }

        /**
         * @brief Evaluates the bounding box to another bounding box whether or not if position, size, and rotation does not match.
         * @returns True if any or all components of either bounding boxes does not match, otherwise true
         */
        inline bool operator!=(GeoBounds other) const noexcept
        {
            return position != other.position || size != other.size || rotation != other.rotation;
        }

        /**
         * @brief Gets the Axis Aligned Bounding Box based on the position and scale of the specified transform.
         */
        static inline Maths::GeoBounds GetAABBFromTransform(Transform transform)
        {
            auto maxFscale = fmaxf(transform.scale.x, transform.scale.y);
            return GeoBounds(transform.position, Maths::GeoVector2F(maxFscale, maxFscale), 0);
        }

        /**
         * @brief Gets the bounds based on the position, scale and rotation of the specified transform.
         */
        static inline Maths::GeoBounds FromTransform(Transform transform) noexcept
        {
            return GeoBounds(transform.position, transform.scale, transform.rotation);
        }
    };
} // namespace NovelRT::Maths

#endif //! NOVELRT_MATHS_GEOBOUNDS_H
