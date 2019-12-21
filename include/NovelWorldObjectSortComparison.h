// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELWORLDOBJECTSORTCOMPARISON_H
#define NOVELRT_NOVELWORLDOBJECTSORTCOMPARISON_H

#include "NovelWorldObject.h"
namespace NovelRT {
  struct NovelWorldObjectSortComparison {

  public:
    inline bool operator()(NovelWorldObject* lhs, NovelWorldObject* rhs) const {
      return lhs->getOrderInLayer() < rhs->getOrderInLayer();
    }
  };
}
#endif //NOVELRT_NOVELWORLDOBJECTSORTCOMPARISON_H
