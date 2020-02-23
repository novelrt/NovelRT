#ifndef NOVELRT_MATHS_QUADTREE_H
#define NOVELRT_MATHS_QUADTREE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  class QuadTree : public std::enable_shared_from_this<QuadTree> {
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
    explicit QuadTree(const GeoBounds& bounds, std::weak_ptr<QuadTree> parent = std::shared_ptr<QuadTree>(nullptr)) noexcept :
      _parent(parent),
      _bounds(bounds),
      _points(),
      _children(),
      _pointCount(0) {
    }

    const std::weak_ptr<QuadTree>& getParent() const noexcept {
      return _parent;
    }

    const GeoBounds& getBounds() const noexcept {
      return _bounds;
    }

    const std::shared_ptr<QuadTreePoint>& getPoint(size_t index) const noexcept {
      return _points[index];
    }

    template <typename TQuadTreePoint>
    const std::shared_ptr<TQuadTreePoint>& getPoint(size_t index) const {
      return static_cast<std::shared_ptr<TQuadTreePoint>>(getPoint(index));
    }

    size_t getPointCount() const noexcept {
      return _pointCount;
    }

    const std::shared_ptr<QuadTree>& getTopLeft() const noexcept {
      return _children[TOP_LEFT];
    }

    const std::shared_ptr<QuadTree>& getTopRight() const noexcept {
      return _children[TOP_RIGHT];
    }

    const std::shared_ptr<QuadTree>& getBottomLeft() const noexcept {
      return _children[BOTTOM_LEFT];
    }

    const std::shared_ptr<QuadTree>& getBottomRight() const noexcept {
      return _children[BOTTOM_RIGHT];
    }

    bool tryInsert(std::shared_ptr<QuadTreePoint> point) noexcept {
      if (point == nullptr || !getBounds().pointIsWithinBounds(point->getPosition())) {
        return false;
      }

      if (getTopLeft() == nullptr) {
        if (getPointCount() < POINT_CAPACITY) {
          _points[_pointCount++] = point;
          return true;
        }
        subdivideTree();
      }

      auto result = getTopLeft()->tryInsert(point) ||
                    getTopRight()->tryInsert(point) ||
                    getBottomLeft()->tryInsert(point) ||
                    getBottomRight()->tryInsert(point);

      assert(result);
      return result;
    }

    template <typename TQuadTreePoint, typename... TArgs>
    bool tryInsert(const GeoBounds& bounds, TArgs... args) {
      return tryInsert(std::make_shared<TQuadTreePoint>(bounds.getCornerInWorldSpace(0), std::forward<TArgs>(args)...) ||
             tryInsert(std::make_shared<TQuadTreePoint>(bounds.getCornerInWorldSpace(1), std::forward<TArgs>(args)...) ||
             tryInsert(std::make_shared<TQuadTreePoint>(bounds.getCornerInWorldSpace(3), std::forward<TArgs>(args)...) ||
             tryInsert(std::make_shared<TQuadTreePoint>(bounds.getCornerInWorldSpace(2), std::forward<TArgs>(args)...);
    }

    bool tryRemove(std::shared_ptr<QuadTreePoint> point) noexcept {
      if (point == nullptr || !getBounds().pointIsWithinBounds(point->getPosition())) {
        return false;
      }

      if (getTopLeft() == nullptr) {
        for (size_t i = 0; i < getPointCount(); i++) {
          if (getPoint(i) == point) {
            auto lastPoint = --_pointCount;
            _points[i] = getPoint(lastPoint);
            _points[lastPoint] = nullptr;
            tryMergeTree();
            return true;
          }
        }
        return false;
      }

      return getTopLeft()->tryRemove(point) ||
             getTopRight()->tryRemove(point) ||
             getBottomLeft()->tryRemove(point) ||
             getBottomRight()->tryRemove(point);
    }

    void getIntersectingPoints(const GeoBounds& bounds, std::vector<std::shared_ptr<QuadTreePoint>>& intersectingPoints) {
      if (getBounds().intersectsWith(bounds)) {
        return;
      }

      if (getTopLeft() == nullptr) {
        for (size_t index = 0; index < getPointCount(); index++) {
          auto point = getPoint(index);
          if (bounds.pointIsWithinBounds(point->getPosition())) {
            intersectingPoints.emplace_back(point);
          }
        }
      } else {
        getTopLeft()->getIntersectingPoints(bounds, intersectingPoints);
        getTopRight()->getIntersectingPoints(bounds, intersectingPoints);
        getBottomLeft()->getIntersectingPoints(bounds, intersectingPoints);
        getBottomRight()->getIntersectingPoints(bounds, intersectingPoints);
      }
    }

    std::vector<std::shared_ptr<QuadTreePoint>> getIntersectingPoints(const GeoBounds& bounds) {
      auto intersectingPoints = std::vector<std::shared_ptr<QuadTreePoint>>();
      getIntersectingPoints(bounds, intersectingPoints);
      return intersectingPoints;
    }
  };
}

#endif //!NOVELRT_MATHS_QUADTREE_H
