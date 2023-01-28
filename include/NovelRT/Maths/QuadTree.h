#ifndef NOVELRT_MATHS_QUADTREE_H
#define NOVELRT_MATHS_QUADTREE_H

#ifndef NOVELRT_MATHS_H
#error NovelRT does not support including types explicitly by default. Please include Maths.h instead for the Maths namespace subset.
#endif

namespace NovelRT::Maths
{
    /**
     * @brief A point quadtree used for comparing two-dimensional points.
     */
    class QuadTree : public std::enable_shared_from_this<QuadTree>
    {
    private:
        static const int32_t POINT_CAPACITY = 4;

        static const int32_t TOP_LEFT = 0;
        static const int32_t TOP_RIGHT = 1;
        static const int32_t BOTTOM_LEFT = 2;
        static const int32_t BOTTOM_RIGHT = 3;

        std::weak_ptr<QuadTree> _parent;
        GeoBounds _bounds;
        std::array<std::shared_ptr<QuadTreePoint>, POINT_CAPACITY> _points;
        std::array<std::shared_ptr<QuadTree>, 4> _children;
        size_t _pointCount;

        void subdivideTree() noexcept;
        void tryMergeTree() noexcept;

    public:
        /**
         * @brief Instantiates a QuadTree instance with the specified bounds and parent.
         *
         * @param bounds The area in which this QuadTree will map points.
         * @param parent The parent to this instance in the tree's hierarchy. If none is provided, this QuadTree
         * instance will be at the root of the hierarchy.
         * @return Newly constructed QuadTree object.
         */
        [[nodiscard]] explicit QuadTree(GeoBounds bounds,
                          std::weak_ptr<QuadTree> parent = std::shared_ptr<QuadTree>(nullptr)) noexcept
            : _parent(parent), _bounds(bounds), _points(), _children(), _pointCount(0)
        {
        }

        /**
         * @brief Returns a pointer to the parent instance in this QuadTree's hierarchy.
         *
         * @return A std::weak_ptr<QuadTree>& to the parent QuadTree. if this instance is the root of the tree, nullptr
         * is returned instead.
         */
        [[nodiscard]] const std::weak_ptr<QuadTree>& getParent() const noexcept
        {
            return _parent;
        }

        /**
         * @brief Returns the bounds this QuadTree covers.
         *
         * @return The area in which this QuadTree maps points.
         */
        [[nodiscard]] GeoBounds getBounds() const noexcept
        {
            return _bounds;
        }

        /**
         * @brief Returns the point instance under the specified index.
         *
         * @param index The index of the point to retrieve. A valid index ranges from 0 to 3 inclusive.
         * @return A std::shared_ptr<TQuadTreePoint>&, pointing to the instance. If no instance was stored under the
         * given index, nullptr is returned instead.
         */
        [[nodiscard]] const std::shared_ptr<QuadTreePoint>& getPoint(size_t index) const noexcept
        {
            return _points[index];
        }

        /**
         * @brief Returns the point instance under the specified index.
         *
         * @tparam TQuadTreePoint A point type that can be casted as a QuadTreePoint instance.
         * @param index The index of the point to retrieve. A valid index ranges from 0 to 3 inclusive.
         * @return A std::shared_ptr<QuadTreePoint>& to the QuadTreePoint instance. If no instance was stored under the
         * given index, nullptr is returned instead.
         */
        template<typename TQuadTreePoint> [[nodiscard]] const std::shared_ptr<TQuadTreePoint>& getPoint(size_t index) const
        {
            return static_cast<std::shared_ptr<TQuadTreePoint>>(getPoint(index));
        }

        /**
         * @brief Returns the amount of points stored in this QuadTree instance.
         *
         * @return The number of points stored in this instance.
         */
        [[nodiscard]] size_t getPointCount() const noexcept
        {
            return _pointCount;
        }

        /**
         * @brief Returns the child QuadTree node for the top left area.
         *
         * @return The child QuadTree covering the top left area of this QuadTree. If this QuadTree instance does not
         * have any children, nullptr is returned instead.
         */
        [[nodiscard]] const std::shared_ptr<QuadTree>& getTopLeft() const noexcept
        {
            return _children[TOP_LEFT];
        }

        /**
         * @brief Returns the child QuadTree node for the top right area.
         *
         * @return The child QuadTree covering the top right area of this QuadTree. If this QuadTree instance does not
         * have any children, nullptr is returned instead.
         */
        [[nodiscard]] const std::shared_ptr<QuadTree>& getTopRight() const noexcept
        {
            return _children[TOP_RIGHT];
        }

        /**
         * @brief Returns the child QuadTree node for the bottom left area.
         *
         * @return The child QuadTree covering the botom left area of this QuadTree. If this QuadTree instance does not
         * have any children, nullptr is returned instead.
         */
        [[nodiscard]] const std::shared_ptr<QuadTree>& getBottomLeft() const noexcept
        {
            return _children[BOTTOM_LEFT];
        }

        /**
         * @brief Returns the child QuadTree node for the bottom right area.
         *
         * @return The child QuadTree covering the bottom right area of this QuadTree. If this QuadTree instance does
         * not have any children, nullptr is returned instead.
         */
        [[nodiscard]] const std::shared_ptr<QuadTree>& getBottomRight() const noexcept
        {
            return _children[BOTTOM_RIGHT];
        }

