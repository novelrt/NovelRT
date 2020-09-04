// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/Maths/NovelRTQuadTree.h"


using namespace NovelRT;
using namespace NovelRT::Maths;

static const float TEST_WIDTH = 1920.0f;
static const float TEST_HEIGHT = 1080.0f;

NovelRTGeoBounds getCenteredBoundsC(float width, float height) {
  auto size = GeoVector2F(width, height);
  auto position = GeoVector2F(0, 0);
  GeoBounds* result = new GeoBounds(position, size, 0);
  return *reinterpret_cast<NovelRTGeoBounds*>(result);
}

bool checkPointsForEqualityC(NovelRTQuadTreePoint one, NovelRTQuadTreePoint two) {
  auto left = reinterpret_cast<Maths::QuadTreePoint*>(one);
  auto right = reinterpret_cast<Maths::QuadTreePoint*>(two);
  return left->getPosition() == right->getPosition();
}

bool checkPointsForEqualityCpp(Maths::QuadTreePoint* left, Maths::QuadTreePoint* right) {
  return left->getPosition() == right->getPosition();
}

bool checkBoundsForEquality(NovelRTGeoBounds one, NovelRTGeoBounds two) {
  auto left = reinterpret_cast<GeoBounds&>(one);
  auto right = reinterpret_cast<GeoBounds&>(two);
  return left == right;
}

class InteropQuadTreeTest : public testing::Test {
protected:
  NovelRTQuadTree _quadTree;

  void SetUp() override {
    auto bounds = new NovelRTGeoBounds{};
    *bounds = getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
    _quadTree = NovelRT_QuadTree_create(*bounds);
  }

};

TEST_F(InteropQuadTreeTest, createReturnsValidHandle) {
  EXPECT_NE(reinterpret_cast<Maths::QuadTree*>(NovelRT_QuadTree_create(getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT))), nullptr);
}

TEST_F(InteropQuadTreeTest, deleteReturnsSuccessWhenGivenValidHandle) {
  NovelRTQuadTree tree = NovelRT_QuadTree_create(getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT));
  EXPECT_EQ(NovelRT_QuadTree_delete(tree, nullptr), NOVELRT_SUCCESS);
}

