// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/SceneGraph/NrtSceneNode.h"
#include "NovelRT.Interop/SceneGraph/NrtSceneNodeBreadthFirstIterator.h"
#include "NovelRT.Interop/NrtInteropUtils.h"

using namespace NovelRT;
using namespace NovelRT::SceneGraph;

bool compareNodeWithSet(NrtSceneNode lhs, NrtSceneNodeSet rhs) {
  auto left = reinterpret_cast<SceneNode*>(lhs)->shared_from_this();
  auto right = *reinterpret_cast<std::set<std::shared_ptr<SceneNode>>*>(rhs)->begin();

  return left == right;
}

TEST(InteropSceneNodeTest, createHasZeroChildren) {
  NrtSceneNode sceneNode = Nrt_SceneNode_create();
  NrtSceneNodeSet nodeSet = NULL;
  size_t size = 0;

  Nrt_SceneNode_getChildren(sceneNode, &nodeSet);
  size = Nrt_SceneNodeSet_getSize(nodeSet);
  ASSERT_EQ(0, size);
}

TEST(InteropSceneNodeTest, createHasZeroParents) {
  NrtSceneNode sceneNode = Nrt_SceneNode_create();
  NrtSceneNodeSet nodeSet = NULL;
  size_t size = 0;

  Nrt_SceneNode_getParents(sceneNode, &nodeSet);
  size = Nrt_SceneNodeSet_getSize(nodeSet);
  ASSERT_EQ(0, size);
}

TEST(InteropSceneNodeTest, insertNodeCreatesParentChildRelationship) {
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  NrtSceneNode childNode = Nrt_SceneNode_create();
  ASSERT_EQ(1, Nrt_SceneNode_insert(parentNode, childNode));

  NrtSceneNodeSet parentNodeParents = NULL;
  NrtSceneNodeSet parentNodeChildren = NULL;
  Nrt_SceneNode_getParents(parentNode, &parentNodeParents);
  Nrt_SceneNode_getChildren(parentNode, &parentNodeChildren);
  size_t parentSetSize = 0;
  size_t childrenSetSize = 0;
  parentSetSize = Nrt_SceneNodeSet_getSize(parentNodeParents);
  childrenSetSize = Nrt_SceneNodeSet_getSize(parentNodeChildren);
  ASSERT_EQ(0, parentSetSize);
  ASSERT_EQ(1, childrenSetSize);

  NrtSceneNodeSet childNodeParents = NULL;
  NrtSceneNodeSet childNodeChildren = NULL;
  Nrt_SceneNode_getParents(childNode, &childNodeParents);
  Nrt_SceneNode_getChildren(childNode, &childNodeChildren);
  parentSetSize = Nrt_SceneNodeSet_getSize(childNodeParents);
  childrenSetSize = Nrt_SceneNodeSet_getSize(childNodeChildren);

  ASSERT_EQ(1, parentSetSize);
  ASSERT_EQ(0, childrenSetSize);

  NrtSceneNode returnedFromParent = NULL;
  NrtSceneNode returnedFromChild = NULL;
  Nrt_SceneNodeSet_getSceneNodeFromIndex(parentNodeChildren, 0, &returnedFromParent);
  Nrt_SceneNodeSet_getSceneNodeFromIndex(childNodeParents, 0, &returnedFromChild);
  ASSERT_TRUE(compareNodeWithSet(childNode, parentNodeChildren));
  ASSERT_TRUE(compareNodeWithSet(parentNode, childNodeParents));
}

TEST(InteropSceneNodeTest, insertNodeTwiceReturnsFalse)
{
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  NrtSceneNode childNode = Nrt_SceneNode_create();
  ASSERT_TRUE(Nrt_SceneNode_insert(parentNode, childNode));
  ASSERT_FALSE(Nrt_SceneNode_insert(parentNode, childNode));
}

