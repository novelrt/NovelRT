// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Graphics {
  Camera::Camera() :
    _cameraUboMatrix(Utilities::Lazy<Maths::GeoMatrix4x4<float>>(std::function<Maths::GeoMatrix4x4<float>()>(std::bind(&Camera::generateUboMatrix, this)))),
    _cameraFrameState(CameraFrameState::ModifiedInCurrent) {
  }

  std::unique_ptr<Camera> Camera::createDefaultOrthographicProjection(const Maths::GeoVector2<float>& windowSize) {
    auto returnVal = std::make_unique<Camera>();
    returnVal->setProjectionMatrix(Maths::GeoMatrix4x4<float>(glm::ortho<float>(0, windowSize.getX(), windowSize.getY(), 0, 0, 65535)));
    returnVal->setViewMatrix(Maths::GeoMatrix4x4<float>(glm::scale(glm::vec3(windowSize.getX() / 1920.0f, windowSize.getY() / 1080.0f, -1.0f))));
    return returnVal;
  }

  Maths::GeoMatrix4x4<float> Camera::generateUboMatrix() {
    return getProjectionMatrix() * getViewMatrix();
  }

  void Camera::initialiseCameraForFrame() {
    switch (_cameraFrameState) {
      case CameraFrameState::ModifiedInCurrent:
        _cameraFrameState = CameraFrameState::ModifiedInLast;
        break;
      case CameraFrameState::ModifiedInLast:
        _cameraFrameState = CameraFrameState::Unmodified;
        break;
      case CameraFrameState::Unmodified:
        break;
    }
  }

  void Camera::forceResize(const Maths::GeoVector2<float>& windowSize) {
    setProjectionMatrix(Maths::GeoMatrix4x4<float>(glm::ortho<float>(0, windowSize.getX(), windowSize.getY(), 0, 0, 65535)));
    setViewMatrix(Maths::GeoMatrix4x4<float>(glm::scale(glm::vec3(windowSize.getX() / 1920.0f, windowSize.getY() / 1080.0f, -1.0f))));
  }
}
