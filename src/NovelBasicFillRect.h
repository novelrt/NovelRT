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
        NovelBasicFillRect(NovelRenderingService* novelRenderer, const float& screenScale, const GeoVector<float>& position, const GeoVector<float>& size, const RGBAConfig& fillColour, const float& rotation, const GeoVector<float>& scale, const int& layer, const int& orderInLayer);

        void drawObject() const override;

        RGBAConfig getColourConfig() const;

        void setColourConfig(const RGBAConfig& value);

    private:

        RGBAConfig _colourConfig;






    };
}

#endif //NOVELRT_NOVELRECT_H
