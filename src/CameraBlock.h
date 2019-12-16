#ifndef NOVELRT_CAMERABLOCK_H
#define NOVELRT_CAMERABLOCK_H
namespace NovelRT {
  struct CameraBlock {
    glm::mat4 cameraMatrix;
    CameraBlock(glm::mat4 matrix) {
      cameraMatrix = matrix;
    }
  };
}
#endif
