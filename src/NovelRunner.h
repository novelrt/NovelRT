//
// Created by matth on 16/02/2019.
//

#ifndef NOVELRT_NOVELRUNNER_H
#define NOVELRT_NOVELRUNNER_H

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

private:
  StepTimer _stepTimer;
  std::vector<NovelUpdateSubscriber> _updateSubscribers;
  NovelLayeringService* _layeringService;
  std::unique_ptr<NovelRenderingService> _novelRenderer;
  std::unique_ptr<NovelInteractionService> _novelInteractionService;
  int _exitCode = 1;
};
}

#endif //NOVELRT_NOVELRUNNER_H
