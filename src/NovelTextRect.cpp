//
// Created by matth on 27/02/2019.
//

#include "NovelTextRect.h"
namespace NovelRT {
void NovelTextRect::drawObject() const {

}

RGBAConfig NovelTextRect::getColourConfig() const {
  return _colourConfig;
}

void NovelTextRect::setColourConfig(const RGBAConfig& value) {
  _colourConfig = value;
}
void NovelTextRect::configureObjectBuffers(const bool refreshBuffers) {
  NovelRenderObject::configureObjectBuffers(refreshBuffers);
}
NovelTextRect::NovelTextRect(NovelLayeringService* layeringService,
                             const float fontSize,
                             const float screenScale,
                             const std::string& fontFileDir,
                             RGBAConfig& colourConfig,
                             const NovelCommonArgs& args,
                             GLuint programId) : NovelRenderObject(layeringService,
                                                                   screenScale,
                                                                   GeoVector<float>(0, 0),
                                                                   args,
                                                                   programId), _colourConfig(colourConfig), _fontFileDir(fontFileDir), _fontSize(fontSize) {

}
}