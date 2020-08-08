// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRTInterop/Maths/QuadTree_t.h"
#include "NovelRT.h"

std::list<std::shared_ptr<NovelRT::Maths::QuadTree>> _collection;
//int _collected = 0;

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

   QuadTree_t QuadTree_create(GeoBounds_t& bounds) {
     auto b = reinterpret_cast<Maths::GeoBounds&>(bounds);
     auto treePointer = std::shared_ptr<Maths::QuadTree>(new Maths::QuadTree(b));
     _collection.insert(_collection.end(), treePointer->shared_from_this());
     auto tree = reinterpret_cast<QuadTree_t&>(treePointer);
     return tree;
   }
  
   const QuadTree_t QuadTree_getParent(QuadTree_t tree) {
     auto treePointer = reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree);
     auto parentTree = treePointer->getParent().lock()->shared_from_this();
     _collection.insert(_collection.end(), parentTree);
     auto treeToReturn = reinterpret_cast<QuadTree_t&>(parentTree);
     return treeToReturn;
   }
  
   const GeoBounds_t QuadTree_getBounds(QuadTree_t tree) {
     Maths::GeoBounds* bounds = new Maths::GeoBounds({ 0,0 }, {0,0}, 0);
     *bounds = reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree)->getBounds();
     return reinterpret_cast<const GeoBounds_t&>(*bounds);
   }
  
   const QuadTreePoint_t QuadTree_getPoint(QuadTree_t tree, size_t index) {
     auto treePointer = reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree);
     auto point = treePointer->getPoint(index);
     return reinterpret_cast<QuadTreePoint_t&>(point);
   }
  
   size_t QuadTree_getPointCount(QuadTree_t tree) {
     return reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree)->getPointCount();
   }
  
   const QuadTree_t QuadTree_getTopLeft(QuadTree_t tree) {
     auto treePointer = reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree);
     auto childTree = treePointer->getTopLeft()->shared_from_this();
     _collection.insert(_collection.end(), childTree);
     return reinterpret_cast<QuadTree_t&>(childTree);
   }

   const QuadTree_t QuadTree_getTopRight(QuadTree_t tree) {
     auto treePointer = reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree);
     auto childTree = treePointer->getTopRight()->shared_from_this();
     _collection.insert(_collection.end(), childTree);
     return reinterpret_cast<QuadTree_t&>(childTree);
   }

  const QuadTree_t QuadTree_getBottomLeft(QuadTree_t tree) {
     auto treePointer = reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree);
     auto childTree = treePointer->getBottomLeft()->shared_from_this();
     _collection.insert(_collection.end(), childTree);
     return reinterpret_cast<QuadTree_t&>(childTree);
   }

  const QuadTree_t QuadTree_getBottomRight(QuadTree_t tree) {
     auto treePointer = reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree);
     auto childTree = treePointer->getBottomRight()->shared_from_this();
     _collection.insert(_collection.end(), childTree);
     return reinterpret_cast<QuadTree_t&>(childTree);
   }
  
  bool QuadTree_tryInsert(QuadTree_t tree, QuadTreePoint_t& point) {
    auto treePointer = reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree);
    auto cPoint = reinterpret_cast<std::shared_ptr<Maths::QuadTreePoint>&>(point);
    return treePointer->tryInsert(cPoint);
  }
  
  bool QuadTree_tryRemove(QuadTree_t tree, QuadTreePoint_t& point) {
    auto treePointer = reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree);
    auto cPoint = reinterpret_cast<std::shared_ptr<Maths::QuadTreePoint>&>(point);
    return treePointer->tryRemove(cPoint);
  }
    
  PointVector QuadTree_getIntersectingPoints(QuadTree_t tree, const GeoBounds_t& bounds) {
    std::vector<std::shared_ptr<Maths::QuadTreePoint>>* points = new std::vector<std::shared_ptr<Maths::QuadTreePoint>>();
    auto treePointer = reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree);
    *points = treePointer->getIntersectingPoints(reinterpret_cast<const Maths::GeoBounds&>(bounds));
    return reinterpret_cast<PointVector>(points);
  }

   void QuadTree_destroy(QuadTree_t tree) {
     auto sharedPtr = reinterpret_cast<std::shared_ptr<Maths::QuadTree>&>(tree);
     _collection.remove(sharedPtr);
     sharedPtr.reset();
   }

#ifdef __cplusplus
}
#endif