TEST_F(InteropQuadTreeTest, deleteReturnsNullptrFailureWhenGivenNullptr) {
  const char* errorOutput = nullptr;

  ASSERT_EQ(NovelRT_QuadTree_delete(nullptr, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsNullptr(), errorOutput);
}

TEST_F(InteropQuadTreeTest, deleteReturnsAlreadyDeletedOrRemovedFailureWhenPointIsBeingHeldOntoElsewhereAndHasAlreadyBeenDeletedFromCache) {
  const char* errorOutput = nullptr;
  auto handle = reinterpret_cast<Maths::QuadTree*>(NovelRT_QuadTree_create(getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT)))->shared_from_this();
  ASSERT_EQ(NovelRT_QuadTree_delete(reinterpret_cast<NovelRTQuadTree>(handle.get()), &errorOutput), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_delete(reinterpret_cast<NovelRTQuadTree>(handle.get()), &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(NovelRT_getErrMsgIsAlreadyDeletedOrRemoved(), errorOutput);
}

TEST_F(InteropQuadTreeTest, getIntersectingPointsReturnsValidPointVectorHandleAndCanAlsoBeDeleted) {
  NovelRTPointVector vec = nullptr;

  int32_t result = NovelRT_QuadTree_getIntersectingPoints(_quadTree, getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT), &vec, nullptr);
  EXPECT_EQ(result, NOVELRT_SUCCESS);
  EXPECT_EQ(NovelRT_PointVector_delete(vec, nullptr), NOVELRT_SUCCESS);
}

TEST_F(InteropQuadTreeTest, getIntersectingPointsReturnsNullptrFailureWhenGivenNullPtrForInput) {
  NovelRTGeoBounds expectedBounds = getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
  NovelRTPointVector outputVector = nullptr;
  const char* errorOutput = nullptr;

  ASSERT_EQ(NovelRT_QuadTree_getIntersectingPoints(nullptr, expectedBounds, &outputVector, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, getIntersectingPointsReturnsNullptrFailureWhenGivenNullPtrForOutput) {
  NovelRTGeoBounds expectedBounds = getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
  const char* errorOutput = nullptr;

  ASSERT_EQ(NovelRT_QuadTree_getIntersectingPoints(_quadTree, expectedBounds, nullptr, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, getIntersectingPointsReturnsNullptrFailureWhenGivenNullPtrForBothInputAndOutput) {
  NovelRTGeoBounds expectedBounds = getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
  const char* errorOutput = nullptr;

  ASSERT_EQ(NovelRT_QuadTree_getIntersectingPoints(nullptr, expectedBounds, nullptr, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, getBoundsGetsCorrectBounds) {
  NovelRTGeoBounds expectedBounds = getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
  NovelRTGeoBounds actualBounds = NovelRT_GeoBounds_zero();
  ASSERT_EQ(NovelRT_QuadTree_getBounds(_quadTree, &actualBounds, nullptr), NOVELRT_SUCCESS);

  EXPECT_TRUE(checkBoundsForEquality(actualBounds, expectedBounds));
}

TEST_F(InteropQuadTreeTest, getBoundsReturnsNullptrFailureWhenGivenNullPtrForInput) {
  NovelRTGeoBounds outputBounds = NovelRT_GeoBounds_zero();
  const char* errorOutput = nullptr;
  ASSERT_EQ(NovelRT_QuadTree_getBounds(nullptr, &outputBounds, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, getBoundsReturnsNullptrFailureWhenGivenNullPtrForOutput) {
  NovelRTGeoBounds outputBounds = NovelRT_GeoBounds_zero();
  const char* errorOutput = nullptr;
  ASSERT_EQ(NovelRT_QuadTree_getBounds(_quadTree, nullptr, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, getBoundsReturnsNullptrFailureWhenGivenNullPtrForBothInputAndOutput) {
  NovelRTGeoBounds outputBounds = NovelRT_GeoBounds_zero();
  const char* errorOutput = nullptr;
  ASSERT_EQ(NovelRT_QuadTree_getBounds(nullptr, nullptr, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, getPointCountReturnsZeroWhenTreeHasNoPoints) {
  size_t actualSize = 0;
  ASSERT_EQ(NovelRT_QuadTree_getPointCount(_quadTree, &actualSize, nullptr), NOVELRT_SUCCESS);
  EXPECT_EQ(actualSize, 0u);
}

TEST_F(InteropQuadTreeTest, getPointCountReturnsNullptrFailureWhenGivenNullptrForInput) {
  size_t actualSize = 0;
  const char* errorOutput = nullptr;
  size_t size = 0;
  ASSERT_EQ(NovelRT_QuadTree_getPointCount(nullptr, &actualSize, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, getPointCountReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorOutput = nullptr;
  ASSERT_EQ(NovelRT_QuadTree_getPointCount(_quadTree, nullptr, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, getPointCountReturnsNullptrFailureWhenGivenNullptrForBothInputAndOutput) {
  const char* errorOutput = nullptr;
  ASSERT_EQ(NovelRT_QuadTree_getPointCount(nullptr, nullptr, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, getPointMethodsReturnsNullptrWhenTreeHasNoChildren) {
  NovelRTQuadTree topLeft = nullptr;
  NovelRTQuadTree topRight = nullptr;
  NovelRTQuadTree bottomLeft = nullptr;
  NovelRTQuadTree bottomRight = nullptr;

  ASSERT_EQ(NovelRT_QuadTree_getTopLeft(_quadTree, &topLeft, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getTopRight(_quadTree, &topRight, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getBottomLeft(_quadTree, &bottomLeft, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getBottomRight(_quadTree, &bottomRight, nullptr), NOVELRT_SUCCESS);

  EXPECT_EQ(topLeft, nullptr);
  EXPECT_EQ(topRight, nullptr);
  EXPECT_EQ(bottomLeft, nullptr);
  EXPECT_EQ(bottomRight, nullptr);
}

TEST_F(InteropQuadTreeTest, getPointReturnsNullForTooLargeIndex) {
  NovelRTQuadTreePoint point0 = nullptr;
  NovelRTQuadTreePoint point1 = nullptr;
  NovelRTQuadTreePoint point2 = nullptr;
  NovelRTQuadTreePoint point3 = nullptr;

  ASSERT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 0, &point0, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 1, &point1, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 2, &point2, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 3, &point3, nullptr), NOVELRT_SUCCESS);

  EXPECT_EQ(point0, nullptr);
  EXPECT_EQ(point1, nullptr);
  EXPECT_EQ(point2, nullptr);
  EXPECT_EQ(point3, nullptr);
}

TEST_F(InteropQuadTreeTest, getPointReturnsNullptrFailureWhenGivenNullptrForInput) {
  NovelRTQuadTreePoint point = nullptr;
  const char* errorOutput = nullptr;

  ASSERT_EQ(NovelRT_QuadTree_getPoint(nullptr, 0, &point, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, getPointReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorOutput = nullptr;

  ASSERT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 0, nullptr, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, getPointReturnsNullptrFailureWhenGivenNullptrForInputAndOutput) {
  const char* errorOutput = nullptr;

  ASSERT_EQ(NovelRT_QuadTree_getPoint(nullptr, 0, nullptr, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, insertOneReturnsTrue) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t result = NOVELRT_FALSE;

  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point0, &result, nullptr), NOVELRT_SUCCESS);

  EXPECT_TRUE(result);
}

TEST_F(InteropQuadTreeTest, insertReturnsNullptrFailureWhenGivenNullptrForInput) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t result = NOVELRT_FALSE;
  const char* errorOutput = nullptr;
  
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(nullptr, point0, &result, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, insertReturnsNullptrFailureWhenGivenNullptrForOutput) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  const char* errorOutput = nullptr;
  
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point0, nullptr, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, insertReturnsNullptrFailureWhenGivenNullptrForInputAndOutput) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  const char* errorOutput = nullptr;
  
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(nullptr, point0, nullptr, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, insertFourDoesNotSubdivide) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  size_t outputSizeResult = 0u;
  ASSERT_EQ(NovelRT_QuadTree_getPointCount(_quadTree, &outputSizeResult, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(outputSizeResult, 4u);

  NovelRTQuadTreePoint outputPointResult0 = nullptr;
  NovelRTQuadTreePoint outputPointResult1 = nullptr;
  NovelRTQuadTreePoint outputPointResult2 = nullptr;
  NovelRTQuadTreePoint outputPointResult3 = nullptr;

  ASSERT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 0, &outputPointResult0, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 1, &outputPointResult1, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 2, &outputPointResult2, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 3, &outputPointResult3, nullptr), NOVELRT_SUCCESS);
  
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResult0, point0));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResult1, point1));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResult2, point2));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResult3, point3));

  NovelRTQuadTree outputCornerTreeTopLeft = nullptr;
  NovelRTQuadTree outputCornerTreeTopRight = nullptr;
  NovelRTQuadTree outputCornerTreeBottomLeft = nullptr;
  NovelRTQuadTree outputCornerTreeBottomRight = nullptr;

  ASSERT_EQ(NovelRT_QuadTree_getTopLeft(_quadTree, &outputCornerTreeTopLeft, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getTopRight(_quadTree, &outputCornerTreeTopRight, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getBottomLeft(_quadTree, &outputCornerTreeBottomLeft, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getBottomRight(_quadTree, &outputCornerTreeBottomRight, nullptr), NOVELRT_SUCCESS);

  EXPECT_EQ(outputCornerTreeTopLeft, nullptr);
  EXPECT_EQ(outputCornerTreeTopRight, nullptr);
  EXPECT_EQ(outputCornerTreeBottomLeft, nullptr);
  EXPECT_EQ(outputCornerTreeBottomRight, nullptr);
}

TEST_F(InteropQuadTreeTest, insertFiveDoesSubdivideAndPointsAreCorrect) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  auto point4 = NovelRT_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  int32_t point4InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point4, &point4InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point4InsertResult);

  size_t outputSizeResult = 0u;
  ASSERT_EQ(NovelRT_QuadTree_getPointCount(_quadTree, &outputSizeResult, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(outputSizeResult, 0u);

  NovelRTQuadTree treeOutputTopLeft = nullptr;  
  NovelRTQuadTree treeOutputTopRight = nullptr;
  NovelRTQuadTree treeOutputBottomLeft = nullptr;
  NovelRTQuadTree treeOutputBottomRight = nullptr;

  int32_t treeResultTopLeft = NovelRT_QuadTree_getTopLeft(_quadTree, &treeOutputTopLeft, nullptr);
  int32_t treeResultTopRight = NovelRT_QuadTree_getTopRight(_quadTree, &treeOutputTopRight, nullptr);
  int32_t treeResultBottomLeft = NovelRT_QuadTree_getBottomLeft(_quadTree, &treeOutputBottomLeft, nullptr);
  int32_t treeResultBottomRight = NovelRT_QuadTree_getBottomRight(_quadTree, &treeOutputBottomRight, nullptr);

  ASSERT_EQ(treeResultTopLeft, NOVELRT_SUCCESS);
  ASSERT_EQ(treeResultTopRight, NOVELRT_SUCCESS);
  ASSERT_EQ(treeResultBottomLeft, NOVELRT_SUCCESS);
  ASSERT_EQ(treeResultBottomRight, NOVELRT_SUCCESS);

  size_t outputChildTreeSizeTopLeft = 0u;
  size_t outputChildTreeSizeTopRight = 0u;
  size_t outputChildTreeSizeBottomLeft = 0u;
  size_t outputChildTreeSizeBottomRight = 0u;

  int32_t pointCountOperationResultTopLeft = NovelRT_QuadTree_getPointCount(treeOutputTopLeft, &outputChildTreeSizeTopLeft, nullptr);  
  int32_t pointCountOperationResultTopRight = NovelRT_QuadTree_getPointCount(treeOutputTopRight, &outputChildTreeSizeTopRight, nullptr);
  int32_t pointCountOperationResultBottomLeft = NovelRT_QuadTree_getPointCount(treeOutputBottomLeft, &outputChildTreeSizeBottomLeft, nullptr);
  int32_t pointCountOperationResultBottomRight = NovelRT_QuadTree_getPointCount(treeOutputBottomRight, &outputChildTreeSizeBottomRight, nullptr);

  ASSERT_EQ(pointCountOperationResultTopLeft, NOVELRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultTopRight, NOVELRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultBottomLeft, NOVELRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultBottomRight, NOVELRT_SUCCESS);

  EXPECT_EQ(outputChildTreeSizeTopLeft, 2u);
  EXPECT_EQ(outputChildTreeSizeTopRight, 1u);
  EXPECT_EQ(outputChildTreeSizeBottomLeft, 1u);
  EXPECT_EQ(outputChildTreeSizeBottomRight, 1u);

  NovelRTQuadTree treeOutputTwoTopLeft = nullptr;  
  NovelRTQuadTree treeOutputTwoTopRight = nullptr;
  NovelRTQuadTree treeOutputTwoBottomLeft = nullptr;
  NovelRTQuadTree treeOutputTwoBottomRight = nullptr;

  int32_t treeResultTwoTopLeft = NovelRT_QuadTree_getTopLeft(_quadTree, &treeOutputTwoTopLeft, nullptr);
  int32_t treeResultTwoTopRight = NovelRT_QuadTree_getTopRight(_quadTree, &treeOutputTopRight, nullptr);
  int32_t treeResultTwoBottomLeft = NovelRT_QuadTree_getBottomLeft(_quadTree, &treeOutputBottomLeft, nullptr);
  int32_t treeResultTwoBottomRight = NovelRT_QuadTree_getBottomRight(_quadTree, &treeOutputBottomRight, nullptr);

  NovelRTQuadTreePoint outputPointResultTopLeft = nullptr;
  NovelRTQuadTreePoint outputPointResultTopRight = nullptr;
  NovelRTQuadTreePoint outputPointResultBottomLeft = nullptr;
  NovelRTQuadTreePoint outputPointResultBottomRight = nullptr;
  NovelRTQuadTreePoint outputPointResultTopLeftTwo = nullptr;

  NovelRT_QuadTree_getPoint(treeOutputTopLeft, 0, &outputPointResultTopLeft, nullptr);
  NovelRT_QuadTree_getPoint(treeOutputTopRight, 0, &outputPointResultTopRight, nullptr);
  NovelRT_QuadTree_getPoint(treeOutputBottomLeft, 0, &outputPointResultBottomLeft, nullptr);
  NovelRT_QuadTree_getPoint(treeOutputBottomRight, 0, &outputPointResultBottomRight, nullptr);
  NovelRT_QuadTree_getPoint(treeOutputTopLeft, 1, &outputPointResultTopLeftTwo, nullptr);
 
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultTopLeft, point0));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultTopRight, point1));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultBottomLeft, point2));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultBottomRight, point3));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultTopLeftTwo, point4));
}

TEST_F(InteropQuadTreeTest, insertFiveDoesSubdivideAndBoundsAreCorrect) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  auto point4 = NovelRT_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  int32_t point4InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point4, &point4InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point4InsertResult);

  size_t outputSizeResult = 0u;
  ASSERT_EQ(NovelRT_QuadTree_getPointCount(_quadTree, &outputSizeResult, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(outputSizeResult, 0u);

  NovelRTQuadTree treeOutputTopLeft = nullptr;  
  NovelRTQuadTree treeOutputTopRight = nullptr;
  NovelRTQuadTree treeOutputBottomLeft = nullptr;
  NovelRTQuadTree treeOutputBottomRight = nullptr;

  int32_t treeResultTopLeft = NovelRT_QuadTree_getTopLeft(_quadTree, &treeOutputTopLeft, nullptr);
  int32_t treeResultTopRight = NovelRT_QuadTree_getTopRight(_quadTree, &treeOutputTopRight, nullptr);
  int32_t treeResultBottomLeft = NovelRT_QuadTree_getBottomLeft(_quadTree, &treeOutputBottomLeft, nullptr);
  int32_t treeResultBottomRight = NovelRT_QuadTree_getBottomRight(_quadTree, &treeOutputBottomRight, nullptr);

  ASSERT_EQ(treeResultTopLeft, NOVELRT_SUCCESS);
  ASSERT_EQ(treeResultTopRight, NOVELRT_SUCCESS);
  ASSERT_EQ(treeResultBottomLeft, NOVELRT_SUCCESS);
  ASSERT_EQ(treeResultBottomRight, NOVELRT_SUCCESS);

  size_t outputChildTreeSizeTopLeft = 0u;
  size_t outputChildTreeSizeTopRight = 0u;
  size_t outputChildTreeSizeBottomLeft = 0u;
  size_t outputChildTreeSizeBottomRight = 0u;

  int32_t pointCountOperationResultTopLeft = NovelRT_QuadTree_getPointCount(treeOutputTopLeft, &outputChildTreeSizeTopLeft, nullptr);  
  int32_t pointCountOperationResultTopRight = NovelRT_QuadTree_getPointCount(treeOutputTopRight, &outputChildTreeSizeTopRight, nullptr);
  int32_t pointCountOperationResultBottomLeft = NovelRT_QuadTree_getPointCount(treeOutputBottomLeft, &outputChildTreeSizeBottomLeft, nullptr);
  int32_t pointCountOperationResultBottomRight = NovelRT_QuadTree_getPointCount(treeOutputBottomRight, &outputChildTreeSizeBottomRight, nullptr);

  ASSERT_EQ(pointCountOperationResultTopLeft, NOVELRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultTopRight, NOVELRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultBottomLeft, NOVELRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultBottomRight, NOVELRT_SUCCESS);

  EXPECT_EQ(outputChildTreeSizeTopLeft, 2u);
  EXPECT_EQ(outputChildTreeSizeTopRight, 1u);
  EXPECT_EQ(outputChildTreeSizeBottomLeft, 1u);
  EXPECT_EQ(outputChildTreeSizeBottomRight, 1u);

  auto expectedSize = NovelRTGeoVector2F { TEST_WIDTH / 2, TEST_HEIGHT / 2 };

  NovelRTGeoBounds outputBoundsTopLeft = NovelRT_GeoBounds_zero();
  NovelRTGeoBounds outputBoundsTopRight = NovelRT_GeoBounds_zero();
  NovelRTGeoBounds outputBoundsBottomLeft = NovelRT_GeoBounds_zero();
  NovelRTGeoBounds outputBoundsBottomRight = NovelRT_GeoBounds_zero();

  int32_t boundsResultTopLeft = NovelRT_QuadTree_getBounds(treeOutputTopLeft, &outputBoundsTopLeft, nullptr);
  int32_t boundsResultTopRight = NovelRT_QuadTree_getBounds(treeOutputTopRight, &outputBoundsTopRight, nullptr);
  int32_t boundsResultBottomLeft = NovelRT_QuadTree_getBounds(treeOutputBottomLeft, &outputBoundsBottomLeft, nullptr);
  int32_t boundsResultBottomRight = NovelRT_QuadTree_getBounds(treeOutputBottomRight, &outputBoundsBottomRight, nullptr);

  ASSERT_EQ(boundsResultTopLeft, NOVELRT_SUCCESS);
  ASSERT_EQ(boundsResultTopRight, NOVELRT_SUCCESS);
  ASSERT_EQ(boundsResultBottomLeft, NOVELRT_SUCCESS);
  ASSERT_EQ(boundsResultBottomRight, NOVELRT_SUCCESS);

  EXPECT_TRUE(checkBoundsForEquality(outputBoundsTopLeft, NovelRTGeoBounds { NovelRTGeoVector2F { -TEST_WIDTH / 4, TEST_HEIGHT / 4 }, expectedSize, 0 }));
  EXPECT_TRUE(checkBoundsForEquality(outputBoundsTopRight, NovelRTGeoBounds { NovelRTGeoVector2F { TEST_WIDTH / 4, TEST_HEIGHT / 4 }, expectedSize, 0 }));
  EXPECT_TRUE(checkBoundsForEquality(outputBoundsBottomLeft, NovelRTGeoBounds { NovelRTGeoVector2F { -TEST_WIDTH / 4, -TEST_HEIGHT / 4 }, expectedSize, 0 }));
  EXPECT_TRUE(checkBoundsForEquality(outputBoundsBottomRight, NovelRTGeoBounds { NovelRTGeoVector2F { TEST_WIDTH / 4, -TEST_HEIGHT / 4 },  expectedSize, 0 }));
}

TEST_F(InteropQuadTreeTest, insertOutOfBoundsReturnsFalse) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(3840.0f, 2160.0f);

  int32_t outputBool = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point0, &outputBool, nullptr), NOVELRT_SUCCESS);
  EXPECT_EQ(NOVELRT_FALSE, outputBool);
}

TEST_F(InteropQuadTreeTest, PointVector_getSizeReturnsCorrectValue) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  auto point4 = NovelRT_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  int32_t point4InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point4, &point4InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point4InsertResult);

  NovelRTGeoBounds inputGeoBounds = NovelRT_GeoBounds_zero();
  NovelRTPointVector resultVector = nullptr;
  size_t outputVectorSize = 0u;

  ASSERT_EQ(NovelRT_QuadTree_getBounds(_quadTree, &inputGeoBounds, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getIntersectingPoints(_quadTree, inputGeoBounds, &resultVector, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_PointVector_getSize(resultVector, &outputVectorSize, nullptr), NOVELRT_SUCCESS);

  EXPECT_EQ(outputVectorSize, 5u);
}

TEST_F(InteropQuadTreeTest, PointVector_deleteReturnsNullptrFailureWhenGivenNullptr) {
  const char* errorOutput = nullptr;

  ASSERT_EQ(NovelRT_PointVector_delete(nullptr, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, getIntersectingPointsReturnsAllPoints) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  auto point4 = NovelRT_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  int32_t point4InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point4, &point4InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point4InsertResult);

  NovelRTGeoBounds outputGeoBounds = NovelRT_GeoBounds_zero();
  NovelRTPointVector resultVector = nullptr;
  size_t outputVectorSize = 0u;

  ASSERT_EQ(NovelRT_QuadTree_getBounds(_quadTree, &outputGeoBounds, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getIntersectingPoints(_quadTree, outputGeoBounds, &resultVector, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_PointVector_getSize(resultVector, &outputVectorSize, nullptr), NOVELRT_SUCCESS);

  NovelRTQuadTreePoint outputPoint0 = nullptr;
  NovelRTQuadTreePoint outputPoint1 = nullptr;
  NovelRTQuadTreePoint outputPoint2 = nullptr;
  NovelRTQuadTreePoint outputPoint3 = nullptr;
  NovelRTQuadTreePoint outputPoint4 = nullptr;

  ASSERT_EQ(NovelRT_PointVector_getPointFromIndex(resultVector, 0, &outputPoint0, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_PointVector_getPointFromIndex(resultVector, 1, &outputPoint1, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_PointVector_getPointFromIndex(resultVector, 2, &outputPoint2, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_PointVector_getPointFromIndex(resultVector, 3, &outputPoint3, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_PointVector_getPointFromIndex(resultVector, 4, &outputPoint4, nullptr), NOVELRT_SUCCESS);

  EXPECT_TRUE(checkPointsForEqualityC(outputPoint0, point0));
  EXPECT_TRUE(checkPointsForEqualityC(outputPoint1, point4));
  EXPECT_TRUE(checkPointsForEqualityC(outputPoint2, point1));
  EXPECT_TRUE(checkPointsForEqualityC(outputPoint3, point2));
  EXPECT_TRUE(checkPointsForEqualityC(outputPoint4, point3));
}

TEST_F(InteropQuadTreeTest, removeExistingReturnsTrue) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);

  int32_t outputInsertBool = NOVELRT_FALSE;
  int32_t outputRemoveBool = NOVELRT_FALSE;

  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point0, &outputInsertBool, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_tryRemove(_quadTree, point0, &outputRemoveBool, nullptr), NOVELRT_SUCCESS);
  ASSERT_TRUE(outputInsertBool);
  EXPECT_TRUE(outputRemoveBool);
}

TEST_F(InteropQuadTreeTest, removeNoneExistingReturnsFalse) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  
  int32_t outputBool = NOVELRT_FALSE;

  ASSERT_EQ(NovelRT_QuadTree_tryRemove(_quadTree, point0, &outputBool, nullptr), NOVELRT_SUCCESS);
  EXPECT_FALSE(outputBool);
}

TEST_F(InteropQuadTreeTest, removeReturnsNullptrFailureWhenGivenNullptrForInput) {
  auto point = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  const char* errorOutput = nullptr;
  int32_t outputBool = NOVELRT_FALSE;
  
  ASSERT_EQ(NovelRT_QuadTree_tryRemove(nullptr, point, &outputBool, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, removeReturnsNullptrFailureWhenGivenNullptrForOutput) {
  auto point = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  const char* errorOutput = nullptr;
  
  ASSERT_EQ(NovelRT_QuadTree_tryRemove(_quadTree, point, nullptr, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, removeReturnsNullptrFailureWhenGivenNullptrForInputAndOutput) {
  auto point = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  const char* errorOutput = nullptr;
  
  ASSERT_EQ(NovelRT_QuadTree_tryRemove(nullptr, point, nullptr, &errorOutput), NOVELRT_FAILURE);
  EXPECT_EQ(errorOutput, NovelRT_getErrMsgIsNullptr());
}

TEST_F(InteropQuadTreeTest, removeOneCausesMergeWhenAdjacentPointCountLessThan5) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  auto point4 = NovelRT_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  int32_t point4InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point4, &point4InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point4InsertResult);

  int32_t tryRemoveOutputBool = NOVELRT_FALSE;

  ASSERT_EQ(NovelRT_QuadTree_tryRemove(_quadTree, point4, &tryRemoveOutputBool, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(tryRemoveOutputBool);

  size_t outputPointCount = 0u;

  ASSERT_EQ(NovelRT_QuadTree_getPointCount(_quadTree, &outputPointCount, nullptr), NOVELRT_SUCCESS);
  EXPECT_EQ(outputPointCount, 4u);

  NovelRTQuadTreePoint newOutputPoint0 = nullptr;
  NovelRTQuadTreePoint newOutputPoint1 = nullptr;
  NovelRTQuadTreePoint newOutputPoint2 = nullptr;
  NovelRTQuadTreePoint newOutputPoint3 = nullptr;

  ASSERT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 0, &newOutputPoint0, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 1, &newOutputPoint1, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 2, &newOutputPoint2, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 3, &newOutputPoint3, nullptr), NOVELRT_SUCCESS);

  EXPECT_TRUE(checkPointsForEqualityC(newOutputPoint0, point0));
  EXPECT_TRUE(checkPointsForEqualityC(newOutputPoint1, point1));
  EXPECT_TRUE(checkPointsForEqualityC(newOutputPoint2, point2));
  EXPECT_TRUE(checkPointsForEqualityC(newOutputPoint3, point3));

  NovelRTQuadTree newTopLeftTree = nullptr;
  NovelRTQuadTree newTopRightTree = nullptr;
  NovelRTQuadTree newBottomLeftTree = nullptr;
  NovelRTQuadTree newBottomRightTree = nullptr;

  ASSERT_EQ(NovelRT_QuadTree_getTopLeft(_quadTree, &newTopLeftTree, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getTopRight(_quadTree, &newTopRightTree, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getBottomLeft(_quadTree, &newBottomLeftTree, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getBottomRight(_quadTree, &newBottomRightTree, nullptr), NOVELRT_SUCCESS);

  EXPECT_EQ(newTopLeftTree, nullptr);
  EXPECT_EQ(newTopLeftTree, nullptr);
  EXPECT_EQ(newTopLeftTree, nullptr);
  EXPECT_EQ(newTopLeftTree, nullptr);
}

TEST_F(InteropQuadTreeTest, removeOneDoesNotCauseMergeWhenAdjacentPointCountMoreThan4) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  auto point4 = NovelRT_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  int32_t point4InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point4, &point4InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point4InsertResult);

  auto point5 = NovelRT_QuadTreePoint_createFromFloat(0.5f, 0.5f);
  int32_t point5InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point5, &point5InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point5InsertResult);

  int32_t tryRemoveOutputBool = NOVELRT_FALSE;

  ASSERT_EQ(NovelRT_QuadTree_tryRemove(_quadTree, point5, &tryRemoveOutputBool, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(tryRemoveOutputBool);

  size_t outputPointCount = 0u;

  ASSERT_EQ(NovelRT_QuadTree_getPointCount(_quadTree, &outputPointCount, nullptr), NOVELRT_SUCCESS);
  EXPECT_EQ(outputPointCount, 0u);

  NovelRTQuadTree treeOutputTopLeft = nullptr;  
  NovelRTQuadTree treeOutputTopRight = nullptr;
  NovelRTQuadTree treeOutputBottomLeft = nullptr;
  NovelRTQuadTree treeOutputBottomRight = nullptr;

  int32_t treeResultTopLeft = NovelRT_QuadTree_getTopLeft(_quadTree, &treeOutputTopLeft, nullptr);
  int32_t treeResultTopRight = NovelRT_QuadTree_getTopRight(_quadTree, &treeOutputTopRight, nullptr);
  int32_t treeResultBottomLeft = NovelRT_QuadTree_getBottomLeft(_quadTree, &treeOutputBottomLeft, nullptr);
  int32_t treeResultBottomRight = NovelRT_QuadTree_getBottomRight(_quadTree, &treeOutputBottomRight, nullptr);

  ASSERT_EQ(treeResultTopLeft, NOVELRT_SUCCESS);
  ASSERT_EQ(treeResultTopRight, NOVELRT_SUCCESS);
  ASSERT_EQ(treeResultBottomLeft, NOVELRT_SUCCESS);
  ASSERT_EQ(treeResultBottomRight, NOVELRT_SUCCESS);

  size_t outputChildTreeSizeTopLeft = 0u;
  size_t outputChildTreeSizeTopRight = 0u;
  size_t outputChildTreeSizeBottomLeft = 0u;
  size_t outputChildTreeSizeBottomRight = 0u;

  int32_t pointCountOperationResultTopLeft = NovelRT_QuadTree_getPointCount(treeOutputTopLeft, &outputChildTreeSizeTopLeft, nullptr);  
  int32_t pointCountOperationResultTopRight = NovelRT_QuadTree_getPointCount(treeOutputTopRight, &outputChildTreeSizeTopRight, nullptr);
  int32_t pointCountOperationResultBottomLeft = NovelRT_QuadTree_getPointCount(treeOutputBottomLeft, &outputChildTreeSizeBottomLeft, nullptr);
  int32_t pointCountOperationResultBottomRight = NovelRT_QuadTree_getPointCount(treeOutputBottomRight, &outputChildTreeSizeBottomRight, nullptr);

  ASSERT_EQ(pointCountOperationResultTopLeft, NOVELRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultTopRight, NOVELRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultBottomLeft, NOVELRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultBottomRight, NOVELRT_SUCCESS);

  EXPECT_EQ(outputChildTreeSizeTopLeft, 2u);
  EXPECT_EQ(outputChildTreeSizeTopRight, 1u);
  EXPECT_EQ(outputChildTreeSizeBottomLeft, 1u);
  EXPECT_EQ(outputChildTreeSizeBottomRight, 1u);

  NovelRTQuadTreePoint outputPointResultTopLeft = nullptr;
  NovelRTQuadTreePoint outputPointResultTopRight = nullptr;
  NovelRTQuadTreePoint outputPointResultBottomLeft = nullptr;
  NovelRTQuadTreePoint outputPointResultBottomRight = nullptr;
  NovelRTQuadTreePoint outputPointResultTopLeftTwo = nullptr;

  NovelRT_QuadTree_getPoint(treeOutputTopLeft, 0, &outputPointResultTopLeft, nullptr);
  NovelRT_QuadTree_getPoint(treeOutputTopRight, 0, &outputPointResultTopRight, nullptr);
  NovelRT_QuadTree_getPoint(treeOutputBottomLeft, 0, &outputPointResultBottomLeft, nullptr);
  NovelRT_QuadTree_getPoint(treeOutputBottomRight, 0, &outputPointResultBottomRight, nullptr);
  NovelRT_QuadTree_getPoint(treeOutputTopLeft, 1, &outputPointResultTopLeftTwo, nullptr);
 
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultTopLeft, point0));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultTopRight, point1));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultBottomLeft, point2));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultBottomRight, point3));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultTopLeftTwo, point4));
}

