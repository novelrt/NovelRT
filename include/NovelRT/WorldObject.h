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
    int _layer;
    bool _active;

  protected:
    bool _isDirty;

  public:
    WorldObject(const Transform& transform, int layer);
    virtual ~WorldObject() { }

    inline Transform& getTransform() {
      _isDirty = true;
      return _transform;
    }

    inline const Transform& getTransform() const {
      return _transform;
    }

    inline int getLayer() const {
      return _layer;
    }

    inline void setLayer(int value) {
      _layer = value;
    }

    virtual bool getActive() const;

    virtual void setActive(bool value);

    virtual void executeObjectBehaviour() = 0;
};
}

#endif //NOVELRT_WORLDOBJECT_H
