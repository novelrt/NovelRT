// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See License.md in the repository root for more information.
#include <iostream>
#include "NovelBasicFillRect.h"
#include "GeoBounds.h"

namespace NovelRT {

NovelBasicFillRect::NovelBasicFillRect(NovelLayeringService* layeringService,
                                       float screenScale,
                                       const GeoVector<float>& size,
                                       const RGBAConfig& fillColour,
                                       const NovelCommonArgs& args,
                                       GLuint programId) :
    NovelRenderObject(layeringService, screenScale, size, args, programId), _colourConfig(fillColour),
    _colourBuffer(Lazy<GLuint>(generateStandardBuffer)) {
}

void NovelBasicFillRect::drawObject() {
  if (!getActive())
    return;

  glUseProgram(_programId);
  glBindVertexArray(_vertexArrayObject.getActual());
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, _buffer.getActual());
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