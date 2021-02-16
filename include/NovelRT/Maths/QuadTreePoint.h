#ifndef NOVELRT_MATHS_QUADTREENODE_H
#define NOVELRT_MATHS_QUADTREENODE_H

#include "GeoVector2F.h"

namespace NovelRT::Maths
{
    class QuadTreePoint : public std::enable_shared_from_this<QuadTreePoint>
    {
    private:
        GeoVector2F _position;

    public:
        QuadTreePoint(GeoVector2F position) : _position(position)
        {
        }

        QuadTreePoint(float x, float y) : QuadTreePoint(GeoVector2F(x, y))
        {
        }

        GeoVector2F getPosition() const noexcept
        {
            return _position;
        }
    };
} // namespace NovelRT::Maths

#endif //! NOVELRT_MATHS_QUADTREENODE_H
