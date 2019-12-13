// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GEOBOUNDS_H
#define NOVELRT_GEOBOUNDS_H

#include "GeoVector.h"
#include <vector>
namespace NovelRT {
  class GeoBounds {

  private:
    GeoVector<float> _position;
    std::vector<GeoVector<float>> _corners = std::vector<GeoVector<float>>(4);
    void rotateToAngle(float rotationAngleValue);

  public:
    GeoBounds(const GeoVector<float>& position, const GeoVector<float>& size, float rotation);
    bool pointIsWithinBounds(const GeoVector<float>& point) const;
    GeoVector<float> getCornerInWorldSpace(int index) const;
    GeoVector<float> getCornerInOpenGLSurfaceSpace(int index, float screenScale) const;
  };
}
#endif //NOVELRT_GEOBOUNDS_H
