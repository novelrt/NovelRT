//
// Created by matth on 05/01/2019.
//

#include "NovelImageRect.h"

namespace NovelRT {

NovelImageRect::NovelImageRect(NovelLayeringService* layeringService,
                               const float& screenScale,
                               const std::string_view imageDir,
                               const NovelCommonArgs& args) :
    NovelRenderObject(layeringService, screenScale, GeoVector<float>(0, 0), args),
    _imageDir(imageDir) {
  _width = 0;
  _height = 0;
  setWorldSpaceSize(GeoVector<float>(_width, _height));
  setScale(args.startingScale);
}

void NovelImageRect::setScale(const GeoVector<float>& value) {
  NovelObject::_scale = value;
}

void NovelImageRect::drawObject() const {
  if (!getActive())
    return;

  GeoVector<float> position = getWorldSpacePosition() * _screenScale;
  GeoVector<float> size = getWorldSpaceSize() * _screenScale;
  size = size * getScale();
}
void NovelImageRect::configureBuffer() {

}
}
