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

   QuadTree_t QuadTree_create(GeoBounds_t& bounds) {
     auto b = reinterpret_cast<Maths::GeoBounds&>(bounds);
     auto treePointer = std::make_shared<Maths::QuadTree>(b);
     _treeCollection.push_back(treePointer);
     return reinterpret_cast<QuadTree_t&>(treePointer);
   }
  
   QuadTree_t QuadTree_getParent(QuadTree_t tree) {
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     auto parentTree = treePointer->getParent();
     return reinterpret_cast<QuadTree_t&>(parentTree);
   }
  
   GeoBounds_t QuadTree_getBounds(QuadTree_t tree) {
     Maths::GeoBounds* bounds = new Maths::GeoBounds({ 0,0 }, {0,0}, 0);
     *bounds = reinterpret_cast<Maths::QuadTree*>(tree)->getBounds();
     return reinterpret_cast<const GeoBounds_t&>(*bounds);
   }
  
   QuadTreePoint_t QuadTree_getPoint(QuadTree_t tree, size_t index) {
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     auto point = treePointer->getPoint(index).get();
     return reinterpret_cast<QuadTreePoint_t&>(point);
   }
  
   size_t QuadTree_getPointCount(QuadTree_t tree) {
     return reinterpret_cast<Maths::QuadTree*>(tree)->getPointCount();
   }
  
   QuadTree_t QuadTree_getTopLeft(QuadTree_t tree) {
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     auto childTree = treePointer->getTopLeft().get();
     return reinterpret_cast<QuadTree_t&>(childTree);
   }

   QuadTree_t QuadTree_getTopRight(QuadTree_t tree) {
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     auto childTree = treePointer->getTopRight().get();
     return reinterpret_cast<QuadTree_t&>(childTree);
   }
   
   QuadTree_t QuadTree_getBottomLeft(QuadTree_t tree) {
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     auto childTree = treePointer->getBottomLeft().get();
     return reinterpret_cast<QuadTree_t&>(childTree);
   }
   
   QuadTree_t QuadTree_getBottomRight(QuadTree_t tree) {
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     auto childTree = treePointer->getBottomRight().get();
     return reinterpret_cast<QuadTree_t&>(childTree);
   }
  
   bool QuadTree_tryInsert(QuadTree_t tree, QuadTreePoint_t point) {
    auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
    return treePointer->tryInsert(reinterpret_cast<std::shared_ptr<Maths::QuadTreePoint>&>(point));
   }
  
  bool QuadTree_tryRemove(QuadTree_t tree, QuadTreePoint_t point) {
    auto treePointer = reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree);
    return treePointer->tryRemove(reinterpret_cast<std::shared_ptr<Maths::QuadTreePoint>&>(point));
  }
    
//TODO: Add deleter method for PointVector.
  PointVector QuadTree_getIntersectingPoints(QuadTree_t tree, const GeoBounds_t& bounds) {
    std::vector<std::shared_ptr<Maths::QuadTreePoint>>* points = new std::vector<std::shared_ptr<Maths::QuadTreePoint>>();
    auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
    *points = treePointer->getIntersectingPoints(reinterpret_cast<const Maths::GeoBounds&>(bounds));
    return reinterpret_cast<PointVector>(points);
  }

//TODO: We should probably add return codes for stuff like this, because C.
  void QuadTree_delete(QuadTree_t tree) {
    _treeCollection.remove(reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree));
  }

#ifdef __cplusplus
}
#endif
