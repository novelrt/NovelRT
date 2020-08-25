// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT {
  Transform::Transform(const Maths::GeoVector2F& position, float rotation, const Maths::GeoVector2F& scale) noexcept :
    _position(position),
    _scale(scale),
    _rotation(rotation){}

  Transform::Transform() noexcept :
    _position(Maths::GeoVector2F::zero()),
    _scale(Maths::GeoVector2F::zero()),
    _rotation(0.0f){}
}
