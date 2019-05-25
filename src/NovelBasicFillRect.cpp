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
  _vertexBufferData = {
      bounds.getCornerInOpenGLSurfaceSpace(0, _screenScale).getX(), bounds.getCornerInOpenGLSurfaceSpace(0, _screenScale).getY(), 0.0f,
      bounds.getCornerInOpenGLSurfaceSpace(2, _screenScale).getX(), bounds.getCornerInOpenGLSurfaceSpace(2, _screenScale).getY(), 0.0f,
      bounds.getCornerInOpenGLSurfaceSpace(1, _screenScale).getX(), bounds.getCornerInOpenGLSurfaceSpace(1, _screenScale).getY(), 0.0f,
      bounds.getCornerInOpenGLSurfaceSpace(0, _screenScale).getX(), bounds.getCornerInOpenGLSurfaceSpace(0, _screenScale).getY(), 0.0f,
      bounds.getCornerInOpenGLSurfaceSpace(3, _screenScale).getX(), bounds.getCornerInOpenGLSurfaceSpace(3, _screenScale).getY(), 0.0f,
      bounds.getCornerInOpenGLSurfaceSpace(2, _screenScale).getX(), bounds.getCornerInOpenGLSurfaceSpace(2, _screenScale).getY(), 0.0f,
  };

  GLfloat targetArray[_vertexBufferData.size()];
  std::copy(_vertexBufferData.begin(), _vertexBufferData.end(), targetArray);
// Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &_buffer);
// The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, _buffer);
// Give our vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(targetArray), targetArray, GL_STATIC_DRAW);

}

void NovelBasicFillRect::setWorldSpaceSize(const GeoVector<float>& value) {
  configureBuffer();
  _size = value;
}

void NovelBasicFillRect::drawObject() const {
  if (!getActive()) return;

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, _buffer);
  glVertexAttribPointer(
      0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
      3,                  // size
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride
      (void*) 0            // array buffer offset
  );
// Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices total -> 1 triangle
  glDisableVertexAttribArray(0);

}

RGBAConfig NovelBasicFillRect::getColourConfig() const {
  return _colourConfig;
}
void NovelBasicFillRect::setColourConfig(const RGBAConfig& value) {
  _colourConfig = value;
}
}