//
// Created by matth on 05/01/2019.
//

#include <iostream>
#include "NovelImageRect.h"

namespace NovelRT {

NovelImageRect::NovelImageRect(NovelLayeringService* layeringService, NovelRenderingService* renderingService, const float& screenScale,
                               const std::string_view imageDir, const NovelCommonArgs& args) :
    NovelRenderObject(layeringService, renderingService, screenScale, GeoVector<float>(0, 0), args), _imageDir(imageDir) {

  _imageHandle = nvgCreateImage(_drawContext, _imageDir.c_str(), NVG_IMAGE_NEAREST);
  _width = 0;
  _height = 0;
  nvgImageSize(_drawContext, _imageHandle, &_width, &_height);
  setSize(GeoVector<float>(_width, _height));
  setScale(args.startingScale);
}

void NovelImageRect::setScale(const GeoVector<float>& value) {
  _paint = nvgImagePattern(_drawContext,
                           0,
                           0,
                           (_width * _screenScale) * value.getX(),
                           (_height * _screenScale) * value.getY(),
                           0,
                           _imageHandle,
                           1);
  NovelObject::_scale = value;
}

void NovelImageRect::drawObject() const {
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
  nvgFillPaint(_drawContext, _paint);
  nvgFill(_drawContext);
  nvgRestore(_drawContext);
}
}
