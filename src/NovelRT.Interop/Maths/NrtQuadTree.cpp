// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Maths/NrtQuadTree.h"
#include "NovelRT.h"
#include <list>
#include <cmath>

std::list<std::shared_ptr<NovelRT::Maths::QuadTree>> _treeCollection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

   NrtQuadTree Nrt_QuadTree_create(NrtGeoBounds bounds) {
     _treeCollection.push_back(std::make_shared<Maths::QuadTree>(*reinterpret_cast<const Maths::GeoBounds*>(&bounds)));
     return reinterpret_cast<NrtQuadTree>(_treeCollection.back().get());
   }

  NrtResult Nrt_QuadTree_getParent(const NrtQuadTree tree, NrtQuadTree* outputParentTree) {
     if(tree == nullptr || outputParentTree == nullptr) {
       Nrt_setErrMsgIsNullptrInternal();
       return NRT_FAILURE_NULLPTR_PROVIDED;
     }

     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     auto parentTree = treePointer->getParent();
     *outputParentTree = reinterpret_cast<NrtQuadTree&>(parentTree);

     return NRT_SUCCESS;
   }

  NrtGeoBounds Nrt_QuadTree_getBounds(const NrtQuadTree tree) {
     Maths::GeoBounds bounds = Maths::GeoBounds({ 0,0 }, {0,0}, 0);
     bounds = reinterpret_cast<Maths::QuadTree*>(tree)->getBounds();
     return *reinterpret_cast<NrtGeoBounds*>(&bounds);
   }

  NrtResult Nrt_QuadTree_getPoint(const NrtQuadTree tree, size_t index, NrtQuadTreePoint* outputPoint) {
     if(tree == nullptr || outputPoint == nullptr) {
       Nrt_setErrMsgIsNullptrInternal();
       return NRT_FAILURE_NULLPTR_PROVIDED;
     }

     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     auto point = treePointer->getPoint(index).get();
     *outputPoint = reinterpret_cast<NrtQuadTreePoint&>(point);

     return NRT_SUCCESS;
   }

  size_t Nrt_QuadTree_getPointCount(const NrtQuadTree tree) {
     return reinterpret_cast<Maths::QuadTree*>(tree)->getPointCount();
   }

  NrtResult Nrt_QuadTree_getTopLeft(const NrtQuadTree tree, NrtQuadTree* outputCornerTree) {
     if(tree == nullptr || outputCornerTree == nullptr) {
       Nrt_setErrMsgIsNullptrInternal();
       return NRT_FAILURE_NULLPTR_PROVIDED;
     }

     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     *outputCornerTree = reinterpret_cast<NrtQuadTree>(treePointer->getTopLeft().get());

     return NRT_SUCCESS;
   }

  NrtResult Nrt_QuadTree_getTopRight(const NrtQuadTree tree, NrtQuadTree* outputCornerTree) {
     if(tree == nullptr || outputCornerTree == nullptr) {
       Nrt_setErrMsgIsNullptrInternal();
       return NRT_FAILURE_NULLPTR_PROVIDED;
     }

     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     *outputCornerTree = reinterpret_cast<NrtQuadTree>(treePointer->getTopRight().get());

     return NRT_SUCCESS;
   }

  NrtResult Nrt_QuadTree_getBottomLeft(const NrtQuadTree tree, NrtQuadTree* outputCornerTree) {
     if(tree == nullptr || outputCornerTree == nullptr) {
       Nrt_setErrMsgIsNullptrInternal();
       return NRT_FAILURE_NULLPTR_PROVIDED;
     }

     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     *outputCornerTree = reinterpret_cast<NrtQuadTree>(treePointer->getBottomLeft().get());

     return NRT_SUCCESS;
   }

  NrtResult Nrt_QuadTree_getBottomRight(const NrtQuadTree tree, NrtQuadTree* outputCornerTree) {
     if(tree == nullptr || outputCornerTree == nullptr) {
       Nrt_setErrMsgIsNullptrInternal();
       return NRT_FAILURE_NULLPTR_PROVIDED;
     }

     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     *outputCornerTree = reinterpret_cast<NrtQuadTree>(treePointer->getBottomRight().get());

     return NRT_SUCCESS;
   }

  NrtBool Nrt_QuadTree_tryInsert(const NrtQuadTree tree, NrtQuadTreePoint point) {
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
    return static_cast<int32_t>(treePointer->tryInsert(reinterpret_cast<Maths::QuadTreePoint*>(point)->shared_from_this()));
   }

  NrtBool Nrt_QuadTree_tryRemove(const NrtQuadTree tree, NrtQuadTreePoint point) {
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
    return static_cast<int32_t>(treePointer->tryRemove(reinterpret_cast<Maths::QuadTreePoint*>(point)->shared_from_this()));
  }

  NrtResult Nrt_QuadTree_getIntersectingPoints(const NrtQuadTree tree, NrtGeoBounds bounds, NrtPointVector* outputResultVector) {
     if(tree == nullptr || outputResultVector == nullptr) {
       Nrt_setErrMsgIsNullptrInternal();
       return NRT_FAILURE_NULLPTR_PROVIDED;
     }

    std::vector<std::shared_ptr<Maths::QuadTreePoint>>* points = new std::vector<std::shared_ptr<Maths::QuadTreePoint>>();
    *points = reinterpret_cast<Maths::QuadTree*>(tree)->getIntersectingPoints(*reinterpret_cast<const Maths::GeoBounds*>(&bounds));
    *outputResultVector = reinterpret_cast<NrtPointVector>(points);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_PointVector_delete(NrtPointVector vector) {
    if(vector == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    delete reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(vector);

    return NRT_SUCCESS;
  }

  size_t Nrt_PointVector_getSize(const NrtPointVector vector) {
    return reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(vector)->size();
  }

  NrtResult Nrt_PointVector_getPointFromIndex(const NrtPointVector vector, size_t index, NrtQuadTreePoint* outputPoint) {
    if(vector == nullptr || outputPoint == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    *outputPoint = reinterpret_cast<NrtQuadTreePoint>(reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(vector)->at(index).get());

    return NRT_SUCCESS;
  }

  NrtResult Nrt_QuadTree_delete(NrtQuadTree tree) {
    if(tree == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    auto ptr = reinterpret_cast<Maths::QuadTree*>(tree)->shared_from_this();

    if(std::find(_treeCollection.begin(), _treeCollection.end(), ptr) == _treeCollection.end()) {
      Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
      return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }

    _treeCollection.remove(ptr);

    return NRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif
