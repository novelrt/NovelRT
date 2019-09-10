//
// Created by matth on 05/01/2019.
//

#ifndef NOVELRT_NOVELIMAGERECT_H
#define NOVELRT_NOVELIMAGERECT_H

#include "RGBAConfig.h"
#include "NovelRenderObject.h"

namespace NovelRT {

class NovelImageRect : public NovelRenderObject {
public:
  NovelImageRect(NovelLayeringService* layeringService,
                 const float& screenScale,
                 const GeoVector<float>& size,
                 const std::string_view imageDir,
                 const NovelCommonArgs& args, GLuint programId);

  NovelImageRect(NovelLayeringService* layeringService,
                 const float& screenScale,
                 const GeoVector<float>& size,
                 const NovelCommonArgs& args,
                 GLuint programId);

  void drawObject() const final;
  void setScale(const GeoVector<float>& value) final;

  void setTextureInternal(const GLuint textureId);

protected:
  void configureObjectBuffers(const bool refreshBuffers = false) final;

private:
  std::string _imageDir;
  int _imageHandle;
  int _width;
  int _height;
  GLuint _textureId;
  std::vector<GLfloat> _uvCoordinates;

  GLuint _uvBuffer;
  GLuint _colourBuffer;
};

}
#endif //NOVELRT_NOVELIMAGERECT_H
