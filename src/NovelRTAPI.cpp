//
// Created by miron on 2/22/19.
//

#include "NovelRTAPI.h"
#include "NovelRunner.h"

extern "C" {
    NovelRunnerWrapper* createRunner(int displayNumber) {
        return reinterpret_cast<NovelRunnerWrapper*>(new NovelRT::NovelRunner(displayNumber));
    }

    void destroyRunner(NovelRunnerWrapper* runner) {
        delete reinterpret_cast<NovelRT::NovelRunner*>(runner);
    }

    void executeUpdateSubscriptions(NovelRunnerWrapper* runner, const float deltaTime) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->executeUpdateSubscriptions(deltaTime);
    }

    void runOnUpdate(NovelRunnerWrapper* runner, NovelSubscriber subscriber) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->runOnUpdate(subscriber);
    }

    void stopRunningOnUpdate(NovelRunnerWrapper* runner, NovelSubscriber subscriber) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->stopRunningOnUpdate(subscriber);
    }

    int runNovel(NovelRunnerWrapper* runner) {
        return reinterpret_cast<NovelRT::NovelRunner*>(runner)->runNovel();
    }
}