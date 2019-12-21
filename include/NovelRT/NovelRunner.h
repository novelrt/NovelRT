// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELRUNNER_H
#define NOVELRT_NOVELRUNNER_H

#include <string>

#include "NovelDebugService.h"
#include "Graphics/NovelRenderingService.h"
#include "Input/NovelInteractionService.h"
#include "Timing/NovelStepTimer.h"
#include "Audio/NovelAudioService.h"

namespace NovelRT {
/**
 * The base class for creating a visual novel.
 */
  class NovelRunner {
  private:
    StepTimer _stepTimer;
    std::vector<NovelUpdateSubscriber> _updateSubscribers;
    std::unique_ptr<LayeringService> _layeringService;
    std::unique_ptr<DebugService> _novelDebugService;
    std::unique_ptr<NovelInteractionService> _novelInteractionService;
    std::unique_ptr<AudioService> _novelAudioService;
    std::unique_ptr<WindowingService> _novelWindowingService;
    std::unique_ptr<NovelRenderingService> _novelRenderer;
    int _exitCode = 1;


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
    NovelRenderingService* getRenderer() const;
    /// The Interaction Service associated with this Runner
    NovelInteractionService* getInteractionService() const;
    /// The Debug Service associated with this Runner.
    DebugService* getDebugService() const;
    AudioService* getAudioService() const;
  };
}

#endif //NOVELRT_NOVELRUNNER_H
