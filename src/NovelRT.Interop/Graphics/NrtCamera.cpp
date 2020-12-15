// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <NovelRT.Interop/Graphics/NrtCamera.h>
#include <NovelRT.h>
#include <list>

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;

std::list<std::unique_ptr<Camera>> _cameraCollection;

#ifdef __cplusplus
extern "C" {
#endif

  NrtCamera Nrt_Camera_create() {
    _cameraCollection.push_back(std::make_unique<Camera>());
    return reinterpret_cast<NrtCamera>(_cameraCollection.back().get());
  }

  NrtGeoMatrix4x4F Nrt_Camera_getViewMatrix(NrtCamera camera) {
    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
    auto mat4 = cameraPtr->getViewMatrix();
    return *reinterpret_cast<NrtGeoMatrix4x4F*>(&mat4);
  }

  NrtResult Nrt_Camera_setViewMatrix(NrtCamera camera, NrtGeoMatrix4x4F inputMatrix) {
    if(camera == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
    cameraPtr->setViewMatrix(*reinterpret_cast<GeoMatrix4x4F*>(&inputMatrix));

    return NRT_SUCCESS;
  }

  NrtGeoMatrix4x4F Nrt_Camera_getProjectionMatrix(NrtCamera camera) {
    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
    auto mat4 = cameraPtr->getProjectionMatrix();
    return *reinterpret_cast<NrtGeoMatrix4x4F*>(&mat4);
  }

  NrtResult Nrt_Camera_setProjectionMatrix(NrtCamera camera, NrtGeoMatrix4x4F inputMatrix) {
    if(camera == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
    cameraPtr->setProjectionMatrix(*reinterpret_cast<GeoMatrix4x4F*>(&inputMatrix));

    return NRT_SUCCESS;

  }

  NrtGeoMatrix4x4F Nrt_Camera_getCameraUboMatrix(NrtCamera camera) {
    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
    auto mat4 = cameraPtr->getCameraUboMatrix();
    return *reinterpret_cast<NrtGeoMatrix4x4F*>(&mat4);
  }

  NrtCameraFrameState Nrt_Camera_getFrameState(NrtCamera camera) {
    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
    auto frameState = cameraPtr->getFrameState();
    return *reinterpret_cast<NrtCameraFrameState*>(&frameState);
  }

  NrtResult Nrt_Camera_setForceResizeCallback(NrtCamera camera, void(*callback)(NrtCamera, NrtGeoVector2F)) {
    if(camera == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
    cameraPtr->forceResizeCallback() = std::function<void(Camera*, GeoVector2F)>([callback](auto camera, auto newSize){ callback(reinterpret_cast<NrtCamera>(camera), *reinterpret_cast<NrtGeoVector2F*>(&newSize)); });

    return NRT_SUCCESS;
  }

  NrtCamera Nrt_Camera_createDefaultOrthographicProjection(NrtGeoVector2F windowSize) {
    _cameraCollection.push_back(Camera::createDefaultOrthographicProjection(*reinterpret_cast<GeoVector2F*>(&windowSize)));
    return reinterpret_cast<NrtCamera>(_cameraCollection.back().get());
  }

  NrtCamera Nrt_Camera_createDefaultPerspectiveProjection(NrtGeoVector2F windowSize) {
    _cameraCollection.push_back(Camera::createDefaultPerspectiveProjection(*reinterpret_cast<GeoVector2F*>(&windowSize)));
    return reinterpret_cast<NrtCamera>(_cameraCollection.back().get());
  }

  NrtResult Nrt_Camera_destroy(NrtCamera camera) {
    if(camera == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);

    for (auto& cppCamera : _cameraCollection) {
      if (cppCamera.get() != cameraPtr) {
        continue;
      }

      _cameraCollection.remove(cppCamera);
      return NRT_SUCCESS;
    }

    Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
    return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
  }

#ifdef __cplusplus
}
#endif
