// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GEOBOUNDS_H
#define NOVELRT_GEOBOUNDS_H

#include "GeoVector.h"
#include <vector>
#include "Lazy.h"

namespace NovelRT {
class GeoBounds {
public:
  GeoBounds(const GeoVector<float>& position, const GeoVector<float>& size, float rotation);
  bool pointIsWithinBounds(const GeoVector<float>& point) const;
  GeoVector<float> getCornerInLocalSpace(int index) const;
  GeoVector<float> getCornerInWorldSpace(int index) const;
  GeoVector<float> getPosition() const;
  void setPosition(const GeoVector<float>& value);
  GeoVector<float> getSize() const;
  void setSize(const GeoVector<float>& value);
  float getRotation() const;
  void setRotation(float value);

private:
  GeoVector<float> _position;
  float _rotation;
  GeoVector<float> _size;
};
}
#endif //NOVELRT_GEOBOUNDS_H
