// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INPUT_INTERACTIONOBJECT_H
#define NOVELRT_INPUT_INTERACTIONOBJECT_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Input {
  class InteractionObject : public WorldObject {
    friend class InteractionService;

  public:
    Utilities::Event<> Interacted;

  private:
    KeyCode _subscribedKey = KeyCode::LeftMouseButton;
    std::function<void(InteractionObject*)> _notifyHasBeenDrawnObject;

  public:
    InteractionObject(const Transform& transform, int layer, const std::function<void(InteractionObject*)> notifyHasBeenDrawnObject);

    void executeObjectBehaviour() final;
    virtual bool validateInteractionPerimeter(const Maths::GeoVector2<float>& mousePosition) const = 0;

    inline const KeyCode& subscribedKey() const noexcept {
      return _subscribedKey;
    }

    inline KeyCode& subscribedKey() noexcept {
      return _subscribedKey;
    }
  };
}

#endif //!NOVELRT_INPUT_INTERACTIONOBJECT_H
