//
// Created by matth on 05/01/2019.
//

#ifndef NOVELRT_NOVELIMAGERECT_H
#define NOVELRT_NOVELIMAGERECT_H

#include "NovelObject.h"
#include "RGBAConfig.h"
#include <string>
#include "nanovg/nanovg.h"

namespace NovelRT {

    class NovelImageRect : public NovelObject {
    public:
        NovelImageRect(const GeoVector<float>& position, NVGcontext* context, const std::string& imageDir, const float& rotation = 0);

        void drawObject() const override;

    private:
        std::string _imageDir;
        int _imageHandle;
        NVGpaint _paint;

    };

}
#endif //NOVELRT_NOVELIMAGERECT_H
