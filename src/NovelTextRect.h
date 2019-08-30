//
// Created by matth on 27/02/2019.
//

#ifndef NOVELRT_NOVELTEXTRECT_H
#define NOVELRT_NOVELTEXTRECT_H
#include "NovelRenderObject.h"
#include "RGBAConfig.h"
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace NovelRT {
class NovelTextRect : public NovelRenderObject {
public:
  NovelTextRect(NovelLayeringService* layeringService,
                const float fontSize,
                const float screenScale,
                const std::string& fontFileDir,
                RGBAConfig& colourConfig,
                const NovelCommonArgs& args,
                GLuint programId);

  void drawObject() const final;

  RGBAConfig getColourConfig() const;

  void setColourConfig(const RGBAConfig& value);

protected:
  void configureObjectBuffers(const bool refreshBuffers = false) final;
private:
  RGBAConfig _colourConfig;
  std::string _fontFileDir;
  float _fontSize;
};
}
#endif //NOVELRT_NOVELTEXTRECT_H
