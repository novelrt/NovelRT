// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_RENDEROBJECT_H
#define NOVELRT_GRAPHICS_RENDEROBJECT_H
#include "../Transform.h"
#include "../Utilities/Lazy.h"
#include <string>
#include <glad/glad.h>
#include <memory>
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Camera.h"
#include "CameraBlock.h"

namespace NovelRT {

class RenderObject : public Transform {

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
  Lazy<CameraBlock> _finalViewMatrixData;
  void OnCameraViewChanged(CameraViewChangedEventArgs args);

public:
  RenderObject(LayeringService* layeringService,
                    const CommonArgs& args, ShaderProgram shaderProgram, Camera* camera);

  void executeObjectBehaviour() final;
  void setRotation(const float value) override;
  void setScale(const GeoVector<float>& value) override;
  void setPosition(const GeoVector<float>& value) override;
  virtual ~RenderObject();
  };
}
#endif //NOVELRT_GRAPHICS_RENDEROBJECT_H
