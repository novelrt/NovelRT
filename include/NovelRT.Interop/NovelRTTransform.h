// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/GeoVector2F_t.h"
#include "NovelRT.Interop/Maths/GeoBounds_t.h"
#ifndef NOVELRT_INTEROP_TRANSFORM_H
#define NOVELRT_INTEROP_TRANSFORM_H

#ifdef __cplusplus
extern "C" {
#endif

struct NovelRTTransform {
    GeoVector2F_t _position;
    GeoVector2F_t _scale;
    float _rotation;
};

NovelRTTransform Transform_create(const GeoVector2F_t& position, float rotation, const GeoVector2F_t& scale) noexcept;
NovelRTTransform Transform_createDefault() noexcept;
GeoBounds_t Transform_getAABB(const NovelRTTransform& transform);
GeoBounds_t Transform_getBounds(const NovelRTTransform& transform);
const GeoVector2F_t& Transform_getPositionReadOnly(const NovelRTTransform& transform);
GeoVector2F_t& Transform_getPosition(const NovelRTTransform& transform);
void Transform_setPosition(NovelRTTransform& transform, const GeoVector2F_t& position);
const float& Transform_getRotationReadOnly(const NovelRTTransform& transform);
float& Transform_getRotation(const NovelRTTransform& transform);
void Transform_setRotation(NovelRTTransform& transform, const float& rotation);
const GeoVector2F_t& Transform_getScaleReadOnly(const NovelRTTransform& transform);
GeoVector2F_t& Transform_getScale(const NovelRTTransform& transform);
void Transform_setScale(NovelRTTransform& transform, const GeoVector2F_t& scale);
//TODO: Add delete method?

#ifdef __cplusplus
}
#endif


#endif //NOVELRT_INTEROP_TRANSFORM_H
