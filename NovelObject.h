//
// Created by matth on 15/12/2018.
//

#ifndef NOVELRT_NOVELOBJECT_H
#define NOVELRT_NOVELOBJECT_H
#include "nanovg/nanovg.h"
#include "GeoVector.h"

namespace NovelRT {
    class NovelObject {
    public:
        NovelObject(const GeoVector<float>& position, const GeoVector<float>& size, NVGcontext *context, const float& rotation = 0);

        GeoVector<float> getPosition() const;

        void setPosition(const GeoVector<float>& value);

        float getRotation() const;

        void setRotation(const float& value);

        GeoVector<float> getScale() const;

        void setScale(const GeoVector<float>& value);

        GeoVector<float> getSize() const;

        void setSize(const GeoVector<float>& value);

        virtual void drawObject(float deltaTime) const = 0;


    private:
        GeoVector<float> _position;
        GeoVector<float> _scale;
        GeoVector<float> _size;
        float _rotation;

    protected:
        NVGcontext* _context;
    };


}

#endif //NOVELRT_NOVELOBJECT_H
