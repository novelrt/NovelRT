//
// Created by matth on 16/02/2019.
//

#include <iostream>
#include "NovelRunner.h"
#include <SDL2/SDL.h>

namespace NovelRT {
NovelRunner::NovelRunner(int displayNumber, NovelLayeringService* layeringService, uint32_t targetFrameRate)
    : _layeringService(layeringService), _novelRenderer(std::make_unique<NovelRenderingService>(_layeringService)), _stepTimer(targetFrameRate) {
  _novelRenderer->initialiseRendering(displayNumber);
  _novelInteractionService = std::make_unique<NovelInteractionService>(_layeringService, _novelRenderer->getScreenScale());
  _novelInteractionService->subscribeToQuit([this]{_exitCode = 0;});
}

int NovelRunner::runNovel() {
  uint32_t lastFramesPerSecond = 0;

  while (_exitCode) {
    _stepTimer.tick(_updateSubscribers);

    auto framesPerSecond = _stepTimer.getFramesPerSecond();

    if (framesPerSecond != lastFramesPerSecond) {
      std::cout << "\33[2K"; // Erase the current line
      std::cout << '\r';     // Move cursor to beginning of the line
      std::cout << framesPerSecond << " fps";
    }

    _novelInteractionService->consumePlayerInput();
    _novelRenderer->beginFrame();
    _layeringService->executeAllObjectBehaviours();
    _novelRenderer->endFrame();
    _novelInteractionService->ExecuteClickedInteractable();

  }
  _novelRenderer->tearDown();
  return _exitCode;
}

NovelRenderingService* NovelRunner::getRenderer() const {
  return _novelRenderer.get();
}

void NovelRunner::runOnUpdate(NovelUpdateSubscriber subscriber) {
  _updateSubscribers.push_back(subscriber);
}

void NovelRunner::stopRunningOnUpdate(NovelUpdateSubscriber subscriber) {
  if (std::find(
      _updateSubscribers.begin(),
      _updateSubscribers.end(),
      subscriber) != _updateSubscribers.end()) {
    _updateSubscribers.erase(std::remove_if(
        _updateSubscribers.begin(),
        _updateSubscribers.end(),
        [subscriber](NovelUpdateSubscriber existingSubscriber) {
          return subscriber == existingSubscriber;
        }));
  } else {
    return;
  }
}

NovelInteractionService* NovelRunner::getInteractionService() const {
  return _novelInteractionService.get();
}
}
