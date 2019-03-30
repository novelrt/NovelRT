//
// Created by matth on 16/12/2018.
//

#include <iostream>
#include "NovelBasicFillRect.h"

namespace NovelRT {

NovelBasicFillRect::NovelBasicFillRect(NovelLayeringService* layeringService,
                                       const float screenScale,
                                       const GeoVector<float>& size,
                                       const RGBAConfig& fillColour,
                                       const NovelCommonArgs& args,
                                       NovelRenderingService* renderingService) :
    NovelRenderObject(layeringService, screenScale, size, args, renderingService), _colourConfig(fillColour) {}

void NovelBasicFillRect::drawObject() const {
  if (!getActive())
    return;

  GeoVector<float> position = getPosition() * _screenScale;
  GeoVector<float> size = getSize() * _screenScale;
  size = size * getScale();
  nvgSave(_drawContext);
  nvgTranslate(_drawContext, position.getX(), position.getY());
  nvgRotate(_drawContext, getRotation());
  nvgTranslate(_drawContext, -(size.getX() / 2), -(size.getY() / 2));
  nvgBeginPath(_drawContext);
  nvgRect(_drawContext, 0, 0, size.getX(), size.getY());
  nvgFillColor(_drawContext,
               nvgRGBA(_colourConfig.getR(), _colourConfig.getG(), _colourConfig.getB(), _colourConfig.getA()));
  nvgFill(_drawContext);
  nvgRestore(_drawContext);
}
}