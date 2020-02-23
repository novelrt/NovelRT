// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_QUADTREENODE_H
#define NOVELRT_QUADTREENODE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::SceneGraph {
  class QuadTreeNode : public SceneNode {
  private:
    static const int32_t TOP_LEFT = 0;
    static const int32_t TOP_RIGHT = 1;
    static const int32_t BOTTOM_LEFT = 2;
    static const int32_t BOTTOM_RIGHT = 3;

    std::array<std::shared_ptr<QuadTreeScenePoint>, 4> _quadTreePoints;

  public:
    QuadTreeNode(std::array<std::shared_ptr<QuadTreeScenePoint>, 4> quadTreePoints)
      : _quadTreePoints(quadTreePoints) {
    }

    const std::shared_ptr<QuadTreeScenePoint>& getTopLeft() const noexcept {
      return _quadTreePoints[TOP_LEFT];
    }

    const std::shared_ptr<QuadTreeScenePoint>& getTopRight() const noexcept {
      return _quadTreePoints[TOP_RIGHT];
    }

    const std::shared_ptr<QuadTreeScenePoint>& getBottomLeft() const noexcept {
      return _quadTreePoints[BOTTOM_LEFT];
    }

    const std::shared_ptr<QuadTreeScenePoint>& getBottomRight() const noexcept {
      return _quadTreePoints[BOTTOM_RIGHT];
    }
  };
}

#endif
