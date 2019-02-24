//
// Created by matth on 15/12/2018.
//

#ifndef NOVELRT_NOVELOBJECT_H
#define NOVELRT_NOVELOBJECT_H
#include "GeoVector.h"
#include "../lib/nanovg/nanovg.h"
#include "NovelRenderingService.h"
#include "NovelLayeringService.h"

namespace NovelRT {
class NovelLayeringService;
class NovelObject {
public:
  NovelObject(NovelLayeringService* layeringService, const float& screenScale, const GeoVector<float>& size,
              const NovelCommonArgs& args);

  virtual GeoVector<float> getPosition() const;

  virtual void setPosition(const GeoVector<float>& value);

  virtual float getRotation() const;

  virtual void setRotation(const float value);

  virtual GeoVector<float> getScale() const;

  virtual void setScale(const GeoVector<float>& value);

  virtual GeoVector<float> getSize() const;

  virtual void setSize(const GeoVector<float>& value);

  virtual int getLayer() const;

  virtual void setLayer(const int value);

  virtual int getOrderInLayer() const;

  virtual void setOrderInLayer(const int value);

  virtual bool getActive() const;

  virtual void setActive(const bool value);

  virtual void executeObjectBehaviour() const = 0;

  inline bool operator>(const NovelObject& other) const {
    return getOrderInLayer() > other.getOrderInLayer();
  }

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
};

}

#endif //NOVELRT_NOVELOBJECT_H
