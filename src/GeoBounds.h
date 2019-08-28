//
// Created by matth on 30/03/2019.
//

#ifndef NOVELRT_GEOBOUNDS_H
#define NOVELRT_GEOBOUNDS_H

#include "GeoVector.h"
#include <vector>
namespace NovelRT {
class GeoBounds {
public:
  GeoBounds(const GeoVector<float>& position, const GeoVector<float>& size, float rotation);
  bool pointIsWithinBounds(const GeoVector<float>& point) const;
  GeoVector<float> getCornerInWorldSpace(const int index) const;
  GeoVector<float> getCornerInOpenGLSurfaceSpace(const int index, const float scale) const;
private:
  std::vector<GeoVector<float>> _corners = std::vector<GeoVector<float>>(4);
  void rotateToAngle(float rotationAngleValue);
  GeoVector<float> _position;
};
}
#endif //NOVELRT_GEOBOUNDS_H
