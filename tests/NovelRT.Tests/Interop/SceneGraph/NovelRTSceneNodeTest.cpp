// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/SceneGraph/NovelRTSceneNode.h"
#include "NovelRT.Interop/SceneGraph/NovelRTSceneNodeBreadthFirstIterator.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"

using namespace NovelRT;
using namespace NovelRT::SceneGraph;

bool compareNodeWithSet(NovelRTSceneNode lhs, NovelRTSceneNodeSet rhs) {
  auto left = reinterpret_cast<SceneNode*>(lhs)->shared_from_this();
  auto right = *reinterpret_cast<std::set<std::shared_ptr<SceneNode>>*>(rhs)->begin();

  return left == right;
}



TEST(InteropSceneNodeTest, createHasZeroChildren) {
  NovelRTSceneNode sceneNode = NovelRT_SceneNode_create();
  NovelRTSceneNodeSet nodeSet = NULL;
  size_t size = 0;

  NovelRT_SceneNode_getChildren(sceneNode, &nodeSet, nullptr);
  NovelRT_SceneNodeSet_getSize(nodeSet, &size, nullptr);
  ASSERT_EQ(0, size);
}

TEST(InteropSceneNodeTest, createHasZeroParents) {
  NovelRTSceneNode sceneNode = NovelRT_SceneNode_create();
  NovelRTSceneNodeSet nodeSet = NULL;
  size_t size = 0;

  NovelRT_SceneNode_getParents(sceneNode, &nodeSet, nullptr);
  NovelRT_SceneNodeSet_getSize(nodeSet, &size, nullptr);
  ASSERT_EQ(0, size);
}

TEST(InteropSceneNodeTest, insertNodeCreatesParentChildRelationship) {
  NovelRTSceneNode parentNode = NovelRT_SceneNode_create();
  NovelRTSceneNode childNode = NovelRT_SceneNode_create();
  int32_t result = 0;
  ASSERT_EQ(0, NovelRT_SceneNode_insert(parentNode, childNode, &result, nullptr));

  NovelRTSceneNodeSet parentNodeParents = NULL;
  NovelRTSceneNodeSet parentNodeChildren = NULL;
  NovelRT_SceneNode_getParents(parentNode, &parentNodeParents, nullptr);
  NovelRT_SceneNode_getChildren(parentNode, &parentNodeChildren, nullptr);
  size_t parentSetSize = 0;
  size_t childrenSetSize = 0;
  NovelRT_SceneNodeSet_getSize(parentNodeParents, &parentSetSize, nullptr);
  NovelRT_SceneNodeSet_getSize(parentNodeChildren, &childrenSetSize, nullptr);
  ASSERT_EQ(0, parentSetSize);
  ASSERT_EQ(1, childrenSetSize);

  NovelRTSceneNodeSet childNodeParents = NULL;
  NovelRTSceneNodeSet childNodeChildren = NULL;
  NovelRT_SceneNode_getParents(childNode, &childNodeParents, nullptr);
  NovelRT_SceneNode_getChildren(childNode, &childNodeChildren, nullptr);
  NovelRT_SceneNodeSet_getSize(childNodeParents, &parentSetSize, nullptr);
  NovelRT_SceneNodeSet_getSize(childNodeChildren, &childrenSetSize, nullptr);

  ASSERT_EQ(1, parentSetSize);
  ASSERT_EQ(0, childrenSetSize);

  NovelRTSceneNode returnedFromParent = NULL;
  NovelRTSceneNode returnedFromChild = NULL;
  NovelRT_SceneNodeSet_getSceneNodeFromIndex(parentNodeChildren, 0, &returnedFromParent, nullptr);
  NovelRT_SceneNodeSet_getSceneNodeFromIndex(childNodeParents, 0, &returnedFromChild, nullptr);
  ASSERT_TRUE(compareNodeWithSet(childNode, parentNodeChildren));
  ASSERT_TRUE(compareNodeWithSet(parentNode, childNodeParents));
}

TEST(InteropSceneNodeTest, insertNodeTwiceReturnsFalse)
{
  NovelRTSceneNode parentNode = NovelRT_SceneNode_create();
  NovelRTSceneNode childNode = NovelRT_SceneNode_create();
  int32_t result = 0;
  NovelRT_SceneNode_insert(parentNode, childNode, &result, nullptr);
  ASSERT_TRUE(result);
  NovelRT_SceneNode_insert(parentNode, childNode, &result, nullptr);
  ASSERT_FALSE(result);
}