        /**
         * @brief Attempts to store the given point within this QuadTree's hierarchy.
         *
         * @param point A pointer to a two-dimensional position instance.
         * @return true if a point has succesfully been inserted, otherwise false.
         */
        [[nodiscard]] bool tryInsert(std::shared_ptr<QuadTreePoint> point) noexcept
        {
            if (point == nullptr || !getBounds().pointIsWithinBounds(point->getPosition()))
            {
                return false;
            }

            if (getTopLeft() == nullptr)
            {
                if (getPointCount() < POINT_CAPACITY)
                {
                    _points[_pointCount++] = point;
                    return true;
                }
                subdivideTree();
            }

            auto result = getTopLeft()->tryInsert(point) || getTopRight()->tryInsert(point) ||
                          getBottomLeft()->tryInsert(point) || getBottomRight()->tryInsert(point);

            assert(result);
            return result;
        }

        /**
         * @brief Attempts to insert a bounding box into the quadtree.
         *
         * @details
         * A TQuadTreePoint most have a constructor that matches TQuadTreePoint(GeoVector, TArgs).
         *
         * @tparam TQuadTreePoint A point type that can be casted as a QuadTreePoint instance.
         * @tparam ...TArgs The variable length argument types for constructing a TQuadTreePoint.
         * @param bounds The bounding area to insert into the QuadTree
         * @param ...args Additional arguments needed to create the point instance.
         * @return true if a TQuadTreePoint has succesfully been inserted, otherwise false.
         */
        template<typename TQuadTreePoint, typename... TArgs> [[nodiscard]] bool tryInsert(GeoBounds bounds, TArgs... args)
        {
            return tryInsert(std::make_shared<TQuadTreePoint>(bounds.getCornerInWorldSpace(0),
                                                              std::forward<TArgs>(args)...)) ||
                   tryInsert(std::make_shared<TQuadTreePoint>(bounds.getCornerInWorldSpace(1),
                                                              std::forward<TArgs>(args)...)) ||
                   tryInsert(std::make_shared<TQuadTreePoint>(bounds.getCornerInWorldSpace(3),
                                                              std::forward<TArgs>(args)...)) ||
                   tryInsert(
                       std::make_shared<TQuadTreePoint>(bounds.getCornerInWorldSpace(2), std::forward<TArgs>(args)...));
        }

        /**
         * @brief Attempts to remove a point from the QuadTree.
         *
         * @param point The point to remove from the QuadTree,
         * @return true if the point has been succesfully removed, otherwise false.
         */
        [[nodiscard]] bool tryRemove(std::shared_ptr<QuadTreePoint> point) noexcept
        {
            if (point == nullptr || !getBounds().pointIsWithinBounds(point->getPosition()))
            {
                return false;
            }

            if (getTopLeft() == nullptr)
            {
                for (size_t i = 0; i < getPointCount(); i++)
                {
                    if (getPoint(i) == point)
                    {
                        auto lastPoint = --_pointCount;
                        _points[i] = getPoint(lastPoint);
                        _points[lastPoint] = nullptr;
                        tryMergeTree();
                        return true;
                    }
                }
                return false;
            }

            return getTopLeft()->tryRemove(point) || getTopRight()->tryRemove(point) ||
                   getBottomLeft()->tryRemove(point) || getBottomRight()->tryRemove(point);
        }

        /**
         * @brief Gets a set of points that intersect with the given bounds and stores it in the given vector.
         *
         * @param bounds The area in which to look for points in the QuadTree.
         * @param intersectingPoints A collection of points that will be filled with the intersecting points.
         */
        void getIntersectingPoints(GeoBounds bounds, std::vector<std::shared_ptr<QuadTreePoint>>& intersectingPoints)
        {
            if (!getBounds().intersectsWith(bounds))
            {
                return;
            }

            if (getTopLeft() == nullptr)
            {
                for (size_t index = 0; index < getPointCount(); index++)
                {
                    auto point = getPoint(index);
                    if (bounds.pointIsWithinBounds(point->getPosition()))
                    {
                        intersectingPoints.emplace_back(point);
                    }
                }
            }
            else
            {
                getTopLeft()->getIntersectingPoints(bounds, intersectingPoints);
                getTopRight()->getIntersectingPoints(bounds, intersectingPoints);
                getBottomLeft()->getIntersectingPoints(bounds, intersectingPoints);
                getBottomRight()->getIntersectingPoints(bounds, intersectingPoints);
            }
        }

        /**
         * @brief Gets a set of points that intersect with the given bounds.
         *
         * @param bounds The area in which to look for points in the QuadTree.
         * @return A collection of points filled with the intersecting points.
         */
        [[nodiscard]] std::vector<std::shared_ptr<QuadTreePoint>> getIntersectingPoints(GeoBounds bounds)
        {
            auto intersectingPoints = std::vector<std::shared_ptr<QuadTreePoint>>();
            getIntersectingPoints(bounds, intersectingPoints);
            return intersectingPoints;
        }
    };
}

#endif //! NOVELRT_MATHS_QUADTREE_H
