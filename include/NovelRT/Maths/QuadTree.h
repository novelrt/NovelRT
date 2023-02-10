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

        void SubdivideTree() noexcept;
        void MergeTree() noexcept;

    public:
        /**
         * @brief Instantiates a QuadTree instance with the specified bounds and parent.
         *
         * @param bounds The area in which this QuadTree will map points.
         * @param parent The parent to this instance in the tree's hierarchy. If none is provided, this QuadTree
         * instance will be at the root of the hierarchy.
         * @return Newly constructed QuadTree object.
         */
        explicit QuadTree(GeoBounds bounds,
                          std::weak_ptr<QuadTree> parent = std::shared_ptr<QuadTree>(nullptr)) noexcept
            : _parent(parent), _bounds(bounds), _points(), _children(), _pointCount(0)
        {
        }

        /**
         * @brief Returns a pointer to the parent instance in this QuadTree's hierarchy.
         *
         * @details
         * This method does not directly modify the QuadTree instance. Calling this without using the result has no
         * effect and introduces overhead for calling a method.
         *
         * @return A std::weak_ptr<QuadTree>& to the parent QuadTree. if this instance is the root of the tree, nullptr
         * is returned instead.
         */
        [[nodiscard]] const std::weak_ptr<QuadTree>& GetParent() const noexcept
        {
            return _parent;
        }

        /**
         * @brief Returns the bounds this QuadTree covers.
         *
         * @details
         * This method does not directly modify the QuadTree instance. Calling this without using the result has no
         * effect and introduces overhead for calling a method.
         *
         * @return The area in which this QuadTree maps points.
         */
        [[nodiscard]] GeoBounds GetBounds() const noexcept
        {
            return _bounds;
        }

        /**
         * @brief Returns the point instance under the specified index.
         *
         * @details
         * This method does not directly modify the QuadTree instance. Calling this without using the result has no
         * effect and introduces overhead for calling a method.
         *
         * @param index The index of the point to retrieve. A valid index ranges from 0 to 3 inclusive.
         * @return A std::shared_ptr<TQuadTreePoint>&, pointing to the instance. If no instance was stored under the
         * given index, nullptr is returned instead.
         */
        [[nodiscard]] const std::shared_ptr<QuadTreePoint>& GetPoint(size_t index) const noexcept
        {
            return _points[index];
        }

        /**
         * @brief Returns the point instance under the specified index.
         *
         * @details
         * This method does not directly modify the QuadTree instance. Calling this without using the result has no
         * effect and introduces overhead for calling a method.
         *
         * @tparam TQuadTreePoint A point type that can be casted as a QuadTreePoint instance.
         * @param index The index of the point to retrieve. A valid index ranges from 0 to 3 inclusive.
         * @return A std::shared_ptr<QuadTreePoint>& to the QuadTreePoint instance. If no instance was stored under the
         * given index, nullptr is returned instead.
         */
        template<typename TQuadTreePoint>
        [[nodiscard]] const std::shared_ptr<TQuadTreePoint>& GetPoint(size_t index) const
        {
            return static_cast<std::shared_ptr<TQuadTreePoint>>(GetPoint(index));
        }

        /**
         * @brief Returns the amount of points stored in this QuadTree instance.
         *
         * @details
         * This method does not directly modify the QuadTree instance. Calling this without using the result has no
         * effect and introduces overhead for calling a method.
         *
         * @return The number of points stored in this instance.
         */
        [[nodiscard]] size_t GetPointCount() const noexcept
        {
            return _pointCount;
        }

        /**
         * @brief Returns the child QuadTree node for the top left area.
         *
         * @details
         * This method does not directly modify the QuadTree instance. Calling this without using the result has no
         * effect and introduces overhead for calling a method.
         *
         * @return The child QuadTree covering the top left area of this QuadTree. If this QuadTree instance does not
         * have any children, nullptr is returned instead.
         */
        [[nodiscard]] const std::shared_ptr<QuadTree>& GetTopLeft() const noexcept
        {
            return _children[TOP_LEFT];
        }

        /**
         * @brief Returns the child QuadTree node for the top right area.
         *
         * @details
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return The child QuadTree covering the top right area of this QuadTree. If this QuadTree instance does not
         * have any children, nullptr is returned instead.
         */
        [[nodiscard]] const std::shared_ptr<QuadTree>& GetTopRight() const noexcept
        {
            return _children[TOP_RIGHT];
        }

        /**
         * @brief Returns the child QuadTree node for the bottom left area.
         *
         * @details
         * This method does not directly modify the QuadTree instance. Calling this without using the result has no
         * effect and introduces overhead for calling a method.
         *
         * @return The child QuadTree covering the bottom left area of this QuadTree. If this QuadTree instance does not
         * have any children, nullptr is returned instead.
         */
        [[nodiscard]] const std::shared_ptr<QuadTree>& GetBottomLeft() const noexcept
        {
            return _children[BOTTOM_LEFT];
        }

        /**
         * @brief Returns the child QuadTree node for the bottom right area.
         *
         * @details
         * This method does not directly modify the QuadTree instance. Calling this without using the result has no
         * effect and introduces overhead for calling a method.
         *
         * @return The child QuadTree covering the bottom right area of this QuadTree. If this QuadTree instance does
         * not have any children, nullptr is returned instead.
         */
        [[nodiscard]] const std::shared_ptr<QuadTree>& GetBottomRight() const noexcept
        {
            return _children[BOTTOM_RIGHT];
        }

        /**
         * @brief Attempts to store the given point within this QuadTree's hierarchy.
         *
         * @details
         * This method modifies the structure of the QuadTree, it is therefore recommended to use the result to handle
         * invalid behavior, for example: \code{.cpp}
         * [[maybe_unused]] bool result = TryInsert(point);
         * assert(result);
         * \endcode
         * In this example it is expected that TryInsert should always return true.
         *
         * @param point A pointer to a two-dimensional position instance.
         * @return true if a point has successfully been inserted, otherwise false.
         */
        [[nodiscard]] bool TryInsert(std::shared_ptr<QuadTreePoint> point) noexcept
        {
            if (point == nullptr || !GetBounds().PointIsWithinBounds(point->GetPosition()))
            {
                return false;
            }

            if (GetTopLeft() == nullptr)
            {
                if (GetPointCount() < POINT_CAPACITY)
                {
                    _points[_pointCount++] = point;
                    return true;
                }
                SubdivideTree();
            }

            auto result = GetTopLeft()->TryInsert(point) || GetTopRight()->TryInsert(point) ||
                          GetBottomLeft()->TryInsert(point) || GetBottomRight()->TryInsert(point);

            assert(result);
            return result;
        }

        /**
         * @brief Attempts to insert a bounding box into the QuadTree.
         *
         * @details
         * A TQuadTreePoint must have a constructor that matches TQuadTreePoint(GeoVector, TArgs).
         *
         * This method modifies the structure of the QuadTree, it is therefore recommended to use the result to handle
         * invalid behavior, for example: \code{.cpp}
         * [[maybe_unused]] bool result = TryInsert<MyQuadTreePoint>(bounds);
         * assert(result);
         * \endcode
         * In this example it is expected that TryInsert should always return true.
         *
         * @tparam TQuadTreePoint A point type that can be casted as a QuadTreePoint instance.
         * @tparam ...TArgs The variable length argument types for constructing a TQuadTreePoint.
         * @param bounds The bounding area to insert into the QuadTree
         * @param ...args Additional arguments needed to create the point instance.
         * @return true if a TQuadTreePoint has successfully been inserted, otherwise false.
         */
        template<typename TQuadTreePoint, typename... TArgs>
        [[nodiscard]] bool TryInsert(GeoBounds bounds, TArgs... args)
        {
            return TryInsert(std::make_shared<TQuadTreePoint>(bounds.GetCornerInWorldSpace(0),
                                                              std::forward<TArgs>(args)...)) ||
                   TryInsert(std::make_shared<TQuadTreePoint>(bounds.GetCornerInWorldSpace(1),
                                                              std::forward<TArgs>(args)...)) ||
                   TryInsert(std::make_shared<TQuadTreePoint>(bounds.GetCornerInWorldSpace(3),
                                                              std::forward<TArgs>(args)...)) ||
                   TryInsert(
                       std::make_shared<TQuadTreePoint>(bounds.GetCornerInWorldSpace(2), std::forward<TArgs>(args)...));
        }

        /**
         * @brief Attempts to remove a point from the QuadTree.
         *
         * @details
         * This method modifies the structure of the QuadTree, it is therefore recommended to use the result to handle
         * invalid behavior, for example: \code{.cpp}
         * [[maybe_unused]] bool result = TryRemove(point);
         * assert(result);
         * \endcode
         * In this example it is expected that TryRemove should always return true.
         *
         * @param point The point to remove from the QuadTree,
         * @return true if the point has been successfully removed, otherwise false.
         */
        [[nodiscard]] bool TryRemove(std::shared_ptr<QuadTreePoint> point) noexcept
        {
            if (point == nullptr || !GetBounds().PointIsWithinBounds(point->GetPosition()))
            {
                return false;
            }

            if (GetTopLeft() == nullptr)
            {
                for (size_t i = 0; i < GetPointCount(); i++)
                {
                    if (GetPoint(i) == point)
                    {
                        auto lastPoint = --_pointCount;
                        _points[i] = GetPoint(lastPoint);
                        _points[lastPoint] = nullptr;
                        MergeTree();
                        return true;
                    }
                }
                return false;
            }

            return GetTopLeft()->TryRemove(point) || GetTopRight()->TryRemove(point) ||
                   GetBottomLeft()->TryRemove(point) || GetBottomRight()->TryRemove(point);
        }

        /**
         * @brief Gets a set of points that intersect with the given bounds and stores it in the given vector.
         *
         * @param bounds The area in which to look for points in the QuadTree.
         * @param intersectingPoints A collection of points that will be filled with the intersecting points.
         */
        void GetIntersectingPoints(GeoBounds bounds, std::vector<std::shared_ptr<QuadTreePoint>>& intersectingPoints)
        {
            if (!GetBounds().IntersectsWith(bounds))
            {
                return;
            }

            if (GetTopLeft() == nullptr)
            {
                for (size_t index = 0; index < GetPointCount(); index++)
                {
                    auto point = GetPoint(index);
                    if (bounds.PointIsWithinBounds(point->GetPosition()))
                    {
                        intersectingPoints.emplace_back(point);
                    }
                }
            }
            else
            {
                GetTopLeft()->GetIntersectingPoints(bounds, intersectingPoints);
                GetTopRight()->GetIntersectingPoints(bounds, intersectingPoints);
                GetBottomLeft()->GetIntersectingPoints(bounds, intersectingPoints);
                GetBottomRight()->GetIntersectingPoints(bounds, intersectingPoints);
            }
        }

        /**
         * @brief Gets a set of points that intersect with the given bounds.
         *
         * @details
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @param bounds The area in which to look for points in the QuadTree.
         * @return A collection of points filled with the intersecting points.
         */
        [[nodiscard]] std::vector<std::shared_ptr<QuadTreePoint>> GetIntersectingPoints(GeoBounds bounds)
        {
            auto intersectingPoints = std::vector<std::shared_ptr<QuadTreePoint>>();
            GetIntersectingPoints(bounds, intersectingPoints);
            return intersectingPoints;
        }
    };
}

#endif //! NOVELRT_MATHS_QUADTREE_H
