//
// Created by matth on 19/12/2018.
//

#ifndef NOVELRT_NOVELRUNNER_H
#define NOVELRT_NOVELRUNNER_H

#include "SDL2/SDL.h"
#include "nanovg/nanovg.h"

namespace NovelRT {
    class NovelRunner {
    public:
        int runNovel(int aspectRatioWidth, int aspectRatioHeight);

    private:
        bool nanovgInit();

        bool sdlInit();

        SDL_Window *_window;
        struct NVGcontext *_nanovgContext;
        SDL_GLContext _openGLContext;
    };

}
#endif //NOVELRT_NOVELRUNNER_H