TEST(InteropSceneNodeTest, removeNodeUpdatesParentChildRelationship)
{
  NovelRTSceneNode parentNode = NovelRT_SceneNode_create();
  NovelRTSceneNode childNode = NovelRT_SceneNode_create();
  int32_t result = 0;
  
  NovelRT_SceneNode_insert(parentNode, childNode, &result, nullptr);

  NovelRT_SceneNode_remove(parentNode, childNode, &result, nullptr);
  ASSERT_TRUE(result);

  NovelRTSceneNodeSet parentNodeParents = NULL;
  NovelRTSceneNodeSet parentNodeChildren = NULL;
  NovelRT_SceneNode_getParents(parentNode, &parentNodeParents, nullptr);
  NovelRT_SceneNode_getChildren(parentNode, &parentNodeChildren, nullptr);
  size_t parentSetSize = 0;
  size_t childrenSetSize = 0;
  NovelRT_SceneNodeSet_getSize(parentNodeParents, &parentSetSize, nullptr);
  NovelRT_SceneNodeSet_getSize(parentNodeChildren, &childrenSetSize, nullptr);
  ASSERT_EQ(0, parentSetSize);
  ASSERT_EQ(0, childrenSetSize);

  NovelRTSceneNodeSet childNodeParents = NULL;
  NovelRTSceneNodeSet childNodeChildren = NULL;
  NovelRT_SceneNode_getParents(childNode, &childNodeParents, nullptr);
  NovelRT_SceneNode_getChildren(childNode, &childNodeChildren, nullptr);
  NovelRT_SceneNodeSet_getSize(childNodeParents, &parentSetSize, nullptr);
  NovelRT_SceneNodeSet_getSize(childNodeChildren, &childrenSetSize, nullptr);

  ASSERT_EQ(0, parentSetSize);
  ASSERT_EQ(0, childrenSetSize);
}

TEST(InteropSceneNodeTest, removeNodeTwiceReturnsFalse)
{
  NovelRTSceneNode parentNode = NovelRT_SceneNode_create();
  NovelRTSceneNode childNode = NovelRT_SceneNode_create();
  int32_t result = 0;
  NovelRT_SceneNode_insert(parentNode, childNode, &result, nullptr);
  NovelRT_SceneNode_remove(parentNode, childNode, &result, nullptr);
  
  NovelRT_SceneNode_remove(parentNode, childNode, &result, nullptr);

  ASSERT_FALSE(result);
}

TEST(InteropSceneNodeTest, unrelatedNodesAreNotAdjacent) {
  NovelRTSceneNode parentNode = NovelRT_SceneNode_create();
  NovelRTSceneNode childNode = NovelRT_SceneNode_create();
  int32_t result = 0;

  NovelRT_SceneNode_isAdjacent(parentNode, childNode, &result, nullptr);
  ASSERT_FALSE(result);
  NovelRT_SceneNode_isAdjacent(childNode, parentNode, &result, nullptr);
  ASSERT_FALSE(result);
}

TEST(InteropSceneNodeTest, parentChildNodesAreAdjacent) {
  NovelRTSceneNode parentNode = NovelRT_SceneNode_create();
  NovelRTSceneNode childNode = NovelRT_SceneNode_create();
  int32_t result = 0;
  NovelRT_SceneNode_insert(parentNode, childNode, &result, nullptr);

  NovelRT_SceneNode_isAdjacent(parentNode, childNode, &result, nullptr);
  ASSERT_TRUE(result);
  NovelRT_SceneNode_isAdjacent(childNode, parentNode, &result, nullptr);
  ASSERT_TRUE(result);
}

TEST(InteropSceneNodeTest, childNodeIsReachableFromParent) {
  NovelRTSceneNode parentNode = NovelRT_SceneNode_create();
  NovelRTSceneNode childNode = NovelRT_SceneNode_create();
  int32_t result = 0;

  NovelRT_SceneNode_insert(parentNode, childNode, &result, nullptr);

  NovelRT_SceneNode_canReach(parentNode, childNode, &result, nullptr);
  ASSERT_TRUE(result);
}

NovelRTSceneNode childNode = NovelRT_SceneNode_create();

