//
// Created by matth on 05/01/2019.
//

#include "NovelImageRect.h"

namespace NovelRT {

    NovelImageRect::NovelImageRect(const GeoVector<float> &position, NVGcontext *context, const std::string &imageDir,
                                   const float &rotation) : NovelObject(position, GeoVector<float>(0, 0), context,
                                                                        rotation), _imageDir(imageDir) {
        _imageHandle = nvgCreateImage(_context, _imageDir.c_str(), NVG_IMAGE_NEAREST);
        int width = 0;
        int height = 0;
        nvgImageSize(_context, _imageHandle, &width, &height);
        _paint = nvgImagePattern(_context, 0, 0, width, height, 0, _imageHandle, 1);
        setSize(GeoVector<float>(width, height));
    }

    void NovelImageRect::drawObject() const {
        if (!getActive()) return;
        
        GeoVector<float> position = getPosition();
        GeoVector<float> size = getSize();
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