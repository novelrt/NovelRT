// Copyright © Matt Jones and Contributors. Licensed under the MIT LICENCE.md (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELOBJECTSORTCOMPARISON_H
#define NOVELRT_NOVELOBJECTSORTCOMPARISON_H

#include "NovelWorldObject.h"
namespace NovelRT {
struct NovelObjectSortComparison {
public:
  inline bool operator()(NovelWorldObject* lhs, NovelWorldObject* rhs) const {
    return lhs->getOrderInLayer() < rhs->getOrderInLayer();
  }
};
}
#endif //NOVELRT_NOVELOBJECTSORTCOMPARISON_H
