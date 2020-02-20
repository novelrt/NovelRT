// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELRUNNER_H
#define NOVELRT_NOVELRUNNER_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT {
/**
 * The base class for creating a visual novel.
 */
  class NovelRunner {

  public:
    Utilities::Event<> SceneConstructionRequested;
    Utilities::Event<double> Update;

  private:
    int _exitCode;
    Utilities::Lazy<std::unique_ptr<Timing::StepTimer>> _stepTimer;

    std::shared_ptr<DebugService> _novelDebugService;
    std::shared_ptr<Input::InteractionService> _novelInteractionService;
    std::shared_ptr<Audio::AudioService> _novelAudioService;
    std::shared_ptr<DotNet::RuntimeService> _novelDotNetRuntimeService;
    std::shared_ptr<Windowing::WindowingService> _novelWindowingService;
    std::shared_ptr<Graphics::RenderingService> _novelRenderer;
    LoggingService _loggingService;


  public:
    /**
     * Instantiates the NovelRunner class with its presets.
     *
     * @param displayNumber The display on which to start the novel.
     * @param layeringService The LayeringService that NovelRunner should use.
     * @param targetFrameRate The framerate that should be targeted and capped.
     */
    explicit NovelRunner(int displayNumber, const std::string& windowTitle = "NovelRTTest", uint32_t targetFrameRate = 0);
    /**
     * Starts the visual novel.
     * @returns Exit code.
     */

    int runNovel();
    /// The Rendering Service associated with this Runner.
    std::weak_ptr<Graphics::RenderingService> getRenderer() const;
    /// The Interaction Service associated with this Runner
    std::weak_ptr<Input::InteractionService> getInteractionService() const;
    /// The Debug Service associated with this Runner.
    std::weak_ptr<DebugService> getDebugService() const;
    std::weak_ptr<Audio::AudioService> getAudioService() const;
    std::weak_ptr<DotNet::RuntimeService> getDotNetRuntimeService() const;
    std::weak_ptr<Windowing::WindowingService> getWindowingService() const;

    ~NovelRunner();
  };
}

#endif //NOVELRT_NOVELRUNNER_H
