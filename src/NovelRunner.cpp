// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <iostream>
#include <NovelRT.h>
#include <SDL2/SDL.h>

namespace NovelRT {
  NovelRunner::NovelRunner(int displayNumber, const std::string& windowTitle, uint32_t targetFrameRate)
    : _stepTimer(Timing::StepTimer(targetFrameRate)),
    _layeringService(std::make_unique<LayeringService>()),
    _novelDebugService(std::make_unique<DebugService>(this)),
    _novelInteractionService(std::make_unique<Input::InteractionService>(_layeringService.get())),
    _novelAudioService(std::make_unique<Audio::AudioService>()),
    _novelWindowingService(std::make_unique<WindowingService>()),
    _novelRenderer(std::make_unique<RenderingService>(_layeringService.get(), _novelWindowingService.get())) {
    _novelWindowingService->initialiseWindow(displayNumber, windowTitle);
    _novelRenderer->initialiseRendering();
    _novelInteractionService->setScreenSize(_novelWindowingService->getWindowSize());
    _novelInteractionService->subscribeToQuit([this] { _exitCode = 0; });
  }

  int NovelRunner::runNovel() {
    uint32_t lastFramesPerSecond = 0;

    while (_exitCode) {
      _stepTimer.tick(_updateSubscribers);
      _novelDebugService->setFramesPerSecond(_stepTimer.getFramesPerSecond());
      _novelInteractionService->consumePlayerInput();
      _novelRenderer->beginFrame();
      _layeringService->executeAllObjectBehaviours();
      _novelRenderer->endFrame();
      _novelInteractionService->ExecuteClickedInteractable();
    }

    _novelRenderer->tearDown();
    _novelAudioService->~AudioService();
    return _exitCode;
  }

  RenderingService* NovelRunner::getRenderer() const {
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
    }
    else {
      return;
    }
  }

  InteractionService* NovelRunner::getInteractionService() const {
    return _novelInteractionService.get();
  }

  DebugService* NovelRunner::getDebugService() const {
    return _novelDebugService.get();
  }

  AudioService* NovelRunner::getAudioService() const {
    return _novelAudioService.get();
  }
}
