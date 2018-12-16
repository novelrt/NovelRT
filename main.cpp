#include <iostream>

#include "SDL/include/SDL.h"
#include <iostream>

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glext.h>

#define NANOVG_GL2_IMPLEMENTATION

#include "nanovg/nanovg.h"
#include "nanovg/nanovg_gl.h"
#include "nanovg/nanovg_gl_utils.h"

bool init() {
    if (getenv("LINUX_SSH_ENABLED"))
        setenv("DISPLAY", "127.0.0.1:0", true);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }
    // create window
    window = SDL_CreateWindow(
            "hello_sdl2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());

        return false;
    }
    return true;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    return 0;
}