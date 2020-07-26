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

  private:
    void HandleInteractionDraw(InteractionObject* target);
    InteractionObject* _clickTarget;
    std::map<KeyCode, KeyState> _keyStates;
    std::map<KeyCode, Maths::GeoVector2<float>> _mousePositionsOnScreenPerButton;
    Maths::GeoVector2<float> _screenSize;
    LoggingService _logger;
    void validateIfKeyCached(KeyCode code);
    void processKeyState(KeyCode code, KeyState state);
    void processMouseStates();
    void acceptMouseButtonClickPush(int button, int action, const Maths::GeoVector2<float>& mousePosition);
    void acceptKeyboardInputBindingPush(int key, int action);

  public:
    InteractionService(std::shared_ptr<Windowing::WindowingService> windowingService) noexcept;

    void consumePlayerInput();

    std::unique_ptr<BasicInteractionRect> createBasicInteractionRect(const Transform& transform, int layer);

    void executeClickedInteractable();

    inline void setScreenSize(const Maths::GeoVector2<float>& value) noexcept {
      _screenSize = value;
    }

    inline KeyState getKeyState(KeyCode value) const noexcept {
      auto it = _keyStates.find(value);
      if (it != _keyStates.end()) {
        return it->second;
      }

      return KeyState::Idle;
    }
  };
}

#endif //NOVELRT_INPUT_INTERACTIONSERVICE_H
