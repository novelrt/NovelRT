// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT {
  Transform::Transform(Maths::GeoVector2F position, float rotation, Maths::GeoVector2F scale) noexcept :
    position(position),
    scale(scale),
    rotation(rotation){}

  Transform::Transform() noexcept :
    position(Maths::GeoVector2F::zero()),
    scale(Maths::GeoVector2F::zero()),
    rotation(0.0f){}
}
