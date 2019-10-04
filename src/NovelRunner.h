// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELRUNNER_H
#define NOVELRT_NOVELRUNNER_H

#include "NovelDebugService.h"
#include "NovelRenderingService.h"
#include "NovelInteractionService.h"
#include "NovelStepTimer.h"

namespace NovelRT {
class NovelRunner {
public:
  void runOnUpdate(NovelUpdateSubscriber);
  void stopRunningOnUpdate(NovelUpdateSubscriber);

  explicit NovelRunner(int, NovelLayeringService*, uint32_t targetFrameRate = 0);
  int runNovel();
  NovelRenderingService* getRenderer() const;
  NovelInteractionService* getInteractionService() const;
  NovelDebugService* getDebugService() const;

private:
  StepTimer _stepTimer;
  std::vector<NovelUpdateSubscriber> _updateSubscribers;
  NovelLayeringService* _layeringService;
  std::unique_ptr<NovelDebugService> _novelDebugService;
  std::unique_ptr<NovelRenderingService> _novelRenderer;
  std::unique_ptr<NovelInteractionService> _novelInteractionService;
  int _exitCode = 1;
};
}

#endif //NOVELRT_NOVELRUNNER_H
