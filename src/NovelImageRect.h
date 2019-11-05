// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELIMAGERECT_H
#define NOVELRT_NOVELIMAGERECT_H

#include "RGBAConfig.h"
#include "NovelRenderObject.h"
#include "NovelLoggingService.h"

namespace NovelRT {

class NovelImageRect : public NovelRenderObject {
public:
  NovelImageRect(NovelLayeringService* layeringService,
                 const float& screenScale,
                 const GeoVector<float>& size,
                 std::string_view imageDir,
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
  NovelLoggingService _logger;
  std::string _imageDir;
  std::string _previousImageDir;
  int _imageHandle;
  int _width;
  int _height;
  Lazy<GLuint> _textureId;
  std::vector<GLfloat> _uvCoordinates;
  Lazy<GLuint> _uvBuffer;
  Lazy<GLuint> _colourTintBuffer;
  RGBAConfig _colourTint;
  std::vector<GLfloat> _colourTintData;
};

}
#endif //NOVELRT_NOVELIMAGERECT_H
