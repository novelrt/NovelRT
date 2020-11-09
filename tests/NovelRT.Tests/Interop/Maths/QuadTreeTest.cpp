// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/Maths/NrtQuadTree.h"

using namespace NovelRT;
using namespace NovelRT::Maths;

static const float TEST_WIDTH = 1920.0f;
static const float TEST_HEIGHT = 1080.0f;

NrtGeoBounds getCenteredBoundsC(float width, float height) {
  auto size = GeoVector2F(width, height);
  auto position = GeoVector2F(0, 0);
  GeoBounds* result = new GeoBounds(position, size, 0);
  return *reinterpret_cast<NrtGeoBounds*>(result);
}

bool checkPointsForEqualityC(NrtQuadTreePoint one, NrtQuadTreePoint two) {
  auto left = reinterpret_cast<Maths::QuadTreePoint*>(one);
  auto right = reinterpret_cast<Maths::QuadTreePoint*>(two);
  return left->getPosition() == right->getPosition();
}

bool checkPointsForEqualityCpp(Maths::QuadTreePoint* left, Maths::QuadTreePoint* right) {
  return left->getPosition() == right->getPosition();
}

bool checkBoundsForEquality(NrtGeoBounds one, NrtGeoBounds two) {
  auto left = reinterpret_cast<GeoBounds&>(one);
  auto right = reinterpret_cast<GeoBounds&>(two);
  return left == right;
}

class InteropQuadTreeTest : public testing::Test {
protected:
  NrtQuadTree _quadTree;

  void SetUp() override {
    auto bounds = new NrtGeoBounds{};
    *bounds = getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
    _quadTree = Nrt_QuadTree_create(*bounds);
  }

};

TEST_F(InteropQuadTreeTest, createReturnsValidHandle) {
  EXPECT_NE(reinterpret_cast<Maths::QuadTree*>(Nrt_QuadTree_create(getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT))), nullptr);
}

TEST_F(InteropQuadTreeTest, deleteReturnsSuccessWhenGivenValidHandle) {
  NrtQuadTree tree = Nrt_QuadTree_create(getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT));
  EXPECT_EQ(Nrt_QuadTree_delete(tree), NRT_SUCCESS);
}

TEST_F(InteropQuadTreeTest, deleteReturnsNullptrFailureWhenGivenNullptr) {
  const char* errorOutput = nullptr;

  ASSERT_EQ(Nrt_QuadTree_delete(nullptr), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsNullptr(), errorOutput); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, deleteReturnsAlreadyDeletedOrRemovedFailureWhenPointIsBeingHeldOntoElsewhereAndHasAlreadyBeenDeletedFromCache) {
  const char* errorOutput = nullptr;
  auto handle = reinterpret_cast<Maths::QuadTree*>(Nrt_QuadTree_create(getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT)))->shared_from_this();
  ASSERT_EQ(Nrt_QuadTree_delete(reinterpret_cast<NrtQuadTree>(handle.get())), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_delete(reinterpret_cast<NrtQuadTree>(handle.get())), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(Nrt_getErrMsgIsAlreadyDeletedOrRemoved(), errorOutput); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, getIntersectingPointsReturnsValidPointVectorHandleAndCanAlsoBeDeleted) {
  NrtPointVector vec = nullptr;

  int32_t result = Nrt_QuadTree_getIntersectingPoints(_quadTree, getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT), &vec);
  EXPECT_EQ(result, NRT_SUCCESS);
  EXPECT_EQ(Nrt_PointVector_delete(vec), NRT_SUCCESS);
}

