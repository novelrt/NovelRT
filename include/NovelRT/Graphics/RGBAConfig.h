// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_RGBACONFIG_H
#define NOVELRT_GRAPHICS_RGBACONFIG_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  class RGBAConfig {

  private:
    int _r;
    int _g;
    int _b;
    int _a;

  public:
    RGBAConfig(int r,
               int g,
               int b,
               int a);

    int getR() const;
    float getRScalar() const;
    void setR(int value);

    int getG() const;
    float getGScalar() const;
    void setG(int value);

    int getB() const;
    float getBScalar() const;
    void setB(int value);

    int getA() const;
    float getAScalar() const;
    void setA(int value);
  };
}

#endif //NOVELRT_GRAPHICS_RGBACONFIG_H
