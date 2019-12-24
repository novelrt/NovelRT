// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_RENDEROBJECT_H
#define NOVELRT_GRAPHICS_RENDEROBJECT_H
#include <string>
#include <glad/glad.h>
#include <memory>
#include <glm/glm.hpp>

namespace NovelRT::Graphics {

class RenderObject : public WorldObject {

protected:
  virtual void drawObject() = 0;
  virtual void configureObjectBuffers();
  static GLuint generateStandardBuffer();
  CameraBlock generateViewData();
  CameraBlock generateCameraBlock();

  Utilities::Lazy<GLuint> _vertexBuffer;
  Utilities::Lazy<GLuint> _vertexArrayObject;
  ShaderProgram _shaderProgram;
  std::vector<GLfloat> _vertexBufferData;
  bool _bufferInitialised = false;
  Camera* _camera;
  CameraBlock _uboCameraData;
  Utilities::Lazy<CameraBlock> _finalViewMatrixData;
  void OnCameraViewChanged(CameraViewChangedEventArgs args);

public:
  RenderObject(const Transform& transform, ShaderProgram shaderProgram, Camera* camera);

  void executeObjectBehaviour() final;
  virtual ~RenderObject();
  };
}
#endif //NOVELRT_GRAPHICS_RENDEROBJECT_H
