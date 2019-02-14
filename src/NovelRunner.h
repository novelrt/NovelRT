//
// Created by matth on 19/12/2018.
//

#ifndef NOVELRT_NOVELRUNNER_H
#define NOVELRT_NOVELRUNNER_H

#include "../lib/SDL2/include/SDL.h"
#include "../lib/nanovg/nanovg.h"
#include <vector>
#include <map>
#include "NovelObject.h"
#include "NovelImageRect.h"
#include "NovelBasicFillRect.h"
#include <functional>

namespace NovelRT {
    class NovelRunner {
    public:
        NovelImageRect& getImageRect(const std::string& filePath, const GeoVector<float>& startingPosition, const GeoVector<float>& startingRotation, const GeoVector<float>& startingScale);
        NovelBasicFillRect& getBasicFillRect(const GeoVector<float>& startingPosition, const GeoVector<float>& startingRotation, const GeoVector<float>& startingSize, const GeoVector<float>& startingScale);
        void addSubscriber(const std::function<void(const float&)>& subscriber);
        void addSubcribers(const std::vector<std::function<void(const float&)>>);
        void stopRunningOnUpdate(const std::function<void(const float&)>& subscriber);

        int runNovel(int displayNumber);

    private:
        std::vector<std::function<void(const float&)>> _updateSubscribers;

        bool nanovgInit();
        void invokeSubscribers(const float&);

        bool sdlInit(const int& displayNumber);

        SDL_Window *_window;
        struct NVGcontext *_nanovgContext;
        SDL_GLContext _openGLContext;
        int _aspectRatioWidth;
        int _aspectRatioHeight;
        SDL_DisplayMode _current;
        std::map<int, std::vector<NovelObject*>> _renderObjects;
        float _screenScale;

    };

}
#endif //NOVELRT_NOVELRUNNER_H