TEST_F(InteropQuadTreeTest, getIntersectingPointsReturnsNullptrFailureWhenGivenNullPtrForInput) {
  NrtGeoBounds expectedBounds = getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
  NrtPointVector outputVector = nullptr;
  const char* errorOutput = nullptr;

  ASSERT_EQ(Nrt_QuadTree_getIntersectingPoints(nullptr, expectedBounds, &outputVector), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, getIntersectingPointsReturnsNullptrFailureWhenGivenNullPtrForOutput) {
  NrtGeoBounds expectedBounds = getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
  const char* errorOutput = nullptr;

  ASSERT_EQ(Nrt_QuadTree_getIntersectingPoints(_quadTree, expectedBounds, nullptr), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, getIntersectingPointsReturnsNullptrFailureWhenGivenNullPtrForBothInputAndOutput) {
  NrtGeoBounds expectedBounds = getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
  const char* errorOutput = nullptr;

  ASSERT_EQ(Nrt_QuadTree_getIntersectingPoints(nullptr, expectedBounds, nullptr), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, getBoundsGetsCorrectBounds) {
  NrtGeoBounds expectedBounds = getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
  NrtGeoBounds actualBounds = Nrt_GeoBounds_zero();
  ASSERT_EQ(Nrt_QuadTree_getBounds(_quadTree, &actualBounds), NRT_SUCCESS);

  EXPECT_TRUE(checkBoundsForEquality(actualBounds, expectedBounds));
}

TEST_F(InteropQuadTreeTest, getBoundsReturnsNullptrFailureWhenGivenNullPtrForInput) {
  NrtGeoBounds outputBounds = Nrt_GeoBounds_zero();
  const char* errorOutput = nullptr;
  ASSERT_EQ(Nrt_QuadTree_getBounds(nullptr, &outputBounds), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, getBoundsReturnsNullptrFailureWhenGivenNullPtrForOutput) {
  NrtGeoBounds outputBounds = Nrt_GeoBounds_zero();
  const char* errorOutput = nullptr;
  ASSERT_EQ(Nrt_QuadTree_getBounds(_quadTree, nullptr), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, getBoundsReturnsNullptrFailureWhenGivenNullPtrForBothInputAndOutput) {
  NrtGeoBounds outputBounds = Nrt_GeoBounds_zero();
  const char* errorOutput = nullptr;
  ASSERT_EQ(Nrt_QuadTree_getBounds(nullptr, nullptr), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, getPointCountReturnsZeroWhenTreeHasNoPoints) {
  size_t actualSize = 0;
  ASSERT_EQ(Nrt_QuadTree_getPointCount(_quadTree, &actualSize), NRT_SUCCESS);
  EXPECT_EQ(actualSize, 0u);
}

TEST_F(InteropQuadTreeTest, getPointCountReturnsNullptrFailureWhenGivenNullptrForInput) {
  size_t actualSize = 0;
  const char* errorOutput = nullptr;
  size_t size = 0;
  ASSERT_EQ(Nrt_QuadTree_getPointCount(nullptr, &actualSize), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, getPointCountReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorOutput = nullptr;
  ASSERT_EQ(Nrt_QuadTree_getPointCount(_quadTree, nullptr), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, getPointCountReturnsNullptrFailureWhenGivenNullptrForBothInputAndOutput) {
  const char* errorOutput = nullptr;
  ASSERT_EQ(Nrt_QuadTree_getPointCount(nullptr, nullptr), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, getPointMethodsReturnsNullptrWhenTreeHasNoChildren) {
  NrtQuadTree topLeft = nullptr;
  NrtQuadTree topRight = nullptr;
  NrtQuadTree bottomLeft = nullptr;
  NrtQuadTree bottomRight = nullptr;

  ASSERT_EQ(Nrt_QuadTree_getTopLeft(_quadTree, &topLeft), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getTopRight(_quadTree, &topRight), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getBottomLeft(_quadTree, &bottomLeft), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getBottomRight(_quadTree, &bottomRight), NRT_SUCCESS);

  EXPECT_EQ(topLeft, nullptr);
  EXPECT_EQ(topRight, nullptr);
  EXPECT_EQ(bottomLeft, nullptr);
  EXPECT_EQ(bottomRight, nullptr);
}

TEST_F(InteropQuadTreeTest, getPointReturnsNullForTooLargeIndex) {
  NrtQuadTreePoint point0 = nullptr;
  NrtQuadTreePoint point1 = nullptr;
  NrtQuadTreePoint point2 = nullptr;
  NrtQuadTreePoint point3 = nullptr;

  ASSERT_EQ(Nrt_QuadTree_getPoint(_quadTree, 0, &point0), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getPoint(_quadTree, 1, &point1), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getPoint(_quadTree, 2, &point2), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getPoint(_quadTree, 3, &point3), NRT_SUCCESS);

  EXPECT_EQ(point0, nullptr);
  EXPECT_EQ(point1, nullptr);
  EXPECT_EQ(point2, nullptr);
  EXPECT_EQ(point3, nullptr);
}

TEST_F(InteropQuadTreeTest, getPointReturnsNullptrFailureWhenGivenNullptrForInput) {
  NrtQuadTreePoint point = nullptr;
  const char* errorOutput = nullptr;

  ASSERT_EQ(Nrt_QuadTree_getPoint(nullptr, 0, &point), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, getPointReturnsNullptrFailureWhenGivenNullptrForOutput) {
  const char* errorOutput = nullptr;

  ASSERT_EQ(Nrt_QuadTree_getPoint(_quadTree, 0, nullptr), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, getPointReturnsNullptrFailureWhenGivenNullptrForInputAndOutput) {
  const char* errorOutput = nullptr;

  ASSERT_EQ(Nrt_QuadTree_getPoint(nullptr, 0, nullptr), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, insertOneReturnsTrue) {
  auto point0 = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t result = NRT_FALSE;

  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point0, &result), NRT_SUCCESS);

  EXPECT_TRUE(result);
}

TEST_F(InteropQuadTreeTest, insertReturnsNullptrFailureWhenGivenNullptrForInput) {
  auto point0 = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t result = NRT_FALSE;
  const char* errorOutput = nullptr;
  
  ASSERT_EQ(Nrt_QuadTree_tryInsert(nullptr, point0, &result), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, insertReturnsNullptrFailureWhenGivenNullptrForOutput) {
  auto point0 = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  const char* errorOutput = nullptr;
  
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point0, nullptr), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, insertReturnsNullptrFailureWhenGivenNullptrForInputAndOutput) {
  auto point0 = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  const char* errorOutput = nullptr;
  
  ASSERT_EQ(Nrt_QuadTree_tryInsert(nullptr, point0, nullptr), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, insertFourDoesNotSubdivide) {
  auto point0 = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = Nrt_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = Nrt_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = Nrt_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  size_t outputSizeResult = 0u;
  ASSERT_EQ(Nrt_QuadTree_getPointCount(_quadTree, &outputSizeResult), NRT_SUCCESS);
  ASSERT_EQ(outputSizeResult, 4u);

  NrtQuadTreePoint outputPointResult0 = nullptr;
  NrtQuadTreePoint outputPointResult1 = nullptr;
  NrtQuadTreePoint outputPointResult2 = nullptr;
  NrtQuadTreePoint outputPointResult3 = nullptr;

  ASSERT_EQ(Nrt_QuadTree_getPoint(_quadTree, 0, &outputPointResult0), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getPoint(_quadTree, 1, &outputPointResult1), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getPoint(_quadTree, 2, &outputPointResult2), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getPoint(_quadTree, 3, &outputPointResult3), NRT_SUCCESS);
  
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResult0, point0));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResult1, point1));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResult2, point2));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResult3, point3));

  NrtQuadTree outputCornerTreeTopLeft = nullptr;
  NrtQuadTree outputCornerTreeTopRight = nullptr;
  NrtQuadTree outputCornerTreeBottomLeft = nullptr;
  NrtQuadTree outputCornerTreeBottomRight = nullptr;

  ASSERT_EQ(Nrt_QuadTree_getTopLeft(_quadTree, &outputCornerTreeTopLeft), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getTopRight(_quadTree, &outputCornerTreeTopRight), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getBottomLeft(_quadTree, &outputCornerTreeBottomLeft), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getBottomRight(_quadTree, &outputCornerTreeBottomRight), NRT_SUCCESS);

  EXPECT_EQ(outputCornerTreeTopLeft, nullptr);
  EXPECT_EQ(outputCornerTreeTopRight, nullptr);
  EXPECT_EQ(outputCornerTreeBottomLeft, nullptr);
  EXPECT_EQ(outputCornerTreeBottomRight, nullptr);
}

TEST_F(InteropQuadTreeTest, insertFiveDoesSubdivideAndPointsAreCorrect) {
  auto point0 = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = Nrt_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = Nrt_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = Nrt_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  auto point4 = Nrt_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  int32_t point4InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point4, &point4InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point4InsertResult);

  size_t outputSizeResult = 0u;
  ASSERT_EQ(Nrt_QuadTree_getPointCount(_quadTree, &outputSizeResult), NRT_SUCCESS);
  ASSERT_EQ(outputSizeResult, 0u);

  NrtQuadTree treeOutputTopLeft = nullptr;  
  NrtQuadTree treeOutputTopRight = nullptr;
  NrtQuadTree treeOutputBottomLeft = nullptr;
  NrtQuadTree treeOutputBottomRight = nullptr;

  int32_t treeResultTopLeft = Nrt_QuadTree_getTopLeft(_quadTree, &treeOutputTopLeft);
  int32_t treeResultTopRight = Nrt_QuadTree_getTopRight(_quadTree, &treeOutputTopRight);
  int32_t treeResultBottomLeft = Nrt_QuadTree_getBottomLeft(_quadTree, &treeOutputBottomLeft);
  int32_t treeResultBottomRight = Nrt_QuadTree_getBottomRight(_quadTree, &treeOutputBottomRight);

  ASSERT_EQ(treeResultTopLeft, NRT_SUCCESS);
  ASSERT_EQ(treeResultTopRight, NRT_SUCCESS);
  ASSERT_EQ(treeResultBottomLeft, NRT_SUCCESS);
  ASSERT_EQ(treeResultBottomRight, NRT_SUCCESS);

  size_t outputChildTreeSizeTopLeft = 0u;
  size_t outputChildTreeSizeTopRight = 0u;
  size_t outputChildTreeSizeBottomLeft = 0u;
  size_t outputChildTreeSizeBottomRight = 0u;

  int32_t pointCountOperationResultTopLeft = Nrt_QuadTree_getPointCount(treeOutputTopLeft, &outputChildTreeSizeTopLeft);  
  int32_t pointCountOperationResultTopRight = Nrt_QuadTree_getPointCount(treeOutputTopRight, &outputChildTreeSizeTopRight);
  int32_t pointCountOperationResultBottomLeft = Nrt_QuadTree_getPointCount(treeOutputBottomLeft, &outputChildTreeSizeBottomLeft);
  int32_t pointCountOperationResultBottomRight = Nrt_QuadTree_getPointCount(treeOutputBottomRight, &outputChildTreeSizeBottomRight);

  ASSERT_EQ(pointCountOperationResultTopLeft, NRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultTopRight, NRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultBottomLeft, NRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultBottomRight, NRT_SUCCESS);

  EXPECT_EQ(outputChildTreeSizeTopLeft, 2u);
  EXPECT_EQ(outputChildTreeSizeTopRight, 1u);
  EXPECT_EQ(outputChildTreeSizeBottomLeft, 1u);
  EXPECT_EQ(outputChildTreeSizeBottomRight, 1u);

  NrtQuadTree treeOutputTwoTopLeft = nullptr;  
  NrtQuadTree treeOutputTwoTopRight = nullptr;
  NrtQuadTree treeOutputTwoBottomLeft = nullptr;
  NrtQuadTree treeOutputTwoBottomRight = nullptr;

  int32_t treeResultTwoTopLeft = Nrt_QuadTree_getTopLeft(_quadTree, &treeOutputTwoTopLeft);
  int32_t treeResultTwoTopRight = Nrt_QuadTree_getTopRight(_quadTree, &treeOutputTopRight);
  int32_t treeResultTwoBottomLeft = Nrt_QuadTree_getBottomLeft(_quadTree, &treeOutputBottomLeft);
  int32_t treeResultTwoBottomRight = Nrt_QuadTree_getBottomRight(_quadTree, &treeOutputBottomRight);

  NrtQuadTreePoint outputPointResultTopLeft = nullptr;
  NrtQuadTreePoint outputPointResultTopRight = nullptr;
  NrtQuadTreePoint outputPointResultBottomLeft = nullptr;
  NrtQuadTreePoint outputPointResultBottomRight = nullptr;
  NrtQuadTreePoint outputPointResultTopLeftTwo = nullptr;

  Nrt_QuadTree_getPoint(treeOutputTopLeft, 0, &outputPointResultTopLeft);
  Nrt_QuadTree_getPoint(treeOutputTopRight, 0, &outputPointResultTopRight);
  Nrt_QuadTree_getPoint(treeOutputBottomLeft, 0, &outputPointResultBottomLeft);
  Nrt_QuadTree_getPoint(treeOutputBottomRight, 0, &outputPointResultBottomRight);
  Nrt_QuadTree_getPoint(treeOutputTopLeft, 1, &outputPointResultTopLeftTwo);
 
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultTopLeft, point0));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultTopRight, point1));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultBottomLeft, point2));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultBottomRight, point3));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultTopLeftTwo, point4));
}

