// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_CAMERA_H
#define NOVELRT_GRAPHICS_CAMERA_H
#include "../Maths/GeoMatrix4.h"
#include "../Utilities/Lazy.h"
#include "../Utilities/Misc.h"
#include "../Maths/GeoVector.h"
#include "CameraViewChangedEventArgs.h"

namespace NovelRT::Graphics {
  class Camera {

    NOVELRT_EVENT(CameraViewChanged, CameraViewChangedEventArgs)

      //TODO: Look Im just trying to make this legal code okay?
  public:
    enum class CameraMode : unsigned int {
      None,
      Orthographic,
      Perspective
    };

  private:

    Maths::GeoMatrix4<float> _viewMatrix;
    Maths::GeoMatrix4<float> _projectionMatrix;
    Utilities::Lazy<Maths::GeoMatrix4<float>> _cameraUboMatrix;

    Maths::GeoMatrix4<float> generateUboMatrix();
    CameraMode _cameraMode;

  public:

    Camera();

    inline Maths::GeoMatrix4<float> getViewMatrix() const {
      return _viewMatrix;
    }

    //TODO: Jeez this is written badly
    inline void setViewMatrix(Maths::GeoMatrix4<float> value) {
      _cameraUboMatrix.reset();
      _viewMatrix = value;
      raiseCameraViewChanged(CameraViewChangedEventArgs(getCameraUboMatrix()));
    }

    inline Maths::GeoMatrix4<float> getProjectionMatrix() const {
      return _projectionMatrix;
    }

    inline void setProjectionMatrix(Maths::GeoMatrix4<float> value) {
      _cameraUboMatrix.reset();
      _projectionMatrix = value;
      raiseCameraViewChanged(CameraViewChangedEventArgs(getCameraUboMatrix()));
    }

    inline Maths::GeoMatrix4<float> getCameraUboMatrix() {
      return _cameraUboMatrix.getActual();
    }
  };
}
#endif //NOVELRT_GRAPHICS_CAMERA_H
