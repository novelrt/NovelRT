// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELTEXTRECT_H
#define NOVELRT_NOVELTEXTRECT_H
#include "NovelRenderObject.h"
#include "RGBAConfig.h"
#include <string>
#include "GraphicsCharacterRenderData.h"
#include "NovelImageRect.h"
#include "NovelLoggingService.h"
#include "ShaderProgram.h"

namespace NovelRT {
  class NovelTextRect : public NovelRenderObject {
  private:
    void reloadText();

    std::string _fontFileDir;
    std::string _previousFontFileDir = "";
    std::string _text = "";
    std::vector<NovelImageRect*> _letterRects;
    std::map<GLchar, GraphicsCharacterRenderData> _fontCharacters;
    NovelCommonArgs _args;
    NovelLoggingService _logger;
    RGBAConfig _colourConfig;
    float _fontSize;

  protected:
    void configureObjectBuffers() final;

  public:
    NovelTextRect(NovelLayeringService* layeringService,
      const NovelCommonArgs& args,
      ShaderProgram programId,
      NovelCamera* camera,
      float fontSize,
      const std::string& fontFileDir,
      const RGBAConfig& colourConfig);

    void drawObject() final;

    RGBAConfig getColourConfig() const;

    void setColourConfig(const RGBAConfig& value);

    std::string getText() const;
    void setText(const std::string& value);
  };
}
#endif //NOVELRT_NOVELTEXTRECT_H
