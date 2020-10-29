
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_CAMERA_H
#define NOVELRT_INTEROP_GRAPHICS_CAMERA_H

#include "NovelRTGraphicsTypedefs.h"
#include "../Maths/NovelRTGeoMatrix4x4F.h"
#include "NovelRTCameraFrameState.h"

#ifdef __cplusplus
extern "C" {
#endif

  NovelRTCamera NovelRT_Camera_create();
  int32_t NovelRT_Camera_getViewMatrix(NovelRTCamera camera, NovelRTGeoMatrix4x4F* outputMatrix);
  int32_t NovelRT_Camera_setViewMatrix(NovelRTCamera camera, NovelRTGeoMatrix4x4F inputMatrix);
  int32_t NovelRT_Camera_getProjectionMatrix(NovelRTCamera camera, NovelRTGeoMatrix4x4F* outputMatrix);
  int32_t NovelRT_Camera_setProjectionMatrix(NovelRTCamera camera, NovelRTGeoMatrix4x4F inputMatrix);
  int32_t NovelRT_Camera_getCameraUboMatrix(NovelRTCamera camera, NovelRTGeoMatrix4x4F* outputMatrix);
  int32_t NovelRT_Camera_getFrameState(NovelRTCamera camera, NovelRTCameraFrameState* outputFrameState);
  int32_t NovelRT_Camera_setForceResizeCallback(NovelRTCamera camera, void(*callback)(NovelRTCamera, NovelRTGeoVector2F));
  NovelRTCamera NovelRT_Camera_createDefaultOrthographicProjection(NovelRTGeoVector2F windowSize);
  NovelRTCamera NovelRT_Camera_createDefaultPerspectiveProjection(NovelRTGeoVector2F windowSize);
  int32_t NovelRT_Camera_destroy(NovelRTCamera camera);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_GRAPHICS_CAMERA_H
