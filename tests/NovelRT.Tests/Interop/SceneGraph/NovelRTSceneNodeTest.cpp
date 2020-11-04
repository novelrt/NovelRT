// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/SceneGraph/NovelRTSceneNode.h"
#include "NovelRT.Interop/SceneGraph/NovelRTSceneNodeBreadthFirstIterator.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"

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

  Nrt_SceneNode_getChildren(sceneNode, &nodeSet, nullptr);
  Nrt_SceneNodeSet_getSize(nodeSet, &size, nullptr);
  ASSERT_EQ(0, size);
}

TEST(InteropSceneNodeTest, createHasZeroParents) {
  NrtSceneNode sceneNode = Nrt_SceneNode_create();
  NrtSceneNodeSet nodeSet = NULL;
  size_t size = 0;

  Nrt_SceneNode_getParents(sceneNode, &nodeSet, nullptr);
  Nrt_SceneNodeSet_getSize(nodeSet, &size, nullptr);
  ASSERT_EQ(0, size);
}

TEST(InteropSceneNodeTest, insertNodeCreatesParentChildRelationship) {
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  NrtSceneNode childNode = Nrt_SceneNode_create();
  int32_t result = 0;
  ASSERT_EQ(0, Nrt_SceneNode_insert(parentNode, childNode, &result, nullptr));

  NrtSceneNodeSet parentNodeParents = NULL;
  NrtSceneNodeSet parentNodeChildren = NULL;
  Nrt_SceneNode_getParents(parentNode, &parentNodeParents, nullptr);
  Nrt_SceneNode_getChildren(parentNode, &parentNodeChildren, nullptr);
  size_t parentSetSize = 0;
  size_t childrenSetSize = 0;
  Nrt_SceneNodeSet_getSize(parentNodeParents, &parentSetSize, nullptr);
  Nrt_SceneNodeSet_getSize(parentNodeChildren, &childrenSetSize, nullptr);
  ASSERT_EQ(0, parentSetSize);
  ASSERT_EQ(1, childrenSetSize);

  NrtSceneNodeSet childNodeParents = NULL;
  NrtSceneNodeSet childNodeChildren = NULL;
  Nrt_SceneNode_getParents(childNode, &childNodeParents, nullptr);
  Nrt_SceneNode_getChildren(childNode, &childNodeChildren, nullptr);
  Nrt_SceneNodeSet_getSize(childNodeParents, &parentSetSize, nullptr);
  Nrt_SceneNodeSet_getSize(childNodeChildren, &childrenSetSize, nullptr);

  ASSERT_EQ(1, parentSetSize);
  ASSERT_EQ(0, childrenSetSize);

  NrtSceneNode returnedFromParent = NULL;
  NrtSceneNode returnedFromChild = NULL;
  Nrt_SceneNodeSet_getSceneNodeFromIndex(parentNodeChildren, 0, &returnedFromParent, nullptr);
  Nrt_SceneNodeSet_getSceneNodeFromIndex(childNodeParents, 0, &returnedFromChild, nullptr);
  ASSERT_TRUE(compareNodeWithSet(childNode, parentNodeChildren));
  ASSERT_TRUE(compareNodeWithSet(parentNode, childNodeParents));
}

TEST(InteropSceneNodeTest, insertNodeTwiceReturnsFalse)
{
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  NrtSceneNode childNode = Nrt_SceneNode_create();
  int32_t result = 0;
  Nrt_SceneNode_insert(parentNode, childNode, &result, nullptr);
  ASSERT_TRUE(result);
  Nrt_SceneNode_insert(parentNode, childNode, &result, nullptr);
  ASSERT_FALSE(result);
}

