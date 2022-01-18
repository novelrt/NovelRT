// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_SCENEGRAPH_H
#define NOVELRT_SCENEGRAPH_H

// dependencies
#include "../Maths/Maths.h"
#include <array>
#include <memory>
#include <queue>
#include <set>
#include <stack>

/**
 * @brief Provides Scene Graph features for a variety of purposes, such as rendering or input.
 */
namespace NovelRT::SceneGraph
{
    class QuadTreeNode;
    class QuadTreeScenePoint;
    class RenderObjectNode;
    class Scene;
    class SceneNode;
}

// clang-format off

#include "SceneNode.h"
#include "QuadTreeNode.h"
#include "QuadTreeScenePoint.h"
#include "RenderObjectNode.h"
#include "Scene.h"

// clang-format on

#endif // !NOVELRT_SCENEGRAPH_H
