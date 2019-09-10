
//
// Created by matth on 27/02/2019.
//

#ifndef NOVELRT_NOVELTEXTRECT_H
#define NOVELRT_NOVELTEXTRECT_H
#include "NovelRenderObject.h"
#include "RGBAConfig.h"
#include <string>
#include "GraphicsCharacterRenderData.h"

namespace NovelRT {
class NovelTextRect : public NovelRenderObject {
public:
  NovelTextRect(NovelLayeringService* layeringService,
                const float fontSize,
                const float screenScale,
                const std::string& fontFileDir,
                const RGBAConfig& colourConfig,
                const NovelCommonArgs& args,
                const GLuint programId);

  void drawObject() const final;

  RGBAConfig getColourConfig() const;

  void setColourConfig(const RGBAConfig& value);

  std::string getText() const;
  void setText(const std::string& value);

protected:
  void configureObjectBuffers(const bool refreshBuffers = false) final;
private:
  RGBAConfig _colourConfig;
  std::string _fontFileDir;
  float _fontSize;
  std::map<GLchar, GraphicsCharacterRenderData> _fontCharacters;
  std::string _text;
  GLuint _textBuffer;
};
}
#endif //NOVELRT_NOVELTEXTRECT_H
