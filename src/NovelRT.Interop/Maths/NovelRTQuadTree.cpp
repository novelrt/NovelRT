// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NovelRTInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Maths/NovelRTQuadTree.h"
#include "NovelRT.h"
#include <list>
#include <cmath>

std::list<std::shared_ptr<NovelRT::Maths::QuadTree>> _treeCollection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

   NovelRTQuadTree NovelRT_QuadTree_create(NovelRTGeoBounds bounds) {
     _treeCollection.push_back(std::make_shared<Maths::QuadTree>(*reinterpret_cast<const Maths::GeoBounds*>(&bounds)));
     return reinterpret_cast<NovelRTQuadTree>(_treeCollection.back().get());
   }
  
  int32_t NovelRT_QuadTree_getParent(const NovelRTQuadTree tree, NovelRTQuadTree* outputParentTree) {
     if(tree == nullptr || outputParentTree == nullptr) {
       NovelRT_setErrMsgIsNullptrInternal();
       return NOVELRT_FAILURE;
     }
     
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     auto parentTree = treePointer->getParent();
     *outputParentTree = reinterpret_cast<NovelRTQuadTree&>(parentTree);

     return NOVELRT_SUCCESS;
   }
  
  int32_t NovelRT_QuadTree_getBounds(const NovelRTQuadTree tree, NovelRTGeoBounds* outputGeoBounds) {
     if(tree == nullptr || outputGeoBounds == nullptr) {
       NovelRT_setErrMsgIsNullptrInternal();
       return NOVELRT_FAILURE;
     }
     
     Maths::GeoBounds bounds = Maths::GeoBounds({ 0,0 }, {0,0}, 0);
     bounds = reinterpret_cast<Maths::QuadTree*>(tree)->getBounds();
     *outputGeoBounds = *reinterpret_cast<NovelRTGeoBounds*>(&bounds);

     return NOVELRT_SUCCESS;
   }
  
  int32_t NovelRT_QuadTree_getPoint(const NovelRTQuadTree tree, size_t index, NovelRTQuadTreePoint* outputPoint) {
     if(tree == nullptr || outputPoint == nullptr) {
       NovelRT_setErrMsgIsNullptrInternal();
       return NOVELRT_FAILURE;
     }
     
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     auto point = treePointer->getPoint(index).get();
     *outputPoint = reinterpret_cast<NovelRTQuadTreePoint&>(point);

     return NOVELRT_SUCCESS;
   }
  
  int32_t NovelRT_QuadTree_getPointCount(const NovelRTQuadTree tree, size_t* outputSize) {
     if(tree == nullptr || outputSize == nullptr) {
       NovelRT_setErrMsgIsNullptrInternal();
       return NOVELRT_FAILURE;
     }
     
     *outputSize = reinterpret_cast<Maths::QuadTree*>(tree)->getPointCount();

     return NOVELRT_SUCCESS;
   }
  
  int32_t NovelRT_QuadTree_getTopLeft(const NovelRTQuadTree tree, NovelRTQuadTree* outputCornerTree) {
     if(tree == nullptr || outputCornerTree == nullptr) {
       NovelRT_setErrMsgIsNullptrInternal();
       return NOVELRT_FAILURE;
     }

     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     *outputCornerTree = reinterpret_cast<NovelRTQuadTree>(treePointer->getTopLeft().get());

     return NOVELRT_SUCCESS;
   }

  int32_t NovelRT_QuadTree_getTopRight(const NovelRTQuadTree tree, NovelRTQuadTree* outputCornerTree) {
     if(tree == nullptr || outputCornerTree == nullptr) {
       NovelRT_setErrMsgIsNullptrInternal();
       return NOVELRT_FAILURE;
     }

     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     *outputCornerTree = reinterpret_cast<NovelRTQuadTree>(treePointer->getTopRight().get());

     return NOVELRT_SUCCESS;
   }
   
  int32_t NovelRT_QuadTree_getBottomLeft(const NovelRTQuadTree tree, NovelRTQuadTree* outputCornerTree) {
     if(tree == nullptr || outputCornerTree == nullptr) {
       NovelRT_setErrMsgIsNullptrInternal();
       return NOVELRT_FAILURE;
     }

     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     *outputCornerTree = reinterpret_cast<NovelRTQuadTree>(treePointer->getBottomLeft().get());

     return NOVELRT_SUCCESS;
   }
   
  int32_t NovelRT_QuadTree_getBottomRight(const NovelRTQuadTree tree, NovelRTQuadTree* outputCornerTree) {
     if(tree == nullptr || outputCornerTree == nullptr) {
       NovelRT_setErrMsgIsNullptrInternal();
       return NOVELRT_FAILURE;
     }

     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     *outputCornerTree = reinterpret_cast<NovelRTQuadTree>(treePointer->getBottomRight().get());

     return NOVELRT_SUCCESS;
   }
  
  int32_t NovelRT_QuadTree_tryInsert(const NovelRTQuadTree tree, NovelRTQuadTreePoint point, int32_t* outputResult) {
     if(tree == nullptr || outputResult == nullptr) {
       NovelRT_setErrMsgIsNullptrInternal();
       return NOVELRT_FAILURE;
     }

    auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
    *outputResult = static_cast<int32_t>(treePointer->tryInsert(reinterpret_cast<Maths::QuadTreePoint*>(point)->shared_from_this()));

    return NOVELRT_SUCCESS;
   }
  
  int32_t NovelRT_QuadTree_tryRemove(const NovelRTQuadTree tree, NovelRTQuadTreePoint point, int32_t* outputResult) {
     if(tree == nullptr || outputResult == nullptr) {
       NovelRT_setErrMsgIsNullptrInternal();
       return NOVELRT_FAILURE;
     }

    auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
    *outputResult = static_cast<int32_t>(treePointer->tryRemove(reinterpret_cast<Maths::QuadTreePoint*>(point)->shared_from_this()));

    return NOVELRT_SUCCESS;
  }
  
  int32_t NovelRT_QuadTree_getIntersectingPoints(const NovelRTQuadTree tree, NovelRTGeoBounds bounds, NovelRTPointVector* outputResultVector) {
     if(tree == nullptr || outputResultVector == nullptr) {
       NovelRT_setErrMsgIsNullptrInternal();
       return NOVELRT_FAILURE;
     }

    std::vector<std::shared_ptr<Maths::QuadTreePoint>>* points = new std::vector<std::shared_ptr<Maths::QuadTreePoint>>();
    *points = reinterpret_cast<Maths::QuadTree*>(tree)->getIntersectingPoints(*reinterpret_cast<const Maths::GeoBounds*>(&bounds));
    *outputResultVector = reinterpret_cast<NovelRTPointVector>(points);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_PointVector_delete(NovelRTPointVector vector) {
    if(vector == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    delete reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(vector);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_PointVector_getSize(const NovelRTPointVector vector, size_t* outputSize) {
    if(vector == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    *outputSize = reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(vector)->size();

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_PointVector_getPointFromIndex(const NovelRTPointVector vector, size_t index, NovelRTQuadTreePoint* outputPoint) {
    if(vector == nullptr || outputPoint == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }
    
    *outputPoint = reinterpret_cast<NovelRTQuadTreePoint>(reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(vector)->at(index).get());

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_QuadTree_delete(NovelRTQuadTree tree) {
    if(tree == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    auto ptr = reinterpret_cast<Maths::QuadTree*>(tree)->shared_from_this();

    if(std::find(_treeCollection.begin(), _treeCollection.end(), ptr) == _treeCollection.end()) {
      NovelRT_setErrMsgIsAlreadyDeletedOrRemovedInternal();
      return NOVELRT_FAILURE;
    }

    _treeCollection.remove(ptr);

    return NOVELRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif
