// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/SceneGraph/NrtSceneNode.h>
#include <NovelRT.Interop/SceneGraph/NrtSceneNodeBreadthFirstIterator.h>
#include <NovelRT/NovelRT.h>

#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::SceneGraph;

bool compareNodeWithSet(NrtSceneNodeHandle lhs, NrtSceneNodeSetHandle rhs)
{
    auto left = reinterpret_cast<SceneNode*>(lhs)->shared_from_this();
    auto right = *reinterpret_cast<std::set<std::shared_ptr<SceneNode>>*>(rhs)->begin();

    return left == right;
}

TEST(InteropSceneNodeTest, createHasZeroChildren)
{
    NrtSceneNodeHandle sceneNode = Nrt_SceneNode_Create();
    NrtSceneNodeSetHandle nodeSet = NULL;
    size_t size = 0;

    Nrt_SceneNode_GetChildren(sceneNode, &nodeSet);
    size = Nrt_SceneNodeSet_GetSize(nodeSet);
    ASSERT_EQ(0, size);
}

TEST(InteropSceneNodeTest, createHasZeroParents)
{
    NrtSceneNodeHandle sceneNode = Nrt_SceneNode_Create();
    NrtSceneNodeSetHandle nodeSet = NULL;
    size_t size = 0;

    Nrt_SceneNode_GetParents(sceneNode, &nodeSet);
    size = Nrt_SceneNodeSet_GetSize(nodeSet);
    ASSERT_EQ(0, size);
}

TEST(InteropSceneNodeTest, insertNodeCreatesParentChildRelationship)
{
    NrtSceneNodeHandle parentNode = Nrt_SceneNode_Create();
    NrtSceneNodeHandle childNode = Nrt_SceneNode_Create();
    ASSERT_EQ(1, Nrt_SceneNode_Insert(parentNode, childNode));

    NrtSceneNodeSetHandle parentNodeParents = NULL;
    NrtSceneNodeSetHandle parentNodeChildren = NULL;
    Nrt_SceneNode_GetParents(parentNode, &parentNodeParents);
    Nrt_SceneNode_GetChildren(parentNode, &parentNodeChildren);
    size_t parentSetSize = 0;
    size_t childrenSetSize = 0;
    parentSetSize = Nrt_SceneNodeSet_GetSize(parentNodeParents);
    childrenSetSize = Nrt_SceneNodeSet_GetSize(parentNodeChildren);
    ASSERT_EQ(0, parentSetSize);
    ASSERT_EQ(1, childrenSetSize);

    NrtSceneNodeSetHandle childNodeParents = NULL;
    NrtSceneNodeSetHandle childNodeChildren = NULL;
    Nrt_SceneNode_GetParents(childNode, &childNodeParents);
    Nrt_SceneNode_GetChildren(childNode, &childNodeChildren);
    parentSetSize = Nrt_SceneNodeSet_GetSize(childNodeParents);
    childrenSetSize = Nrt_SceneNodeSet_GetSize(childNodeChildren);

    ASSERT_EQ(1, parentSetSize);
    ASSERT_EQ(0, childrenSetSize);

    NrtSceneNodeHandle returnedFromParent = NULL;
    NrtSceneNodeHandle returnedFromChild = NULL;
    Nrt_SceneNodeSet_GetSceneNodeFromIndex(parentNodeChildren, 0, &returnedFromParent);
    Nrt_SceneNodeSet_GetSceneNodeFromIndex(childNodeParents, 0, &returnedFromChild);
    ASSERT_TRUE(compareNodeWithSet(childNode, parentNodeChildren));
    ASSERT_TRUE(compareNodeWithSet(parentNode, childNodeParents));
}

TEST(InteropSceneNodeTest, insertNodeTwiceReturnsFalse)
{
    NrtSceneNodeHandle parentNode = Nrt_SceneNode_Create();
    NrtSceneNodeHandle childNode = Nrt_SceneNode_Create();
    ASSERT_TRUE(Nrt_SceneNode_Insert(parentNode, childNode));
    ASSERT_FALSE(Nrt_SceneNode_Insert(parentNode, childNode));
}