TEST_F(InteropQuadTreeTest, insertFiveDoesSubdivideAndBoundsAreCorrect) {
  auto point0 = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = Nrt_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = Nrt_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = Nrt_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  auto point4 = Nrt_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  int32_t point4InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point4, &point4InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point4InsertResult);

  size_t outputSizeResult = 0u;
  ASSERT_EQ(Nrt_QuadTree_getPointCount(_quadTree, &outputSizeResult), NRT_SUCCESS);
  ASSERT_EQ(outputSizeResult, 0u);

  NrtQuadTree treeOutputTopLeft = nullptr;  
  NrtQuadTree treeOutputTopRight = nullptr;
  NrtQuadTree treeOutputBottomLeft = nullptr;
  NrtQuadTree treeOutputBottomRight = nullptr;

  int32_t treeResultTopLeft = Nrt_QuadTree_getTopLeft(_quadTree, &treeOutputTopLeft);
  int32_t treeResultTopRight = Nrt_QuadTree_getTopRight(_quadTree, &treeOutputTopRight);
  int32_t treeResultBottomLeft = Nrt_QuadTree_getBottomLeft(_quadTree, &treeOutputBottomLeft);
  int32_t treeResultBottomRight = Nrt_QuadTree_getBottomRight(_quadTree, &treeOutputBottomRight);

  ASSERT_EQ(treeResultTopLeft, NRT_SUCCESS);
  ASSERT_EQ(treeResultTopRight, NRT_SUCCESS);
  ASSERT_EQ(treeResultBottomLeft, NRT_SUCCESS);
  ASSERT_EQ(treeResultBottomRight, NRT_SUCCESS);

  size_t outputChildTreeSizeTopLeft = 0u;
  size_t outputChildTreeSizeTopRight = 0u;
  size_t outputChildTreeSizeBottomLeft = 0u;
  size_t outputChildTreeSizeBottomRight = 0u;

  int32_t pointCountOperationResultTopLeft = Nrt_QuadTree_getPointCount(treeOutputTopLeft, &outputChildTreeSizeTopLeft);  
  int32_t pointCountOperationResultTopRight = Nrt_QuadTree_getPointCount(treeOutputTopRight, &outputChildTreeSizeTopRight);
  int32_t pointCountOperationResultBottomLeft = Nrt_QuadTree_getPointCount(treeOutputBottomLeft, &outputChildTreeSizeBottomLeft);
  int32_t pointCountOperationResultBottomRight = Nrt_QuadTree_getPointCount(treeOutputBottomRight, &outputChildTreeSizeBottomRight);

  ASSERT_EQ(pointCountOperationResultTopLeft, NRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultTopRight, NRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultBottomLeft, NRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultBottomRight, NRT_SUCCESS);

  EXPECT_EQ(outputChildTreeSizeTopLeft, 2u);
  EXPECT_EQ(outputChildTreeSizeTopRight, 1u);
  EXPECT_EQ(outputChildTreeSizeBottomLeft, 1u);
  EXPECT_EQ(outputChildTreeSizeBottomRight, 1u);

  auto expectedSize = NrtGeoVector2F { TEST_WIDTH / 2, TEST_HEIGHT / 2 };

  NrtGeoBounds outputBoundsTopLeft = Nrt_GeoBounds_zero();
  NrtGeoBounds outputBoundsTopRight = Nrt_GeoBounds_zero();
  NrtGeoBounds outputBoundsBottomLeft = Nrt_GeoBounds_zero();
  NrtGeoBounds outputBoundsBottomRight = Nrt_GeoBounds_zero();

  int32_t boundsResultTopLeft = Nrt_QuadTree_getBounds(treeOutputTopLeft, &outputBoundsTopLeft);
  int32_t boundsResultTopRight = Nrt_QuadTree_getBounds(treeOutputTopRight, &outputBoundsTopRight);
  int32_t boundsResultBottomLeft = Nrt_QuadTree_getBounds(treeOutputBottomLeft, &outputBoundsBottomLeft);
  int32_t boundsResultBottomRight = Nrt_QuadTree_getBounds(treeOutputBottomRight, &outputBoundsBottomRight);

  ASSERT_EQ(boundsResultTopLeft, NRT_SUCCESS);
  ASSERT_EQ(boundsResultTopRight, NRT_SUCCESS);
  ASSERT_EQ(boundsResultBottomLeft, NRT_SUCCESS);
  ASSERT_EQ(boundsResultBottomRight, NRT_SUCCESS);

  EXPECT_TRUE(checkBoundsForEquality(outputBoundsTopLeft, NrtGeoBounds { NrtGeoVector2F { -TEST_WIDTH / 4, TEST_HEIGHT / 4 }, expectedSize, 0 }));
  EXPECT_TRUE(checkBoundsForEquality(outputBoundsTopRight, NrtGeoBounds { NrtGeoVector2F { TEST_WIDTH / 4, TEST_HEIGHT / 4 }, expectedSize, 0 }));
  EXPECT_TRUE(checkBoundsForEquality(outputBoundsBottomLeft, NrtGeoBounds { NrtGeoVector2F { -TEST_WIDTH / 4, -TEST_HEIGHT / 4 }, expectedSize, 0 }));
  EXPECT_TRUE(checkBoundsForEquality(outputBoundsBottomRight, NrtGeoBounds { NrtGeoVector2F { TEST_WIDTH / 4, -TEST_HEIGHT / 4 },  expectedSize, 0 }));
}

