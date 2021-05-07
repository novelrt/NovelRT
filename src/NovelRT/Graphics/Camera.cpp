// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>

namespace NovelRT::Graphics
{
    Camera::Camera() noexcept
        : _cameraUboMatrix(Utilities::Lazy<Maths::GeoMatrix4x4F>(
              std::function<Maths::GeoMatrix4x4F()>(std::bind(&Camera::generateUboMatrix, this)))),
          _cameraFrameState(CameraFrameState::ModifiedInCurrent)
    {
    }

    std::unique_ptr<Camera> Camera::createDefaultOrthographicProjection(Maths::GeoVector2F windowSize) noexcept
    {
        auto callback = [](Camera* camera, Maths::GeoVector2F windowSize) {
            camera->setProjectionMatrix(
                Maths::GeoMatrix4x4F(glm::ortho(0.0f, windowSize.x, windowSize.y, 0.0f, 0.0f, 65535.0f)));
            camera->setViewMatrix(
                Maths::GeoMatrix4x4F(glm::scale(glm::vec3(windowSize.x / 1920.0f, windowSize.y / 1080.0f, -1.0f))));
        };

        auto returnVal = std::make_unique<Camera>();
        returnVal->forceResizeCallback() = callback;

        callback(returnVal.get(), windowSize);

        return returnVal;
    }

    std::unique_ptr<Camera> Camera::createDefaultPerspectiveProjection(Maths::GeoVector2F windowSize) noexcept
    {
        auto callback = [](Camera* camera, Maths::GeoVector2F windowSize) {
            auto aspect = windowSize.y != 0 ? windowSize.x / windowSize.y : 0;

            camera->setProjectionMatrix(
                Maths::GeoMatrix4x4F(glm::perspective(glm::radians(90.0f), aspect, 0.1f, 100.0f)));
            camera->setViewMatrix(Maths::GeoMatrix4x4F(
                glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))));
        };

        auto returnVal = std::make_unique<Camera>();
        returnVal->forceResizeCallback() = callback;

        callback(returnVal.get(), windowSize);

        return returnVal;
    }

    Maths::GeoMatrix4x4F Camera::generateUboMatrix() noexcept
    {
        return getProjectionMatrix() * getViewMatrix();
    }

    void Camera::initialiseCameraForFrame() noexcept
    {
        switch (_cameraFrameState)
        {
            case CameraFrameState::ModifiedInCurrent:
                _cameraFrameState = CameraFrameState::ModifiedInLast;
                break;
            case CameraFrameState::ModifiedInLast:
                _cameraFrameState = CameraFrameState::Unmodified;
                break;
            case CameraFrameState::Unmodified:
                break;
        }
    }

    void Camera::forceResize(Maths::GeoVector2F windowSize) noexcept
    {
        forceResizeCallback()(this, windowSize);
    }
} // namespace NovelRT::Graphics
