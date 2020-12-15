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
    static inline const uint32_t INPUT_BUFFER_COUNT = 2;

    uint32_t _previousBufferIndex;
    uint32_t _currentBufferIndex;
    void HandleInteractionDraw(InteractionObject* target);
    InteractionObject* _clickTarget;
    std::array<std::map<KeyCode, KeyStateFrameChangeLog>, INPUT_BUFFER_COUNT> _keyStates;
    Maths::GeoVector2F _screenSize;
    Maths::GeoVector2F _cursorPosition;
    LoggingService _logger;
    void processKeyState(KeyCode code, KeyState state);
    void processKeyStates();
    void acceptMouseButtonClickPush(int32_t button, int32_t action, Maths::GeoVector2F mousePosition);
    void acceptKeyboardInputBindingPush(int32_t key, int32_t action);

  public:
    InteractionService(std::shared_ptr<Windowing::WindowingService> windowingService) noexcept;

    void consumePlayerInput();

    std::unique_ptr<BasicInteractionRect> createBasicInteractionRect(Transform transform, int32_t layer);

    void executeClickedInteractable();

    inline void setScreenSize(Maths::GeoVector2F value) noexcept {
      _screenSize = value;
    }

    inline KeyStateFrameChangeLog getKeyState(KeyCode value) const noexcept {
      auto& currentBuffer = _keyStates.at(_currentBufferIndex);
      auto it = currentBuffer.find(value);
      if (it != currentBuffer.end()) {
        return it->second;
      }

      return KeyStateFrameChangeLog{};
    }
  };
}

#endif //NOVELRT_INPUT_INTERACTIONSERVICE_H
