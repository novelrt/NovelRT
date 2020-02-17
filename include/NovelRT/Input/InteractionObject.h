// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INPUT_INTERACTIONOBJECT_H
#define NOVELRT_INPUT_INTERACTIONOBJECT_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Input {
  class InteractionObject : public WorldObject {
    friend class InteractionService;

  private:
    KeyCode _subscribedKey = KeyCode::LeftMouseButton;
    std::function<void(InteractionObject*)> _notifyHasBeenDrawnObject;

  public:
    InteractionObject(const Transform& transform, int layer, const std::function<void(InteractionObject*)> notifyHasBeenDrawnObject);

    Utilities::Event<> Interacted;

    void executeObjectBehaviour() final;
    virtual bool validateInteractionPerimeter(const Maths::GeoVector<float>& mousePosition) const = 0;
    KeyCode getSubscribedKey() const;
    void setSubscribedKey(KeyCode key);
  };
}

#endif //NOVELRT_INPUT_INTERACTIONOBJECT_H
