// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_BASEGEOMATRIX4X4F_H
#define NOVELRT_MATHS_BASEGEOMATRIX4X4F_H

#include "BaseGeoVector4F.h"  

#ifdef __cplusplus
extern "C" {
#endif

  struct NovelRTGeoMatrix4x4F
  {
    NovelRTGeoVector4F x;
    NovelRTGeoVector4F y;
    NovelRTGeoVector4F z;
    NovelRTGeoVector4F w;
  };

#ifdef __cplusplus
}
#endif

#endif