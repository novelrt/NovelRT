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
    auto handleId = static_cast<int>(_collection.size()+1);
    QuadTree_t handle = new QuadTreeHandle{ handleId, {0,0,0,0} };
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
    QuadTree_t parentHandle = new QuadTreeHandle{ handleId };
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
    if (_collection.find(tree) == _collection.end())
    {
      return static_cast<size_t>(0);
    }
    return _collection[tree]->getPointCount();
  }

  const QuadTree_t QuadTree_getTopLeft(QuadTree_t tree) {
    if (tree->children[TOP_LEFT] <= 0 ) {
      auto topLeft = _collection[tree]->getTopLeft();
      if (topLeft != nullptr)
      {
        for (const auto element : _collection)
        {
          if (topLeft == element.second)
          {
            return element.first;
          }
        }
        auto handleId = static_cast<int>(_collection.size()+1);
        QuadTree_t treeHandle = new QuadTreeHandle{ handleId };
        _collection.emplace(treeHandle, topLeft);
        return treeHandle;
      }
      return nullptr;
    }

    int childId = tree->children[TOP_LEFT];
    for (auto test : _collection) {
      if (test.first->id == childId) {
        return test.first;
      }
    }
    //If nothing is found, we should assume it doesn't exist
    return nullptr;
  }

  const QuadTree_t QuadTree_getTopRight(QuadTree_t tree) {
    if (tree->children[TOP_RIGHT] <= 0) {
      auto topRight = _collection[tree]->getTopRight();
      if (topRight != nullptr)
      {
        for (const auto element : _collection)
        {
          if (topRight == element.second)
          {
            return element.first;
          }
        }
        auto handleId = static_cast<int>(_collection.size() + 1);
        QuadTree_t treeHandle = new QuadTreeHandle{ handleId };
        _collection.emplace(treeHandle, topRight);
        return treeHandle;
      }
      return nullptr;
    }

    int childId = tree->children[TOP_RIGHT];
    for (auto test : _collection) {
      if (test.first->id == childId) {
        return test.first;
      }
    }
    //If nothing is found, we should assume it doesn't exist
    return nullptr;
  }

  const QuadTree_t QuadTree_getBottomLeft(QuadTree_t tree) {
    if (tree->children[BOTTOM_LEFT] <= 0) {
      auto bottomLeft = _collection[tree]->getBottomLeft();
      if (bottomLeft != nullptr)
      {
        for (const auto element : _collection)
        {
          if (bottomLeft == element.second)
          {
            return element.first;
          }
        }
        auto handleId = static_cast<int>(_collection.size() + 1);
        QuadTree_t treeHandle = new QuadTreeHandle{ handleId };
        _collection.emplace(treeHandle, bottomLeft);
        return treeHandle;
      }
      return nullptr;
    }

    int childId = tree->children[BOTTOM_LEFT];
    for (auto test : _collection) {
      if (test.first->id == childId) {
        return test.first;
      }
    }
    //If nothing is found, we should assume it doesn't exist
    return nullptr;
  }

  const QuadTree_t QuadTree_getBottomRight(QuadTree_t tree) {
    if (tree->children[BOTTOM_RIGHT] <= 0) {
      auto bottomRight = _collection[tree]->getBottomRight();
      if (bottomRight != nullptr)
      {
        for (const auto element : _collection)
        {
          if (bottomRight == element.second)
          {
            return element.first;
          }
        }
        auto handleId = static_cast<int>(_collection.size() + 1);
        QuadTree_t treeHandle = new QuadTreeHandle{ handleId };
        _collection.emplace(treeHandle, bottomRight);
        return treeHandle;
      }
      return nullptr;
    }

    int childId = tree->children[BOTTOM_RIGHT];
    for (auto test : _collection) {
      if (test.first->id == childId) {
        return test.first;
      }
    }
    //If nothing is found, we should assume it doesn't exist
    return nullptr;
  }

  bool QuadTree_tryInsert(QuadTree_t tree, QuadTreePoint_t& point) {
    auto originalCount = _collection[tree]->getPointCount();
    auto pointToInsert = reinterpret_cast<Maths::QuadTreePoint*>(point);
    bool result = _collection[tree]->tryInsert(std::make_shared<Maths::QuadTreePoint>(*pointToInsert));
    auto newCount = _collection[tree]->getPointCount();
    if (newCount < originalCount) {
      auto topLeft = QuadTree_getTopLeft(tree);
      auto topRight = QuadTree_getTopRight(tree);
      auto bottomLeft = QuadTree_getBottomLeft(tree);
      auto bottomRight = QuadTree_getBottomRight(tree);

      if (topLeft != nullptr) {
        tree->children[TOP_LEFT] = topLeft->id;
      }
      if (topRight != nullptr) {
        tree->children[TOP_RIGHT] = topRight->id;
      }
      if (bottomLeft != nullptr) {
        tree->children[BOTTOM_LEFT] = bottomLeft->id;
      }
      if (bottomRight != nullptr) {
        tree->children[BOTTOM_RIGHT] = bottomRight->id;
      }
    }

    return result;
  }

  bool QuadTree_tryRemove(QuadTree_t tree, QuadTreePoint_t& point) {
    
    if (_collection.size() == 0) {
      return false;
    }

    auto pointToRemove = reinterpret_cast<Maths::QuadTreePoint*>(point);
    auto pointCount = _collection[tree]->getPointCount();
    if (pointCount < 1) {
      return false;
    }

    for (int i = 0; i < pointCount; i++) {
      auto originalSharedPtr = _collection[tree]->getPoint(i);
      auto originalPoint = originalSharedPtr.get();
      if (originalPoint->getPosition() == pointToRemove->getPosition()) {
        return _collection[tree]->tryRemove(originalSharedPtr);
      }
    }

    return false;
  }

  PointVector QuadTree_getIntersectingPoints(QuadTree_t tree, const GeoBounds_t& bounds)
  {
    std::vector<std::shared_ptr<Maths::QuadTreePoint>>* points = new std::vector<std::shared_ptr<Maths::QuadTreePoint>>();
    *points = _collection[tree]->getIntersectingPoints(reinterpret_cast<const Maths::GeoBounds&>(bounds));

    std::vector<QuadTreePoint_t>* converted = new std::vector<QuadTreePoint_t>();
    for (std::shared_ptr<Maths::QuadTreePoint> point : *points)
    {
      Maths::QuadTreePoint* ptr = point.get();
      converted->emplace_back(reinterpret_cast<QuadTreePoint_t>(ptr));
    }

    return reinterpret_cast<PointVector>(converted);
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
