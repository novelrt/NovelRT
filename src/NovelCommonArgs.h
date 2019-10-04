// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELCOMMONARGS_H
#define NOVELRT_NOVELCOMMONARGS_H

#include "GeoVector.h"
namespace NovelRT {
struct NovelCommonArgs {
public:
  NovelCommonArgs() {};
  GeoVector<float> startingPosition = GeoVector<float>(0, 0);
  float startingRotation = 0;
  GeoVector<float> startingScale = GeoVector<float>(1.0f, 1.0f);
  int layer = 0;
  int orderInLayer = 0;
};
}

#endif //NOVELRT_NOVELCOMMONARGS_H
