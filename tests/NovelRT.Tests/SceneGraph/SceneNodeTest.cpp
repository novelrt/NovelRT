// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::SceneGraph;

TEST(SceneNodeTest, createHasZeroChildren)
{
    auto sceneNode = std::make_shared<SceneNode>();
    ASSERT_EQ(0, sceneNode->getChildren().size());
}

TEST(SceneNodeTest, createHasZeroParents)
{
    auto sceneNode = std::make_shared<SceneNode>();
    ASSERT_EQ(0, sceneNode->getParents().size());
}

TEST(SceneNodeTest, insertNodeCreatesParentChildRelationship)
{
    auto parentSceneNode = std::make_shared<SceneNode>();
    auto childSceneNode = std::make_shared<SceneNode>();

    ASSERT_EQ(true, parentSceneNode->insert(childSceneNode));

    ASSERT_EQ(0, parentSceneNode->getParents().size());
    ASSERT_EQ(1, parentSceneNode->getChildren().size());

    ASSERT_EQ(1, childSceneNode->getParents().size());
    ASSERT_EQ(0, childSceneNode->getChildren().size());

    ASSERT_EQ(childSceneNode, *parentSceneNode->getChildren().begin());
    ASSERT_EQ(parentSceneNode, *childSceneNode->getParents().begin());
}

TEST(SceneNodeTest, insertNodeTwiceReturnsFalse)
{
    auto parentSceneNode = std::make_shared<SceneNode>();
    auto childSceneNode = std::make_shared<SceneNode>();

    parentSceneNode->insert(childSceneNode);

    ASSERT_EQ(false, parentSceneNode->insert(childSceneNode));
}

TEST(SceneNodeTest, removeNodeUpdatesParentChildRelationship)
{
    auto parentSceneNode = std::make_shared<SceneNode>();
    auto childSceneNode = std::make_shared<SceneNode>();

    parentSceneNode->insert(childSceneNode);

    ASSERT_EQ(true, parentSceneNode->remove(childSceneNode));

    ASSERT_EQ(0, parentSceneNode->getParents().size());
    ASSERT_EQ(0, parentSceneNode->getChildren().size());

    ASSERT_EQ(0, childSceneNode->getParents().size());
    ASSERT_EQ(0, childSceneNode->getChildren().size());
}

TEST(SceneNodeTest, removeNodeTwiceReturnsFalse)
{
    auto parentSceneNode = std::make_shared<SceneNode>();
    auto childSceneNode = std::make_shared<SceneNode>();

    parentSceneNode->insert(childSceneNode);
    parentSceneNode->remove(childSceneNode);

    ASSERT_EQ(false, parentSceneNode->remove(childSceneNode));
}

TEST(SceneNodeTest, unrelatedNodesAreNotAdjacent)
{
    auto parentSceneNode = std::make_shared<SceneNode>();
    auto childSceneNode = std::make_shared<SceneNode>();

    ASSERT_EQ(false, parentSceneNode->isAdjacent(childSceneNode));
    ASSERT_EQ(false, childSceneNode->isAdjacent(parentSceneNode));
}

TEST(SceneNodeTest, parentChildNodesAreAdjacent)
{
    auto parentSceneNode = std::make_shared<SceneNode>();
    auto childSceneNode = std::make_shared<SceneNode>();

    parentSceneNode->insert(childSceneNode);

    ASSERT_EQ(true, parentSceneNode->isAdjacent(childSceneNode));
    ASSERT_EQ(true, childSceneNode->isAdjacent(parentSceneNode));
}

TEST(SceneNodeTest, childNodeIsReachableFromParent)
{
    auto parentSceneNode = std::make_shared<SceneNode>();
    auto childSceneNode = std::make_shared<SceneNode>();

    parentSceneNode->insert(childSceneNode);

    ASSERT_EQ(true, parentSceneNode->canReach(childSceneNode));
}

TEST(SceneNodeTest, childNodeIsReachableFromParentBreadthFirst)
{
    auto parentSceneNode = std::make_shared<SceneNode>();
    auto childSceneNode = std::make_shared<SceneNode>();

    parentSceneNode->insert(childSceneNode);

    auto result = parentSceneNode->traverseBreadthFirst<bool>(
        [&](const std::shared_ptr<SceneNode>& traversedNode) { return traversedNode == childSceneNode; });

    while ((*result != true) && !result.isEnd())
    {
        result++;
    }

    ASSERT_EQ(true, *result);
}

TEST(SceneNodeTest, parentNodeIsNotReachableFromChild)
{
    auto parentSceneNode = std::make_shared<SceneNode>();
    auto childSceneNode = std::make_shared<SceneNode>();

    parentSceneNode->insert(childSceneNode);

    ASSERT_EQ(false, childSceneNode->canReach(parentSceneNode));
}

TEST(SceneNodeTest, nodeIsReachableFromSelf)
{
    auto sceneNode = std::make_shared<SceneNode>();
    ASSERT_EQ(true, sceneNode->canReach(sceneNode));
}

TEST(SceneNodeTest, breadthFirstTraversalVisitsEachNodeOnceEvenWithCycle)
{
    auto parentSceneNode = std::make_shared<SceneNode>();
    auto childSceneNode = std::make_shared<SceneNode>();

    parentSceneNode->insert(childSceneNode);
    childSceneNode->insert(parentSceneNode);

    int32_t parentSceneNodeHitCount = 0;
    int32_t childSceneNodeHitCount = 0;
    int32_t otherSceneNodeHitCount = 0;

    parentSceneNode->traverseBreadthFirst([&](const std::shared_ptr<SceneNode>& traversedNode) {
        if (traversedNode == parentSceneNode)
        {
            parentSceneNodeHitCount++;
        }
        else if (traversedNode == childSceneNode)
        {
            childSceneNodeHitCount++;
        }
        else
        {
            otherSceneNodeHitCount++;
        }
    });

    ASSERT_EQ(1, parentSceneNodeHitCount);
    ASSERT_EQ(1, childSceneNodeHitCount);
    ASSERT_EQ(0, otherSceneNodeHitCount);
}

TEST(SceneNodeTest, depthFirstTraversalVisitsEachNodeOnceEvenWithCycle)
{
    auto parentSceneNode = std::make_shared<SceneNode>();
    auto childSceneNode = std::make_shared<SceneNode>();

    parentSceneNode->insert(childSceneNode);
    childSceneNode->insert(parentSceneNode);

    int32_t parentSceneNodeHitCount = 0;
    int32_t childSceneNodeHitCount = 0;
    int32_t otherSceneNodeHitCount = 0;

    parentSceneNode->traverseDepthFirst([&](const std::shared_ptr<SceneNode>& traversedNode) {
        if (traversedNode == parentSceneNode)
        {
            parentSceneNodeHitCount++;
        }
        else if (traversedNode == childSceneNode)
        {
            childSceneNodeHitCount++;
        }
        else
        {
            otherSceneNodeHitCount++;
        }
    });

    ASSERT_EQ(1, parentSceneNodeHitCount);
    ASSERT_EQ(1, childSceneNodeHitCount);
    ASSERT_EQ(0, otherSceneNodeHitCount);
}