TEST(InteropSceneNodeTest, childNodeIsReachableFromParentBreadthFirst) {
  typedef int32_t(*wrapperFunction)(NovelRTSceneNode);
  
  NovelRTSceneNode parentNode = NovelRT_SceneNode_create();

  int32_t result = 0;

  NovelRT_SceneNode_insert(parentNode, childNode, &result, nullptr);

  auto func = [](NovelRTSceneNode traversedNode) -> int32_t {
    if(traversedNode == childNode) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  };

  func(childNode);

  int32_t(*vari)(NovelRTSceneNode) = func;

  vari(childNode);

  NovelRTSceneNodeBreadthFirstIterator it = nullptr;
  auto res = NovelRT_SceneNode_traverseBreadthFirstWithIterator(parentNode, vari, &it, nullptr);
  ASSERT_EQ(res, 0);

  int32_t loopResult = 0;
  int32_t isEqual = 0;
  res = NovelRT_SceneNodeBreadthFirstIterator_isEnd(it, &loopResult, nullptr);
  ASSERT_EQ(res, 0);

  res = NovelRT_SceneNodeBreadthFirstIterator_runFunction(it, &isEqual, nullptr);
  ASSERT_EQ(res, 0);  

  while ((isEqual != NOVELRT_TRUE) && (loopResult == NOVELRT_FALSE)) {
    NovelRT_SceneNodeBreadthFirstIterator_increment(it, nullptr);
    NovelRT_SceneNodeBreadthFirstIterator_isEnd(it, &loopResult, nullptr);
    NovelRT_SceneNodeBreadthFirstIterator_runFunction(it, &isEqual, nullptr);
  }

  ASSERT_EQ(true, isEqual);
}

TEST(InteropSceneNodeTest, parentNodeIsNotReachableFromChild) {
  NovelRTSceneNode parentNode = NovelRT_SceneNode_create();
  NovelRTSceneNode childNode = NovelRT_SceneNode_create();
  int32_t result = 0;

  NovelRT_SceneNode_insert(parentNode, childNode, &result, nullptr);

  NovelRT_SceneNode_canReach(childNode, parentNode, &result, nullptr);
  
  ASSERT_EQ(false, result);
}

TEST(InteropSceneNodeTest, nodeIsReachableFromSelf) {
  NovelRTSceneNode parentNode = NovelRT_SceneNode_create();
  int32_t result = 0;

  NovelRT_SceneNode_canReach(parentNode, parentNode, &result, nullptr);
  
  ASSERT_EQ(true, result);
}

// TEST(InteropSceneNodeTest, breadthFirstTraversalVisitsEachNodeOnceEvenWithCycle) {
//   auto parentSceneNode = std::make_shared<SceneNode>();
//   auto childSceneNode = std::make_shared<SceneNode>();

//   parentSceneNode->insert(childSceneNode);
//   childSceneNode->insert(parentSceneNode);

//   int32_t parentSceneNodeHitCount = 0;
//   int32_t childSceneNodeHitCount = 0;
//   int32_t otherSceneNodeHitCount = 0;

//   parentSceneNode->traverseBreadthFirst([&](const std::shared_ptr<SceneNode>& traversedNode) {
//     if (traversedNode == parentSceneNode) {
//       parentSceneNodeHitCount++;
//     }
//     else if (traversedNode == childSceneNode) {
//       childSceneNodeHitCount++;
//     }
//     else {
//       otherSceneNodeHitCount++;
//     }
//   });

//   ASSERT_EQ(1, parentSceneNodeHitCount);
//   ASSERT_EQ(1, childSceneNodeHitCount);
//   ASSERT_EQ(0, otherSceneNodeHitCount);
// }

// TEST(InteropSceneNodeTest, depthFirstTraversalVisitsEachNodeOnceEvenWithCycle) {
//   auto parentSceneNode = std::make_shared<SceneNode>();
//   auto childSceneNode = std::make_shared<SceneNode>();

//   parentSceneNode->insert(childSceneNode);
//   childSceneNode->insert(parentSceneNode);

//   int32_t parentSceneNodeHitCount = 0;
//   int32_t childSceneNodeHitCount = 0;
//   int32_t otherSceneNodeHitCount = 0;

//   parentSceneNode->traverseDepthFirst([&](const std::shared_ptr<SceneNode>& traversedNode) {
//     if (traversedNode == parentSceneNode) {
//       parentSceneNodeHitCount++;
//     }
//     else if (traversedNode == childSceneNode) {
//       childSceneNodeHitCount++;
//     }
//     else {
//       otherSceneNodeHitCount++;
//     }
//     });

//   ASSERT_EQ(1, parentSceneNodeHitCount);
//   ASSERT_EQ(1, childSceneNodeHitCount);
//   ASSERT_EQ(0, otherSceneNodeHitCount);
// }

