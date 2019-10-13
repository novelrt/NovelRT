// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELCAMERA_H
#define NOVELRT_NOVELCAMERA_H
#include "GeoMatrix4.h"
#include "Lazy.h"
#include <glad/glad.h>

namespace NovelRT {
class NovelCamera {
private:
  struct CameraBlock {
    glm::mat4 cameraMatrix;
    CameraBlock(glm::mat4 matrix) {
      cameraMatrix = matrix;
    }
  };

  GeoMatrix4<float> _viewMatrix;
  GeoMatrix4<float> _projectionMatrix;
  Lazy<GeoMatrix4<float>> _cameraUboMatrix;
  Lazy<CameraBlock> _cameraBlockObj;

  GeoMatrix4<float> generateUboMatrix();
  CameraBlock generateCameraBlock();
  Lazy<GLuint> _cameraUbo;

public:
  NovelCamera();

  inline GeoMatrix4<float> getViewMatrix() const {
    return _viewMatrix;
  }

  inline void setViewMatrix(GeoMatrix4<float> value) {
    _cameraUboMatrix.reset();
    _cameraBlockObj.reset();
    _viewMatrix = value;
  }

  inline GeoMatrix4<float> getProjectionMatrix() const {
    return _projectionMatrix;
  }

  inline void setProjectionMatrix(GeoMatrix4<float> value) {
    _cameraUboMatrix.reset();
    _cameraBlockObj.reset();
    _projectionMatrix = value;
  }

  inline GeoMatrix4<float> getCameraUboMatrix() {
    return _cameraUboMatrix.getActual();
  }

  void PushCameraMatrixToGPU(GLuint shaderProgramId);
};
}
#endif //NOVELRT_NOVELCAMERA_H