TEST(InteropSceneNodeTest, removeNodeUpdatesParentChildRelationship)
{
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  NrtSceneNode childNode = Nrt_SceneNode_create();
  int32_t result = 0;
  
  Nrt_SceneNode_insert(parentNode, childNode, &result, nullptr);

  Nrt_SceneNode_remove(parentNode, childNode, &result, nullptr);
  ASSERT_TRUE(result);

  NrtSceneNodeSet parentNodeParents = NULL;
  NrtSceneNodeSet parentNodeChildren = NULL;
  Nrt_SceneNode_getParents(parentNode, &parentNodeParents, nullptr);
  Nrt_SceneNode_getChildren(parentNode, &parentNodeChildren, nullptr);
  size_t parentSetSize = 0;
  size_t childrenSetSize = 0;
  Nrt_SceneNodeSet_getSize(parentNodeParents, &parentSetSize, nullptr);
  Nrt_SceneNodeSet_getSize(parentNodeChildren, &childrenSetSize, nullptr);
  ASSERT_EQ(0, parentSetSize);
  ASSERT_EQ(0, childrenSetSize);

  NrtSceneNodeSet childNodeParents = NULL;
  NrtSceneNodeSet childNodeChildren = NULL;
  Nrt_SceneNode_getParents(childNode, &childNodeParents, nullptr);
  Nrt_SceneNode_getChildren(childNode, &childNodeChildren, nullptr);
  Nrt_SceneNodeSet_getSize(childNodeParents, &parentSetSize, nullptr);
  Nrt_SceneNodeSet_getSize(childNodeChildren, &childrenSetSize, nullptr);

  ASSERT_EQ(0, parentSetSize);
  ASSERT_EQ(0, childrenSetSize);
}

TEST(InteropSceneNodeTest, removeNodeTwiceReturnsFalse)
{
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  NrtSceneNode childNode = Nrt_SceneNode_create();
  int32_t result = 0;
  Nrt_SceneNode_insert(parentNode, childNode, &result, nullptr);
  Nrt_SceneNode_remove(parentNode, childNode, &result, nullptr);
  
  Nrt_SceneNode_remove(parentNode, childNode, &result, nullptr);

  ASSERT_FALSE(result);
}

TEST(InteropSceneNodeTest, unrelatedNodesAreNotAdjacent) {
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  NrtSceneNode childNode = Nrt_SceneNode_create();
  int32_t result = 0;

  Nrt_SceneNode_isAdjacent(parentNode, childNode, &result, nullptr);
  ASSERT_FALSE(result);
  Nrt_SceneNode_isAdjacent(childNode, parentNode, &result, nullptr);
  ASSERT_FALSE(result);
}

TEST(InteropSceneNodeTest, parentChildNodesAreAdjacent) {
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  NrtSceneNode childNode = Nrt_SceneNode_create();
  int32_t result = 0;
  Nrt_SceneNode_insert(parentNode, childNode, &result, nullptr);

  Nrt_SceneNode_isAdjacent(parentNode, childNode, &result, nullptr);
  ASSERT_TRUE(result);
  Nrt_SceneNode_isAdjacent(childNode, parentNode, &result, nullptr);
  ASSERT_TRUE(result);
}

TEST(InteropSceneNodeTest, childNodeIsReachableFromParent) {
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  NrtSceneNode childNode = Nrt_SceneNode_create();
  int32_t result = 0;

  Nrt_SceneNode_insert(parentNode, childNode, &result, nullptr);

  Nrt_SceneNode_canReach(parentNode, childNode, &result, nullptr);
  ASSERT_TRUE(result);
}

NrtSceneNode childNode = Nrt_SceneNode_create();

TEST(InteropSceneNodeTest, childNodeIsReachableFromParentBreadthFirst) {
  typedef int32_t(*wrapperFunction)(NrtSceneNode);
  
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  
  int32_t result = 0;

  Nrt_SceneNode_insert(parentNode, childNode, &result, nullptr);

  auto func = [](NrtSceneNode traversedNode) -> int32_t {
    if(traversedNode == childNode) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  };

  int32_t(*vari)(NrtSceneNode) = func;

  NrtSceneNodeBreadthFirstIterator it = nullptr;
  auto res = Nrt_SceneNode_traverseBreadthFirstWithIterator(parentNode, vari, &it, nullptr);

  ASSERT_EQ(res, NRT_SUCCESS);

  int32_t loopResult = 0;
  int32_t isEqual = 0;
  res = Nrt_SceneNodeBreadthFirstIterator_isEnd(it, &loopResult, nullptr);
  ASSERT_EQ(res, NRT_SUCCESS);

  while ((isEqual != NRT_TRUE) && (loopResult == NRT_FALSE)) {
    Nrt_SceneNodeBreadthFirstIterator_increment(it, nullptr);
    Nrt_SceneNodeBreadthFirstIterator_isEnd(it, &loopResult, nullptr);
    Nrt_SceneNodeBreadthFirstIterator_runFunction(it, &isEqual, nullptr);
  }

  ASSERT_EQ(true, isEqual);
  
  ASSERT_EQ(Nrt_SceneNode_delete(parentNode, nullptr), NRT_SUCCESS);
  ASSERT_EQ(Nrt_SceneNode_delete(childNode, nullptr), NRT_SUCCESS);
}

