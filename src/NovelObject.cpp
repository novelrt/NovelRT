//
// Created by matth on 15/12/2018.
//

#include "NovelObject.h"
#include "../lib/nanovg/nanovg.h"

namespace NovelRT {
    NovelObject::NovelObject(const GeoVector<float>& position, const GeoVector<float>& size, NVGcontext *context, const float& rotation, const GeoVector<float>& scale) : _position(position), _rotation(rotation), _size(size), _context(context), _scale(scale) {
    }

    GeoVector<float> NovelObject::getPosition() const {
        return _position;
    }

    void NovelObject::setPosition(const GeoVector<float>& value)  {
        _position = value;
    }

    float NovelObject::getRotation() const {
        return _rotation;
    }

    void NovelObject::setRotation(const float& value) {
        _rotation = value;
    }

    GeoVector<float> NovelObject::getScale() const {
        return _scale;
    }

    void NovelObject::setScale(const GeoVector<float>& value) {
        _scale = value;
    }

    GeoVector<float> NovelObject::getSize() const {
        return _size;
    }

    void NovelObject::setSize(const GeoVector<float>& value) {
        _size = value;
    }

    bool NovelObject::getActive() const {
        return _active;
    }

    void NovelObject::setActive(const bool& value) {
        _active = value;
    }

    int NovelObject::getLayer() const {
        return _layer;
    }

    void NovelObject::setLayer(const int &value) {
        _layer = value;
    }

    int NovelObject::getOrderInLayer() const {
        return _orderInLayer;
    }

    void NovelObject::setOrderInLayer(const int& value) {
        _orderInLayer = value;
    }
}
