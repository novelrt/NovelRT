// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Maths {
  void QuadTree::subdivideTree() noexcept {
    assert(getPointCount() == POINT_CAPACITY);

    const GeoVector2<float> TOP_LEFT_SCALE = GeoVector2<float>(-0.5, +0.5);
    const GeoVector2<float> TOP_RIGHT_SCALE = GeoVector2<float>(+0.5, +0.5);
    const GeoVector2<float> BOTTOM_LEFT_SCALE = GeoVector2<float>(-0.5, -0.5);
    const GeoVector2<float> BOTTOM_RIGHT_SCALE = GeoVector2<float>(+0.5, -0.5);

    GeoVector2 size = getBounds().size() / 2;
    GeoVector2 position = getBounds().position();

    _children[TOP_LEFT] = std::make_unique<QuadTree>(GeoBounds(position + (size * TOP_LEFT_SCALE), size, 0), weak_from_this());
    _children[TOP_RIGHT] = std::make_unique<QuadTree>(GeoBounds(position + (size * TOP_RIGHT_SCALE), size, 0), weak_from_this());
    _children[BOTTOM_LEFT] = std::make_unique<QuadTree>(GeoBounds(position + (size * BOTTOM_LEFT_SCALE), size, 0), weak_from_this());
    _children[BOTTOM_RIGHT] = std::make_unique<QuadTree>(GeoBounds(position + (size * BOTTOM_RIGHT_SCALE), size, 0), weak_from_this());

    for (size_t i = 0; i < getPointCount(); i++) {
      auto point = getPoint(i);

      auto result = tryInsert(point);
      assert(result); unused(result);

      _points[i] = nullptr;
    }

    _pointCount = 0;
  }

  void QuadTree::tryMergeTree() noexcept {
    auto parent = getParent().lock();

    if (parent == nullptr) {
      return;
    }

    size_t totalPointCount = 0;

    for (auto child : parent->_children) {
      if (child->getTopLeft() != nullptr) {
        return;
      }
      totalPointCount += child->getPointCount();
    }

    if (totalPointCount <= POINT_CAPACITY) {
      size_t d = 0;

      for (size_t c = 0; c < 4; c++) {
        auto child = parent->_children[c];

        for (size_t s = 0; s < child->getPointCount(); s++) {
          parent->_points[d++] = child->getPoint(s);
        }

        parent->_children[c] = nullptr;
      }

      assert(d == totalPointCount);
      parent->_pointCount = totalPointCount;
    }
  }
}
