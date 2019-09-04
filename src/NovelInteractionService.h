//
// Created by matth on 22/02/2019.
//

#ifndef NOVELRT_NOVELINTERACTIONSERVICE_H
#define NOVELRT_NOVELINTERACTIONSERVICE_H
#include "NovelInteractionObject.h"
#include "KeyCode.h"
#include "NovelBasicInteractionRect.h"

namespace NovelRT {
class NovelInteractionService { friend class NovelInteractionObject;
NOVELRT_PARAMETERLESS_EVENT(Quit)
public:
  NovelInteractionService(NovelLayeringService* layeringService, const float screenScale);

  void consumePlayerInput();

  NovelBasicInteractionRect* getBasicInteractionRect(const GeoVector<float>& startingSize,
                                                     const NovelCommonArgs& args);
  void executeClickedInteractable();

  //NovelInteractionObject getInteractionRect(const NovelCommonArgs& args);
private:
  void handleInteractionDraw(NovelInteractionObject* target);
  NovelInteractionObject* _clickTarget;
  std::map<KeyCode, bool> _keyStates;
  std::map<KeyCode, GeoVector<float>> _mousePositionsOnScreenPerButton;
  NovelLayeringService* _layeringService;
  float _screenScale;
};
}

#endif //NOVELRT_NOVELINTERACTIONSERVICE_H
