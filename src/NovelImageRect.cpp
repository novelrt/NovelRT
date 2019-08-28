//
// Created by matth on 05/01/2019.
//

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include "NovelImageRect.h"
#include "GeoBounds.h"

namespace NovelRT {

NovelImageRect::NovelImageRect(NovelLayeringService* layeringService,
                               const float& screenScale,
                               const std::string_view imageDir,
                               const NovelCommonArgs& args,
                               const GLuint programId) :
    NovelRenderObject(layeringService, screenScale, GeoVector<float>(0, 0), args, programId),
    _imageDir(imageDir) {

}

void NovelImageRect::setScale(const GeoVector<float>& value) {
  NovelObject::_scale = value;
}

void NovelImageRect::drawObject() const {
  if (!getActive())
    return;


  glUseProgram(_programId);

}
void NovelImageRect::configureObjectBuffers(const bool refreshBuffers) {
  NovelRenderObject::configureObjectBuffers(refreshBuffers);

  SDL_Surface* surface = IMG_Load("test-yuri.png");

  glGenTextures(1, &_textureId);
  glBindTexture(GL_TEXTURE_2D, _textureId);

  int mode = GL_RGB;

  if(surface->format->BytesPerPixel == 4) {
    mode = GL_RGBA;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  _uvCoordinates = {
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f
  };

}
}
