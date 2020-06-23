// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRTInterop/Maths/QuadTree_t.h"
#include "NovelRT.h"

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

  QuadTree_t QuadTree_create(GeoBounds_t& bounds) {
    return QuadTree_t{ nullptr, bounds, {}, {}, 0 };
  }

  const QuadTree_t QuadTree_getParent(QuadTree_t& tree) {
    //const std::weak_ptr<Maths::QuadTree> parent = reinterpret_cast<Maths::QuadTree*>(tree)->getParent();
    //return reinterpret_cast<const QuadTree_t>(parent.lock().get());
    return *(tree._parent);
  }

  const GeoBounds_t QuadTree_getBounds(QuadTree_t& tree) {
    //Maths::QuadTree* cTree = reinterpret_cast<Maths::QuadTree*>(tree);
    //const Maths::GeoBounds* bounds = new Maths::GeoBounds(cTree->getBounds());
    //return reinterpret_cast<const GeoBounds_t&>(bounds);
    return tree._bounds;
  }

  const QuadTreePoint_t QuadTree_getPoint(QuadTree_t& tree, size_t index) {
    //Maths::QuadTree* parent = reinterpret_cast<Maths::QuadTree*>(tree);
    //auto point = parent->getPoint(index);
    //if (point == nullptr)
    //{
    //  return nullptr;
    //}
    //else
    //{
    //  return reinterpret_cast<const QuadTreePoint_t*>(point.get());
    //}
    return *(tree._points[index]);
  }

  size_t QuadTree_getPointCount(QuadTree_t& tree) {
    return tree._pointCount;
  }

  const QuadTree_t* QuadTree_getTopLeft(QuadTree_t& tree) {
    /*Maths::QuadTree* parent = reinterpret_cast<Maths::QuadTree*>(tree);
    auto topLeft = parent->getTopLeft();
    if (topLeft == nullptr)
    {
      return nullptr;
    }
    else
    {
      const QuadTree_t cQuadTree = reinterpret_cast<const QuadTree_t>(topLeft.get());
      return cQuadTree;
    }*/
    return tree._children[0];
  }

  const QuadTree_t* QuadTree_getTopRight(QuadTree_t& tree) {
    /*Maths::QuadTree* parent = reinterpret_cast<Maths::QuadTree*>(tree);
    auto topRight = parent->getTopRight();
    if (topRight == nullptr)
    {
      return nullptr;
    }
    else
    {
      return reinterpret_cast<const QuadTree_t>(topRight.get());
    }*/
    return tree._children[1];
  }

  const QuadTree_t* QuadTree_getBottomLeft(QuadTree_t& tree) {
    /*Maths::QuadTree* parent = reinterpret_cast<Maths::QuadTree*>(tree);
    auto bottomLeft = parent->getBottomLeft();
    if (bottomLeft == nullptr)
    {
      return nullptr;
    }
    else
    {
      return reinterpret_cast<const QuadTree_t>(bottomLeft.get());
    }*/
    return tree._children[2];
  }

  const QuadTree_t* QuadTree_getBottomRight(QuadTree_t& tree) {
    /*Maths::QuadTree* parent = reinterpret_cast<Maths::QuadTree*>(tree);
    auto bottomRight = parent->getBottomRight();
    if (bottomRight == nullptr)
    {
      return nullptr;
    }
    else
    {
      return reinterpret_cast<const QuadTree_t>(bottomRight.get());
    }*/
    return tree._children[3];
  }

  bool QuadTree_tryInsert(QuadTree_t& tree, QuadTreePoint_t& point) {
    /*Maths::QuadTree* cTree = reinterpret_cast<Maths::QuadTree*>(tree);
    std::shared_ptr<Maths::QuadTreePoint> cPoint = std::shared_ptr<Maths::QuadTreePoint>(reinterpret_cast<Maths::QuadTreePoint*>(point));
    
    auto result = cTree->tryInsert(cPoint);
    return result;*/
    Maths::QuadTree cTree = *reinterpret_cast<Maths::QuadTree*>(&tree);
    Maths::QuadTreePoint cPoint = *reinterpret_cast<Maths::QuadTreePoint*>(&point);
    auto result = cTree.tryInsert(std::make_shared<Maths::QuadTreePoint>(cPoint));
    tree = reinterpret_cast<QuadTree_t&>(cTree);
    return result;
  }

  //Template with template args... yikes
  //bool tryInsert(const GeoBounds& bounds, TArgs... args)
  //bool tryRemove(std::shared_ptr<QuadTreePoint> point)

  //Template
  //const std::shared_ptr<TQuadTreePoint>& getPoint(size_t index);

  //Needs a vector
  //void getIntersectingPoints(const GeoBounds& bounds, std::vector<std::shared_ptr<QuadTreePoint>>& intersectingPoints)
  //std::vector<std::shared_ptr<QuadTreePoint>> getIntersectingPoints(const GeoBounds& bounds)
#ifdef __cplusplus
}
#endif
