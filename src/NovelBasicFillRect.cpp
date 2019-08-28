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
                                       const NovelCommonArgs& args,
                                       const GLuint programId) :
    NovelRenderObject(layeringService, screenScale, size, args, programId), _colourConfig(fillColour) {

}

void NovelBasicFillRect::drawObject() const {
  if (!getActive())
    return;

  glUseProgram(_programId);
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

  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, _colourBuffer);
  glVertexAttribPointer(
      1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
      4,                                // size
      GL_FLOAT,                         // type
      GL_FALSE,                         // normalized?
      0,                                // stride
      nullptr                        // array buffer offset
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
void NovelBasicFillRect::configureObjectBuffers(bool refreshBuffers) {
  NovelRenderObject::configureObjectBuffers(refreshBuffers);

  //if(refreshBuffers){
    _colourData = {
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f
    };

    glGenBuffers(1, &_colourBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _colourBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _colourData.size(), _colourData.data(), GL_STATIC_DRAW);
  //}
}
}