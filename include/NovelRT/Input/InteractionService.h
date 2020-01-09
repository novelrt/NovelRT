// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INPUT_INTERACTIONSERVICE_H
#define NOVELRT_INPUT_INTERACTIONSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Input {
  class InteractionService {
    friend class InteractionObject;
    friend class Windowing::WindowingService; //I get this looks weird but its because GLFW treats the window as this system as well as the window.

    NOVELRT_PARAMETERLESS_EVENT(Quit)

  private:
    NovelRunner* const _runner;

    void HandleInteractionDraw(InteractionObject* target);
    InteractionObject* _clickTarget;
    std::map<KeyCode, KeyState> _keyStates;
    std::map<KeyCode, Maths::GeoVector<float>> _mousePositionsOnScreenPerButton;
    Maths::GeoVector<float> _screenSize;
    LoggingService _logger;

  public:
    InteractionService(NovelRunner* const runner);

    void consumePlayerInput();

    std::unique_ptr<BasicInteractionRect> createBasicInteractionRect(const Transform& transform, int layer);

    void executeClickedInteractable();

    inline void setScreenSize(const Maths::GeoVector<float>& value) {
      _screenSize = value;
    }
  };
}

#endif //NOVELRT_INPUT_INTERACTIONSERVICE_H
