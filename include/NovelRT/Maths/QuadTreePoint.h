// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_QUADTREENODE_H
#define NOVELRT_MATHS_QUADTREENODE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  class QuadTreePoint {
  private:
    GeoVector2<float> _position;

  public:
    QuadTreePoint(GeoVector2<float> position) :
      _position(position) {
    }

    QuadTreePoint(float x, float y) : QuadTreePoint(GeoVector2<float>(x, y)) {
    }

    const GeoVector2<float>& getPosition() const noexcept {
      return _position;
    }
  };
}

#endif //!NOVELRT_MATHS_QUADTREENODE_H