TEST(InteropSceneNodeTest, removeNodeUpdatesParentChildRelationship)
{
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  NrtSceneNode childNode = Nrt_SceneNode_create();
  int32_t result = 0;
  result = Nrt_SceneNode_insert(parentNode, childNode);
  result = Nrt_SceneNode_remove(parentNode, childNode);
  ASSERT_TRUE(result);

  NrtSceneNodeSet parentNodeParents = NULL;
  NrtSceneNodeSet parentNodeChildren = NULL;
  Nrt_SceneNode_getParents(parentNode, &parentNodeParents);
  Nrt_SceneNode_getChildren(parentNode, &parentNodeChildren);
  size_t parentSetSize = 0;
  size_t childrenSetSize = 0;
  parentSetSize = Nrt_SceneNodeSet_getSize(parentNodeParents);
  childrenSetSize = Nrt_SceneNodeSet_getSize(parentNodeChildren);
  ASSERT_EQ(0, parentSetSize);
  ASSERT_EQ(0, childrenSetSize);

  NrtSceneNodeSet childNodeParents = NULL;
  NrtSceneNodeSet childNodeChildren = NULL;
  Nrt_SceneNode_getParents(childNode, &childNodeParents);
  Nrt_SceneNode_getChildren(childNode, &childNodeChildren);
  parentSetSize = Nrt_SceneNodeSet_getSize(childNodeParents);
  childrenSetSize = Nrt_SceneNodeSet_getSize(childNodeChildren);

  ASSERT_EQ(0, parentSetSize);
  ASSERT_EQ(0, childrenSetSize);
}

TEST(InteropSceneNodeTest, removeNodeTwiceReturnsFalse)
{
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  NrtSceneNode childNode = Nrt_SceneNode_create();
  int32_t result = 0;
  result = Nrt_SceneNode_insert(parentNode, childNode);
  result = Nrt_SceneNode_remove(parentNode, childNode);
  result = Nrt_SceneNode_remove(parentNode, childNode);

  ASSERT_FALSE(result);
}

TEST(InteropSceneNodeTest, unrelatedNodesAreNotAdjacent) {
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  NrtSceneNode childNode = Nrt_SceneNode_create();
  ASSERT_FALSE(Nrt_SceneNode_isAdjacent(parentNode, childNode));
  ASSERT_FALSE(Nrt_SceneNode_isAdjacent(childNode, parentNode));
}

TEST(InteropSceneNodeTest, parentChildNodesAreAdjacent) {
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  NrtSceneNode childNode = Nrt_SceneNode_create();
  Nrt_SceneNode_insert(parentNode, childNode);
  ASSERT_TRUE(Nrt_SceneNode_isAdjacent(parentNode, childNode));
  ASSERT_TRUE(Nrt_SceneNode_isAdjacent(childNode, parentNode));
}

TEST(InteropSceneNodeTest, childNodeIsReachableFromParent) {
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  NrtSceneNode childNode = Nrt_SceneNode_create();

  Nrt_SceneNode_insert(parentNode, childNode);
  ASSERT_TRUE(Nrt_SceneNode_canReach(parentNode, childNode));
}

NrtSceneNode childNode = Nrt_SceneNode_create();

TEST(InteropSceneNodeTest, childNodeIsReachableFromParentBreadthFirst) {
  typedef int32_t(*wrapperFunction)(NrtSceneNode);

  NrtSceneNode parentNode = Nrt_SceneNode_create();
  Nrt_SceneNode_insert(parentNode, childNode);

  auto func = [](NrtSceneNode traversedNode) -> int32_t {
    if(traversedNode == childNode) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  };

  int32_t(*vari)(NrtSceneNode) = func;

  NrtSceneNodeBreadthFirstIterator it = nullptr;
  auto res = Nrt_SceneNode_traverseBreadthFirstWithIterator(parentNode, vari, &it);

  ASSERT_EQ(res, NRT_SUCCESS);

  int32_t loopResult = 0;
  int32_t isEqual = 0;
  loopResult = Nrt_SceneNodeBreadthFirstIterator_isEnd(it);

  while ((isEqual != NRT_TRUE) && (loopResult == NRT_FALSE)) {
    Nrt_SceneNodeBreadthFirstIterator_increment(it);
    loopResult = Nrt_SceneNodeBreadthFirstIterator_isEnd(it);
    isEqual = Nrt_SceneNodeBreadthFirstIterator_runFunction(it);
  }

  ASSERT_EQ(true, isEqual);

  ASSERT_EQ(Nrt_SceneNode_delete(parentNode), NRT_SUCCESS);
  ASSERT_EQ(Nrt_SceneNode_delete(childNode), NRT_SUCCESS);
}

