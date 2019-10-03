//
// Created by matth on 16/12/2018.
//

#include <iostream>
#include "NovelBasicFillRect.h"
#include "GeoBounds.h"

namespace NovelRT {

NovelBasicFillRect::NovelBasicFillRect(NovelLayeringService* layeringService,
                                       const GeoVector<float>& size,
                                       const RGBAConfig& fillColour,
                                       const NovelCommonArgs& args,
                                       GLuint programId) :
    NovelRenderObject(layeringService, size, args, programId), _colourConfig(fillColour),
    _colourBuffer(Lazy<GLuint>(generateStandardBuffer)) {
}

void NovelBasicFillRect::drawObject() {
  if (!getActive())
    return;

  glUseProgram(_programId);

/*  glBindBuffer(GL_UNIFORM_BUFFER, _modelTransformUniformBuffer.getActual());
  GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
  memcpy(p, &_modelTransform.getActual(), sizeof(_modelTransform.getActual()));
  glUnmapBuffer(GL_UNIFORM_BUFFER);*/

  glUniformMatrix3fv(1, 1, GL_FALSE, &_modelTransform.getActual()[0][0]);

  glBindVertexArray(_vertexArrayObject.getActual());
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer.getActual());
  glVertexAttribPointer(
      2,
      3,
      GL_FLOAT,
      GL_FALSE,
      0,
      nullptr
  );

  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, _colourBuffer.getActual());
  glVertexAttribPointer(
      3,
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