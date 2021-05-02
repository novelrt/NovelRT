
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_CAMERA_H
#define NOVELRT_INTEROP_GRAPHICS_CAMERA_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtCameraHandle Nrt_Camera_create();
    NrtGeoMatrix4x4F Nrt_Camera_getViewMatrix(NrtCameraHandle camera);
    NrtResult Nrt_Camera_setViewMatrix(NrtCameraHandle camera, NrtGeoMatrix4x4F inputMatrix);
    NrtGeoMatrix4x4F Nrt_Camera_getProjectionMatrix(NrtCameraHandle camera);
    NrtResult Nrt_Camera_setProjectionMatrix(NrtCameraHandle camera, NrtGeoMatrix4x4F inputMatrix);
    NrtGeoMatrix4x4F Nrt_Camera_getCameraUboMatrix(NrtCameraHandle camera);
    NrtCameraFrameState Nrt_Camera_getFrameState(NrtCameraHandle camera);
    NrtResult Nrt_Camera_setForceResizeCallback(NrtCameraHandle camera,
                                                void (*callback)(NrtCameraHandle, NrtGeoVector2F, void*), void* context);
    NrtCameraHandle Nrt_Camera_createDefaultOrthographicProjection(NrtGeoVector2F windowSize);
    NrtCameraHandle Nrt_Camera_createDefaultPerspectiveProjection(NrtGeoVector2F windowSize);
    NrtResult Nrt_Camera_destroy(NrtCameraHandle camera);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_GRAPHICS_CAMERA_H
