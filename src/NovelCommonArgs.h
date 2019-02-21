//
// Created by miron on 2/21/19.
//

#ifndef NOVELRT_NOVELCOMMONARGS_H
#define NOVELRT_NOVELCOMMONARGS_H

#include "NovelRenderingService.h"

namespace NovelRT {
    class NovelCommonArgs {
    public:
        NovelCommonArgs(
                const GeoVector<float>& startingPosition,
                const float startingRotation,
                const GeoVector<float>& startingScale,
                const int layer,
                const int orderInLayer
                ) :
                startingPosition(startingPosition),
                startingRotation(startingRotation),
                startingScale(startingScale),
                layer(layer),
                orderInLayer(orderInLayer)
                {};
        const GeoVector<float>& startingPosition;
        const float startingRotation;
        const GeoVector<float>& startingScale;
        const int layer;
        const int orderInLayer;
    };
}

#endif //NOVELRT_NOVELCOMMONARGS_H
