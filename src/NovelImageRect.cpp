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
                               const GLuint programId) :
    NovelRenderObject(layeringService, screenScale, size, args, programId),
    _imageDir(imageDir) {

}

NovelImageRect::NovelImageRect(NovelLayeringService* layeringService,
                               const float& screenScale,
                               const GeoVector<float>& size,
                               const NovelCommonArgs& args,
                               GLuint programId) :  NovelRenderObject(layeringService, screenScale, size, args, programId),
_imageDir("") {

}

void NovelImageRect::setScale(const GeoVector<float>& value) {
  NovelObject::_scale = value;
}

void NovelImageRect::drawObject() const {
  if (!getActive())
    return;


  glUseProgram(_programId);
  glBindTexture(GL_TEXTURE_2D, _textureId);
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
  glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
  glVertexAttribPointer(
      1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
      2,                                // size
      GL_FLOAT,                         // type
      GL_FALSE,                         // normalized?
      0,                                // stride
      nullptr                        // array buffer offset
  );
// Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices total -> 1 triangle
  auto bla = glGetError();
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);


}

void NovelImageRect::configureObjectBuffers(const bool refreshBuffers) {
  NovelRenderObject::configureObjectBuffers(refreshBuffers);

  if (refreshBuffers) {

    if(!_imageDir.empty()) {


    SDL_Surface* surface = IMG_Load(_imageDir.c_str());

    if(surface == nullptr) {
      std::cerr << "ERROR: File load returned a null pointer! Cannot load texture!" <<std::endl;
      throw -1;
    }

    if(_bufferInitialised) {
      glDeleteTextures(1, &_textureId);
    }

    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    int mode = GL_RGB;

    if(surface->format->BytesPerPixel == 4) {
      mode = GL_RGBA;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    SDL_free(surface);

    }
    _uvCoordinates = {
      0.0f, 1.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f,
      1.0f, 0.0f
    };

    glGenBuffers(1, &_uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _uvCoordinates.size(), _uvCoordinates.data(), GL_STATIC_DRAW);
  }
}
void NovelImageRect::setTextureInternal(const GLuint textureId) {
  _textureId = textureId;
}

}
