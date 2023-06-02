// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>

namespace NovelRT::Maths
{
    GeoBounds::GeoBounds(GeoVector2F position, GeoVector2F size, float rotation) noexcept
        : position(position), size(size), rotation(rotation)
    {
    }

    bool GeoBounds::PointIsWithinBounds(GeoVector2F point) const noexcept
    {
        auto corner0 = GetCornerInWorldSpace(0);
        auto corner2 = GetCornerInWorldSpace(2);

        if (point.x >= corner0.x && point.x <= corner2.x && point.y <= corner2.y && point.y >= corner0.y)
            return true;

        return false;
    }

    bool GeoBounds::IntersectsWith(GeoBounds otherBounds) const
    {
        if (rotation != 0.0f || otherBounds.rotation != 0.0f)
            throw NovelRT::Core::Exceptions::NotSupportedException(
                "Box intersection does not currently support rotated bounds. AABB support only.");

        auto minA = position - GetExtents();
        auto maxA = position + GetExtents();

        auto minB = otherBounds.position - otherBounds.GetExtents();
        auto maxB = otherBounds.position + otherBounds.GetExtents();

        return !((minA > maxB) || (maxA < minB));
    }

    GeoVector2F GeoBounds::GetCornerInLocalSpace(int32_t index) const noexcept
    {
        GeoVector2F returnValue;
        auto boundsSize = size;
        switch (index)
        {
            case 0:
                returnValue = GeoVector2F(-(boundsSize.x / 2), -(boundsSize.y / 2));
                break;
            case 1:
                returnValue = GeoVector2F(+(boundsSize.x / 2), -(boundsSize.y / 2));
                break;
            case 2:
                returnValue = GeoVector2F(+(boundsSize.x / 2), +(boundsSize.y / 2));
                break;
            case 3:
                returnValue = GeoVector2F(-(boundsSize.x / 2), +(boundsSize.y / 2));
                break;
        }

        returnValue.RotateToAngleAroundPointDeg(rotation, position);
        return returnValue;
    }

    GeoVector2F GeoBounds::GetCornerInWorldSpace(int32_t index) const noexcept
    {
        return position + GetCornerInLocalSpace(index);
    }

    GeoVector2F GeoBounds::GetExtents() const noexcept
    {
        return size / 2.0f;
    }
} // namespace NovelRT::Maths
