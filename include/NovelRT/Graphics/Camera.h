// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_CAMERA_H
#define NOVELRT_GRAPHICS_CAMERA_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  class Camera {
    friend class RenderingService;

  private:
    Maths::GeoMatrix4x4F _viewMatrix;
    Maths::GeoMatrix4x4F _projectionMatrix;
    Utilities::Lazy<Maths::GeoMatrix4x4F> _cameraUboMatrix;
    Maths::GeoMatrix4x4F generateUboMatrix();
    CameraFrameState _cameraFrameState;
    std::function<void(Camera*, Maths::GeoVector2F)> _forceResizeCallback;

    void initialiseCameraForFrame();
    void forceResize(Maths::GeoVector2F windowSize);

  public:
    Camera();

    inline Maths::GeoMatrix4x4F getViewMatrix() const {
      return _viewMatrix;
    }

    inline void setViewMatrix(Maths::GeoMatrix4x4F value) {
      _cameraFrameState = CameraFrameState::ModifiedInCurrent;
      _cameraUboMatrix.reset();
      _viewMatrix = value;
    }

    inline Maths::GeoMatrix4x4F getProjectionMatrix() const {
      return _projectionMatrix;
    }

    inline void setProjectionMatrix(Maths::GeoMatrix4x4F value) {
      _cameraFrameState = CameraFrameState::ModifiedInCurrent;
      _cameraUboMatrix.reset();
      _projectionMatrix = value;
    }

    inline Maths::GeoMatrix4x4F getCameraUboMatrix() {
      return _cameraUboMatrix.getActual();
    }

    inline CameraFrameState getFrameState() const {
      return _cameraFrameState;
    }

    inline const std::function<void(Camera*, Maths::GeoVector2F)>& forceResizeCallback() const {
      return _forceResizeCallback;
    }

    inline std::function<void(Camera*, Maths::GeoVector2F)>& forceResizeCallback() {
      return _forceResizeCallback;
    }

    /**
     * Creates an orthographic camera using default settings and the given window size.
     */
    static std::unique_ptr<Camera> createDefaultOrthographicProjection(Maths::GeoVector2F windowSize);

    /**
     * Creates a perspective camera using default settings and the given window size.
     */
    static std::unique_ptr<Camera> createDefaultPerspectiveProjection(Maths::GeoVector2F windowSize);
  };
}

#endif //NOVELRT_GRAPHICS_CAMERA_H
