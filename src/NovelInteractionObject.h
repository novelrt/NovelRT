// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELINTERACTIONOBJECT_H
#define NOVELRT_NOVELINTERACTIONOBJECT_H
#include <algorithm>
#include <functional>
#include "NovelObject.h"
#include "KeyCode.h"
#include "NovelRTMacroUtilities.h"

namespace NovelRT {
class NovelInteractionObject : public NovelObject {
  friend class NovelInteractionService; //how to make shit tightly coupled oh god

NOVELRT_PARAMETERLESS_EVENT(Interacted)
public:
  NovelInteractionObject(NovelLayeringService* layeringService, float screenScale, const GeoVector<float>& size,
                         const NovelCommonArgs& args, const std::function<void(NovelInteractionObject*)> notifyHasBeenDrawnObject);
  void executeObjectBehaviour() final;
  virtual bool validateInteractionPerimeter(const GeoVector<float>& mousePosition) const = 0;
  KeyCode getSubscribedKey() const;
  void setSubscribedKey(KeyCode key);

private:
  std::function<void(NovelInteractionObject*)> _notifyHasBeenDrawnObject;
  KeyCode _subscribedKey = LeftMouseButton;

};
}
#endif //NOVELRT_NOVELINTERACTIONOBJECT_H
