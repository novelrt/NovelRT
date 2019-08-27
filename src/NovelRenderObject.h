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
                    const NovelCommonArgs& args);

  void executeObjectBehaviour() final;

protected:
  virtual void drawObject() const = 0;
  virtual void configureBuffer() = 0;
  GLuint _buffer;
  GLuint _vertexArrayObject;

public:
  std::string wew;
};
}
#endif //NOVELRT_NOVELRENDEROBJECT_H
