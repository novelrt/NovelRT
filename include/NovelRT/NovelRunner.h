// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NOVELRUNNER_H
#define NOVELRT_NOVELRUNNER_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT
{
    /**
     * @brief The base class for creating a visual novel.
     */
    class NovelRunner
    {

    public:
        /**
         * @brief This event is used for constructing the rendered scene. This is called once per frame update.
         */
        Utilities::Event<> SceneConstructionRequested;
        /**
         * @brief An event that occurs on a frame update, with the delta Timestamp between the last frame update and the
         * new one. <br/> Use this to define game behaviour that is required to be done per-frame.
         */
        Utilities::Event<Timing::Timestamp> Update;

    private:
        int32_t _exitCode;
        Utilities::Lazy<std::unique_ptr<Timing::StepTimer>> _stepTimer;
        std::shared_ptr<Windowing::WindowingService> _novelWindowingService;
        std::shared_ptr<Input::InteractionService> _novelInteractionService;
        std::shared_ptr<Audio::AudioService> _novelAudioService;
        std::shared_ptr<DotNet::RuntimeService> _novelDotNetRuntimeService;
        std::shared_ptr<Graphics::RenderingService> _novelRenderer;
        std::shared_ptr<DebugService> _novelDebugService;
        LoggingService _loggingService;

    public:
        /**
         * @brief Instantiates the NovelRunner class with its presets.
         *
         * @param displayNumber The display on which to start the novel.
         * @param windowTitle The title of the window created for NovelRunner.
         * @param targetFrameRate The framerate that should be targeted and capped.
         */
        explicit NovelRunner(int32_t displayNumber,
                             const std::string& windowTitle = "NovelRTTest",
                             uint32_t targetFrameRate = 0,
                             bool transparency = false);
        /**
         * @brief Launches the NovelRT game loop. This method will block until the game terminates.
         * @returns Exit code.
         */
        int32_t runNovel();

        /// @brief Gets the Rendering Service associated with this Runner.
        std::shared_ptr<Graphics::RenderingService> getRenderer() const;
        /// @brief Gets the Interaction Service associated with this Runner
        std::shared_ptr<Input::InteractionService> getInteractionService() const;
        /// @brief Gets the Debug Service associated with this Runner.
        std::shared_ptr<DebugService> getDebugService() const;
        /// @brief Gets the Audio Service associated with this Runner.
        std::shared_ptr<Audio::AudioService> getAudioService() const;
        /// @brief Gets the .NET Runtime Service associated with this Runner.
        std::shared_ptr<DotNet::RuntimeService> getDotNetRuntimeService() const;
        /// @brief Gets the Windowing Service associated with this Runner.
        std::shared_ptr<Windowing::WindowingService> getWindowingService() const;

        /**
         * @brief Terminates the game.
         */
        ~NovelRunner();
    };
} // namespace NovelRT

#endif // NOVELRT_NOVELRUNNER_H