TEST(InteropSceneNodeTest, parentNodeIsNotReachableFromChild) {
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  childNode = Nrt_SceneNode_create();
  Nrt_SceneNode_insert(parentNode, childNode);
  ASSERT_FALSE(Nrt_SceneNode_canReach(childNode, parentNode));

  ASSERT_EQ(Nrt_SceneNode_delete(childNode), NRT_SUCCESS);
  ASSERT_EQ(Nrt_SceneNode_delete(parentNode), NRT_SUCCESS);
}

TEST(InteropSceneNodeTest, nodeIsReachableFromSelf) {
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  ASSERT_TRUE(Nrt_SceneNode_canReach(parentNode, parentNode));
  ASSERT_EQ(Nrt_SceneNode_delete(parentNode), NRT_SUCCESS);
}

//These are now defined here as they needed to be referenced for the lambda functions.
NrtSceneNode parentNode = Nrt_SceneNode_create();
int32_t parentSceneNodeHitCount = 0;
int32_t childSceneNodeHitCount = 0;
int32_t otherSceneNodeHitCount = 0;

TEST(InteropSceneNodeTest, breadthFirstTraversalVisitsEachNodeOnceEvenWithCycle) {
  childNode = Nrt_SceneNode_create();

  ASSERT_TRUE(Nrt_SceneNode_insert(parentNode, childNode));
  ASSERT_TRUE(Nrt_SceneNode_insert(childNode, parentNode));

  auto func = [](NrtSceneNode traversedNode) -> void {
    if (traversedNode == parentNode) {
      parentSceneNodeHitCount++;
     }
     else if (traversedNode == childNode) {
       childSceneNodeHitCount++;
     }
     else {
       otherSceneNodeHitCount++;
     }
  };

  void(*vari)(NrtSceneNode) = func;

  auto res = Nrt_SceneNode_traverseBreadthFirst(parentNode, vari);
  ASSERT_EQ(res, NRT_SUCCESS);
  ASSERT_EQ(1, parentSceneNodeHitCount);
  ASSERT_EQ(1, childSceneNodeHitCount);
  ASSERT_EQ(0, otherSceneNodeHitCount);

  ASSERT_EQ(Nrt_SceneNode_delete(parentNode), NRT_SUCCESS);
  ASSERT_EQ(Nrt_SceneNode_delete(childNode), NRT_SUCCESS);
}

 TEST(InteropSceneNodeTest, depthFirstTraversalVisitsEachNodeOnceEvenWithCycle) {
  parentNode = Nrt_SceneNode_create();
  childNode = Nrt_SceneNode_create();
  parentSceneNodeHitCount = 0;
  childSceneNodeHitCount = 0;
  otherSceneNodeHitCount = 0;

  ASSERT_TRUE(Nrt_SceneNode_insert(parentNode, childNode));
  ASSERT_TRUE(Nrt_SceneNode_insert(childNode, parentNode));

  auto func = [](NrtSceneNode traversedNode) -> void {
    if (traversedNode == parentNode) {
      parentSceneNodeHitCount++;
     }
     else if (traversedNode == childNode) {
       childSceneNodeHitCount++;
     }
     else {
       otherSceneNodeHitCount++;
     }
  };

  void(*vari)(NrtSceneNode) = func;

  auto res = Nrt_SceneNode_traverseDepthFirst(parentNode, vari);
  ASSERT_EQ(res, NRT_SUCCESS);
  ASSERT_EQ(1, parentSceneNodeHitCount);
  ASSERT_EQ(1, childSceneNodeHitCount);
  ASSERT_EQ(0, otherSceneNodeHitCount);

  ASSERT_EQ(Nrt_SceneNode_delete(parentNode), NRT_SUCCESS);
  ASSERT_EQ(Nrt_SceneNode_delete(childNode), NRT_SUCCESS);
}
