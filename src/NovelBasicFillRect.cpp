//
// Created by matth on 16/12/2018.
//

#include <iostream>
#include "NovelBasicFillRect.h"
#include "GeoBounds.h"

namespace NovelRT {

NovelBasicFillRect::NovelBasicFillRect(NovelLayeringService* layeringService,
                                       const float screenScale,
                                       const GeoVector<float>& size,
                                       const RGBAConfig& fillColour,
                                       const NovelCommonArgs& args) :
    NovelRenderObject(layeringService, screenScale, size, args), _colourConfig(fillColour) {
  configureBuffer();
}

void NovelBasicFillRect::configureBuffer() {
  GeoVector<float> position = getWorldSpacePosition() * _screenScale;
  GeoVector<float> size = getWorldSpaceSize() * _screenScale;
  GeoBounds bounds(position, size);
  //I think this is forward facing?
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

  glGenVertexArrays(1, &_vertexArrayObject);

// Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &_buffer);
// The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, _buffer);
// Give our vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexBufferData.size(), _vertexBufferData.data(), GL_STATIC_DRAW);

}

void NovelBasicFillRect::setWorldSpaceSize(const GeoVector<float>& value) {
  configureBuffer();
  _size = value;
}

void NovelBasicFillRect::drawObject() const {
  if (!getActive()) return;

  glBindVertexArray(_vertexArrayObject);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, _buffer);
  glVertexAttribPointer(
      0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
      3,                  // size
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride
      nullptr          // array buffer offset
  );
// Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices total -> 1 triangle
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);

}

RGBAConfig NovelBasicFillRect::getColourConfig() const {
  return _colourConfig;
}
void NovelBasicFillRect::setColourConfig(const RGBAConfig& value) {
  _colourConfig = value;
}
}