// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELRECT_H
#define NOVELRT_NOVELRECT_H

#include "NovelRenderObject.h"
#include "RGBAConfig.h"
#include "ShaderProgram.h"
#include "NovelCamera.h"

namespace NovelRT {
  class NovelBasicFillRect : public NovelRenderObject {

  private:
    RGBAConfig _colourConfig;
    Lazy<GLuint> _colourBuffer;
    std::vector<GLfloat> _colourData;

  protected:
    void configureObjectBuffers() final;

  public:
    NovelBasicFillRect(NovelLayeringService* layeringService,
                       const RGBAConfig& fillColour,
                       const NovelCommonArgs& args,
                       ShaderProgram shaderProgram,
                       NovelCamera* camera);

    void drawObject() final;
    RGBAConfig getColourConfig() const;
    void setColourConfig(const RGBAConfig& value);
  };
}

#endif //NOVELRT_NOVELRECT_H
