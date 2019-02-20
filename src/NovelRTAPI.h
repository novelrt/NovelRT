//
// Created by miron on 2/14/19.
//

#ifndef LIBNOVELRT_NOVELRTAPI_H
#define LIBNOVELRT_NOVELRTAPI_H

#include "NovelRenderingService.h"
#include "NovelRunner.h"

extern "C" int runNovel(NovelRT::NovelRunner* runner) {
    return runner->runNovel();
};

extern "C" void runOnUpdate(NovelSubscriber subscriber, NovelRT::NovelRunner* runner) {
    runner
    ->getRenderer()
    ->runOnUpdate(subscriber);
};

extern "C" NovelRT::NovelRunner* createRunner(int displayNumber) {
    return new NovelRT::NovelRunner(displayNumber);
};

#endif //LIBNOVELRT_NOVELRTAPI_H
