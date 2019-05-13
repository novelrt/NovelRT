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
}