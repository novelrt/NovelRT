//
// Created by matth on 19/12/2018.
//

#include "NovelRunner.h"

#include "../lib/SDL2/include/SDL.h"
#include <iostream>

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glext.h>

#if OPENGL_VERSION==3
#define NANOVG_GL3_IMPLEMENTATION
#elif OPENGL_VERSION==2
#define NANOVG_GL2_IMPLEMENTATION
#endif
#include "../lib/nanovg/nanovg.h"
#include "../lib/nanovg/nanovg_gl.h"
#include "../lib/nanovg/nanovg_gl_utils.h"
#include "GeoVector.h"
#include "NovelBasicFillRect.h"
#include "NovelImageRect.h"


namespace NovelRT {
    bool NovelRunner::sdlInit() {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
            std::cerr << "could not initialize sdl2: " << SDL_GetError() << std::endl;
            return false;
        }

        SDL_GetCurrentDisplayMode(0, &_current);
        // create window

        _window = SDL_CreateWindow(
                "NovelRTTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                500, 500, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (_window == NULL) {
            std::cerr << "could not create window: " << SDL_GetError() << std::endl;

            return false;
        }

        _openGLContext = SDL_GL_CreateContext(_window);
        SDL_GL_MakeCurrent(_window, _openGLContext);
        return true;
    }

    bool NovelRunner::nanovgInit() {
#if OPENGL_VERSION==3
        _nanovgContext = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
#elif OPENGL_VERSION==2
        _nanovgContext = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
#endif
        if (_nanovgContext == NULL) {
            std::cerr << "%llu\n", _nanovgContext;
            std::cerr << "Could not init nanovg.\n";
            return false;
        }

        return true;
    }

    int NovelRunner::runNovel(int aspectRatioWidth, int aspectRatioHeight) {
        _aspectRatioWidth = aspectRatioWidth;
        _aspectRatioHeight = aspectRatioHeight;
        if (!sdlInit()) {
            std::cerr << "Apologies, something went wrong. Reason: SDL could not initialise." << std::endl;
            return 1;
        }

        if (!nanovgInit()) {
            std::cerr << "Apologies, something went wrong. Reason: nanovg could not initialise." << std::endl;
            return 1;
        }

        int winWidth, winHeight;
        int fbWidth, fbHeight;
        float pxRatio;

        SDL_GetWindowSize(_window, &winWidth, &winHeight);
        fbWidth = winWidth;
        fbHeight = winHeight;

        pxRatio = (float) fbWidth / (float) winWidth;

        SDL_Event event;
        int running = 1;

        Uint64 NOW = SDL_GetPerformanceCounter();
        Uint64 LAST = 0;
        float deltaTime = 0;
/*        NovelBasicFillRect rect = NovelBasicFillRect(GeoVector<float>(500, 500),
                                                                       GeoVector<float>(200, 200),
                                                                       RGBAConfig(255, 0, 0, 255),
                                                                       _nanovgContext);

        auto imageRect = NovelImageRect(GeoVector<float>(200, 500), _nanovgContext, "test-yuri.png");*/



        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = 0;
                    break;
                }
            }
            LAST = NOW;
            NOW = SDL_GetPerformanceCounter();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            nvgBeginFrame(_nanovgContext, winWidth, winHeight, pxRatio);
            deltaTime = ((NOW - LAST) * 1000 / SDL_GetPerformanceFrequency()) * 0.001;

/*            rect.drawObject();
            imageRect.drawObject();*/

            for (auto i = _renderObjects.begin(); i != _renderObjects.end(); ++i) {
                i->drawObject();
            }

            nvgEndFrame(_nanovgContext);
            SDL_GL_SwapWindow(_window);
        }

        SDL_DestroyWindow(_window);
        SDL_Quit();
        return 0;
    }
}