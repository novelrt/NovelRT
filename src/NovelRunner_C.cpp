//
// Created by miron on 2/20/19.
//

#include "NovelRunner.h"
#include "NovelRunner_C.h"

extern "C" {
    NovelRunner_t *createRunner(int displayNumber) {
        return reinterpret_cast<NovelRunner_t*>(new NovelRT::NovelRunner(displayNumber));
    }

    void destroyRunner(NovelRunner_t* runner) {
        delete reinterpret_cast<NovelRT::NovelRunner*>(runner);
    }

    void executeUpdateSubscriptions(NovelRunner_t* runner, const float deltaTime) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->executeUpdateSubscriptions(deltaTime);
    }

    void runOnUpdate(NovelRunner_t* runner, NovelSubscriber subscriber) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->runOnUpdate(subscriber);
    }

    void stopRunningOnUpdate(NovelRunner_t* runner, NovelSubscriber subscriber) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->stopRunningOnUpdate(subscriber);
    }

    int runNovel(NovelRunner_t* runner) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->runNovel();
    }
}
