//
// Created by matth on 23/02/2019.
//

#include <iostream>
#include "NovelRenderObject.h"
#include "GeoBounds.h"

namespace NovelRT {
NovelRenderObject::NovelRenderObject(NovelLayeringService* layeringService,
                                     const float screenScale,
                                     const GeoVector<float>& size,
                                     const NovelCommonArgs& args,
                                     const GLuint programId) : NovelObject(layeringService, screenScale, size, args),
                                                               _programId(programId),
                                                               _vertexArrayObject(LazyFunction<GLuint>([] {
                                                                 GLuint tempVao;
                                                                 glGenVertexArrays(1, &tempVao);
                                                                 return tempVao;
                                                               })),
                                                               _buffer(LazyFunction<GLuint>([] {
                                                                 GLuint tempBuffer;
                                                                 glGenBuffers(1, &tempBuffer);
                                                                 return tempBuffer;
                                                               })) {
}

void NovelRenderObject::executeObjectBehaviour() {
  if (!_bufferInitialised) {
    configureObjectBuffers();
    _bufferInitialised = true;
  }
  drawObject();
}

void NovelRenderObject::configureObjectBuffers() {
  auto bounds = getScreenSpaceObjectBounds();

  auto topLeft = bounds.getCornerInOpenGLSurfaceSpace(0, _screenScale);
  auto bottomRight = bounds.getCornerInOpenGLSurfaceSpace(2, _screenScale);
  auto topRight = bounds.getCornerInOpenGLSurfaceSpace(1, _screenScale);
  auto bottomLeft = bounds.getCornerInOpenGLSurfaceSpace(3, _screenScale);
  _vertexBufferData = {
      topLeft.getX(), topLeft.getY(), 0.0f,
      bottomRight.getX(), bottomRight.getY(), 0.0f,
      topRight.getX(), topRight.getY(), 0.0f,
      topLeft.getX(), topLeft.getY(), 0.0f,
      bottomLeft.getX(), bottomLeft.getY(), 0.0f,
      bottomRight.getX(), bottomRight.getY(), 0.0f,
  };

  _vertexArrayObject.getActual(); //this is just here to force initialisation.

// The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, _buffer.getActual());

// Give our vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexBufferData.size(), _vertexBufferData.data(), GL_STATIC_DRAW);

}
void NovelRenderObject::setWorldSpaceSize(const GeoVector<float>& value) {
  NovelObject::setWorldSpaceSize(value);
  configureObjectBuffers();
}
void NovelRenderObject::setRotation(const float value) {
  NovelObject::setRotation(value);
  configureObjectBuffers();
}
void NovelRenderObject::setScale(const GeoVector<float>& value) {
  NovelObject::setScale(value);
  configureObjectBuffers();
}
void NovelRenderObject::setWorldSpacePosition(const GeoVector<float>& value) {
  NovelObject::setWorldSpacePosition(value);
  configureObjectBuffers();
}
NovelRenderObject::~NovelRenderObject() {
  auto vao = _vertexArrayObject.getActual();
  glDeleteVertexArrays(1, &vao);
}
}
