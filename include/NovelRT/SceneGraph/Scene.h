// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_SCENE_H
#define NOVELRT_SCENE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::SceneGraph {
  class Scene {
  private:
    std::set<std::shared_ptr<SceneNode>> _nodes;

  public:
    const std::set<std::shared_ptr<SceneNode>>& getNodes() {
      return _nodes;
    }

    bool insert(const std::shared_ptr<SceneNode>& node) {
      return _nodes.insert(node).second;
    }

    bool remove(const std::shared_ptr<SceneNode>& node) {
      auto numErased = _nodes.erase(node);
      assert((numErased == 0) || (numErased == 1));
      return numErased != 0;
    }
  };
}

#endif
