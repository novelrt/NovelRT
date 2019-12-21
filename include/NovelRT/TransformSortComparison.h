// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELWORLDOBJECTSORTCOMPARISON_H
#define NOVELRT_NOVELWORLDOBJECTSORTCOMPARISON_H

#include "Transform.h"
namespace NovelRT {
  struct TransformSortComparison {

  public:
    inline bool operator()(Transform* lhs, Transform* rhs) const {
      return lhs->getOrderInLayer() < rhs->getOrderInLayer();
    }
  };
}
#endif //NOVELRT_NOVELWORLDOBJECTSORTCOMPARISON_H
