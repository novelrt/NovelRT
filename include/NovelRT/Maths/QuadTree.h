#ifndef NOVELRT_MATHS_QUADTREE_H
#define NOVELRT_MATHS_QUADTREE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  template <typename TQuadTreePoint>
  class QuadTree {
  private:
    static const int32_t POINT_CAPACITY = 4;

    static const int32_t TOP_LEFT = 0;
    static const int32_t TOP_RIGHT = 1;
    static const int32_t BOTTOM_LEFT = 2;
    static const int32_t BOTTOM_RIGHT = 3;

    typedef std::array<std::shared_ptr<TQuadTreePoint>, POINT_CAPACITY> TPoints;
    typedef std::array<std::unique_ptr<QuadTree>, 4> TChildren;

    GeoBounds _bounds;
    TPoints _points;
    TChildren _children;
    uint32_t _pointCount;

  public:
    explicit QuadTree(const GeoBounds& bounds) noexcept :
      _bounds(bounds),
      _points({}),
      _children({}),
      _pointCount(0) {
      static_assert(std::is_base_of<QuadTreePoint, TQuadTreePoint>::value, "Type argument for TQuadTreePoint must inherit NovelRT::Maths::QuadTreePoint!");
    }

    const GeoBounds& getBounds() const noexcept {
      return _bounds;
    }

    std::shared_ptr<TQuadTreePoint> getPoint(uint32_t index) const noexcept {
      return (index < _pointCount) ? _points[index] : nullptr;
    }

    uint32_t getPointCount() const noexcept {
      return _pointCount;
    }

    QuadTree* getTopLeft() const noexcept {
      return _children[TOP_LEFT].get();
    }

    QuadTree* getTopRight() const noexcept {
      return _children[TOP_RIGHT].get();
    }

    QuadTree* getBottomLeft() const noexcept {
      return _children[BOTTOM_LEFT].get();
    }

    QuadTree* getBottomRight() const noexcept {
      return _children[BOTTOM_RIGHT].get();
    }

    bool tryInsert(std::shared_ptr<TQuadTreePoint> point) noexcept {
      if (point == nullptr || !getBounds().pointIsWithinBounds(point->getPosition())) return false;

      if (_children[TOP_LEFT] == nullptr) {
        if (_pointCount < POINT_CAPACITY) {
          _points[_pointCount++] = point;
          return true;
        }
        subdivideTree();
      }

      auto result = _children[TOP_LEFT]->tryInsert(point) ||
                    _children[TOP_RIGHT]->tryInsert(point) ||
                    _children[BOTTOM_LEFT]->tryInsert(point) ||
                    _children[BOTTOM_RIGHT]->tryInsert(point);

      assert(result);
      return result;
    }

    void subdivideTree() noexcept {
      const GeoVector<float> TOP_LEFT_SCALE = GeoVector<float>(-0.5, +0.5);
      const GeoVector<float> TOP_RIGHT_SCALE = GeoVector<float>(+0.5, +0.5);
      const GeoVector<float> BOTTOM_LEFT_SCALE = GeoVector<float>(-0.5, -0.5);
      const GeoVector<float> BOTTOM_RIGHT_SCALE = GeoVector<float>(+0.5, -0.5);

      GeoVector size = getBounds().getSize() / 2;
      GeoVector position = getBounds().getPosition();

      _children[TOP_LEFT] = std::make_unique<QuadTree>(GeoBounds(position + (size * TOP_LEFT_SCALE), size, 0));
      _children[TOP_RIGHT] = std::make_unique<QuadTree>(GeoBounds(position + (size * TOP_RIGHT_SCALE), size, 0));
      _children[BOTTOM_LEFT] = std::make_unique<QuadTree>(GeoBounds(position + (size * BOTTOM_LEFT_SCALE), size, 0));
      _children[BOTTOM_RIGHT] = std::make_unique<QuadTree>(GeoBounds(position + (size * BOTTOM_RIGHT_SCALE), size, 0));

      for (uint32_t index = 0; index < getPointCount(); index++) {
        auto point = getPoint(index);
        auto result = tryInsert(point);
        assert(result); unused(result);
      }

      _pointCount = 0;
    }

    void getIntersectingPoints(const GeoBounds& bounds, std::vector<std::shared_ptr<TQuadTreePoint>>& intersectingPoints) {
      if (getBounds().intersectsWith(bounds)) {
        return;
      }

      if (_children[TOP_LEFT] == nullptr) {
        for (uint32_t index = 0; index < getPointCount(); index++) {
          auto point = getPoint(index);
          if (bounds.pointIsWithinBounds(point->getPosition())) {
            intersectingPoints.emplace_back(point);
          }
        }
      } else {
        _children[TOP_LEFT]->getIntersectingPoints(bounds, intersectingPoints);
        _children[TOP_RIGHT]->getIntersectingPoints(bounds, intersectingPoints);
        _children[BOTTOM_LEFT]->getIntersectingPoints(bounds, intersectingPoints);
        _children[BOTTOM_RIGHT]->getIntersectingPoints(bounds, intersectingPoints);
      }
    }

    std::vector<std::shared_ptr<TQuadTreePoint>> getIntersectingPoints(const GeoBounds& bounds) {
      auto intersectingPoints = std::vector<std::shared_ptr<TQuadTreePoint>>();
      getIntersectingPoints(bounds, intersectingPoints);
      return intersectingPoints;
    }
  };
}

#endif //!NOVELRT_MATHS_QUADTREE_H
