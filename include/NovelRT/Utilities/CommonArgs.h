// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_UTILITIES_COMMONARGS_H
#define NOVELRT_UTILITIES_COMMONARGS_H
#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Utilities {
  struct CommonArgs {
  public:
    Maths::GeoVector<float> startingPosition = Maths::GeoVector<float>(0, 0);
    float startingRotation = 0;
    Maths::GeoVector<float> startingScale = Maths::GeoVector<float>(1.0f, 1.0f);
    int layer = 0;
    int orderInLayer = 0;

    CommonArgs() {};
  };
}

#endif //NOVELRT_UTILITIES_COMMONARGS_H
