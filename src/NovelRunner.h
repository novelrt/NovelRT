// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELRUNNER_H
#define NOVELRT_NOVELRUNNER_H

#include "NovelDebugService.h"
#include "NovelRenderingService.h"
#include "NovelInteractionService.h"
#include "NovelStepTimer.h"
#include "NovelAudioService.h"

namespace NovelRT {
  /**
   * The base class for creating a visual novel.
   */
  class NovelRunner {

  private:
    StepTimer _stepTimer;
    std::vector<NovelUpdateSubscriber> _updateSubscribers;
    NovelLayeringService* _layeringService;
    std::unique_ptr<NovelDebugService> _novelDebugService;
    std::unique_ptr<NovelRenderingService> _novelRenderer;
    std::unique_ptr<NovelInteractionService> _novelInteractionService;
    std::unique_ptr<NovelAudioService> _novelAudioService;
    int _exitCode = 1;

  public:
    /**
     * Instantiates the NovelRunner class with its presets.
     *
     * @param displayNumber The display on which to start the novel.
     * @param layeringService The NovelLayeringService that NovelRunner should use.
     * @param targetFrameRate The framerate that should be targeted and capped.
     */
    explicit NovelRunner(int, NovelLayeringService*, uint32_t targetFrameRate = 0);

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
     * Starts the visual novel.
     * @returns Exit code.
     */
    int runNovel();
    /// The Rendering Service associated with this Runner.
    NovelRenderingService* getRenderer() const;
    /// The Interaction Service associated with this Runner
    NovelInteractionService* getInteractionService() const;
    /// The Debug Service associated with this Runner.
    NovelDebugService* getDebugService() const;
    NovelAudioService* getAudioService() const;
  };
}

#endif //NOVELRT_NOVELRUNNER_H
