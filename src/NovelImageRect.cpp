//
// Created by matth on 05/01/2019.
//

#include "NovelImageRect.h"

namespace NovelRT {

    NovelImageRect::NovelImageRect(const GeoVector<float> &position, NVGcontext *context, const std::string &imageDir,
                                   const float &rotation, const GeoVector<float>& scale) : NovelObject(position, GeoVector<float>(0, 0), context,
                                                                        rotation, scale), _imageDir(imageDir) {
        _imageHandle = nvgCreateImage(_context, _imageDir.c_str(), NVG_IMAGE_NEAREST);
        _width = 0;
        _height = 0;
        nvgImageSize(_context, _imageHandle, &_width, &_height);
        setSize(GeoVector<float>(_width, _height));
        setScale(scale);
    }

    void NovelImageRect::setScale(const GeoVector<float>& value)  {
        _paint = nvgImagePattern(_context, 0, 0, _width * value.getX(), _height * value.getY(), 0, _imageHandle, 1);
        NovelObject::_scale = value;
    }

    void NovelImageRect::drawObject() const {
        if (!getActive()) return;

        GeoVector<float> position = getPosition();
        GeoVector<float> size = getSize();
        GeoVector<float> scale = getScale();
        size = size * scale;
        nvgSave(_context);
        nvgTranslate(_context, position.getX(), position.getY());
        nvgRotate(_context, getRotation());
        nvgTranslate(_context, -(size.getX() / 2), -(size.getY() / 2));
        nvgBeginPath(_context);
        nvgRect(_context, 0, 0, size.getX(), size.getY());
        nvgFillPaint(_context, _paint);
        nvgFill(_context);
        nvgRestore(_context);
    }


}