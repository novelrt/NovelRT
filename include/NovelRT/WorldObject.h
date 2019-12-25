// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_WORLDOBJECT_H
#define NOVELRT_WORLDOBJECT_H
#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT {
  class WorldObject {
  private:
    Transform _transform;
    bool _active;
  protected:
    bool _isDirty;
  public:
    WorldObject(const Transform& transform);

    inline Transform& getTransform() {
      _isDirty = true;
      return _transform;
    }

    inline const Transform& getTransformReadonly() const {
      return _transform;
    }

    virtual bool getActive() const;

    virtual void setActive(bool value);

    virtual void executeObjectBehaviour() = 0;
};
}
#endif //NOVELRT_WORLDOBJECT_H
