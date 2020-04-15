// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_WORLDOBJECT_H
#define NOVELRT_WORLDOBJECT_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT {
  /**
   * Represents an object in the game world.
   *
   * WorldObjects have a transform, and can be active or not.
   * They are also rendered in the world in order of their layer.
   */
  class WorldObject {
  private:
    Transform _transform;
    int _layer;
    bool _active;

  protected:
    bool _isDirty;

  public:
    WorldObject(const Transform& transform, int layer);
    virtual ~WorldObject() { }

    inline Transform& transform() {
      _isDirty = true;
      return _transform;
    }

    inline const Transform& transform() const {
      return _transform;
    }

    inline const int& layer() const {
      return _layer;
    }

    inline int& layer() {
      return _layer;
    }

    virtual bool getActive() const;

    virtual void setActive(bool value);

    virtual void executeObjectBehaviour() = 0;
};
}

#endif //NOVELRT_WORLDOBJECT_H
