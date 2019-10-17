// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_CAMERAVIEWCHANGEDEVENTARGS_H
#define NOVELRT_CAMERAVIEWCHANGEDEVENTARGS_H
#include "GeoMatrix4.h"
namespace NovelRT {
struct CameraViewChangedEventArgs {
public:
  const GeoMatrix4<float> cameraMatrix;
  CameraViewChangedEventArgs(const GeoMatrix4<float>& newCameraMatrix) : cameraMatrix(newCameraMatrix){};
};
}

#endif //NOVELRT_CAMERAVIEWCHANGEDEVENTARGS_H
