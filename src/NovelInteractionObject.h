//
// Created by matth on 25/03/2019.
//

#ifndef NOVELRT_NOVELINTERACTIONOBJECT_H
#define NOVELRT_NOVELINTERACTIONOBJECT_H

#include "NovelObject.h"

namespace NovelRT {
class NovelInteractionService;
class NovelInteractionObject : NovelObject {
public:
  virtual void checkInteractionPerimeter() const = 0;
  void executeObjectBehaviour() const final;

private:
  void setLastDrawn(const NovelInteractionObject* target) const;
  NovelInteractionService* _interactionService;
};
}
#endif //NOVELRT_NOVELINTERACTIONOBJECT_H
