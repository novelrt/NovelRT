#ifndef NOVELRT_MATHS_QUADTREENODE_H
#define NOVELRT_MATHS_QUADTREENODE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  class QuadTreePoint : public std::enable_shared_from_this<QuadTreePoint> {
  private:
    GeoVector2F _position;

  public:
    QuadTreePoint(GeoVector2F position) :
      _position(position) {
    }

    QuadTreePoint(float x, float y) : QuadTreePoint(GeoVector2F(x, y)) {
    }

    const GeoVector2F& getPosition() const noexcept {
      return _position;
    }
  };
}

#endif //!NOVELRT_MATHS_QUADTREENODE_H
