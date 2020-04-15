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
    /**
     * This event is used for constructing the rendered scene. This is called once per frame update.
     */
    Utilities::Event<> SceneConstructionRequested;
    /**
     * An event that occurs on a frame update, with the delta Timestamp between the last frame update and the new one. <br/>
     * Use this to define game behaviour that is required to be done per-frame.
     */
    Utilities::Event<Timing::Timestamp> Update;

  private:
    int _exitCode;
    Utilities::Lazy<std::unique_ptr<Timing::StepTimer>> _stepTimer;
    std::shared_ptr<DebugService> _novelDebugService;
    std::shared_ptr<Windowing::WindowingService> _novelWindowingService;
    std::shared_ptr<Input::InteractionService> _novelInteractionService;
    std::shared_ptr<Audio::AudioService> _novelAudioService;
    std::shared_ptr<DotNet::RuntimeService> _novelDotNetRuntimeService;
    std::shared_ptr<Graphics::RenderingService> _novelRenderer;
    LoggingService _loggingService;

  public:
    /**
     * Instantiates the NovelRunner class with its presets.
     *
     * @param displayNumber The display on which to start the novel.
     * @param windowTitle The title of the window created for NovelRunner.
     * @param targetFrameRate The framerate that should be targeted and capped.
     */
    explicit NovelRunner(int displayNumber, const std::string& windowTitle = "NovelRTTest", uint32_t targetFrameRate = 0);
    /**
     * Launches the NovelRT game loop. This method will block until the game terminates.
     * @returns Exit code.
     */
    int runNovel();

    /// Gets the Rendering Service associated with this Runner.
    std::weak_ptr<Graphics::RenderingService> getRenderer() const;
    /// Gets the Interaction Service associated with this Runner
    std::weak_ptr<Input::InteractionService> getInteractionService() const;
    /// Gets the Debug Service associated with this Runner.
    std::weak_ptr<DebugService> getDebugService() const;
    /// Gets the Audio Service associated with this Runner.
    std::weak_ptr<Audio::AudioService> getAudioService() const;
    /// Gets the .NET Runtime Service associated with this Runner.
    std::weak_ptr<DotNet::RuntimeService> getDotNetRuntimeService() const;
    /// Gets the Windowing Service associated with this Runner.
    std::weak_ptr<Windowing::WindowingService> getWindowingService() const;

    /**
     * Terminates the game.
     */
    ~NovelRunner();
  };
}

#endif //NOVELRT_NOVELRUNNER_H
