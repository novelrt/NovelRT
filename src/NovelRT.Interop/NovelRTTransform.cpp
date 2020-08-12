// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/GeoVector2F_t.h"
#include "NovelRT.Interop/Maths/GeoBounds_t.h"
#include "NovelRT.Interop/NovelRTTransform.h"
#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

NovelRTTransform Transform_create(const GeoVector2F_t& position, float rotation, const GeoVector2F_t& scale) noexcept {
    return NovelRTTransform{position, scale, rotation};
}

NovelRTTransform Transform_createDefault() noexcept {
    return NovelRTTransform{GeoVector2F_zero(), GeoVector2F_zero(), 0.0f};
}

GeoBounds_t Transform_getAABB(const NovelRTTransform& transform) {
    const Transform& cTransform = reinterpret_cast<const Transform&>(transform);
    auto aabb = cTransform.getAABB();
    return reinterpret_cast<GeoBounds_t&>(aabb);
}

GeoBounds_t Transform_getBounds(const NovelRTTransform& transform) {
    const Transform& cTransform = reinterpret_cast<const Transform&>(transform);
    auto bounds = cTransform.getBounds();
    return reinterpret_cast<GeoBounds_t&>(bounds);
}

const GeoVector2F_t& Transform_getPositionReadOnly(const NovelRTTransform& transform) {
    const Maths::GeoVector2<float>& position = reinterpret_cast<const Transform&>(transform).position();
    return reinterpret_cast<const GeoVector2F_t&>(position);
}

GeoVector2F_t& Transform_getPosition(const NovelRTTransform& transform) {
    auto cTransform = reinterpret_cast<const Transform&>(transform);
    Maths::GeoVector2<float>& position = cTransform.position();
    return reinterpret_cast<GeoVector2F_t&>(position);
}

void Transform_setPosition(NovelRTTransform& transform, const GeoVector2F_t& position) {
    Transform& cTransform = reinterpret_cast<Transform&>(transform);
    cTransform.position() = reinterpret_cast<const Maths::GeoVector2<float>&>(position);
}

const float& Transform_getRotationReadOnly(const NovelRTTransform& transform) {
    return transform._rotation;
}

float& Transform_getRotation(const NovelRTTransform& transform) {
    auto cTransform = reinterpret_cast<const Transform&>(transform);
    return cTransform.rotation();
}

void Transform_setRotation(NovelRTTransform& transform, const float& rotation) {
    Transform& cTransform = reinterpret_cast<Transform&>(transform);
    cTransform.rotation() = rotation;
}

const GeoVector2F_t& Transform_getScaleReadOnly(const NovelRTTransform& transform) {
    return transform._scale;
}

GeoVector2F_t& Transform_getScale(const NovelRTTransform& transform) {
    auto cTransform = reinterpret_cast<const Transform&>(transform);
    Maths::GeoVector2<float>& scale = cTransform.scale();
    return reinterpret_cast<GeoVector2F_t&>(scale);
}

void Transform_setScale(NovelRTTransform& transform, const GeoVector2F_t& scale) {
    Transform& cTransform = reinterpret_cast<Transform&>(transform);
    cTransform.scale() = reinterpret_cast<const Maths::GeoVector2<float>&>(scale);
}

#ifdef __cplusplus
}
#endif

