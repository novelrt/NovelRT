// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/QuadTree_t.h"
#include "NovelRT.h"
#include <list>

std::list<std::shared_ptr<NovelRT::Maths::QuadTreePoint>> _collection; //TODO: Why a list? - Ruby
//int _collected = 0;

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

   QuadTree_t QuadTree_create(GeoBounds_t& bounds) {
     auto b = reinterpret_cast<Maths::GeoBounds&>(bounds);
     auto treePointer = new Maths::QuadTree(b);
     auto tree = reinterpret_cast<QuadTree_t&>(treePointer);
     return tree;
   }
  
   QuadTree_t QuadTree_getParent(QuadTree_t tree) {
     auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
     auto parentTree = treePointer->getParent();
     auto treeToReturn = reinterpret_cast<QuadTree_t&>(parentTree);
     return treeToReturn;
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
  
   bool QuadTree_tryInsert(QuadTree_t tree, QuadTreePoint_t& point) {
    auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
    auto cPoint = reinterpret_cast<Maths::QuadTreePoint*>(point);
    _collection.emplace_back(std::shared_ptr<Maths::QuadTreePoint>(cPoint));
    return treePointer->tryInsert(cPoint->shared_from_this());
   }
  
  bool QuadTree_tryRemove(QuadTree_t tree, QuadTreePoint_t& point) {
    auto treePointer = reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree);
    auto cPoint = reinterpret_cast<Maths::QuadTreePoint*>(point);
    return treePointer->tryRemove(cPoint->shared_from_this());
  }
    
  PointVector QuadTree_getIntersectingPoints(QuadTree_t tree, const GeoBounds_t& bounds) {
    std::vector<std::shared_ptr<Maths::QuadTreePoint>>* points = new std::vector<std::shared_ptr<Maths::QuadTreePoint>>();
    auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
    *points = treePointer->getIntersectingPoints(reinterpret_cast<const Maths::GeoBounds&>(bounds));
    return reinterpret_cast<PointVector>(points);
  }

#ifdef __cplusplus
}
#endif
