// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/Graphics/NovelRTCamera.h"
#include "NovelRT.h"
#include <list>

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;

std::list<std::unique_ptr<Camera>> _cameraCollection;

#ifdef __cplusplus
extern "C" {
#endif

  NovelRTCamera NovelRT_Camera_create() {
    _cameraCollection.push_back(std::make_unique<Camera>());
    return reinterpret_cast<NovelRTCamera>(_cameraCollection.back().get());
  }
  
  int32_t NovelRT_Camera_getViewMatrix(NovelRTCamera camera, NovelRTGeoMatrix4x4F* outputMatrix, const char** errorMessage) {
    if(camera == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
    auto mat4 = cameraPtr->getViewMatrix();
    *outputMatrix = *reinterpret_cast<NovelRTGeoMatrix4x4F*>(&mat4);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_Camera_setViewMatrix(NovelRTCamera camera, NovelRTGeoMatrix4x4F inputMatrix, const char** errorMessage) {
    if(camera == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
    cameraPtr->setViewMatrix(*reinterpret_cast<GeoMatrix4x4F*>(&inputMatrix));

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_Camera_getProjectionMatrix(NovelRTCamera camera, NovelRTGeoMatrix4x4F* outputMatrix, const char** errorMessage) {
    if(camera == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
    auto mat4 = cameraPtr->getProjectionMatrix();
    *outputMatrix = *reinterpret_cast<NovelRTGeoMatrix4x4F*>(&mat4);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_Camera_setProjectionMatrix(NovelRTCamera camera, NovelRTGeoMatrix4x4F inputMatrix, const char** errorMessage) {
    if(camera == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
    cameraPtr->setProjectionMatrix(*reinterpret_cast<GeoMatrix4x4F*>(&inputMatrix));

    return NOVELRT_SUCCESS;

  }

  int32_t NovelRT_Camera_getCameraUboMatrix(NovelRTCamera camera, NovelRTGeoMatrix4x4F* outputMatrix, const char** errorMessage) {
    if(camera == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
    auto mat4 = cameraPtr->getCameraUboMatrix();
    *outputMatrix = *reinterpret_cast<NovelRTGeoMatrix4x4F*>(&mat4);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_Camera_getFrameState(NovelRTCamera camera, NovelRTCameraFrameState* outputFrameState, const char** errorMessage) {
    if(camera == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
    auto frameState = cameraPtr->getFrameState();
    *outputFrameState = *reinterpret_cast<NovelRTCameraFrameState*>(&frameState);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_Camera_setForceResizeCallback(NovelRTCamera camera, void(*callback)(NovelRTCamera, NovelRTGeoVector2F), const char** errorMessage) {
    if(camera == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
    cameraPtr->forceResizeCallback() = std::function<void(Camera*, GeoVector2F)>([callback](auto camera, auto newSize){ callback(reinterpret_cast<NovelRTCamera>(camera), *reinterpret_cast<NovelRTGeoVector2F*>(&newSize)); });

    return NOVELRT_SUCCESS;
  }

  NovelRTCamera NovelRT_Camera_createDefaultOrthographicProjection(NovelRTGeoVector2F windowSize) {
    _cameraCollection.push_back(Camera::createDefaultOrthographicProjection(*reinterpret_cast<GeoVector2F*>(&windowSize)));
    return reinterpret_cast<NovelRTCamera>(_cameraCollection.back().get());
  }

  NovelRTCamera NovelRT_Camera_createDefaultPerspectiveProjection(NovelRTGeoVector2F windowSize) {
    _cameraCollection.push_back(Camera::createDefaultPerspectiveProjection(*reinterpret_cast<GeoVector2F*>(&windowSize)));
    return reinterpret_cast<NovelRTCamera>(_cameraCollection.back().get());
  }

  int32_t NovelRT_Camera_destroy(NovelRTCamera camera, const char** errorMessage) {
    if(camera == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
    
    for (auto& cppCamera : _cameraCollection) {
      if (cppCamera.get() != cameraPtr) {
        continue;
      }

      _cameraCollection.remove(cppCamera);
      
      return NOVELRT_SUCCESS;
    }

      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsAlreadyDeletedOrRemoved();
      }
      
      return NOVELRT_FAILURE;
  }

#ifdef __cplusplus
}
#endif