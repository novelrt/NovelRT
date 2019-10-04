// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELOBJECTSORTCOMPARISON_H
#define NOVELRT_NOVELOBJECTSORTCOMPARISON_H

#include "NovelObject.h"
namespace NovelRT {
struct NovelObjectSortComparison {
public:
  inline bool operator()(NovelObject* lhs, NovelObject* rhs) const {
    return lhs->getOrderInLayer() < rhs->getOrderInLayer();
  }
};
}
#endif //NOVELRT_NOVELOBJECTSORTCOMPARISON_H
