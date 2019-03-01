//
// Created by matth on 16/02/2019.
//

#ifndef NOVELRT_NOVELRUNNER_H
#define NOVELRT_NOVELRUNNER_H

#include "NovelRenderingService.h"

typedef void (* NovelSubscriber)(const float);

namespace NovelRT {
class NovelRunner {
public:
  void runOnUpdate(NovelSubscriber);
  void stopRunningOnUpdate(NovelSubscriber);
  void executeUpdateSubscriptions(const float deltaTime) const;

  explicit NovelRunner(int, NovelLayeringService*);
  int runNovel() const;
  NovelRenderingService* getRenderer() const;

private:
  std::vector<NovelSubscriber> _updateSubscribers;
  NovelLayeringService* _layeringService;
  std::unique_ptr<NovelRenderingService> _novelRenderer;
};
}

#endif //NOVELRT_NOVELRUNNER_H
