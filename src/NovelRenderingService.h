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
        void runOnUpdate(const std::function<void(const float&)>& subscriber);
        void stopRunningOnUpdate(const std::function<void(const float&)>& subscriber);

        int initialiseRendering(const int& displayNumber);

        void updateRenderingLayerInfo(const int& layer, NovelObject* targetObject, const bool& migrate = true);

        NVGcontext* getNanoVGContext() const;

        void renderAllObjects(int winWidth, int winHeight, float pxRatio) const;

        void tearDown() const;

        NovelImageRect& getImageRect(const std::string& filePath, const GeoVector<float>& startingPosition, const float& startingRotation, const GeoVector<float>& startingScale, const int& layer, const int& orderInLayer);
        NovelBasicFillRect& getBasicFillRect(const GeoVector<float>& startingPosition, const float& startingRotation, const GeoVector<float>& startingSize, const GeoVector<float>& startingScale);

        void executeUpdateSubscriptions(const float &deltaTime) const;

        void sortLayerRenderOrder(const int& layer);

        SDL_Window* getWindow();

    private:
        std::vector<std::function<void(const float&)>> _updateSubscribers;

        bool nanovgInit();

        bool sdlInit(const int& displayNumber);

        SDL_Window *_window;
        struct NVGcontext *_nanovgContext;
        SDL_GLContext _openGLContext;
        std::map<int, std::vector<NovelObject*>> _renderObjects;
        float _screenScale;


    };

}
#endif //NOVELRT_NOVELRENDERINGSERVICE_H
