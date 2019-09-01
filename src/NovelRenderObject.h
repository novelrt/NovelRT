//
// Created by matth on 23/02/2019.
//

#ifndef NOVELRT_NOVELRENDEROBJECT_H
#define NOVELRT_NOVELRENDEROBJECT_H
#include "NovelObject.h"
#include <string>
#include <glad/glad.h>

namespace NovelRT {
class NovelRenderObject : public NovelObject {
public:
  NovelRenderObject(NovelLayeringService* layeringService, const float screenScale, const GeoVector<float>& size,
                    const NovelCommonArgs& args, const GLuint programId);

  void executeObjectBehaviour() final;
  void setWorldSpaceSize(const GeoVector<float>& value) override;
  void setRotation(const float value) override;
  void setScale(const GeoVector<float>& value) override;
  void setPosition(const GeoVector<float>& value) override;


protected:
  virtual void drawObject() const = 0;
  virtual void configureObjectBuffers(const bool refreshBuffers = false);

  GLuint _buffer;
  GLuint _vertexArrayObject;
  GLuint _programId;
  std::vector<GLfloat> _vertexBufferData;
  bool _bufferInitialised = false;
};
}
#endif //NOVELRT_NOVELRENDEROBJECT_H
