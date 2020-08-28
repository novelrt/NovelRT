// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_BASEGEOBOUNDS_H
#define NOVELRT_MATHS_BASEGEOBOUNDS_H

#include "BaseGeoVector2F.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct {
    NovelRTGeoVector2F position;
    float rotation;
    NovelRTGeoVector2F size;
  } NovelRTGeoBounds;

#ifdef __cplusplus
}
#endif

#endif