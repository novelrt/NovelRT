// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Graphics/NrtCamera.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.h>

#include <list>

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;

std::list<std::unique_ptr<Camera>> _cameraCollection;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtCameraHandle Nrt_Camera_create()
    {
        _cameraCollection.push_back(std::make_unique<Camera>());
        return reinterpret_cast<NrtCameraHandle>(_cameraCollection.back().get());
    }

    NrtGeoMatrix4x4F Nrt_Camera_getViewMatrix(NrtCameraHandle camera)
    {
        Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
        auto mat4 = cameraPtr->getViewMatrix();
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&mat4);
    }

    NrtResult Nrt_Camera_setViewMatrix(NrtCameraHandle camera, NrtGeoMatrix4x4F inputMatrix)
    {
        if (camera == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
        cameraPtr->setViewMatrix(*reinterpret_cast<GeoMatrix4x4F*>(&inputMatrix));

        return NRT_SUCCESS;
    }

    NrtGeoMatrix4x4F Nrt_Camera_getProjectionMatrix(NrtCameraHandle camera)
    {
        Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
        auto mat4 = cameraPtr->getProjectionMatrix();
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&mat4);
    }

    NrtResult Nrt_Camera_setProjectionMatrix(NrtCameraHandle camera, NrtGeoMatrix4x4F inputMatrix)
    {
        if (camera == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
        cameraPtr->setProjectionMatrix(*reinterpret_cast<GeoMatrix4x4F*>(&inputMatrix));

        return NRT_SUCCESS;
    }

    NrtGeoMatrix4x4F Nrt_Camera_getCameraUboMatrix(NrtCameraHandle camera)
    {
        Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
        auto mat4 = cameraPtr->getCameraUboMatrix();
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&mat4);
    }

    NrtCameraFrameState Nrt_Camera_getFrameState(NrtCameraHandle camera)
    {
        Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
        auto frameState = cameraPtr->getFrameState();
        return *reinterpret_cast<NrtCameraFrameState*>(&frameState);
    }

    NrtResult Nrt_Camera_setForceResizeCallback(NrtCameraHandle camera,
                                                void (*callback)(NrtCameraHandle, NrtGeoVector2F, void*),
                                                void* context)
    {
        if (camera == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        Camera* cameraPtr = reinterpret_cast<Camera*>(camera);
        cameraPtr->forceResizeCallback() = std::function<void(Camera*, GeoVector2F)>([callback, context](auto camera,
                                                                                                         auto newSize) {
            callback(reinterpret_cast<NrtCameraHandle>(camera), *reinterpret_cast<NrtGeoVector2F*>(&newSize), context);
        });

        return NRT_SUCCESS;
    }

    NrtCameraHandle Nrt_Camera_createDefaultOrthographicProjection(NrtGeoVector2F windowSize)
    {
        _cameraCollection.push_back(
            Camera::createDefaultOrthographicProjection(*reinterpret_cast<GeoVector2F*>(&windowSize)));
        return reinterpret_cast<NrtCameraHandle>(_cameraCollection.back().get());
    }

    NrtCameraHandle Nrt_Camera_createDefaultPerspectiveProjection(NrtGeoVector2F windowSize)
    {
        _cameraCollection.push_back(
            Camera::createDefaultPerspectiveProjection(*reinterpret_cast<GeoVector2F*>(&windowSize)));
        return reinterpret_cast<NrtCameraHandle>(_cameraCollection.back().get());
    }

    NrtResult Nrt_Camera_destroy(NrtCameraHandle camera)
    {
        if (camera == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        Camera* cameraPtr = reinterpret_cast<Camera*>(camera);

        for (auto& cppCamera : _cameraCollection)
        {
            if (cppCamera.get() != cameraPtr)
            {
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