TEST_F(InteropQuadTreeTest, insertOutOfBoundsReturnsFalse) {
  auto point0 = Nrt_QuadTreePoint_createFromFloat(3840.0f, 2160.0f);

  int32_t outputBool = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point0, &outputBool), NRT_SUCCESS);
  EXPECT_EQ(NRT_FALSE, outputBool);
}

TEST_F(InteropQuadTreeTest, PointVector_getSizeReturnsCorrectValue) {
  auto point0 = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = Nrt_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = Nrt_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = Nrt_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  auto point4 = Nrt_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  int32_t point4InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point4, &point4InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point4InsertResult);

  NrtGeoBounds inputGeoBounds = Nrt_GeoBounds_zero();
  NrtPointVector resultVector = nullptr;
  size_t outputVectorSize = 0u;

  ASSERT_EQ(Nrt_QuadTree_getBounds(_quadTree, &inputGeoBounds), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getIntersectingPoints(_quadTree, inputGeoBounds, &resultVector), NRT_SUCCESS);
  ASSERT_EQ(Nrt_PointVector_getSize(resultVector, &outputVectorSize), NRT_SUCCESS);

  EXPECT_EQ(outputVectorSize, 5u);
}

TEST_F(InteropQuadTreeTest, PointVector_deleteReturnsNullptrFailureWhenGivenNullptr) {
  const char* errorOutput = nullptr;

  ASSERT_EQ(Nrt_PointVector_delete(nullptr), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, getIntersectingPointsReturnsAllPoints) {
  auto point0 = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = Nrt_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = Nrt_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = Nrt_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  auto point4 = Nrt_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  int32_t point4InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point4, &point4InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point4InsertResult);

  NrtGeoBounds outputGeoBounds = Nrt_GeoBounds_zero();
  NrtPointVector resultVector = nullptr;
  size_t outputVectorSize = 0u;

  ASSERT_EQ(Nrt_QuadTree_getBounds(_quadTree, &outputGeoBounds), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getIntersectingPoints(_quadTree, outputGeoBounds, &resultVector), NRT_SUCCESS);
  ASSERT_EQ(Nrt_PointVector_getSize(resultVector, &outputVectorSize), NRT_SUCCESS);

  NrtQuadTreePoint outputPoint0 = nullptr;
  NrtQuadTreePoint outputPoint1 = nullptr;
  NrtQuadTreePoint outputPoint2 = nullptr;
  NrtQuadTreePoint outputPoint3 = nullptr;
  NrtQuadTreePoint outputPoint4 = nullptr;

  ASSERT_EQ(Nrt_PointVector_getPointFromIndex(resultVector, 0, &outputPoint0), NRT_SUCCESS);
  ASSERT_EQ(Nrt_PointVector_getPointFromIndex(resultVector, 1, &outputPoint1), NRT_SUCCESS);
  ASSERT_EQ(Nrt_PointVector_getPointFromIndex(resultVector, 2, &outputPoint2), NRT_SUCCESS);
  ASSERT_EQ(Nrt_PointVector_getPointFromIndex(resultVector, 3, &outputPoint3), NRT_SUCCESS);
  ASSERT_EQ(Nrt_PointVector_getPointFromIndex(resultVector, 4, &outputPoint4), NRT_SUCCESS);

  EXPECT_TRUE(checkPointsForEqualityC(outputPoint0, point0));
  EXPECT_TRUE(checkPointsForEqualityC(outputPoint1, point4));
  EXPECT_TRUE(checkPointsForEqualityC(outputPoint2, point1));
  EXPECT_TRUE(checkPointsForEqualityC(outputPoint3, point2));
  EXPECT_TRUE(checkPointsForEqualityC(outputPoint4, point3));
}

