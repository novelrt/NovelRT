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
                 const NovelCommonArgs& args,
                 GLuint programId,
                 const RGBAConfig& colourTint);

  NovelImageRect(NovelLayeringService* layeringService,
                 const float& screenScale,
                 const GeoVector<float>& size,
                 const NovelCommonArgs& args,
                 GLuint programId,
                 const RGBAConfig& colourTint);

  void drawObject() final;
  void setScale(const GeoVector<float>& value) final;

  void setTextureInternal(GLuint textureId);

  RGBAConfig getColourTintConfig() const;
  void setColourTintConfig(const RGBAConfig& value);
  ~NovelImageRect() override;

protected:
  void configureObjectBuffers() final;

private:
  std::string _imageDir;
  int _imageHandle;
  int _width;
  int _height;
  LazyFunction<GLuint> _textureId;
  std::vector<GLfloat> _uvCoordinates;
  LazyFunction<GLuint> _uvBuffer;
  LazyFunction<GLuint> _colourTintBuffer;
  RGBAConfig _colourTint;
  std::vector<GLfloat> _colourTintData;
  bool _textureIsSelfManaged = true;
};

}
#endif //NOVELRT_NOVELIMAGERECT_H
