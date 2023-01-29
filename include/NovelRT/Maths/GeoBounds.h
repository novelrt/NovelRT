// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOBOUNDS_H
#define NOVELRT_MATHS_GEOBOUNDS_H

#ifndef NOVELRT_MATHS_H
#error NovelRT does not support including types explicitly by default. Please include Maths.h instead for the Maths namespace subset.
#endif

namespace NovelRT::Maths
{
    /**
     * @brief Represents a bounding box in 2D space with rotational support.
     */
    class GeoBounds
    {
    public:
        /**
         * @brief The centre of the GeoBounds instance as a position in X,Y coordinates in the space used during its
         * creation.
         */
        GeoVector2F position;
        /**
         * @brief The size represented by width and height. This is subject to the space used during the creation of
         * the GeoBounds instance.
         */
        GeoVector2F size;
        /**
         * @brief The rotation of the GeoBounds instance represented in Degrees.
         */
        float rotation;

        /**
         * @brief Instantiates a GeoBounds instance with the specified position, size and rotation.
         *
         * @param position A starting point represented by X and Y in a given space.
         * @param size A size represented by width and height in a given space.
         * @param rotation A starting rotation for the GeoBounds instance that is represented in degrees.
         * @return Newly constructed GeoBounds object containing the position, size, and rotation components.
         */
        GeoBounds(GeoVector2F position, GeoVector2F size, float rotation) noexcept;

        /**
         * @brief Determines if a given GeoVector2F is within the confines of this bounding box.
         * @param point The GeoVector2F to be evaluated.
         * @return true if the given GeoVector2F is within the confines of this GeoBounds instance, otherwise false.
         */
        [[nodiscard]] bool PointIsWithinBounds(GeoVector2F point) const noexcept;

        /**
         * @brief Evaluates whether another GeoBounds instance intersects with this GeoBounds instance or not.
         *
         * This implementation does not support rotation, so only AABB intersection computation is allowed.
         *
         * @return true if the otherBounds intersects with this bounding box, otherwise false.
         * @exception Exceptions::NotSupportedException If either bounding box has a rotation set to a value other than
         * 0.
         */
        [[nodiscard]] bool IntersectsWith(GeoBounds otherBounds) const;

        /**
         * @brief Gets the specified corner, relative to the rotation and size of this GeoBounds instance.
         *
         * @param index 0 for top-left corner, 1 for top-right corner, 2 for bottom-left corner, and 3 for bottom-right
         * corner.
         * @return A GeoVector2F representing the local space position of the corner relative to the rotation and size
         * of the GeoBounds instance.
         */
        [[nodiscard]] GeoVector2F GetCornerInLocalSpace(int32_t index) const noexcept;

        /**
         * @brief Gets the specified corner in world space, relative to the position, rotation and size of this
         * GeoBounds instance.
         *
         * @param index 0 for top-left corner, 1 for top-right corner, 2 for bottom-left corner, and 3 for bottom-right
         * corner.
         * @return A GeoVector2F representing the world space position of the corner relative to the position, size and
         * rotation of the GeoBounds instance.
         */
        [[nodiscard]] GeoVector2F GetCornerInWorldSpace(int32_t index) const noexcept;

        /**
         * @brief Gets the extent of this GeoBounds instance that is represented by the width and height as a
         * GeoVector2F. The extents are always half the size of the GeoBounds instance.
         *
         * @return Returns a GeoVector2F that containts the width and height of the extents.
         */
        [[nodiscard]] GeoVector2F GetExtents() const noexcept;

        /**
         * @brief Evaluates if all the components match between two instances of GeoBounds.
         *
         * @return true if all components of the GeoBounds instances match, otherwise false.
         */
        [[nodiscard]] inline bool operator==(GeoBounds other) const noexcept
        {
            return position == other.position && size == other.size && rotation == other.rotation;
        }

        /**
         * @brief Evaluates if any of the components do not match between two instances of GeoBounds.
         *
         * @return true if any or all components of the GeoBounds instances do not match, otherwise true.
         */
        [[nodiscard]] inline bool operator!=(GeoBounds other) const noexcept
        {
            return position != other.position || size != other.size || rotation != other.rotation;
        }
    };
}

#endif //! NOVELRT_MATHS_GEOBOUNDS_H
