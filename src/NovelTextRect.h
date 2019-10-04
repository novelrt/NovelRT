// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See License.md in the repository root for more information.

#ifndef NOVELRT_NOVELTEXTRECT_H
#define NOVELRT_NOVELTEXTRECT_H
#include "NovelRenderObject.h"
#include "RGBAConfig.h"
#include <string>
#include "GraphicsCharacterRenderData.h"
#include "NovelImageRect.h"

namespace NovelRT {
class NovelTextRect : public NovelRenderObject {
public:
  NovelTextRect(NovelLayeringService* layeringService,
                const float fontSize,
                const std::string& fontFileDir,
                const RGBAConfig& colourConfig,
                const NovelCommonArgs& args,
                const GLuint programId);

  void drawObject() final;

  RGBAConfig getColourConfig() const;

  void setColourConfig(const RGBAConfig& value);

  std::string getText() const;
  void setText(const std::string& value);

protected:
  void configureObjectBuffers() final;
private:
  void reloadText();

  RGBAConfig _colourConfig;
  std::string _fontFileDir;
  std::string _previousFontFileDir = "";
  float _fontSize;
  std::map<GLchar, GraphicsCharacterRenderData> _fontCharacters;
  std::string _text = "";
  std::vector<NovelImageRect*> _letterRects;
  NovelCommonArgs _args;
};
}
#endif //NOVELRT_NOVELTEXTRECT_H
