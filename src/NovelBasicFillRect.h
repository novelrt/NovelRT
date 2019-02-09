//
// Created by matth on 16/12/2018.
//

#ifndef NOVELRT_NOVELRECT_H
#define NOVELRT_NOVELRECT_H

#include "NovelObject.h"
#include "RGBAConfig.h"

namespace NovelRT {
    class NovelBasicFillRect : public NovelObject {
    public:
        NovelBasicFillRect(const GeoVector<float>& position, const GeoVector<float>& size, const RGBAConfig& fillColour, NVGcontext* context, const float& rotation = 0, const GeoVector<float>& scale = GeoVector<float>(1.0f, 1.0f));

        void drawObject() const override;

        RGBAConfig getColourConfig() const;

        void setColourConfig(const RGBAConfig& value);

    private:

        RGBAConfig _colourConfig;






    };
}

#endif //NOVELRT_NOVELRECT_H