TEST(InteropSceneNodeTest, parentNodeIsNotReachableFromChild) {
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  childNode = Nrt_SceneNode_create();
  int32_t result = 0;

  Nrt_SceneNode_insert(parentNode, childNode, &result, nullptr);

  Nrt_SceneNode_canReach(childNode, parentNode, &result, nullptr);
  
  ASSERT_EQ(false, result);
  ASSERT_EQ(Nrt_SceneNode_delete(childNode, nullptr), NRT_SUCCESS);
  ASSERT_EQ(Nrt_SceneNode_delete(parentNode, nullptr), NRT_SUCCESS);
}

TEST(InteropSceneNodeTest, nodeIsReachableFromSelf) {
  NrtSceneNode parentNode = Nrt_SceneNode_create();
  int32_t result = 0;

  Nrt_SceneNode_canReach(parentNode, parentNode, &result, nullptr);
  
  ASSERT_EQ(true, result);
  ASSERT_EQ(Nrt_SceneNode_delete(parentNode, nullptr), NRT_SUCCESS);
}

//These are now defined here as they needed to be referenced for the lambda functions.
NrtSceneNode parentNode = Nrt_SceneNode_create();
int32_t parentSceneNodeHitCount = 0;
int32_t childSceneNodeHitCount = 0;
int32_t otherSceneNodeHitCount = 0;

TEST(InteropSceneNodeTest, breadthFirstTraversalVisitsEachNodeOnceEvenWithCycle) {  
  childNode = Nrt_SceneNode_create();
  int32_t result = 0;

  ASSERT_EQ(Nrt_SceneNode_insert(parentNode, childNode, &result, nullptr), NRT_SUCCESS);
  ASSERT_EQ(result, true);
  ASSERT_EQ(Nrt_SceneNode_insert(childNode, parentNode, &result, nullptr), NRT_SUCCESS);
  ASSERT_EQ(result, true);
  
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

  auto res = Nrt_SceneNode_traverseBreadthFirst(parentNode, vari, nullptr);
  ASSERT_EQ(res, NRT_SUCCESS);
  ASSERT_EQ(1, parentSceneNodeHitCount);
  ASSERT_EQ(1, childSceneNodeHitCount);
  ASSERT_EQ(0, otherSceneNodeHitCount);  

  ASSERT_EQ(Nrt_SceneNode_delete(parentNode, nullptr), NRT_SUCCESS);
  ASSERT_EQ(Nrt_SceneNode_delete(childNode, nullptr), NRT_SUCCESS);
}

 TEST(InteropSceneNodeTest, depthFirstTraversalVisitsEachNodeOnceEvenWithCycle) {  
  parentNode = Nrt_SceneNode_create();
  childNode = Nrt_SceneNode_create();
  int32_t result = 0;
  parentSceneNodeHitCount = 0;
  childSceneNodeHitCount = 0;
  otherSceneNodeHitCount = 0;

  ASSERT_EQ(Nrt_SceneNode_insert(parentNode, childNode, &result, nullptr), NRT_SUCCESS);
  ASSERT_EQ(result, true);
  ASSERT_EQ(Nrt_SceneNode_insert(childNode, parentNode, &result, nullptr), NRT_SUCCESS);
  ASSERT_EQ(result, true);
  
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

  auto res = Nrt_SceneNode_traverseDepthFirst(parentNode, vari, nullptr);
  ASSERT_EQ(res, NRT_SUCCESS);
  ASSERT_EQ(1, parentSceneNodeHitCount);
  ASSERT_EQ(1, childSceneNodeHitCount);
  ASSERT_EQ(0, otherSceneNodeHitCount);  

  ASSERT_EQ(Nrt_SceneNode_delete(parentNode, nullptr), NRT_SUCCESS);
  ASSERT_EQ(Nrt_SceneNode_delete(childNode, nullptr), NRT_SUCCESS);
}