TEST_F(InteropQuadTreeTest, removeExistingReturnsTrue) {
  auto point0 = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);

  int32_t outputInsertBool = NRT_FALSE;
  int32_t outputRemoveBool = NRT_FALSE;

  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point0, &outputInsertBool), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_tryRemove(_quadTree, point0, &outputRemoveBool), NRT_SUCCESS);
  ASSERT_TRUE(outputInsertBool);
  EXPECT_TRUE(outputRemoveBool);
}

TEST_F(InteropQuadTreeTest, removeNoneExistingReturnsFalse) {
  auto point0 = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  
  int32_t outputBool = NRT_FALSE;

  ASSERT_EQ(Nrt_QuadTree_tryRemove(_quadTree, point0, &outputBool), NRT_SUCCESS);
  EXPECT_FALSE(outputBool);
}

TEST_F(InteropQuadTreeTest, removeReturnsNullptrFailureWhenGivenNullptrForInput) {
  auto point = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  const char* errorOutput = nullptr;
  int32_t outputBool = NRT_FALSE;
  
  ASSERT_EQ(Nrt_QuadTree_tryRemove(nullptr, point, &outputBool), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, removeReturnsNullptrFailureWhenGivenNullptrForOutput) {
  auto point = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  const char* errorOutput = nullptr;
  
  ASSERT_EQ(Nrt_QuadTree_tryRemove(_quadTree, point, nullptr), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, removeReturnsNullptrFailureWhenGivenNullptrForInputAndOutput) {
  auto point = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  const char* errorOutput = nullptr;
  
  ASSERT_EQ(Nrt_QuadTree_tryRemove(nullptr, point, nullptr), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(errorOutput, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST_F(InteropQuadTreeTest, removeOneCausesMergeWhenAdjacentPointCountLessThan5) {
  auto point0 = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = Nrt_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = Nrt_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = Nrt_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  auto point4 = Nrt_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  int32_t point4InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point4, &point4InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point4InsertResult);

  int32_t tryRemoveOutputBool = NRT_FALSE;

  ASSERT_EQ(Nrt_QuadTree_tryRemove(_quadTree, point4, &tryRemoveOutputBool), NRT_SUCCESS);
  EXPECT_TRUE(tryRemoveOutputBool);

  size_t outputPointCount = 0u;

  ASSERT_EQ(Nrt_QuadTree_getPointCount(_quadTree, &outputPointCount), NRT_SUCCESS);
  EXPECT_EQ(outputPointCount, 4u);

  NrtQuadTreePoint newOutputPoint0 = nullptr;
  NrtQuadTreePoint newOutputPoint1 = nullptr;
  NrtQuadTreePoint newOutputPoint2 = nullptr;
  NrtQuadTreePoint newOutputPoint3 = nullptr;

  ASSERT_EQ(Nrt_QuadTree_getPoint(_quadTree, 0, &newOutputPoint0), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getPoint(_quadTree, 1, &newOutputPoint1), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getPoint(_quadTree, 2, &newOutputPoint2), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getPoint(_quadTree, 3, &newOutputPoint3), NRT_SUCCESS);

  EXPECT_TRUE(checkPointsForEqualityC(newOutputPoint0, point0));
  EXPECT_TRUE(checkPointsForEqualityC(newOutputPoint1, point1));
  EXPECT_TRUE(checkPointsForEqualityC(newOutputPoint2, point2));
  EXPECT_TRUE(checkPointsForEqualityC(newOutputPoint3, point3));

  NrtQuadTree newTopLeftTree = nullptr;
  NrtQuadTree newTopRightTree = nullptr;
  NrtQuadTree newBottomLeftTree = nullptr;
  NrtQuadTree newBottomRightTree = nullptr;

  ASSERT_EQ(Nrt_QuadTree_getTopLeft(_quadTree, &newTopLeftTree), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getTopRight(_quadTree, &newTopRightTree), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getBottomLeft(_quadTree, &newBottomLeftTree), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getBottomRight(_quadTree, &newBottomRightTree), NRT_SUCCESS);

  EXPECT_EQ(newTopLeftTree, nullptr);
  EXPECT_EQ(newTopLeftTree, nullptr);
  EXPECT_EQ(newTopLeftTree, nullptr);
  EXPECT_EQ(newTopLeftTree, nullptr);
}

TEST_F(InteropQuadTreeTest, removeOneDoesNotCauseMergeWhenAdjacentPointCountMoreThan4) {
  auto point0 = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = Nrt_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = Nrt_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = Nrt_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  auto point4 = Nrt_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  int32_t point4InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point4, &point4InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point4InsertResult);

  auto point5 = Nrt_QuadTreePoint_createFromFloat(0.5f, 0.5f);
  int32_t point5InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point5, &point5InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point5InsertResult);

  int32_t tryRemoveOutputBool = NRT_FALSE;

  ASSERT_EQ(Nrt_QuadTree_tryRemove(_quadTree, point5, &tryRemoveOutputBool), NRT_SUCCESS);
  EXPECT_TRUE(tryRemoveOutputBool);

  size_t outputPointCount = 0u;

  ASSERT_EQ(Nrt_QuadTree_getPointCount(_quadTree, &outputPointCount), NRT_SUCCESS);
  EXPECT_EQ(outputPointCount, 0u);

  NrtQuadTree treeOutputTopLeft = nullptr;  
  NrtQuadTree treeOutputTopRight = nullptr;
  NrtQuadTree treeOutputBottomLeft = nullptr;
  NrtQuadTree treeOutputBottomRight = nullptr;

  int32_t treeResultTopLeft = Nrt_QuadTree_getTopLeft(_quadTree, &treeOutputTopLeft);
  int32_t treeResultTopRight = Nrt_QuadTree_getTopRight(_quadTree, &treeOutputTopRight);
  int32_t treeResultBottomLeft = Nrt_QuadTree_getBottomLeft(_quadTree, &treeOutputBottomLeft);
  int32_t treeResultBottomRight = Nrt_QuadTree_getBottomRight(_quadTree, &treeOutputBottomRight);

  ASSERT_EQ(treeResultTopLeft, NRT_SUCCESS);
  ASSERT_EQ(treeResultTopRight, NRT_SUCCESS);
  ASSERT_EQ(treeResultBottomLeft, NRT_SUCCESS);
  ASSERT_EQ(treeResultBottomRight, NRT_SUCCESS);

  size_t outputChildTreeSizeTopLeft = 0u;
  size_t outputChildTreeSizeTopRight = 0u;
  size_t outputChildTreeSizeBottomLeft = 0u;
  size_t outputChildTreeSizeBottomRight = 0u;

  int32_t pointCountOperationResultTopLeft = Nrt_QuadTree_getPointCount(treeOutputTopLeft, &outputChildTreeSizeTopLeft);  
  int32_t pointCountOperationResultTopRight = Nrt_QuadTree_getPointCount(treeOutputTopRight, &outputChildTreeSizeTopRight);
  int32_t pointCountOperationResultBottomLeft = Nrt_QuadTree_getPointCount(treeOutputBottomLeft, &outputChildTreeSizeBottomLeft);
  int32_t pointCountOperationResultBottomRight = Nrt_QuadTree_getPointCount(treeOutputBottomRight, &outputChildTreeSizeBottomRight);

  ASSERT_EQ(pointCountOperationResultTopLeft, NRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultTopRight, NRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultBottomLeft, NRT_SUCCESS);
  ASSERT_EQ(pointCountOperationResultBottomRight, NRT_SUCCESS);

  EXPECT_EQ(outputChildTreeSizeTopLeft, 2u);
  EXPECT_EQ(outputChildTreeSizeTopRight, 1u);
  EXPECT_EQ(outputChildTreeSizeBottomLeft, 1u);
  EXPECT_EQ(outputChildTreeSizeBottomRight, 1u);

  NrtQuadTreePoint outputPointResultTopLeft = nullptr;
  NrtQuadTreePoint outputPointResultTopRight = nullptr;
  NrtQuadTreePoint outputPointResultBottomLeft = nullptr;
  NrtQuadTreePoint outputPointResultBottomRight = nullptr;
  NrtQuadTreePoint outputPointResultTopLeftTwo = nullptr;

  Nrt_QuadTree_getPoint(treeOutputTopLeft, 0, &outputPointResultTopLeft);
  Nrt_QuadTree_getPoint(treeOutputTopRight, 0, &outputPointResultTopRight);
  Nrt_QuadTree_getPoint(treeOutputBottomLeft, 0, &outputPointResultBottomLeft);
  Nrt_QuadTree_getPoint(treeOutputBottomRight, 0, &outputPointResultBottomRight);
  Nrt_QuadTree_getPoint(treeOutputTopLeft, 1, &outputPointResultTopLeftTwo);
 
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultTopLeft, point0));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultTopRight, point1));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultBottomLeft, point2));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultBottomRight, point3));
  EXPECT_TRUE(checkPointsForEqualityC(outputPointResultTopLeftTwo, point4));
}

TEST_F(InteropQuadTreeTest, getIntersectingPointsForQuadTreeBoundsReturnsAll) {
  auto point0 = Nrt_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  int32_t point0InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point0, &point0InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point0InsertResult);

  auto point1 = Nrt_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  int32_t point1InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point1, &point1InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point1InsertResult);

  auto point2 = Nrt_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  int32_t point2InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point2, &point2InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point2InsertResult);

  auto point3 = Nrt_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  int32_t point3InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point3, &point3InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point3InsertResult);

  auto point4 = Nrt_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  int32_t point4InsertResult = NRT_FALSE;
  ASSERT_EQ(Nrt_QuadTree_tryInsert(_quadTree, point4, &point4InsertResult), NRT_SUCCESS);
  EXPECT_TRUE(point4InsertResult);

  NrtGeoBounds outputGeoBounds = Nrt_GeoBounds_zero();
  NrtPointVector outputVector = nullptr;

  ASSERT_EQ(Nrt_QuadTree_getBounds(_quadTree, &outputGeoBounds), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTree_getIntersectingPoints(_quadTree, outputGeoBounds, &outputVector), NRT_SUCCESS);  
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

