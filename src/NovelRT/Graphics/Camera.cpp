// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>
#include <glm/glm.hpp>

namespace NovelRT::Graphics {
  Camera::Camera() : _cameraUboMatrix(Utilities::Lazy<Maths::GeoMatrix4<float>>(std::function<Maths::GeoMatrix4<float>()>(std::bind(&Camera::generateUboMatrix,
    this)))) {}

  Maths::GeoMatrix4<float> Camera::generateUboMatrix() {
    return getProjectionMatrix() * getViewMatrix();
  }
}
