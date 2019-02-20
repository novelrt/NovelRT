//
// Created by matth on 16/02/2019.
//

#include <iostream>
#include "NovelRunner.h"
#include "../lib/SDL2/include/SDL.h"

namespace NovelRT {
    int NovelRunner::runNovel(NovelRenderingService& novelRenderer) const {

        Uint64 current = SDL_GetPerformanceCounter();
        Uint64 previous = 0;
        float deltaTime = 0;
        SDL_Event event;
        int exitCode = 1;
        while (exitCode) {
            previous = current;
            current = SDL_GetPerformanceCounter();
            deltaTime = ((current - previous) * 1000 / SDL_GetPerformanceFrequency()) * 0.001f;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    exitCode = 0;
                    break;
                }
            }
            novelRenderer.executeUpdateSubscriptions(deltaTime);
            novelRenderer.renderAllObjects();

        }
        novelRenderer.tearDown();
        return exitCode;
    }
}