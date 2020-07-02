// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRTInterop/Maths/QuadTree_t.h"
#include "NovelRT.h"

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

  QuadTree_t QuadTree_create(GeoBounds_t& bounds)
  {
    auto b = reinterpret_cast<Maths::GeoBounds&>(bounds);
    Maths::QuadTree* tree = new Maths::QuadTree(b);
    std::shared_ptr<Maths::QuadTree>* quad = new std::shared_ptr<Maths::QuadTree>();
    *quad = std::make_shared<Maths::QuadTree>(*tree);
    return reinterpret_cast<QuadTree_t>(tree);
  }

  const QuadTree_t QuadTree_getParent(QuadTree_t tree)
  {
    std::weak_ptr<Maths::QuadTree>* parent = new std::weak_ptr<Maths::QuadTree>();
    *parent = reinterpret_cast<std::weak_ptr<Maths::QuadTree>*>(tree)->lock()->getParent();
    return reinterpret_cast<QuadTree_t>(parent);
  }

  const GeoBounds_t QuadTree_getBounds(QuadTree_t tree)
  {
    std::shared_ptr<Maths::QuadTree> quadTree = *reinterpret_cast<std::shared_ptr<Maths::QuadTree>*>(tree);
    Maths::GeoBounds* bounds = new Maths::GeoBounds({ 0,0 }, {0,0}, 0);
    *bounds = quadTree->getBounds();
    return reinterpret_cast<const GeoBounds_t&>(*bounds);
  }

  const QuadTreePoint_t QuadTree_getPoint(QuadTree_t tree, size_t index)
  {
    std::weak_ptr<Maths::QuadTree> quadTree = *reinterpret_cast<std::weak_ptr<Maths::QuadTree>*>(tree);
    auto point = quadTree.lock()->getPoint(index);
    return reinterpret_cast<QuadTreePoint_t&>(point);
  }

  size_t QuadTree_getPointCount(QuadTree_t tree) {
    return reinterpret_cast<std::weak_ptr<Maths::QuadTree>*>(tree)->lock()->getPointCount();
  }

  const QuadTree_t QuadTree_getTopLeft(QuadTree_t tree) {
    std::weak_ptr<Maths::QuadTree> quadTree = *reinterpret_cast<std::weak_ptr<Maths::QuadTree>*>(tree);
    std::weak_ptr<Maths::QuadTree>* point = new std::weak_ptr<Maths::QuadTree>();
    *point = quadTree.lock()->getTopLeft();
    return reinterpret_cast<QuadTree_t>(point);
  }

  const QuadTree_t QuadTree_getTopRight(QuadTree_t tree) {
    std::weak_ptr<Maths::QuadTree> quadTree = *reinterpret_cast<std::weak_ptr<Maths::QuadTree>*>(tree);
    std::weak_ptr<Maths::QuadTree>* point = new std::weak_ptr<Maths::QuadTree>();
    *point = quadTree.lock()->getTopRight();
    return reinterpret_cast<QuadTree_t>(point);
  }

  const QuadTree_t QuadTree_getBottomLeft(QuadTree_t tree) {
    std::weak_ptr<Maths::QuadTree> quadTree = *reinterpret_cast<std::weak_ptr<Maths::QuadTree>*>(tree);
    std::weak_ptr<Maths::QuadTree>* point = new std::weak_ptr<Maths::QuadTree>();
    *point = quadTree.lock()->getBottomLeft();
    return reinterpret_cast<QuadTree_t>(point);
  }

  const QuadTree_t QuadTree_getBottomRight(QuadTree_t tree) {
    std::weak_ptr<Maths::QuadTree> quadTree = *reinterpret_cast<std::weak_ptr<Maths::QuadTree>*>(tree);
    std::weak_ptr<Maths::QuadTree>* point = new std::weak_ptr<Maths::QuadTree>();
    *point = quadTree.lock()->getBottomRight();
    return reinterpret_cast<QuadTree_t>(point);
  }

  bool QuadTree_tryInsert(QuadTree_t tree, QuadTreePoint_t& point) {
    std::weak_ptr<Maths::QuadTree> quadTree = *reinterpret_cast<std::weak_ptr<Maths::QuadTree>*>(tree);
    auto pointToInsert = reinterpret_cast<Maths::QuadTreePoint&>(point);
    auto sharedPoint = std::make_shared<Maths::QuadTreePoint>(pointToInsert);
    return quadTree.lock()->tryInsert(sharedPoint);
  }

  bool QuadTree_tryRemove(QuadTree_t tree, QuadTreePoint_t& point)
  {
    std::weak_ptr<Maths::QuadTree> quadTree = *reinterpret_cast<std::weak_ptr<Maths::QuadTree>*>(tree);
    auto pointToRemove = reinterpret_cast<Maths::QuadTreePoint&>(point);
    auto sharedPoint = std::make_shared<Maths::QuadTreePoint>(pointToRemove);
    return quadTree.lock()->tryRemove(sharedPoint);
  }

  PointVector QuadTree_getIntersectingPoints(QuadTree_t tree, const GeoBounds_t& bounds)
  {
    std::weak_ptr<Maths::QuadTree> quadTree = *reinterpret_cast<std::weak_ptr<Maths::QuadTree>*>(tree);
    std::vector<std::shared_ptr<Maths::QuadTreePoint>>* points = new std::vector<std::shared_ptr<Maths::QuadTreePoint>>();
    *points = quadTree.lock()->getIntersectingPoints(reinterpret_cast<const Maths::GeoBounds&>(bounds));
    return reinterpret_cast<PointVector>(points);
  }
  
#ifdef __cplusplus
}
#endif
