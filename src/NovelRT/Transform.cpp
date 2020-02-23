// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT {
  Transform::Transform(const Maths::GeoVector<float>& position, float rotation, const Maths::GeoVector<float>& scale) noexcept :
    _active(true) {
    setPosition(position);
    setRotation(rotation);
    setScale(scale);
  }

  Transform::Transform() noexcept :
    _active(true) {
    setPosition(Maths::GeoVector<float>::zero());
    setRotation(0.0f);
    setScale(Maths::GeoVector<float>::zero());
  }
}
