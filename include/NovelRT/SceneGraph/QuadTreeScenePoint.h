// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_SCENEGRAPH_QUADTREESCENEPOINT_H
#define NOVELRT_SCENEGRAPH_QUADTREESCENEPOINT_H

#ifndef NOVELRT_SCENEGRAPH_H
#error NovelRT does not support including types explicitly by default. Please include SceneGraph.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::SceneGraph
{
    class QuadTreeScenePoint : public Maths::QuadTreePoint
    {
    private:
        std::shared_ptr<SceneNode> _sceneNode;

    public:
        QuadTreeScenePoint(Maths::GeoVector2F position, std::shared_ptr<SceneNode> sceneNode) noexcept
            : Maths::QuadTreePoint(position), _sceneNode(sceneNode)
        {
        }

        QuadTreeScenePoint(float x, float y, std::shared_ptr<SceneNode> sceneNode) noexcept
            : Maths::QuadTreePoint(x, y), _sceneNode(sceneNode)
        {
        }

        const std::shared_ptr<SceneNode>& getSceneNode() const noexcept
        {
            return _sceneNode;
        }
    };
}

#endif