TEST(InteropSceneNodeTest, removeNodeUpdatesParentChildRelationship)
{
    NrtSceneNodeHandle parentNode = Nrt_SceneNode_Create();
    NrtSceneNodeHandle childNode = Nrt_SceneNode_Create();
    int32_t result = 0;
    result = Nrt_SceneNode_Insert(parentNode, childNode);
    result = Nrt_SceneNode_Remove(parentNode, childNode);
    ASSERT_TRUE(result);

    NrtSceneNodeSetHandle parentNodeParents = NULL;
    NrtSceneNodeSetHandle parentNodeChildren = NULL;
    Nrt_SceneNode_GetParents(parentNode, &parentNodeParents);
    Nrt_SceneNode_GetChildren(parentNode, &parentNodeChildren);
    size_t parentSetSize = 0;
    size_t childrenSetSize = 0;
    parentSetSize = Nrt_SceneNodeSet_GetSize(parentNodeParents);
    childrenSetSize = Nrt_SceneNodeSet_GetSize(parentNodeChildren);
    ASSERT_EQ(0, parentSetSize);
    ASSERT_EQ(0, childrenSetSize);

    NrtSceneNodeSetHandle childNodeParents = NULL;
    NrtSceneNodeSetHandle childNodeChildren = NULL;
    Nrt_SceneNode_GetParents(childNode, &childNodeParents);
    Nrt_SceneNode_GetChildren(childNode, &childNodeChildren);
    parentSetSize = Nrt_SceneNodeSet_GetSize(childNodeParents);
    childrenSetSize = Nrt_SceneNodeSet_GetSize(childNodeChildren);

    ASSERT_EQ(0, parentSetSize);
    ASSERT_EQ(0, childrenSetSize);
}

TEST(InteropSceneNodeTest, removeNodeTwiceReturnsFalse)
{
    NrtSceneNodeHandle parentNode = Nrt_SceneNode_Create();
    NrtSceneNodeHandle childNode = Nrt_SceneNode_Create();
    int32_t result = 0;
    result = Nrt_SceneNode_Insert(parentNode, childNode);
    result = Nrt_SceneNode_Remove(parentNode, childNode);
    result = Nrt_SceneNode_Remove(parentNode, childNode);

    ASSERT_FALSE(result);
}

TEST(InteropSceneNodeTest, unrelatedNodesAreNotAdjacent)
{
    NrtSceneNodeHandle parentNode = Nrt_SceneNode_Create();
    NrtSceneNodeHandle childNode = Nrt_SceneNode_Create();
    ASSERT_FALSE(Nrt_SceneNode_IsAdjacent(parentNode, childNode));
    ASSERT_FALSE(Nrt_SceneNode_IsAdjacent(childNode, parentNode));
}

TEST(InteropSceneNodeTest, parentChildNodesAreAdjacent)
{
    NrtSceneNodeHandle parentNode = Nrt_SceneNode_Create();
    NrtSceneNodeHandle childNode = Nrt_SceneNode_Create();
    Nrt_SceneNode_Insert(parentNode, childNode);
    ASSERT_TRUE(Nrt_SceneNode_IsAdjacent(parentNode, childNode));
    ASSERT_TRUE(Nrt_SceneNode_IsAdjacent(childNode, parentNode));
}

TEST(InteropSceneNodeTest, childNodeIsReachableFromParent)
{
    NrtSceneNodeHandle parentNode = Nrt_SceneNode_Create();
    NrtSceneNodeHandle childNode = Nrt_SceneNode_Create();

    Nrt_SceneNode_Insert(parentNode, childNode);
    ASSERT_TRUE(Nrt_SceneNode_CanReach(parentNode, childNode));
}

NrtSceneNodeHandle childNode = Nrt_SceneNode_Create();

TEST(InteropSceneNodeTest, childNodeIsReachableFromParentBreadthFirst)
{
    NrtSceneNodeHandle parentNode = Nrt_SceneNode_Create();
    Nrt_SceneNode_Insert(parentNode, childNode);

    auto func = [](NrtSceneNodeHandle traversedNode, auto) -> int32_t {
        if (traversedNode == childNode)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    };

    int32_t (*vari)(NrtSceneNodeHandle, void*) = func;

    NrtSceneNodeBreadthFirstIteratorHandle it = nullptr;
    auto res = Nrt_SceneNode_TraverseBreadthFirstWithIterator(parentNode, vari, nullptr, &it);

    ASSERT_EQ(res, NRT_SUCCESS);

    int32_t loopResult = 0;
    int32_t isEqual = 0;
    loopResult = Nrt_SceneNodeBreadthFirstIterator_IsEnd(it);

    while ((isEqual != NRT_TRUE) && (loopResult == NRT_FALSE))
    {
        Nrt_SceneNodeBreadthFirstIterator_Increment(it);
        loopResult = Nrt_SceneNodeBreadthFirstIterator_IsEnd(it);
        isEqual = Nrt_SceneNodeBreadthFirstIterator_RunFunction(it);
    }

    ASSERT_EQ(true, isEqual);

    ASSERT_EQ(Nrt_SceneNode_Destroy(parentNode), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SceneNode_Destroy(childNode), NRT_SUCCESS);
}

