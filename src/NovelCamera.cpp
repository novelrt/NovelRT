// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelCamera.h"

namespace NovelRT {
NovelCamera::NovelCamera() : _cameraUboMatrix(Lazy<GeoMatrix4<float>>(std::function<GeoMatrix4<float>()>(std::bind(&NovelCamera::generateUboMatrix,
                                                                                           this)))),
                             _cameraUbo(std::function<GLuint()>([] {
                               GLuint tempHandle;
                               glGenBuffers(1, &tempHandle);
                               glBindBuffer(GL_UNIFORM_BUFFER, tempHandle);
                               glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraBlock), nullptr, GL_STATIC_DRAW);
                               glBindBuffer(GL_UNIFORM_BUFFER, 0);
                               glBindBufferRange(GL_UNIFORM_BUFFER, 0, tempHandle, 0, sizeof(CameraBlock));
                               return tempHandle;
                             })),
                             _cameraBlockObj(Lazy<CameraBlock>(std::function<CameraBlock()>(std::bind(&NovelCamera::generateCameraBlock, this)))){

}

GeoMatrix4<float> NovelCamera::generateUboMatrix() {
  return getProjectionMatrix() * getViewMatrix();
}

NovelCamera::CameraBlock NovelCamera::generateCameraBlock() {
  return CameraBlock{
      .cameraMatrix = _cameraUboMatrix.getActual().getUnderlyingMatrix()
  };
}

void NovelCamera::PushCameraMatrixToGPU(GLuint shaderProgramId) {
  GLuint cameraBufferIndex = glGetUniformBlockIndex(shaderProgramId, "cameraInformation");
  glUniformBlockBinding(shaderProgramId, cameraBufferIndex, 0);
  GLuint handle = _cameraUbo.getActual();
  glBindBuffer(GL_UNIFORM_BUFFER, handle);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(CameraBlock), &_cameraBlockObj.getActual());
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
}