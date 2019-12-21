// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INPUT_INTERACTIONSERVICE_H
#define NOVELRT_INPUT_INTERACTIONSERVICE_H
#include "NovelInteractionObject.h"
#include "KeyCode.h"
#include "NovelBasicInteractionRect.h"
#include "NovelUtilities.h"
#include "KeyState.h"

namespace NovelRT::Input {
  class InteractionService {
    friend class InteractionObject;

    NOVELRT_PARAMETERLESS_EVENT(Quit)

  private:
    void HandleInteractionDraw(InteractionObject* target);
    InteractionObject* _clickTarget;
    std::map<KeyCode, KeyState> _keyStates;
    std::map<KeyCode, GeoVector<float>> _mousePositionsOnScreenPerButton;
    NovelLayeringService* const _layeringService;
    GeoVector<float> _screenSize;

  public:
    InteractionService(NovelLayeringService* const layeringService);

    void consumePlayerInput();

    BasicInteractionRect* getBasicInteractionRect(const GeoVector<float>& startingSize, const CommonArgs& args);

    void ExecuteClickedInteractable();

    inline void setScreenSize(const GeoVector<float>& value) {
      _screenSize = value;
    }
  };
}

#endif //NOVELRT_INPUT_INTERACTIONSERVICE_H
