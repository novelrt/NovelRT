#ifndef NOVELRT_MATHS_QUADTREENODE_H
#define NOVELRT_MATHS_QUADTREENODE_H

#ifndef NOVELRT_MATHS_H
#error NovelRT does not support including types explicitly by default. Please include Maths.h instead for the Maths namespace subset.
#endif

namespace NovelRT::Maths
{
    /**
     * @brief A point in space that can be stored inside of a QuadTree.
     */
    class QuadTreePoint : public std::enable_shared_from_this<QuadTreePoint>
    {
    private:
        GeoVector2F _position;

    public:
        /**
         * @brief Creates a QuadTreePoint with the given position.
         *
         * @param position The position in two-dimensional space for where the point is located.
         * @return A QuadTreePoint with the given position.
         */
        QuadTreePoint(GeoVector2F position) noexcept : _position(position)
        {
        }

        /**
         * @brief Creates a QuadTreePoint with the given position.
         *
         * @param x The X coordinate of the point's position.
         * @param y The Y coordinate of the point's position.
         * @return A QuadTreePoint with the given position.
         */
        QuadTreePoint(float x, float y) noexcept : QuadTreePoint(GeoVector2F(x, y))
        {
        }

        /**
         * @brief Gets the position of this point in two-dimensional space.
         *
         * @return The position in two-dimensional space of this point.
         */
        [[nodiscard]] GeoVector2F GetPosition() const noexcept
        {
            return _position;
        }
    };
}

#endif //! NOVELRT_MATHS_QUADTREENODE_H
