// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELWORLDOBJECT_H
#define NOVELRT_NOVELWORLDOBJECT_H

namespace NovelRT {
  class LayeringService;
  class Transform {
  protected:
    Maths::GeoVector<float> _position;
    Maths::GeoVector<float> _scale;
    float _rotation;
    bool _active = true;
    int _orderInLayer;
    int _layer;
    LayeringService* _layeringService;

  public:
    Transform(LayeringService* layeringService, const Utilities::CommonArgs& args);

    virtual ~Transform();

    virtual Maths::GeoVector<float> getPosition() const;

    virtual void setPosition(const Maths::GeoVector<float>& value);

    virtual float getRotation() const;

    virtual void setRotation(float value);

    virtual Maths::GeoVector<float> getScale() const;

    virtual void setScale(const Maths::GeoVector<float>& value);

    virtual int getLayer() const;

    virtual void setLayer(int value);

    virtual int getOrderInLayer() const;

    virtual void setOrderInLayer(int value);

    virtual bool getActive() const;

    virtual void setActive(bool value);

    virtual void executeObjectBehaviour() = 0;
  };
}
#endif //NOVELRT_NOVELWORLDOBJECT_H
