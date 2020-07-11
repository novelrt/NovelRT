// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRTInterop/Maths/QuadTree_t.h"
#include "NovelRT.h"

std::unordered_map <QuadTree_t, std::shared_ptr<NovelRT::Maths::QuadTree>> _collection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

  QuadTree_t QuadTree_create(GeoBounds_t& bounds)
  {
    auto b = reinterpret_cast<Maths::GeoBounds&>(bounds);
    auto handleId = static_cast<int>(_collection.size());
    QuadTree_t handle = new Quad{ handleId };
    auto tree = std::make_shared<Maths::QuadTree>(b);
    handle = reinterpret_cast<QuadTree_t>(&tree);
    _collection.emplace(handle, tree);
    return handle;
  }

  const QuadTree_t QuadTree_getParent(QuadTree_t tree)
  {
    auto parent = _collection[tree]->getParent();

    for (const auto element : _collection)
    {
      if (parent.lock() == element.second)
      {
        return element.first;
      }
    }

    auto handleId = static_cast<int>(_collection.size());
    QuadTree_t parentHandle = new Quad{ handleId };
    _collection.emplace(parentHandle, parent);
    return parentHandle;
  }

  const GeoBounds_t QuadTree_getBounds(QuadTree_t tree)
  {
    Maths::GeoBounds* bounds = new Maths::GeoBounds({ 0,0 }, {0,0}, 0);
    *bounds = _collection[tree]->getBounds();
    return reinterpret_cast<const GeoBounds_t&>(*bounds);
  }

  const QuadTreePoint_t QuadTree_getPoint(QuadTree_t tree, size_t index)
  {
    auto point = _collection[tree]->getPoint(index);
    auto pointToReturn = point.get();
    return reinterpret_cast<QuadTreePoint_t&>(pointToReturn);
  }

  size_t QuadTree_getPointCount(QuadTree_t tree) {
    return _collection[tree]->getPointCount();
  }

  const QuadTree_t QuadTree_getTopLeft(QuadTree_t tree) {
    auto newTree = _collection[tree]->getTopLeft();

    if (newTree == nullptr)
    {
      return nullptr;
    }

    for (const auto element : _collection)
    {
      if (newTree == element.second)
      {
        return element.first;
      }
    }
    auto handleId = static_cast<int>(_collection.size());
    QuadTree_t treeHandle = new Quad{ handleId };
    _collection.emplace(treeHandle, newTree);
    return treeHandle;

  }

  const QuadTree_t QuadTree_getTopRight(QuadTree_t tree) {
    auto newTree = _collection[tree]->getTopRight();

    if (newTree == nullptr)
    {
      return nullptr;
    }

    for (const auto element : _collection)
    {
      if (newTree == element.second)
      {
        return element.first;
      }
    }

    auto handleId = static_cast<int>(_collection.size());
    QuadTree_t treeHandle = new Quad{ handleId };
    _collection.emplace(treeHandle, newTree);
    return treeHandle;
  }

  const QuadTree_t QuadTree_getBottomLeft(QuadTree_t tree) {
    auto newTree = _collection[tree]->getBottomLeft();

    if (newTree == nullptr)
    {
      return nullptr;
    }

    for (const auto element : _collection)
    {
      if (newTree == element.second)
      {
        return element.first;
      }
    }

    auto handleId = static_cast<int>(_collection.size());
    QuadTree_t treeHandle = new Quad{ handleId };
    _collection.emplace(treeHandle, newTree);
    return treeHandle;
  }

  const QuadTree_t QuadTree_getBottomRight(QuadTree_t tree) {
    auto newTree = _collection[tree]->getBottomRight();

    if (newTree == nullptr)
    {
      return nullptr;
    }

    for (const auto element : _collection)
    {
      if (newTree == element.second)
      {
        return element.first;
      }
    }

    auto handleId = static_cast<int>(_collection.size());
    QuadTree_t treeHandle = new Quad{ handleId };
    _collection.emplace(treeHandle, newTree);
    return treeHandle;
  }

  bool QuadTree_tryInsert(QuadTree_t tree, QuadTreePoint_t& point) {
    auto pointToInsert = reinterpret_cast<Maths::QuadTreePoint*>(point);
    return _collection[tree]->tryInsert(std::make_shared<Maths::QuadTreePoint>(*pointToInsert));
  }

  bool QuadTree_tryRemove(QuadTree_t tree, QuadTreePoint_t& point)
  {
    auto pointToRemove = reinterpret_cast<Maths::QuadTreePoint*>(point);
    auto sharedPoint = std::make_shared<Maths::QuadTreePoint>(*pointToRemove);
    return _collection[tree]->tryRemove(sharedPoint);
  }

  PointVector QuadTree_getIntersectingPoints(QuadTree_t tree, const GeoBounds_t& bounds)
  {
    std::vector<std::shared_ptr<Maths::QuadTreePoint>>* points = new std::vector<std::shared_ptr<Maths::QuadTreePoint>>();
    *points = _collection[tree]->getIntersectingPoints(reinterpret_cast<const Maths::GeoBounds&>(bounds));
    return reinterpret_cast<PointVector>(points);
  }

  void QuadTree_destroy(QuadTree_t tree)
  {
    auto treeToDestroy = _collection[tree];
    treeToDestroy.reset();
    _collection.erase(tree);
  }

#ifdef __cplusplus
}
#endif
