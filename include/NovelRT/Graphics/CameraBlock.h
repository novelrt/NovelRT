// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#ifndef NOVELRT_CAMERABLOCK_H
#define NOVELRT_CAMERABLOCK_H
#include <glm/glm.hpp>

namespace NovelRT::Graphics {
  struct CameraBlock {
    glm::mat4 cameraMatrix;
    CameraBlock(glm::mat4 matrix) {
      cameraMatrix = matrix;
    }
  };
}
#endif
