// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_RGBACONFIG_H
#define NOVELRT_RGBACONFIG_H

namespace NovelRT {
class RGBAConfig {
public:
  RGBAConfig(int r, int g, int b, int a);

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

private:
  int _r;
  int _g;
  int _b;
  int _a;

};
}

#endif //NOVELRT_RGBACONFIG_H
