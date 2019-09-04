//
// Created by matth on 16/02/2019.
//

#include <iostream>
#include "NovelRunner.h"
#include <SDL2/SDL.h>

namespace NovelRT {
NovelRunner::NovelRunner(int displayNumber, NovelLayeringService* layeringService)
    : _layeringService(layeringService), _novelRenderer(std::make_unique<NovelRenderingService>(_layeringService)) {
  _novelRenderer->initialiseRendering(displayNumber);
  _novelInteractionService = std::make_unique<NovelInteractionService>(_layeringService, _novelRenderer->getScreenScale());
  _novelInteractionService->subscribeToQuit([this]{_exitCode = 0;});
}

int NovelRunner::runNovel() {
  Uint64 current = SDL_GetPerformanceCounter();
  Uint64 previous = 0;
  float deltaTime = 0;
  while (_exitCode) {
    previous = current;
    current = SDL_GetPerformanceCounter();
    deltaTime = ((current - previous) * 1000 / SDL_GetPerformanceFrequency()) * 0.001f;
    executeUpdateSubscriptions(deltaTime);
    _novelInteractionService->consumePlayerInput();
    _novelRenderer->beginFrame();
    _layeringService->executeAllObjectBehaviours();
    _novelRenderer->endFrame();
    _novelInteractionService->executeClickedInteractable();

  }
  _novelRenderer->tearDown();
  return _exitCode;
}

NovelRenderingService* NovelRunner::getRenderer() const {
  return _novelRenderer.get();
}

void NovelRunner::runOnUpdate(NovelSubscriber subscriber) {
  _updateSubscribers.push_back(subscriber);
}

void NovelRunner::stopRunningOnUpdate(NovelSubscriber subscriber) {
  if (std::find(
      _updateSubscribers.begin(),
      _updateSubscribers.end(),
      subscriber) != _updateSubscribers.end()) {
    _updateSubscribers.erase(std::remove_if(
        _updateSubscribers.begin(),
        _updateSubscribers.end(),
        [subscriber](void (* existingSubscriber)(const float)) {
          return subscriber == existingSubscriber;
        }));
  } else {
    return;
  }
}

void NovelRunner::executeUpdateSubscriptions(const float deltaTime) const {
  for (const auto& subscriber : _updateSubscribers) {
    subscriber(deltaTime);
  }
}
NovelInteractionService* NovelRunner::getInteractionService() const {
  return _novelInteractionService.get();
}
}