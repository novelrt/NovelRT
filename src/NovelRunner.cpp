//
// Created by matth on 16/02/2019.
//

#include <iostream>
#include "NovelRunner.h"
#include "../lib/SDL2/include/SDL.h"
#include "NovelImageRect.h"

namespace NovelRT {
    int NovelRunner::runNovel() const {
        auto imageRect = _novelRenderer->getImageRect("test-yuri.png", NovelRT::GeoVector<float>(960, 540), 0, NovelRT::GeoVector<float>(1,1), 0, 0);
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
            executeUpdateSubscriptions(deltaTime);
            _novelRenderer->renderAllObjects();

        }
        _novelRenderer->tearDown();
        return exitCode;
    }

    NovelRunner::NovelRunner(int displayNumber) : _novelRenderer(std::make_shared<NovelRenderingService>()) {
        _novelRenderer->initialiseRendering(displayNumber);
    }

    void NovelRunner::runOnUpdate(NovelSubscriber subscriber) {
        _updateSubscribers.push_back(subscriber);
    }

    void NovelRunner::stopRunningOnUpdate(NovelSubscriber subscriber) {
        if(std::find(
                _updateSubscribers.begin(),
                _updateSubscribers.end(),
                subscriber) != _updateSubscribers.end()) {
            _updateSubscribers.erase(std::remove_if(
                    _updateSubscribers.begin(),
                    _updateSubscribers.end(),
                    [subscriber](void (*existingSubscriber)(const float)) {
                        return subscriber == existingSubscriber;
                    }));
        }
        else {
            return;
        }
    }

    void NovelRunner::executeUpdateSubscriptions(const float deltaTime) const {
        for(const auto& subscriber : _updateSubscribers) {
            subscriber(deltaTime);
        }
    }
}