#include <iostream>

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


SDL_Window* window;
struct NVGcontext* vg;
SDL_GLContext context;

bool sdlInit() {
    if (getenv("LINUX_SSH_ENABLED"))
        setenv("DISPLAY", "127.0.0.1:0", true);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return false;
    }
    // create window
    auto window = SDL_CreateWindow(
            "NovelRTTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            1000, 1000, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());

        return false;
    }

    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);
    return true;
}

bool nanovgInit() {
    vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    if (vg == NULL) {
        printf("%llu\n", context);
        printf("Could not init nanovg.\n");
        return false;
    }

    return true;
}

int main(int argc, char *argv[]) {
    if(!sdlInit()) {
        std::cout << "Apologies, something went wrong. Reason: SDL could not initialise." << std::endl;
        return 1;
    }

    if(!nanovgInit()) {
        std::cout << "Apologies, something went wrong. Reason: nanovg could not initialise." << std::endl;
        return 1;
    }

    int winWidth, winHeight;
    int fbWidth, fbHeight;
    float pxRatio;

    SDL_GetWindowSize(window, &winWidth, &winHeight);
    fbWidth = winWidth;
    fbHeight = winHeight;

    pxRatio = (float) fbWidth / (float) winWidth;

    SDL_Event event;
    int running = 1;

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    float deltaTime = 0;
    NovelRT::NovelBasicFillRect rect = NovelRT::NovelBasicFillRect(NovelRT::GeoVector<float>(500, 500), NovelRT::GeoVector<float>(200, 200), NovelRT::RGBAConfig(0, 0, 0, 255), vg);


    while(running) {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        nvgBeginFrame(vg, winWidth, winHeight, pxRatio);
        deltaTime = ((NOW - LAST) * 1000 / SDL_GetPerformanceFrequency()) * 0.001;
        rect.drawObject(deltaTime);
        nvgEndFrame(vg);

        SDL_GL_SwapWindow(window);
    }


}