//
// Created by matth on 16/02/2019.
//

#ifndef NOVELRT_NOVELRUNNER_H
#define NOVELRT_NOVELRUNNER_H


#include "NovelRenderingService.h"

namespace NovelRT {
    class NovelRunner {
    public:
        explicit NovelRunner(int);
        int runNovel() const;
        std::shared_ptr<NovelRenderingService> getRenderer();

    private:
        std::shared_ptr<NovelRenderingService> _novelRenderer;
    };
}

#endif //NOVELRT_NOVELRUNNER_H
