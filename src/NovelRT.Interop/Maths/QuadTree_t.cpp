// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/QuadTree_t.h"
#include "NovelRT.h"
#include <list>

//int _collected = 0;
std::list<std::shared_ptr<NovelRT::Maths::QuadTree>> _treeCollection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

   NovelRTQuadTree NovelRT_QuadTree_create(GeoBounds_t bounds) {
     _treeCollection.push_back(std::make_shared<Maths::QuadTree>(reinterpret_cast<const Maths::GeoBounds&>(bounds)));
     return reinterpret_cast<NovelRTQuadTree>(_treeCollection.back().get());
   }
  
   NovelRTQuadTree NovelRT_QuadTree_getParent(NovelRTQuadTree tree) {
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     auto parentTree = treePointer->getParent();
     return reinterpret_cast<NovelRTQuadTree&>(parentTree);
   }
  
   GeoBounds_t NovelRT_QuadTree_getBounds(NovelRTQuadTree tree) {
     Maths::GeoBounds* bounds = new Maths::GeoBounds({ 0,0 }, {0,0}, 0);
     *bounds = reinterpret_cast<Maths::QuadTree*>(tree)->getBounds();
     return reinterpret_cast<const GeoBounds_t&>(*bounds);
   }
  
   NovelRTQuadTreePoint NovelRT_QuadTree_getPoint(NovelRTQuadTree tree, size_t index) {
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     auto point = treePointer->getPoint(index).get();
     return reinterpret_cast<NovelRTQuadTreePoint&>(point);
   }
  
   size_t NovelRT_QuadTree_getPointCount(NovelRTQuadTree tree) {
     return reinterpret_cast<Maths::QuadTree*>(tree)->getPointCount();
   }
  
   NovelRTQuadTree NovelRT_QuadTree_getTopLeft(NovelRTQuadTree tree) {
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     return reinterpret_cast<NovelRTQuadTree>(treePointer->getTopLeft().get());
   }

   NovelRTQuadTree NovelRT_QuadTree_getTopRight(NovelRTQuadTree tree) {
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     return reinterpret_cast<NovelRTQuadTree>(treePointer->getTopRight().get());
   }
   
   NovelRTQuadTree NovelRT_QuadTree_getBottomLeft(NovelRTQuadTree tree) {
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     return reinterpret_cast<NovelRTQuadTree>(treePointer->getBottomLeft().get());
   }
   
   NovelRTQuadTree NovelRT_QuadTree_getBottomRight(NovelRTQuadTree tree) {
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     return reinterpret_cast<NovelRTQuadTree>(treePointer->getBottomRight().get());
   }
  
   bool NovelRT_QuadTree_tryInsert(NovelRTQuadTree tree, NovelRTQuadTreePoint point) {
    auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
    return treePointer->tryInsert(reinterpret_cast<Maths::QuadTreePoint*>(point)->shared_from_this());
   }
  
  bool NovelRT_QuadTree_tryRemove(NovelRTQuadTree tree, NovelRTQuadTreePoint point) {
    auto treePointer = reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree);
    return treePointer->tryRemove(reinterpret_cast<Maths::QuadTreePoint*>(point)->shared_from_this());
  }
  
  NovelRTPointVector NovelRT_QuadTree_getIntersectingPoints(NovelRTQuadTree tree, GeoBounds_t bounds) {
    std::vector<std::shared_ptr<Maths::QuadTreePoint>>* points = new std::vector<std::shared_ptr<Maths::QuadTreePoint>>();
    *points = reinterpret_cast<Maths::QuadTree*>(tree)->getIntersectingPoints(reinterpret_cast<const Maths::GeoBounds&>(bounds));
    return reinterpret_cast<NovelRTPointVector>(points);
  }

  void NovelRT_PointVector_delete(NovelRTPointVector vector) {
    delete reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(vector);
  }

  size_t NovelRT_PointVector_getSize(NovelRTPointVector vector) {
    return reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(vector)->size();
  }

  NovelRTQuadTreePoint NovelRT_PointVector_getPointFromIndex(NovelRTPointVector vector, size_t index) {
    return reinterpret_cast<NovelRTQuadTreePoint>(reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(vector)->at(index).get());
  }

//TODO: We should probably add return codes for stuff like this, because C.
  void NovelRT_QuadTree_delete(NovelRTQuadTree tree) {
    _treeCollection.remove(reinterpret_cast<Maths::QuadTree*>(tree)->shared_from_this());
  }

#ifdef __cplusplus
}
#endif