TEST_F(InteropQuadTreeTest, getIntersectingPointsForQuadTreeBoundsReturnsAll) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  auto point4 = NovelRT_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  int32_t point4InsertResult = NOVELRT_FALSE;
  ASSERT_EQ(NovelRT_QuadTree_tryInsert(_quadTree, point4, &point4InsertResult, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(point4InsertResult);

  NovelRTGeoBounds outputGeoBounds = NovelRT_GeoBounds_zero();
  NovelRTPointVector outputVector = nullptr;

  ASSERT_EQ(NovelRT_QuadTree_getBounds(_quadTree, &outputGeoBounds, nullptr), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTree_getIntersectingPoints(_quadTree, outputGeoBounds, &outputVector, nullptr), NOVELRT_SUCCESS);  
  auto intersectingPointsVector = reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(outputVector);

  EXPECT_EQ(intersectingPointsVector->size(), 5u);

  auto cPoint0 = reinterpret_cast<Maths::QuadTreePoint*>(point0);
  auto cPoint1 = reinterpret_cast<Maths::QuadTreePoint*>(point1);
  auto cPoint2 = reinterpret_cast<Maths::QuadTreePoint*>(point2);
  auto cPoint3 = reinterpret_cast<Maths::QuadTreePoint*>(point3);
  auto cPoint4 = reinterpret_cast<Maths::QuadTreePoint*>(point4);

  EXPECT_TRUE(checkPointsForEqualityCpp(intersectingPointsVector->at(0).get(), cPoint0));
  EXPECT_TRUE(checkPointsForEqualityCpp(intersectingPointsVector->at(1).get(), cPoint4));
  EXPECT_TRUE(checkPointsForEqualityCpp(intersectingPointsVector->at(2).get(), cPoint1));
  EXPECT_TRUE(checkPointsForEqualityCpp(intersectingPointsVector->at(3).get(), cPoint2));
  EXPECT_TRUE(checkPointsForEqualityCpp(intersectingPointsVector->at(4).get(), cPoint3));
}

