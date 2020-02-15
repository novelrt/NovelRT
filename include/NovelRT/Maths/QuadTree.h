#ifndef NOVELRT_MATHS_QUADTREE_H
#define NOVELRT_MATHS_QUADTREE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  template <typename TQuadTreePoint>
  class QuadTree {
  private:
    static const int32_t CAPACITY = 4;

    static const int32_t TOP_LEFT = 0;
    static const int32_t TOP_RIGHT = 1;
    static const int32_t BOTTOM_LEFT = 2;
    static const int32_t BOTTOM_RIGHT = 3;

    GeoBounds _bounds;
    TQuadTreePoint* _points[CAPACITY];
    std::unique_ptr<QuadTree> _children[4];

  public:
    explicit QuadTree(GeoBounds bounds) noexcept :
      _bounds(bounds),
      _points({}),
      _children({}) {
      static_assert(std::is_base_of<QuadTreePoint, TQuadTreePoint>::value, "Type argument for TQuadTreePoint must inherit NovelRT::Maths::QuadTreePoint!");
    }

    bool tryInsert(const TQuadTreePoint* const point) noexcept {
      if (point == nullptr || !_treeBounds.pointIsWithinBounds(point->getPosition())) return false;

      if (_children[TOP_LEFT] == nullptr) {
        if (_nodeObjects.size() < NODE_CAPACITY) {
          _nodeObjects.emplace_back(point);
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

      GeoVector size = _bounds.getSize() / 2;
      GeoVector position = _bounds.getPosition();

      _children[TOP_LEFT] = std::make_unique(new QuadTree(GeoBounds(position + (size * TOP_LEFT_SCALE), size, 0)));
      _children[TOP_RIGHT] = std::make_unique(new QuadTree(GeoBounds(position + (size * TOP_RIGHT_SCALE), size, 0)));
      _children[BOTTOM_LEFT] = std::make_unique(new QuadTree(GeoBounds(position + (size * BOTTOM_LEFT_SCALE), size, 0)));
      _children[BOTTOM_RIGHT] = std::make_unique(new QuadTree(GeoBounds(position + (size * BOTTOM_RIGHT_SCALE), size, 0)));

      for (auto point : _points) {
        auto result = tryInsert(point);
        assert(result);
      }

      _points = {};
    }
  };
}

#endif //!NOVELRT_MATHS_QUADTREE_H
