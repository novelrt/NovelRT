// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <iostream>
#include "../include/NovelBasicFillRect.h"
#include "../include/GeoBounds.h"

namespace NovelRT {

NovelBasicFillRect::NovelBasicFillRect(NovelLayeringService* layeringService,
                                       const RGBAConfig& fillColour,
                                       const NovelCommonArgs& args,
                                       ShaderProgram shaderProgram,
                                       NovelCamera* camera) :
    NovelRenderObject(layeringService, args, shaderProgram, camera), _colourConfig(fillColour),
    _colourBuffer(Lazy<GLuint>(generateStandardBuffer)) {}

void NovelBasicFillRect::drawObject() {
  if (!getActive())
    return;

  glUseProgram(_shaderProgram.shaderProgramId);

  glBindBuffer(GL_UNIFORM_BUFFER, _shaderProgram.finalViewMatrixBufferUboId);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraBlock), &_finalViewMatrixData.getActual(), GL_STATIC_DRAW);


  glBindVertexArray(_vertexArrayObject.getActual());
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer.getActual());
  glVertexAttribPointer(
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      0,
      nullptr
  );
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, _colourBuffer.getActual());
  glVertexAttribPointer(
      1,
      4,
      GL_FLOAT,
      GL_FALSE,
      0,
      nullptr
  );

  glDrawArrays(GL_TRIANGLES, 0, 6);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);

}

RGBAConfig NovelBasicFillRect::getColourConfig() const {
  return _colourConfig;
}
void NovelBasicFillRect::setColourConfig(const RGBAConfig& value) {
  _colourConfig = value;
  configureObjectBuffers();
}
void NovelBasicFillRect::configureObjectBuffers() {
  NovelRenderObject::configureObjectBuffers();

  auto config = getColourConfig();
  auto rScalar = config.getRScalar();
  auto gScalar = config.getGScalar();
  auto bScalar = config.getBScalar();
  auto aScalar = config.getAScalar();

  _colourData = {
      rScalar, gScalar, bScalar, aScalar,
      rScalar, gScalar, bScalar, aScalar,
      rScalar, gScalar, bScalar, aScalar,
      rScalar, gScalar, bScalar, aScalar,
      rScalar, gScalar, bScalar, aScalar,
      rScalar, gScalar, bScalar, aScalar,
  };

  auto colourBuffer = _colourBuffer.getActual();
  glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _colourData.size(), _colourData.data(), GL_STATIC_DRAW);
}
}
