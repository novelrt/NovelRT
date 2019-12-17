// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELRENDEROBJECT_H
#define NOVELRT_NOVELRENDEROBJECT_H
#include "NovelWorldObject.h"
#include "Lazy.h"
#include <string>
#include <glad/glad.h>
#include <memory>
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "NovelCamera.h"
#include "CameraBlock.h"

namespace NovelRT {

class NovelRenderObject : public NovelWorldObject {

protected:
  virtual void drawObject() = 0;
  virtual void configureObjectBuffers();
  static GLuint generateStandardBuffer();
  CameraBlock generateViewData();
  CameraBlock generateCameraBlock();

  Lazy<GLuint> _vertexBuffer;
  Lazy<GLuint> _vertexArrayObject;
  ShaderProgram _shaderProgram;
  std::vector<GLfloat> _vertexBufferData;
  bool _bufferInitialised = false;
  NovelCamera* _camera;
  CameraBlock _uboCameraData;
  Lazy<CameraBlock> _finalViewMatrixData;
  void OnCameraViewChanged(CameraViewChangedEventArgs args);

public:
  NovelRenderObject(NovelLayeringService* layeringService, const GeoVector<float>& size,
                    const NovelCommonArgs& args, ShaderProgram shaderProgram, NovelCamera* camera);

  void executeObjectBehaviour() final;
  void setSize(const GeoVector<float>& value) override;
  void setRotation(const float value) override;
  void setScale(const GeoVector<float>& value) override;
  void setPosition(const GeoVector<float>& value) override;
  virtual ~NovelRenderObject();
  };
}
#endif //NOVELRT_NOVELRENDEROBJECT_H
