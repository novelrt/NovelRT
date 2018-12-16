//
// Created by matth on 16/12/2018.
//

#include "RGBAConfig.h"

namespace NovelRT {
    RGBAConfig::RGBAConfig(int r, int g, int b, int a) {
        _r = r;
        _g = g;
        _b = b;
        _a = a;
    }

    int RGBAConfig::getR() const {
        return _r;
    }

    void RGBAConfig::setR(int value) {
        if(value < 0) {
            _r = 0;
        }
        else if (value > 255) {
            _r = 255;
        }
        else {
            _r = value;
        }
    }

    int RGBAConfig::getG() const {
        return _g;
    }

    void RGBAConfig::setG(int value) {
        if(value < 0) {
            _g = 0;
        }
        else if (value > 255) {
            _g = 255;
        }
        else {
            _g = value;
        }
    }

    int RGBAConfig::getB() const {
        return _b;
    }

    void RGBAConfig::setB(int value) {
        if(value < 0) {
            _b = 0;
        }
        else if (value > 255) {
            _b = 255;
        }
        else {
            _b = value;
        }
    }

    int RGBAConfig::getA() const {
        return _a;
    }

    void RGBAConfig::setA(int value) {
        if(value < 0) {
            _a = 0;
        }
        else if (value > 255) {
            _a = 255;
        }
        else {
            _a = value;
        }
    }
}

