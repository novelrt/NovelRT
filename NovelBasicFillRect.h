//
// Created by matth on 16/12/2018.
//

#ifndef NOVELRT_NOVELRECT_H
#define NOVELRT_NOVELRECT_H

#include "NovelObject.h"
#include "RGBAConfig.h"

namespace NovelRT {
    class NovelBasicFillRect : NovelObject {
    public:
        NovelBasicFillRect(const GeoVector<float>& position, const GeoVector<float>& size, const RGBAConfig& fillColour, NVGcontext* context, const float& rotation = 0);

        void drawObject(float deltaTime) const override;

        RGBAConfig getColourConfig() const;

        void setColourConfig(const RGBAConfig& value);

    private:

        RGBAConfig _colourConfig;






    };
}

#endif //NOVELRT_NOVELRECT_H
