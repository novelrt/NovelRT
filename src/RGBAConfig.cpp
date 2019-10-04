// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See License.md in the repository root for more information.

#include "RGBAConfig.h"

namespace NovelRT {
RGBAConfig::RGBAConfig(const int r, const int g, const int b, const int a) {
  _r = r;
  _g = g;
  _b = b;
  _a = a;
}

int RGBAConfig::getR() const {
  return _r;
}

void RGBAConfig::setR(const int value) {
  if (value < 0) {
    _r = 0;
  } else if (value > 255) {
    _r = 255;
  } else {
    _r = value;
  }
}

int RGBAConfig::getG() const {
  return _g;
}

void RGBAConfig::setG(const int value) {
  if (value < 0) {
    _g = 0;
  } else if (value > 255) {
    _g = 255;
  } else {
    _g = value;
  }
}

int RGBAConfig::getB() const {
  return _b;
}

void RGBAConfig::setB(const int value) {
  if (value < 0) {
    _b = 0;
  } else if (value > 255) {
    _b = 255;
  } else {
    _b = value;
  }
}

int RGBAConfig::getA() const {
  return _a;
}

void RGBAConfig::setA(const int value) {
  if (value < 0) {
    _a = 0;
  } else if (value > 255) {
    _a = 255;
  } else {
    _a = value;
  }
}
float RGBAConfig::getRScalar() const {
  return getR() / 255.0f;
}
float RGBAConfig::getGScalar() const {
  return getG() / 255.0f;
}
float RGBAConfig::getBScalar() const {
  return getB() / 255.0f;
}
float RGBAConfig::getAScalar() const {
  return getA() / 255.0f;
}
}

