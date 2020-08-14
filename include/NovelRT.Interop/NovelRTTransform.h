// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/NovelRTGeoVector2F.h"
#include "NovelRT.Interop/Maths/NovelRTGeoBounds.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#ifndef NOVELRT_INTEROP_TRANSFORM_H
#define NOVELRT_INTEROP_TRANSFORM_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    NovelRTGeoVector2F _position;
    NovelRTGeoVector2F _scale;
    float _rotation;
} NovelRTTransform;

NovelRTGeoBounds NovelRT_Transform_getAABB(const NovelRTTransform transform);
NovelRTGeoBounds NovelRT_Transform_getBounds(const NovelRTTransform transform);

#ifdef __cplusplus
}
#endif


#endif //NOVELRT_INTEROP_TRANSFORM_H
