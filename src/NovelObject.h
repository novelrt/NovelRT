// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELOBJECT_H
#define NOVELRT_NOVELOBJECT_H
#include "GeoVector.h"
#include "NovelCommonArgs.h"
#include "NovelLayeringService.h"
#include "GeoBounds.h"

namespace NovelRT {
  class NovelLayeringService;
  class NovelObject {

  protected:
    GeoVector<float> _position;
    GeoVector<float> _scale;
    GeoVector<float> _size;
    float _rotation;
    bool _active = true;
    int _orderInLayer;
    int _layer;
    float _screenScale;
    NovelLayeringService* _layeringService;
    bool _isDirty = true;
    GeoBounds _objectBounds = GeoBounds(GeoVector<float>(0, 0), GeoVector<float>(0, 0), 0);

  public:
    NovelObject(NovelLayeringService* layeringService,
                const float& screenScale,
                const GeoVector<float>& size,
                const NovelCommonArgs& args);
    virtual ~NovelObject();

    virtual GeoVector<float> getWorldSpacePosition() const;
    virtual void setWorldSpacePosition(const GeoVector<float>& value);

    virtual GeoVector<float> getScreenSpacePosition() const;

    virtual float getRotation() const;
    virtual void setRotation(float value);

    virtual GeoVector<float> getScale() const;
    virtual void setScale(const GeoVector<float>& value);

    virtual GeoVector<float> getWorldSpaceSize() const;
    virtual void setWorldSpaceSize(const GeoVector<float>& value);

    virtual GeoVector<float> getScreenSpaceSize() const;

    virtual int getLayer() const;
    virtual void setLayer(int value);

    virtual int getOrderInLayer() const;
    virtual void setOrderInLayer(int value);

    virtual bool getActive() const;
    virtual void setActive(bool value);

    virtual void executeObjectBehaviour() = 0;

    virtual GeoBounds getScreenSpaceObjectBounds();

    virtual float getScaleHypotenuseScalar() const;
  };
}

#endif //NOVELRT_NOVELOBJECT_H
