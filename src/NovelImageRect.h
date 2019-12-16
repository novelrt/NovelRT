// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELIMAGERECT_H
#define NOVELRT_NOVELIMAGERECT_H

#include "RGBAConfig.h"
#include "NovelRenderObject.h"
#include "ShaderProgram.h"

namespace NovelRT {

  class NovelImageRect : public NovelRenderObject {

  private:
    std::string _imageDir;
    std::string _previousImageDir;
    Lazy<GLuint> _textureId;
    std::vector<GLfloat> _uvCoordinates;
    Lazy<GLuint> _uvBuffer;
    Lazy<GLuint> _colourTintBuffer;
    RGBAConfig _colourTint;
    std::vector<GLfloat> _colourTintData;

  protected:
    void configureObjectBuffers() final;

  public:
    NovelImageRect(NovelLayeringService* layeringService,
      const GeoVector<float>& size,
      const NovelCommonArgs& args,
      ShaderProgram shaderProgram,
      NovelCamera* camera,
      const std::string& imageDir,
      const RGBAConfig& colourTint);

    NovelImageRect(NovelLayeringService* layeringService,
      const GeoVector<float>& size,
      const NovelCommonArgs& args,
      ShaderProgram shaderProgram,
      NovelCamera* camera,
      const RGBAConfig& colourTint);

    void drawObject() final;
    void setScale(const GeoVector<float>& value) final;

    void setTextureInternal(GLuint textureId);

    RGBAConfig getColourTintConfig() const;
    void setColourTintConfig(const RGBAConfig& value);
    ~NovelImageRect() override;
  };
}
#endif //NOVELRT_NOVELIMAGERECT_H
