#ifndef NOVELRT_MATHS_QUADTREENODE_H
#define NOVELRT_MATHS_QUADTREENODE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  class QuadTreePoint {
  public:
    virtual GeoVector<float>& getPosition() const noexcept = 0;
  };
}

#endif //!NOVELRT_MATHS_QUADTREENODE_H
