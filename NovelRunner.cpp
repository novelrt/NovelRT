//
// Created by matth on 19/12/2018.
//

#include "NovelRunner.h"

#include "SDL2/SDL.h"
#include <iostream>

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glext.h>

#define NANOVG_GL2_IMPLEMENTATION

#include "nanovg/nanovg.h"
#include "nanovg/nanovg_gl.h"
#include "nanovg/nanovg_gl_utils.h"
#include "GeoVector.h"
#include "NovelBasicFillRect.h"


namespace NovelRT {
    bool NovelRunner::sdlInit() {
        if (getenv("LINUX_SSH_ENABLED"))
            setenv("DISPLAY", "127.0.0.1:0", true);
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
            fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
            return false;
        }
        // create window
        _window = SDL_CreateWindow(
                "NovelRTTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                1000, 1000, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (_window == NULL) {
            std::cerr << "could not create window: %s\n", SDL_GetError();

            return false;
        }

        _openGLContext = SDL_GL_CreateContext(_window);
        SDL_GL_MakeCurrent(_window, _openGLContext);
        return true;
    }

    bool NovelRunner::nanovgInit() {
        _nanovgContext = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
        if (_nanovgContext == NULL) {
            std::cerr << "%llu\n", _nanovgContext;
            std::cerr << "Could not init nanovg.\n";
            return false;
        }

        return true;
    }

    int NovelRunner::runNovel(int aspectRatioWidth, int aspectRatioHeight) {
        if (!sdlInit()) {
            std::cout << "Apologies, something went wrong. Reason: SDL could not initialise." << std::endl;
            return 1;
        }

        if (!nanovgInit()) {
            std::cout << "Apologies, something went wrong. Reason: nanovg could not initialise." << std::endl;
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
        NovelRT::NovelBasicFillRect rect = NovelRT::NovelBasicFillRect(NovelRT::GeoVector<float>(500, 500),
                                                                       NovelRT::GeoVector<float>(200, 200),
                                                                       NovelRT::RGBAConfig(255, 0, 0, 255),
                                                                       _nanovgContext);


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

            rect.drawObject();

            nvgEndFrame(_nanovgContext);
            SDL_GL_SwapWindow(_window);
        }

        SDL_DestroyWindow(_window);
        SDL_Quit();
        return 0;
    }
}