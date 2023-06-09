// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Core/Core.h>
#include <NovelRT/Maths/Maths.h>

namespace NovelRT::Maths
{
    void QuadTree::SubdivideTree() noexcept
    {
        assert(GetPointCount() == POINT_CAPACITY);

        const GeoVector2F TOP_LEFT_SCALE = GeoVector2F(-0.5f, +0.5f);
        const GeoVector2F TOP_RIGHT_SCALE = GeoVector2F(+0.5f, +0.5f);
        const GeoVector2F BOTTOM_LEFT_SCALE = GeoVector2F(-0.5f, -0.5f);
        const GeoVector2F BOTTOM_RIGHT_SCALE = GeoVector2F(+0.5f, -0.5f);

        GeoVector2F size = GetBounds().size / 2;
        GeoVector2F position = GetBounds().position;

        _children[TOP_LEFT] =
            std::make_unique<QuadTree>(GeoBounds(position + (size * TOP_LEFT_SCALE), size, 0), weak_from_this());
        _children[TOP_RIGHT] =
            std::make_unique<QuadTree>(GeoBounds(position + (size * TOP_RIGHT_SCALE), size, 0), weak_from_this());
        _children[BOTTOM_LEFT] =
            std::make_unique<QuadTree>(GeoBounds(position + (size * BOTTOM_LEFT_SCALE), size, 0), weak_from_this());
        _children[BOTTOM_RIGHT] =
            std::make_unique<QuadTree>(GeoBounds(position + (size * BOTTOM_RIGHT_SCALE), size, 0), weak_from_this());

        for (size_t i = 0; i < GetPointCount(); i++)
        {
            auto point = GetPoint(i);

            auto result = TryInsert(point);
            assert(result);
            unused(result);

            _points[i] = nullptr;
        }

        _pointCount = 0;
    }

    void QuadTree::MergeTree() noexcept
    {
        auto parent = GetParent().lock();

        if (parent == nullptr)
        {
            return;
        }

        size_t totalPointCount = 0;

        for (auto child : parent->_children)
        {
            if (child->GetTopLeft() != nullptr)
            {
                return;
            }
            totalPointCount += child->GetPointCount();
        }

        if (totalPointCount <= POINT_CAPACITY)
        {
            size_t d = 0;

            for (size_t c = 0; c < 4; c++)
            {
                auto child = parent->_children[c];

                for (size_t s = 0; s < child->GetPointCount(); s++)
                {
                    parent->_points[d++] = child->GetPoint(s);
                }

                parent->_children[c] = nullptr;
            }

            assert(d == totalPointCount);
            parent->_pointCount = totalPointCount;
        }
    }
} // namespace NovelRT::Maths
