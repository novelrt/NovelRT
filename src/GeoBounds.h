//
// Created by matth on 30/03/2019.
//

#ifndef NOVELRT_GEOBOUNDS_H
#define NOVELRT_GEOBOUNDS_H

#include "GeoVector.h"
namespace NovelRT {
class GeoBounds {
public:
  GeoBounds(const GeoVector<float>& position, const GeoVector<float>& size);
  //GeoVector<float>> getCorners() const;
  bool pointIsWithinBounds(const GeoVector<float>& point) const;
  GeoVector<float> getCornerInWorldSpace(const int index) const;
  GeoVector<float> getCornerInOpenGLSurfaceSpace(const int index, const float scale) const;
private:
  GeoVector<float> _corners[4];
};
}
#endif //NOVELRT_GEOBOUNDS_H
