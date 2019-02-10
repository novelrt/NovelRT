//
// Created by matth on 16/12/2018.
//

#include <iostream>
#include "NovelBasicFillRect.h"

namespace NovelRT{

    NovelBasicFillRect::NovelBasicFillRect(const float& screenScale, const GeoVector<float> &position, const GeoVector<float> &size,
                                           const RGBAConfig &fillColour, NVGcontext* context, const float &rotation, const GeoVector<float>& scale) : NovelObject(screenScale, position, size, context, rotation, scale), _colourConfig(fillColour) {
    }

    void NovelBasicFillRect::drawObject() const {
        if(!getActive()) return;

        GeoVector<float> position = getPosition() * _screenScale;
        GeoVector<float> size = getSize() * _screenScale;
        size = size * getScale();
        nvgSave(_context);
        nvgTranslate(_context, position.getX(), position.getY());
        nvgRotate(_context, getRotation());
        nvgTranslate(_context, -(size.getX() / 2), -(size.getY() / 2));
        nvgBeginPath(_context);
        nvgRect(_context, 0, 0, size.getX(), size.getY());
        nvgFillColor(_context, nvgRGBA(_colourConfig.getR(), _colourConfig.getG(), _colourConfig.getB(), _colourConfig.getA()));
        nvgFill(_context);
        nvgRestore(_context);
    }
}