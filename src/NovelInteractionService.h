// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELINPUTSERVICE_H
#define NOVELRT_NOVELINPUTSERVICE_H
#include "NovelInteractionObject.h"
#include "KeyCode.h"
#include "NovelBasicInteractionRect.h"
#include "NovelUtilities.h"
#include "KeyState.h"

namespace NovelRT {
  class NovelInteractionService {
    friend class NovelInteractionObject;

    NOVELRT_PARAMETERLESS_EVENT(Quit)

  private:
    void HandleInteractionDraw(NovelInteractionObject* target);
    NovelInteractionObject* _clickTarget;
    std::map<KeyCode, KeyState> _keyStates;
    std::map<KeyCode, GeoVector<float>> _mousePositionsOnScreenPerButton;
    NovelLayeringService* const _layeringService;
    GeoVector<float> _screenSize;

  public:
    NovelInteractionService(NovelLayeringService* const layeringService);

    void consumePlayerInput();

    NovelBasicInteractionRect* getBasicInteractionRect(const GeoVector<float>& startingSize, const NovelCommonArgs& args);

    void ExecuteClickedInteractable();

    inline void setScreenSize(const GeoVector<float>& value) {
      _screenSize = value;
    }
  };
}

#endif //NOVELRT_NOVELINPUTSERVICE_H
