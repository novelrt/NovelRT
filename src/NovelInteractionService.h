//
// Created by matth on 22/02/2019.
//

#ifndef NOVELRT_NOVELINPUTSERVICE_H
#define NOVELRT_NOVELINPUTSERVICE_H
#include "NovelInteractionObject.h"
#include "../lib/SDL2/include/SDL_types.h"
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
  void ExecuteClickedInteractable();

  //NovelInteractionObject getInteractionRect(const NovelCommonArgs& args);
private:
  void HandleInteractionDraw(NovelInteractionObject* target);
  NovelInteractionObject* _clickTarget;
  std::map<KeyCode, bool> _keyStates;
  std::map<KeyCode, GeoVector<float>> _mousePositionsOnScreenPerButton;
  NovelLayeringService* _layeringService;
  float _screenScale;
};
}

#endif //NOVELRT_NOVELINPUTSERVICE_H
