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

namespace NovelRT {
    class NovelRunner {
    public:
        int runNovel(int displayNumber);

    private:
        bool nanovgInit();

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
