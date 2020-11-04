
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_CAMERA_H
#define NOVELRT_INTEROP_GRAPHICS_CAMERA_H

#include "NrtGraphicsTypedefs.h"
#include "../Maths/NrtGeoMatrix4x4F.h"
#include "NrtCameraFrameState.h"

#ifdef __cplusplus
extern "C" {
#endif

  NrtCamera Nrt_Camera_create();
  NrtResult Nrt_Camera_getViewMatrix(NrtCamera camera, NrtGeoMatrix4x4F* outputMatrix);
  NrtResult Nrt_Camera_setViewMatrix(NrtCamera camera, NrtGeoMatrix4x4F inputMatrix);
  NrtResult Nrt_Camera_getProjectionMatrix(NrtCamera camera, NrtGeoMatrix4x4F* outputMatrix);
  NrtResult Nrt_Camera_setProjectionMatrix(NrtCamera camera, NrtGeoMatrix4x4F inputMatrix);
  NrtResult Nrt_Camera_getCameraUboMatrix(NrtCamera camera, NrtGeoMatrix4x4F* outputMatrix);
  NrtResult Nrt_Camera_getFrameState(NrtCamera camera, NrtCameraFrameState* outputFrameState);
  NrtResult Nrt_Camera_setForceResizeCallback(NrtCamera camera, void(*callback)(NrtCamera, NrtGeoVector2F));
  NrtCamera Nrt_Camera_createDefaultOrthographicProjection(NrtGeoVector2F windowSize);
  NrtCamera Nrt_Camera_createDefaultPerspectiveProjection(NrtGeoVector2F windowSize);
  NrtResult Nrt_Camera_destroy(NrtCamera camera);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_CAMERA_H
