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

  NOVELRT_PARAMETERLESS_EVENT(SceneConstructionRequested)

  private:
    int _exitCode;
    Utilities::Lazy<Timing::StepTimer> _stepTimer;
    std::vector<NovelUpdateSubscriber> _updateSubscribers;
    std::unique_ptr<DebugService> _novelDebugService;
    std::unique_ptr<Input::InteractionService> _novelInteractionService;
    std::unique_ptr<Audio::AudioService> _novelAudioService;
    std::unique_ptr<DotNet::RuntimeService> _novelDotNetRuntimeService;
    std::unique_ptr<Windowing::WindowingService> _novelWindowingService;
    std::unique_ptr<Graphics::RenderingService> _novelRenderer;
    LoggingService _loggingService;


  public:
    /**
     * Executes the provided code upon update.
     *
     * @param subscriber The code to execute on update.
     */
    void runOnUpdate(NovelUpdateSubscriber);
    /**
     * Stops the execution of the instantiated NovelRunner at the specified event.
     *
     * @param subscriber The event at which the novel should stop running.
     */
    void stopRunningOnUpdate(NovelUpdateSubscriber);

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
    Graphics::RenderingService* getRenderer() const;
    /// The Interaction Service associated with this Runner
    Input::InteractionService* getInteractionService() const;
    /// The Debug Service associated with this Runner.
    DebugService* getDebugService() const;
    Audio::AudioService* getAudioService() const;
    DotNet::RuntimeService* getDotNetRuntimeService() const;
    Windowing::WindowingService* getWindowingService() const;

    ~NovelRunner();
  };
}

#endif //NOVELRT_NOVELRUNNER_H
