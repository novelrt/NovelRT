// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelCamera.h"

namespace NovelRT {
NovelCamera::NovelCamera() : _cameraUboMatrix(std::function<GeoMatrix4<float>()>(std::bind(&NovelCamera::genUboMatrix, this))) {

}

GeoMatrix4<float> NovelCamera::genUboMatrix() {
  return getProjectionMatrix() * getViewMatrix();
}
}