//
// Created by matth on 27/02/2019.
//

#include <iostream>
#include "NovelTextRect.h"

namespace NovelRT {
void NovelTextRect::drawObject() const {

}

RGBAConfig NovelTextRect::getColourConfig() const {
  return _colourConfig;
}

void NovelTextRect::setColourConfig(const RGBAConfig& value) {
  _colourConfig = value;
  configureObjectBuffers();
}
void NovelTextRect::configureObjectBuffers(const bool refreshBuffers) {
  NovelRenderObject::configureObjectBuffers(refreshBuffers);

  if (refreshBuffers) {
    FT_Face face;
    if (FT_New_Face(_freeTypeLoader, _fontFileDir.c_str(), 0, &face)) std::cout << "ERROR: Failed to load font " << _fontFileDir << " via freeType!" << std::endl;

    FT_Set_Pixel_Sizes(face, 0, _fontSize);

  }
}
NovelTextRect::NovelTextRect(NovelLayeringService* layeringService,
                             const float fontSize,
                             const float screenScale,
                             const std::string& fontFileDir,
                             const RGBAConfig& colourConfig,
                             const FT_Library& freeTypeLoader,
                             const NovelCommonArgs& args,
                             const GLuint programId) : NovelRenderObject(layeringService,
                                                                         screenScale,
                                                                         GeoVector<float>(0, 0),
                                                                         args,
                                                                         programId), _colourConfig(colourConfig),
                                                       _fontFileDir(fontFileDir), _fontSize(fontSize),
                                                       _freeTypeLoader(freeTypeLoader) {

}
}