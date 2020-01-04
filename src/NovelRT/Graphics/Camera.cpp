// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Graphics {
  Camera::Camera() : _cameraFrameState(CameraFrameState::ModifiedInCurrent), _cameraUboMatrix(Utilities::Lazy<Maths::GeoMatrix4<float>>(std::function<Maths::GeoMatrix4<float>()>(std::bind(&Camera::generateUboMatrix,
    this)))) {}

  std::unique_ptr<Camera> Camera::createDefaultOrthographicProjection(const Maths::GeoVector<float>& windowSize) {
    auto returnVal = std::make_unique<Camera>();
    returnVal->setProjectionMatrix(Maths::GeoMatrix4<float>(glm::ortho<float>(0, windowSize.getX(), windowSize.getY(), 0, 0, 65535)));
    returnVal->setViewMatrix(Maths::GeoMatrix4<float>(glm::scale(glm::vec3(windowSize.getX() / 1920.0f, windowSize.getY() / 1080.0f, -1.0f))));
    return returnVal;
  }

  Maths::GeoMatrix4<float> Camera::generateUboMatrix() {
    return getProjectionMatrix() * getViewMatrix();
  }

  void Camera::initialiseCameraForFrame() {
    switch (_cameraFrameState) {
      case CameraFrameState::ModifiedInCurrent:
        _cameraFrameState = CameraFrameState::ModifiedInLast;
        break;
      case CameraFrameState::ModifiedInLast:
        _cameraFrameState = CameraFrameState::Unmodified;
    }
  }
}
