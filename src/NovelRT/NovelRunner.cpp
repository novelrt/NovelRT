// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT {
  NovelRunner::NovelRunner(int displayNumber, const std::string& windowTitle, uint32_t targetFrameRate) :
    _exitCode(1),
    _stepTimer(Utilities::Lazy<std::unique_ptr<Timing::StepTimer>>(std::function<Timing::StepTimer*()>([targetFrameRate] {return new Timing::StepTimer(targetFrameRate); }))),
    _novelWindowingService(std::make_unique<Windowing::WindowingService>(this)),
    _novelDebugService(std::make_unique<Debug::DebugService>(this)),
    _novelInteractionService(std::make_unique<Input::InteractionService>(this)),
    _novelAudioService(std::make_unique<Audio::AudioService>()),
    _novelDotNetRuntimeService(std::make_unique<DotNet::RuntimeService>()),
    _novelRenderer(std::make_unique<Graphics::RenderingService>(this)) {
    if (!glfwInit()) {
      const char* err = "";
      glfwGetError(&err);
       _loggingService.logError("GLFW ERROR: ", err);
      throw std::runtime_error("Unable to continue! Cannot start without a glfw window.");
    }
    _novelWindowingService->initialiseWindow(displayNumber, windowTitle);
    _novelRenderer->initialiseRendering();
    _novelInteractionService->setScreenSize(_novelWindowingService->getWindowSize());
    _novelWindowingService->subscribeToWindowTornDown([this] { _exitCode = 0; });
  }

  int NovelRunner::runNovel() {
    uint32_t lastFramesPerSecond = 0;

    while (_exitCode) {
      _stepTimer.getActual()->tick(_updateSubscribers);
      _novelDebugService->setFramesPerSecond(_stepTimer.getActual()->getFramesPerSecond());
      _novelRenderer->beginFrame();
      raiseSceneConstructionRequested();
      _novelRenderer->endFrame();
      _novelInteractionService->consumePlayerInput();
      _novelInteractionService->executeClickedInteractable();
      _novelAudioService->checkSources();
    }

    _novelWindowingService->tearDown();
    return _exitCode;
  }

  Graphics::RenderingService* NovelRunner::getRenderer() const {
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

  Input::InteractionService* NovelRunner::getInteractionService() const {
    return _novelInteractionService.get();
  }

  Debug::DebugService* NovelRunner::getDebugService() const {
    return _novelDebugService.get();
  }

  Audio::AudioService* NovelRunner::getAudioService() const {
    return _novelAudioService.get();
  }

  DotNet::RuntimeService* NovelRunner::getDotNetRuntimeService() const {
    return _novelDotNetRuntimeService.get();
  }

  Windowing::WindowingService* NovelRunner::getWindowingService() const {
	  return _novelWindowingService.get();
  }

  NovelRunner::~NovelRunner() {
    glfwTerminate();
  }
}
