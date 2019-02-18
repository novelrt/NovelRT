//
// Created by matth on 16/02/2019.
//

#ifndef NOVELRT_NOVELRUNNER_H
#define NOVELRT_NOVELRUNNER_H


#include "NovelRenderingService.h"

namespace NovelRT {
    class NovelRunner {
    public:
        int runNovel(const NovelRenderingService& novelRenderer, SDL_Window* window) const;

    };
}

#endif //NOVELRT_NOVELRUNNER_H
