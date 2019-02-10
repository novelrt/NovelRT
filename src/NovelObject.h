//
// Created by matth on 15/12/2018.
//

#ifndef NOVELRT_NOVELOBJECT_H
#define NOVELRT_NOVELOBJECT_H
#include "GeoVector.h"
#include "../lib/nanovg/nanovg.h"

namespace NovelRT {
    class NovelObject {
    public:
        NovelObject(const float& screenScale, const GeoVector<float>& position, const GeoVector<float>& size, NVGcontext *context, const float& rotation = 0, const GeoVector<float>& scale = GeoVector<float>(1, 1));

        virtual GeoVector<float> getPosition() const;

        virtual void setPosition(const GeoVector<float>& value);

        virtual float getRotation() const;

        virtual void setRotation(const float& value);

        virtual GeoVector<float> getScale() const;

        virtual void setScale(const GeoVector<float>& value);

        virtual GeoVector<float> getSize() const;

        virtual void setSize(const GeoVector<float>& value);

        virtual int getLayer() const;

        virtual void setLayer(const int& value);

        virtual int getOrderInLayer() const;

        virtual void setOrderInLayer(const int& value);

        virtual bool getActive() const;

        virtual void setActive(const bool& value);

        virtual void drawObject() const = 0;


    protected:
        GeoVector<float> _position;
        GeoVector<float> _scale;
        GeoVector<float> _size;
        float _rotation;
        bool _active = true;
        int _orderInLayer;
        int _layer;
        NVGcontext* _context;
        float _screenScale;
    };


}

#endif //NOVELRT_NOVELOBJECT_H
