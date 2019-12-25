// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT {
  WorldObject::WorldObject(const Transform& transform) : _transform(transform) {}

  bool WorldObject::getActive() const {
	  return _active;
  }

  void WorldObject::setActive(bool value) {
    _active = value;
  }
}
