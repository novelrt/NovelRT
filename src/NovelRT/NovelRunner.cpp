// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT {
  NovelRunner::NovelRunner(int displayNumber, const std::string& windowTitle, uint32_t targetFrameRate) :
    SceneConstructionRequested(Utilities::Event<>()),
    Update(Utilities::Event<Timing::DeltaTimestamp>()),
    _exitCode(1),
    _stepTimer(Utilities::Lazy<std::unique_ptr<Timing::StepTimer>>(std::function<Timing::StepTimer*()>([targetFrameRate] {return new Timing::StepTimer(targetFrameRate); }))),
    _novelDebugService(std::make_shared<DebugService>(this)),
    _novelWindowingService(std::make_shared<Windowing::WindowingService>(this)),
    _novelInteractionService(std::make_shared<Input::InteractionService>(this)),
    _novelAudioService(std::make_shared<Audio::AudioService>()),
    _novelDotNetRuntimeService(std::make_shared<DotNet::RuntimeService>()),
    _novelRenderer(std::make_shared<Graphics::RenderingService>(this)) {
    if (!glfwInit()) {
      const char* err = "";
      glfwGetError(&err);
       _loggingService.logError("GLFW ERROR: ", err);
      throw std::runtime_error("Unable to continue! Cannot start without a glfw window.");
    }
    _novelWindowingService->initialiseWindow(displayNumber, windowTitle);
    _novelRenderer->initialiseRendering();
    _novelInteractionService->setScreenSize(_novelWindowingService->getWindowSize());
    _novelWindowingService->WindowTornDown += [this] { _exitCode = 0; };
  }

  int NovelRunner::runNovel() {
    while (_exitCode) {
      _stepTimer.getActual()->tick(Update);
      _novelDebugService->setFramesPerSecond(_stepTimer.getActual()->getFramesPerSecond());
      _novelRenderer->beginFrame();
      SceneConstructionRequested();
      _novelRenderer->endFrame();
      _novelInteractionService->consumePlayerInput();
      _novelInteractionService->executeClickedInteractable();
      _novelAudioService->checkSources();
    }

    _novelWindowingService->tearDown();
    return _exitCode;
  }

  std::weak_ptr<Graphics::RenderingService> NovelRunner::getRenderer() const {
    return std::weak_ptr<Graphics::RenderingService>(_novelRenderer);
  }

  std::weak_ptr<Input::InteractionService> NovelRunner::getInteractionService() const {
    return std::weak_ptr<Input::InteractionService>(_novelInteractionService);
  }

  std::weak_ptr<DebugService> NovelRunner::getDebugService() const {
    return std::weak_ptr<DebugService>(_novelDebugService);
  }

  std::weak_ptr<Audio::AudioService> NovelRunner::getAudioService() const {
    return std::weak_ptr<Audio::AudioService>(_novelAudioService);
  }

  std::weak_ptr<DotNet::RuntimeService> NovelRunner::getDotNetRuntimeService() const {
    return std::weak_ptr<DotNet::RuntimeService>(_novelDotNetRuntimeService);
  }

  std::weak_ptr<Windowing::WindowingService> NovelRunner::getWindowingService() const {
    return std::weak_ptr<Windowing::WindowingService>(_novelWindowingService);
  }

  NovelRunner::~NovelRunner() {
    glfwTerminate();
  }
}
