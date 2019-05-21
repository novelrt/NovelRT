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
/*  GLfloat g_vertex_buffer_data[] = {
      -1.0f, -1.0f, 0.0f,
      1.0f, -1.0f, 0.0f,
     -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
     1.0f,  -1.0f, 0.0f,
     -1.0f,  1.0f, 0.0f,
  };
// Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &_buffer);
// The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, _buffer);
// Give our vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);*/

  configureBuffer(true);
}

void NovelBasicFillRect::configureBuffer(bool isInit) {
  GeoVector<float> position = getWorldSpacePosition() * _screenScale;
  GeoVector<float> size = getWorldSpaceSize() * _screenScale;
  /* GeoBounds bounds(position, size);
   GeoVector<float> topLeft = bounds.getCorner(0);
   GeoVector<float> topRight = bounds.getCorner(1);
   GeoVector<float> bottomRight = bounds.getCorner(2);
   GeoVector<float> bottomLeft = bounds.getCornerInWorldSpace(3);
   size = size * getScale();
   _vertexBufferData = {
       (topLeft.getX() / (1920.0f * _screenScale)) - 0.5f, (topLeft.getY() / (1080.0f * _screenScale)) - 0.5f, 0.0f,
       (topRight.getX() / (1920.0f * _screenScale)) - 0.5f, (topRight.getY() / (1080.0f * _screenScale)) - 0.5f, 0.0f,
       (bottomRight.getX() / (1920.0f * _screenScale)) - 0.5f, (bottomRight.getY() / (1080.0f * _screenScale)) - 0.5f, 0.0f,
       //topRight.getX() / (1920.0f * _screenScale), topRight.getY() / (1080.0f * _screenScale), 0.0f,
 *//*      bottomRight.getX() / (1920.0f * _screenScale), bottomRight.getY() / (1080.0f * _screenScale), 0.0f,
      bottomLeft.getX() / (1920.0f * _screenScale), bottomLeft.getY() / (1080.0f * _screenScale), 0.0f,
      bottomLeft.getX() / (1920.0f * _screenScale), bottomLeft.getY() / (1080.0f * _screenScale), 0.0f,*//*
  };*/
  GeoBounds bounds(GeoVector<float>((1920.0f * _screenScale) / 2, (1080.0f * _screenScale) / 2), GeoVector<float>(50, 50));
  _vertexBufferData = {
      bounds.getCornerInOpenGLSurfaceSpace(0, _screenScale).getX(), bounds.getCornerInOpenGLSurfaceSpace(0, _screenScale).getY(), 0.0f,
      bounds.getCornerInOpenGLSurfaceSpace(1, _screenScale).getX(), bounds.getCornerInOpenGLSurfaceSpace(1, _screenScale).getY(), 0.0f,
      bounds.getCornerInOpenGLSurfaceSpace(2, _screenScale).getX(), bounds.getCornerInOpenGLSurfaceSpace(2, _screenScale).getY(), 0.0f,
  };
  std::cout << bounds.getCornerInOpenGLSurfaceSpace(0, _screenScale).getX() << " " << bounds.getCornerInOpenGLSurfaceSpace(0, _screenScale).getY() << std::endl;
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
/*  GeoVector<float> position = getWorldSpacePosition() * _screenScale;
  GeoVector<float> size = getWorldSpaceSize() * _screenScale;
  GeoBounds bounds(position, size);
  GeoVector<float> topLeft = bounds.getCorner(0);
  GeoVector<float> topRight = bounds.getCorner(1);
  GeoVector<float> bottomRight = bounds.getCorner(2);
  GeoVector<float> bottomLeft = bounds.getCornerInWorldSpace(3);
  size = size * getScale();
  _vertexBufferData = {
    topLeft.getX() / (1920.0f * _screenScale), topLeft.getY() / (1080.0f * _screenScale), 0.0f,
      topRight.getX() / (1920.0f * _screenScale), topRight.getY() / (1080.0f * _screenScale), 0.0f,
    bottomRight.getX() / (1920.0f * _screenScale), bottomRight.getY() / (1080.0f * _screenScale), 0.0f,
    bottomLeft.getX() / (1920.0f * _screenScale), bottomLeft.getY() / (1080.0f * _screenScale), 0.0f,
  };
  configureBuffer(false);*/
  _size = value;
}

void NovelBasicFillRect::drawObject() const {
  if (!getActive())
    return;

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