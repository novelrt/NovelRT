// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/SceneGraph/NovelRTSceneNode.h"

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

// TEST(InteropSceneNodeTest, removeNodeTwiceReturnsFalse)
// {
//   auto parentSceneNode = std::make_shared<SceneNode>();
//   auto childSceneNode = std::make_shared<SceneNode>();

//   parentSceneNode->insert(childSceneNode);
//   parentSceneNode->remove(childSceneNode);

//   ASSERT_EQ(false, parentSceneNode->remove(childSceneNode));
// }

// TEST(InteropSceneNodeTest, unrelatedNodesAreNotAdjacent) {
//   auto parentSceneNode = std::make_shared<SceneNode>();
//   auto childSceneNode = std::make_shared<SceneNode>();

//   ASSERT_EQ(false, parentSceneNode->isAdjacent(childSceneNode));
//   ASSERT_EQ(false, childSceneNode->isAdjacent(parentSceneNode));
// }

// TEST(InteropSceneNodeTest, parentChildNodesAreAdjacent) {
//   auto parentSceneNode = std::make_shared<SceneNode>();
//   auto childSceneNode = std::make_shared<SceneNode>();

//   parentSceneNode->insert(childSceneNode);

//   ASSERT_EQ(true, parentSceneNode->isAdjacent(childSceneNode));
//   ASSERT_EQ(true, childSceneNode->isAdjacent(parentSceneNode));
// }

// TEST(InteropSceneNodeTest, childNodeIsReachableFromParent) {
//   auto parentSceneNode = std::make_shared<SceneNode>();
//   auto childSceneNode = std::make_shared<SceneNode>();

//   parentSceneNode->insert(childSceneNode);

//   ASSERT_EQ(true, parentSceneNode->canReach(childSceneNode));
// }

// TEST(InteropSceneNodeTest, childNodeIsReachableFromParentBreadthFirst) {
//   auto parentSceneNode = std::make_shared<SceneNode>();
//   auto childSceneNode = std::make_shared<SceneNode>();

//   parentSceneNode->insert(childSceneNode);

//   auto result = parentSceneNode->traverseBreadthFirst<bool>([&](const std::shared_ptr<SceneNode>& traversedNode) {
//     return traversedNode == childSceneNode;
//   });

//   while ((*result != true) && !result.isEnd()) {
//     result++;
//   }

//   ASSERT_EQ(true, *result);
// }

// TEST(InteropSceneNodeTest, parentNodeIsNotReachableFromChild) {
//   auto parentSceneNode = std::make_shared<SceneNode>();
//   auto childSceneNode = std::make_shared<SceneNode>();

//   parentSceneNode->insert(childSceneNode);

//   ASSERT_EQ(false, childSceneNode->canReach(parentSceneNode));
// }

// TEST(InteropSceneNodeTest, nodeIsReachableFromSelf) {
//   auto sceneNode = std::make_shared<SceneNode>();
//   ASSERT_EQ(true, sceneNode->canReach(sceneNode));
// }

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

