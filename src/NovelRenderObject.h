// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELRENDEROBJECT_H
#define NOVELRT_NOVELRENDEROBJECT_H
#include "NovelObject.h"
#include "Lazy.h"
#include <string>
#include <glad/glad.h>
#include <memory>

namespace NovelRT {
  class NovelRenderObject : public NovelObject {

  protected:
    Lazy<GLuint> _buffer;
    Lazy<GLuint> _vertexArrayObject;
    GLuint _programId;
    std::vector<GLfloat> _vertexBufferData;
    bool _bufferInitialised = false;

    virtual void drawObject() = 0;
    virtual void configureObjectBuffers();
    static GLuint generateStandardBuffer();

  public:
    NovelRenderObject(NovelLayeringService* layeringService,
                      float screenScale,
                      const GeoVector<float>& size,
                      const NovelCommonArgs& args,
                      GLuint programId);
    virtual ~NovelRenderObject();

    void executeObjectBehaviour() final;
    void setWorldSpaceSize(const GeoVector<float>& value) override;
    void setRotation(float value) override;
    void setScale(const GeoVector<float>& value) override;
    void setWorldSpacePosition(const GeoVector<float>& value) override;
  };
}
#endif //NOVELRT_NOVELRENDEROBJECT_H
