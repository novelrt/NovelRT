#ifndef NOVELRT_MATHS_QUADTREENODE_H
#define NOVELRT_MATHS_QUADTREENODE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  class QuadTreePoint {
  private:
    GeoVector<float> _position;

  public:
    QuadTreePoint(GeoVector<float> position) :
      _position(position) {
    }

    QuadTreePoint(float x, float y) : QuadTreePoint(GeoVector<float>(x, y)) {
    }

    const GeoVector<float>& getPosition() const noexcept {
      return _position;
    }
  };
}

#endif //!NOVELRT_MATHS_QUADTREENODE_H
