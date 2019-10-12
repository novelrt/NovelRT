// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELCAMERA_H
#define NOVELRT_NOVELCAMERA_H
#include "GeoMatrix4.h"
#include "Lazy.h"

namespace NovelRT {
class NovelCamera {
private:
  GeoMatrix4<float> _viewMatrix;
  GeoMatrix4<float> _projectionMatrix;
  Lazy<GeoMatrix4<float>> _cameraUboMatrix;

  GeoMatrix4<float> genUboMatrix();

public:
  NovelCamera();

  inline GeoMatrix4<float> getViewMatrix() const {
    return _viewMatrix;
  }
  inline void setViewMatrix(GeoMatrix4<float> value) {
    _cameraUboMatrix.reset();
    _viewMatrix = value;
  }
  inline GeoMatrix4<float> getProjectionMatrix() const {
    return _projectionMatrix;
  }
  inline void setProjectionMatrix(GeoMatrix4<float> value) {
    _cameraUboMatrix.reset();
    _projectionMatrix = value;
  }
  inline GeoMatrix4<float> getCameraUboMatrix() {
    return _cameraUboMatrix.getActual();
  }
};
}
#endif //NOVELRT_NOVELCAMERA_H
