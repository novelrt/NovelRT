// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT {
  Transform::Transform(const Maths::GeoVector2<float>& position, float rotation, const Maths::GeoVector2<float>& scale) noexcept :
    _position(position),
    _scale(scale),
    _rotation(rotation),
    _active(true) {}

  Transform::Transform() noexcept :
    _position(Maths::GeoVector2<float>::zero()),
    _scale(Maths::GeoVector2<float>::zero()),
    _rotation(0.0f),
    _active(true) {}
}
