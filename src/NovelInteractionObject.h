// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELINTERACTIONOBJECT_H
#define NOVELRT_NOVELINTERACTIONOBJECT_H
#include <algorithm>
#include <functional>
#include "NovelWorldObject.h"
#include "KeyCode.h"
#include "NovelRTUtilities.h"

namespace NovelRT {
  class NovelInteractionObject : public NovelWorldObject {
    friend class NovelInteractionService; //how to make shit tightly coupled oh god

    NOVELRT_PARAMETERLESS_EVENT(Interacted)
  private:
    std::function<void(NovelInteractionObject*)> _notifyHasBeenDrawnObject;
    KeyCode _subscribedKey = KeyCode::LeftMouseButton;

  public:
    NovelInteractionObject(NovelLayeringService* layeringService,
      const NovelCommonArgs& args, const std::function<void(NovelInteractionObject*)> notifyHasBeenDrawnObject);
    void executeObjectBehaviour() final;
    virtual bool validateInteractionPerimeter(const GeoVector<float>& mousePosition) const = 0;
    KeyCode getSubscribedKey() const;
    void setSubscribedKey(const KeyCode key);

  };
}
#endif //NOVELRT_NOVELINTERACTIONOBJECT_H
