//
// Created by miron on 2/21/19.
//

#ifndef NOVELRT_NOVELCOMMONARGS_H
#define NOVELRT_NOVELCOMMONARGS_H

#include "NovelRenderingService.h"

namespace NovelRT {
struct NovelCommonArgs {
public:
  NovelCommonArgs() {};
  GeoVector<float> startingPosition = GeoVector<float>(0, 0);
  float startingRotation;
  GeoVector<float> startingScale = GeoVector<float>(1.0f, 1.0f);
  int layer;
  int orderInLayer;
};
}

#endif //NOVELRT_NOVELCOMMONARGS_H
