// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../include/NovelCamera.h"
#include <glm/glm.hpp>

namespace NovelRT {
  NovelCamera::NovelCamera() : _cameraUboMatrix(Lazy<GeoMatrix4<float>>(std::function<GeoMatrix4<float>()>(std::bind(&NovelCamera::generateUboMatrix,
    this)))) {}

  GeoMatrix4<float> NovelCamera::generateUboMatrix() {
    return getProjectionMatrix() * getViewMatrix();
  }
}
