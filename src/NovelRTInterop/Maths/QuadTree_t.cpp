// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRTInterop/Maths/QuadTree_t.h"
#include "NovelRT.h"

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

  QuadTree_t* QuadTree_create(GeoBounds_t* bounds) {
    Maths::GeoBounds cBounds = *reinterpret_cast<Maths::GeoBounds*>(bounds);
    static Maths::QuadTree tree = Maths::QuadTree(cBounds);
    static auto treePtr = std::make_shared<Maths::QuadTree>(tree);
    return reinterpret_cast<QuadTree_t*>(&treePtr);
  }

  const QuadTree_t* QuadTree_getParent(QuadTree_t* tree) {
    static const std::weak_ptr<Maths::QuadTree> parent = reinterpret_cast<Maths::QuadTree*>(tree)->getParent();
    return reinterpret_cast<const QuadTree_t*>(&parent);
  }

  const GeoBounds_t* QuadTree_getBounds(QuadTree_t* tree) {
    std::shared_ptr<Maths::QuadTree> cTree = *reinterpret_cast<std::shared_ptr<Maths::QuadTree>*>(tree);
    static const Maths::GeoBounds bounds = cTree->getBounds();
    return reinterpret_cast<const GeoBounds_t*>(&bounds);
  }

  const QuadTreePoint_t* QuadTree_getPoint(QuadTree_t* tree, size_t index) {
    std::shared_ptr<Maths::QuadTree> parent = *reinterpret_cast<std::shared_ptr<Maths::QuadTree>*>(tree);
    std::shared_ptr<Maths::QuadTreePoint> point = parent->getPoint(index);
    if (point == nullptr)
    {
      return nullptr;
    }
    else
    {
      return reinterpret_cast<const QuadTreePoint_t*>(&(parent->getPoint(index)));
    }
    
  }

  size_t QuadTree_getPointCount(QuadTree_t* tree) {
    std::shared_ptr<Maths::QuadTree> cTree = *reinterpret_cast<std::shared_ptr<Maths::QuadTree>*>(tree);
    return cTree->getPointCount();
  }

  const QuadTree_t* QuadTree_getTopLeft(QuadTree_t* tree) {
    std::shared_ptr<Maths::QuadTree> parent = *reinterpret_cast<std::shared_ptr<Maths::QuadTree>*>(tree);
    std::shared_ptr<Maths::QuadTree> topLeft = parent->getTopLeft();
    if (topLeft == nullptr)
    {
      return nullptr;
    }
    else
    {
    static const QuadTree_t* cQuadTree = reinterpret_cast<const QuadTree_t*>(&topLeft);
    return cQuadTree;
    }
  }

  const QuadTree_t* QuadTree_getTopRight(QuadTree_t* tree) {
    std::shared_ptr<Maths::QuadTree> parent = *reinterpret_cast<std::shared_ptr<Maths::QuadTree>*>(tree);
    static std::shared_ptr<Maths::QuadTree> topRight = parent->getTopRight();
    if (topRight == nullptr)
    {
      return nullptr;
    }
    else
    {
      return reinterpret_cast<const QuadTree_t*>(&topRight);
    }
  }

  const QuadTree_t* QuadTree_getBottomLeft(QuadTree_t* tree) {
    std::shared_ptr<Maths::QuadTree> parent = *reinterpret_cast<std::shared_ptr<Maths::QuadTree>*>(tree);
    static std::shared_ptr<Maths::QuadTree> bottomLeft = parent->getBottomLeft();
    if (bottomLeft == nullptr)
    {
      return nullptr;
    }
    else
    {
      return reinterpret_cast<const QuadTree_t*>(&bottomLeft);
    }
  }

  const QuadTree_t* QuadTree_getBottomRight(QuadTree_t* tree) {
    std::shared_ptr<Maths::QuadTree> parent = *reinterpret_cast<std::shared_ptr<Maths::QuadTree>*>(tree);
    static std::shared_ptr<Maths::QuadTree> bottomRight = parent->getBottomRight();
    if (bottomRight == nullptr)
    {
      return nullptr;
    }
    else
    {
      return reinterpret_cast<const QuadTree_t*>(&bottomRight);
    }
  }

  bool QuadTree_tryInsert(QuadTree_t* tree, QuadTreePoint_t* point) {
    static std::shared_ptr<Maths::QuadTree> cTree = *reinterpret_cast<std::shared_ptr<Maths::QuadTree>*>(tree);
    static std::shared_ptr<Maths::QuadTreePoint> cPoint = std::shared_ptr<Maths::QuadTreePoint>(reinterpret_cast<Maths::QuadTreePoint*>(point));
    
    auto result = cTree->tryInsert(cPoint);
    tree = reinterpret_cast<QuadTree_t*>(&cTree);
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
