// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELRENDEROBJECT_H
#define NOVELRT_NOVELRENDEROBJECT_H
#include "NovelWorldObject.h"
#include "Lazy.h"
#include <string>
#include <glad/glad.h>
#include <memory>
#include <glm/glm.hpp>

namespace NovelRT {

class NovelRenderObject : public NovelWorldObject {

protected:
  virtual void drawObject() = 0;
  virtual void configureObjectBuffers();
  static GLuint generateStandardBuffer();
  glm::mat3 generateModelTransform();

  Lazy<glm::mat3> _modelTransform;
  Lazy<GLuint> _vertexBuffer;
  Lazy<GLuint> _vertexArrayObject;
  GLuint _programId;
  std::vector<GLfloat> _vertexBufferData;
  bool _bufferInitialised = false;

public:
  NovelRenderObject(NovelLayeringService* layeringService, const GeoVector<float>& size,
                    const NovelCommonArgs& args, const GLuint programId);

  void executeObjectBehaviour() final;
  void setSize(const GeoVector<float>& value) override;
  void setRotation(const float value) override;
  void setScale(const GeoVector<float>& value) override;
  void setPosition(const GeoVector<float>& value) override;
  virtual ~NovelRenderObject();
  };
}
#endif //NOVELRT_NOVELRENDEROBJECT_H
