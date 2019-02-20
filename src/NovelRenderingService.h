//
// Created by matth on 19/12/2018.
//

#ifndef NOVELRT_NOVELRENDERINGSERVICE_H
#define NOVELRT_NOVELRENDERINGSERVICE_H

#include "../lib/SDL2/include/SDL.h"
#include "../lib/nanovg/nanovg.h"
#include "GeoVector.h"
#include <vector>
#include <map>
#include <functional>

namespace NovelRT {
    class NovelObject;
    class NovelImageRect;
    class NovelBasicFillRect;

    class NovelRenderingService {
    public:
        int initialiseRendering(const int& displayNumber);

        void updateRenderingLayerInfo(const int& layer, NovelObject* targetObject, const bool& migrate = true);

        NVGcontext* getNanoVGContext() const;

        void renderAllObjects() const;

        void tearDown() const;

        NovelImageRect getImageRect(const std::string_view filePath, const GeoVector<float>& startingPosition, const float& startingRotation, const GeoVector<float>& startingScale, const int& layer, const int& orderInLayer);
        NovelBasicFillRect getBasicFillRect(const GeoVector<float>& startingPosition, const float& startingRotation, const GeoVector<float>& startingSize, const GeoVector<float>& startingScale);

        void sortLayerRenderOrder(const int& layer);

        SDL_Window* getWindow() const;

    private:
        bool nanovgInit();

        bool sdlInit(const int& displayNumber);

        SDL_Window *_window;
        struct NVGcontext *_nanovgContext;
        SDL_GLContext _openGLContext;
        std::map<int, std::vector<NovelObject*>> _renderObjects;
        float _screenScale;


        int _winWidth;
        int _winHeight;
        int _frameBufferWidth;
        float _pxRatio;
    };

}
#endif //NOVELRT_NOVELRENDERINGSERVICE_H
