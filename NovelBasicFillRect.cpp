//
// Created by matth on 16/12/2018.
//

#include "NovelBasicFillRect.h"

namespace NovelRT{

    NovelBasicFillRect::NovelBasicFillRect(const GeoVector<float> &position, const GeoVector<float> &size,
                                           const RGBAConfig &fillColour, NVGcontext* context, const float &rotation) : NovelObject(position, size, context, rotation), _colourConfig(fillColour) {
    }

    void NovelBasicFillRect::drawObject(float deltaTime) const {
        GeoVector<float> position = getPosition();
        GeoVector<float> size = getSize();
        nvgBeginPath(_context);
        nvgRect(_context, position.getX() - (size.getX() / 2.0f), position.getY() - (size.getY() / 2.0f), size.getX(), size.getY());
        nvgFillColor(_context, nvgRGBA(_colourConfig.getR(), _colourConfig.getG(), _colourConfig.getB(), _colourConfig.getA()));
        nvgFill(_context);
    }
}