TEST(InteropSceneNodeTest, parentNodeIsNotReachableFromChild)
{
    NrtSceneNodeHandle parentNode = Nrt_SceneNode_Create();
    childNode = Nrt_SceneNode_Create();
    Nrt_SceneNode_Insert(parentNode, childNode);
    ASSERT_FALSE(Nrt_SceneNode_CanReach(childNode, parentNode));

    ASSERT_EQ(Nrt_SceneNode_Destroy(childNode), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SceneNode_Destroy(parentNode), NRT_SUCCESS);
}

TEST(InteropSceneNodeTest, nodeIsReachableFromSelf)
{
    NrtSceneNodeHandle parentNode = Nrt_SceneNode_Create();
    ASSERT_TRUE(Nrt_SceneNode_CanReach(parentNode, parentNode));
    ASSERT_EQ(Nrt_SceneNode_Destroy(parentNode), NRT_SUCCESS);
}

// These are now defined here as they needed to be referenced for the lambda functions.
NrtSceneNodeHandle parentNode = Nrt_SceneNode_Create();
int32_t parentSceneNodeHitCount = 0;
int32_t childSceneNodeHitCount = 0;
int32_t otherSceneNodeHitCount = 0;

TEST(InteropSceneNodeTest, breadthFirstTraversalVisitsEachNodeOnceEvenWithCycle)
{
    childNode = Nrt_SceneNode_Create();

    ASSERT_TRUE(Nrt_SceneNode_Insert(parentNode, childNode));
    ASSERT_TRUE(Nrt_SceneNode_Insert(childNode, parentNode));

    auto func = [](NrtSceneNodeHandle traversedNode, auto) -> void {
        if (traversedNode == parentNode)
        {
            parentSceneNodeHitCount++;
        }
        else if (traversedNode == childNode)
        {
            childSceneNodeHitCount++;
        }
        else
        {
            otherSceneNodeHitCount++;
        }
    };

    void (*vari)(NrtSceneNodeHandle, void*) = func;

    auto res = Nrt_SceneNode_TraverseBreadthFirst(parentNode, vari, nullptr);
    ASSERT_EQ(res, NRT_SUCCESS);
    ASSERT_EQ(1, parentSceneNodeHitCount);
    ASSERT_EQ(1, childSceneNodeHitCount);
    ASSERT_EQ(0, otherSceneNodeHitCount);

    ASSERT_EQ(Nrt_SceneNode_Destroy(parentNode), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SceneNode_Destroy(childNode), NRT_SUCCESS);
}

TEST(InteropSceneNodeTest, depthFirstTraversalVisitsEachNodeOnceEvenWithCycle)
{
    parentNode = Nrt_SceneNode_Create();
    childNode = Nrt_SceneNode_Create();
    parentSceneNodeHitCount = 0;
    childSceneNodeHitCount = 0;
    otherSceneNodeHitCount = 0;

    ASSERT_TRUE(Nrt_SceneNode_Insert(parentNode, childNode));
    ASSERT_TRUE(Nrt_SceneNode_Insert(childNode, parentNode));

    auto func = [](NrtSceneNodeHandle traversedNode, auto) -> void {
        if (traversedNode == parentNode)
        {
            parentSceneNodeHitCount++;
        }
        else if (traversedNode == childNode)
        {
            childSceneNodeHitCount++;
        }
        else
        {
            otherSceneNodeHitCount++;
        }
    };

    void (*vari)(NrtSceneNodeHandle, void*) = func;

    auto res = Nrt_SceneNode_TraverseDepthFirst(parentNode, vari, nullptr);
    ASSERT_EQ(res, NRT_SUCCESS);
    ASSERT_EQ(1, parentSceneNodeHitCount);
    ASSERT_EQ(1, childSceneNodeHitCount);
    ASSERT_EQ(0, otherSceneNodeHitCount);

    ASSERT_EQ(Nrt_SceneNode_Destroy(parentNode), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SceneNode_Destroy(childNode), NRT_SUCCESS);
}
