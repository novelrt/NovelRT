//
// Created by matth on 22/02/2019.
//

#ifndef NOVELRT_NOVELINPUTSERVICE_H
#define NOVELRT_NOVELINPUTSERVICE_H

#include "NovelInteractionObject.h"
namespace NovelRT {
class NovelInteractionService {
public:


  void initializeInputHandling();

  //NovelInteractionObject getInteractionRect(const NovelCommonArgs& args);

  void setLastInteractableDrawn(const NovelInteractionObject* target);
private:
  const NovelInteractionObject* _target;
};
}

#endif //NOVELRT_NOVELINPUTSERVICE_H
