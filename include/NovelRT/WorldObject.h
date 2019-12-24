#ifndef NOVELRT_WORLDOBJECT_H
#define NOVELRT_WORLDOBJECT_H
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
