//
// Created by matth on 05/01/2019.
//

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "NovelImageRect.h"
#include "GeoBounds.h"

namespace NovelRT {
NovelImageRect::NovelImageRect(NovelLayeringService* layeringService,
                               const float& screenScale,
                               const GeoVector<float>& size,
                               const std::string_view imageDir,
                               const NovelCommonArgs& args,
                               const GLuint programId,
                               const RGBAConfig& colourTint) : NovelRenderObject(layeringService,
                                                                                 screenScale,
                                                                                 size,
                                                                                 args,
                                                                                 programId),
                                                               _imageDir(imageDir), _colourTint(colourTint),
                                                               _uvBuffer(Lazy<GLuint>(generateStandardBuffer)),
                                                               _colourTintBuffer(Lazy<GLuint>(generateStandardBuffer)),
                                                               _textureId(Lazy<GLuint>([] {
                                                                 GLuint tempTexture;
                                                                 glGenTextures(1, &tempTexture);
                                                                 return tempTexture;
                                                               })){

}

NovelImageRect::NovelImageRect(NovelLayeringService* layeringService,
                               const float& screenScale,
                               const GeoVector<float>& size,
                               const NovelCommonArgs& args,
                               GLuint programId,
                               const RGBAConfig& colourTint) : NovelImageRect(layeringService, screenScale, size, "", args, programId, colourTint) {

}

void NovelImageRect::setScale(const GeoVector<float>& value) {
  NovelObject::_scale = value;
}

void NovelImageRect::drawObject() {
  if (!getActive())
    return;

  glUseProgram(_programId);
  glBindTexture(GL_TEXTURE_2D, _textureId.getActual());
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
  glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer.getActual());
  glVertexAttribPointer(
      1,
      2,
      GL_FLOAT,
      GL_FALSE,
      0,
      nullptr
  );
  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, _colourTintBuffer.getActual());
  glVertexAttribPointer(
      2,
      4,
      GL_FLOAT,
      GL_FALSE,
      0,
      nullptr
  );

  glDrawArrays(GL_TRIANGLES, 0, 6);
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
}

void NovelImageRect::configureObjectBuffers() {
  NovelRenderObject::configureObjectBuffers();

  _uvCoordinates = {
      0.0f, 1.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f,
      1.0f, 0.0f
  };

  glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer.getActual());

  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _uvCoordinates.size(), _uvCoordinates.data(), GL_STATIC_DRAW);

  auto config = getColourTintConfig();
  auto rScalar = config.getRScalar();
  auto gScalar = config.getGScalar();
  auto bScalar = config.getBScalar();
  auto aScalar = config.getAScalar();

  _colourTintData = {
      rScalar, gScalar, bScalar, aScalar,
      rScalar, gScalar, bScalar, aScalar,
      rScalar, gScalar, bScalar, aScalar,
      rScalar, gScalar, bScalar, aScalar,
      rScalar, gScalar, bScalar, aScalar,
      rScalar, gScalar, bScalar, aScalar,
  };

  glBindBuffer(GL_ARRAY_BUFFER, _colourTintBuffer.getActual());
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _colourTintData.size(), _colourTintData.data(), GL_STATIC_DRAW);

  if (_imageDir.empty())
    return;

  SDL_Surface* surface = IMG_Load(_imageDir.c_str());

  if (surface == nullptr) {
    std::cerr << "ERROR: File load returned a null pointer! Cannot load texture!" << std::endl;
    throw -1;
  }
  glBindTexture(GL_TEXTURE_2D, _textureId.getActual());

  int mode = GL_RGB;

  if (surface->format->BytesPerPixel == 4) {
    mode = GL_RGBA;
  }

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
  glGenerateMipmap(GL_TEXTURE_2D);
  SDL_FreeSurface(surface);
}

void NovelImageRect::setTextureInternal(GLuint textureId) {
  _imageDir = "";
  _textureId = Lazy<GLuint>(textureId, []{
    GLuint tempBuffer;
    glGenBuffers(1, &tempBuffer);
    return tempBuffer;
  });
}
RGBAConfig NovelImageRect::getColourTintConfig() const {
  return _colourTint;
}
void NovelImageRect::setColourTintConfig(const RGBAConfig& value) {
  _colourTint = value;
}

NovelImageRect::~NovelImageRect() {
  if(_imageDir.empty() && !_textureId.isCreated()) return;

  auto textureId = _textureId.getActual();
  glDeleteTextures(1, &textureId);
}

}
