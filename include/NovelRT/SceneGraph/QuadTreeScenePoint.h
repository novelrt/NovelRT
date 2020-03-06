// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_QUADTREESCENEPOINT_H
#define NOVELRT_QUADTREESCENEPOINT_H

namespace NovelRT::SceneGraph {
  class QuadTreeScenePoint : public Maths::QuadTreePoint {
  private:
    std::shared_ptr<SceneNode> _sceneNode;

  public:
    QuadTreeScenePoint(Maths::GeoVector2<float> position, std::shared_ptr<SceneNode> sceneNode) :
      Maths::QuadTreePoint(position),
      _sceneNode(sceneNode) {
    }

    QuadTreeScenePoint(float x, float y, std::shared_ptr<SceneNode> sceneNode) :
      Maths::QuadTreePoint(x, y),
      _sceneNode(sceneNode) {
    }

    const std::shared_ptr<SceneNode>& getSceneNode() const {
      return _sceneNode;
    }
  };
}

#endif
