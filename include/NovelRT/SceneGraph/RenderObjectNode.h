// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_RENDEROBJECTNODE_H
#define NOVELRT_RENDEROBJECTNODE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::SceneGraph {
  class RenderObjectNode : public SceneNode {
  private:
    std::shared_ptr<Graphics::RenderObject> _renderObject;

  public:
    RenderObjectNode(std::shared_ptr<Graphics::RenderObject> renderObject) :
      _renderObject(renderObject) {
    }

    const std::shared_ptr<Graphics::RenderObject>& getRenderObject() const {
      return _renderObject;
    }
  };
}

#endif
