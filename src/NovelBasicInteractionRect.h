//
// Created by matth on 01/03/2019.
//

#ifndef NOVELRT_NOVELBASICINTERACTIONRECT_H
#define NOVELRT_NOVELBASICINTERACTIONRECT_H
#include "NovelInteractionObject.h"
namespace NovelRT {
class NovelBasicInteractionRect : public NovelInteractionObject {
public:
  void checkInteractionPerimeter() const final;

};
}
#endif //NOVELRT_NOVELBASICINTERACTIONRECT_H
