#ifndef NOVELRT_MATHS_QUADTREE_H
#define NOVELRT_MATHS_QUADTREE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Maths {
  template <typename T>
  class QuadTree {
  private:
    static const int32_t NODE_CAPACITY = 4;

    GeoBounds _treeBounds;
    std::vector<T*> _nodeObjects;
    std::unique_ptr<QuadTree> _topLeft;
    std::unique_ptr<QuadTree> _topRight;
    std::unique_ptr<QuadTree> _bottomLeft;
    std::unique_ptr<QuadTree> _bottomRight;

  public:
    explicit QuadTree(GeoBounds treeBounds) noexcept : _treeBounds(treeBounds), _nodeObjects(std::vector<T>()) {
      static_assert(std::is_base_of<QuadTreeNode, T>::value, "Type argument for T must inherit NovelRT::Maths::QuadTreeNode!");
    }

    bool tryInsertNodeObject(const T* const target) noexcept {
      if(target == nullptr || !_treeBounds.pointIsWithinBounds(target->getPosition())) return false;

      if (_nodeObjects.size() < NODE_CAPACITY && _topLeft == nullptr) {
        _nodeObjects.emplace_back(target);
        return true;
      }

      if(_topLeft == nullptr) subdivideTree();

      //TODO: Refactor this omd
      if (_topLeft->tryInsertNodeObject(target)) return true;
      if (_topRight->tryInsertNodeObject(target)) return true;
      if (_bottomLeft->tryInsertNodeObject(target)) return true;
      if (_bottomRight->tryInsertNodeObject(target)) return true;

      //it should never reach here, but we also can't really afford to throw in this particular code path I don't think
      return false;
    }

  };
}

#endif //!NOVELRT_MATHS_QUADTREE_H
