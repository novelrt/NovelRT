// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_SCENEGRAPH_RENDEROBJECTNODE_H
#define NOVELRT_SCENEGRAPH_RENDEROBJECTNODE_H

#ifndef NOVELRT_SCENEGRAPH_H
#error NovelRT does not support including types explicitly by default. Please include SceneGraph.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::SceneGraph
{
    class RenderObjectNode : public SceneNode
    {
    private:
        std::shared_ptr<Graphics::RenderObject> _renderObject;

    public:
        RenderObjectNode(std::shared_ptr<Graphics::RenderObject> renderObject) noexcept : _renderObject(renderObject)
        {
        }

        const std::shared_ptr<Graphics::RenderObject>& getRenderObject() const noexcept
        {
            return _renderObject;
        }
    };
}

#endif
