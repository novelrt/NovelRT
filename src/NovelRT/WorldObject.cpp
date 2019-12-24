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
