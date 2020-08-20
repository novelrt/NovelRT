// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/Maths/NovelRTQuadTree.h"


using namespace NovelRT;
using namespace NovelRT::Maths;

static const float TEST_WIDTH = 1920.0f;
static const float TEST_HEIGHT = 1080.0f;

NovelRTGeoBounds getCenteredBoundsC(float width, float height) {
  auto size = GeoVector2<float>(width, height);
  auto position = GeoVector2<float>(0, 0);
  GeoBounds* result = new GeoBounds(position, size, 0);
  return reinterpret_cast<NovelRTGeoBounds&>(*result);
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

//TODO: Update all tests with return codes
TEST_F(InteropQuadTreeTest, QuadTree_createReturnsValidHandle) {
  EXPECT_NE(reinterpret_cast<Maths::QuadTree*>(NovelRT_QuadTree_create(getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT))), nullptr);
}

//TODO: This test really REALLY needs return codes.
TEST_F(InteropQuadTreeTest, QuadTree_deleteReturnsSuccess) {
  NovelRTQuadTree tree = NovelRT_QuadTree_create(getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT));
  EXPECT_EQ(NovelRT_QuadTree_delete(tree, nullptr), NOVELRT_SUCCESS);
}

TEST_F(InteropQuadTreeTest, QuadTree_getIntersectingPointsReturnsValidPointVectorHandleAndCanAlsoBeDeleted) {
  NovelRTPointVector vec = nullptr;

  NovelRTResult result = NovelRT_QuadTree_getIntersectingPoints(_quadTree, getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT), &vec, nullptr);
  EXPECT_EQ(result, NOVELRT_SUCCESS);
  EXPECT_EQ(NovelRT_PointVector_delete(vec, nullptr), NOVELRT_SUCCESS);
}

TEST_F(InteropQuadTreeTest, createCorrectlySetsBounds) {
  NovelRTGeoBounds expectedBounds = getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
  
  EXPECT_TRUE(checkBoundsForEquality(NovelRT_QuadTree_getBounds(_quadTree), expectedBounds));
}

TEST_F(InteropQuadTreeTest, createHasNoPoints) {
  EXPECT_EQ(NovelRT_QuadTree_getPointCount(_quadTree), 0u);
}

TEST_F(InteropQuadTreeTest, createHasNoChildren) {
  EXPECT_EQ(NovelRT_QuadTree_getTopLeft(_quadTree), nullptr);
  EXPECT_EQ(NovelRT_QuadTree_getTopRight(_quadTree), nullptr);
  EXPECT_EQ(NovelRT_QuadTree_getBottomLeft(_quadTree), nullptr);
  EXPECT_EQ(NovelRT_QuadTree_getBottomRight(_quadTree), nullptr);
}

TEST_F(InteropQuadTreeTest, getPointReturnsNullForTooLargeIndex) {
  EXPECT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 0), nullptr);
  EXPECT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 1), nullptr);
  EXPECT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 2), nullptr);
  EXPECT_EQ(NovelRT_QuadTree_getPoint(_quadTree, 3), nullptr);
}

TEST_F(InteropQuadTreeTest, insertOneReturnsTrue) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  EXPECT_EQ(true, NovelRT_QuadTree_tryInsert(_quadTree, point0));
}

TEST_F(InteropQuadTreeTest, insertFourDoesNotSubdivide) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point0));

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point1));

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point2));

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point3));

  ASSERT_EQ(NovelRT_QuadTree_getPointCount(_quadTree), 4u);

  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_QuadTree_getPoint(_quadTree, 0), point0));
  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_QuadTree_getPoint(_quadTree, 1), point1));
  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_QuadTree_getPoint(_quadTree, 2), point2));
  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_QuadTree_getPoint(_quadTree, 3), point3));

  EXPECT_EQ(NovelRT_QuadTree_getTopLeft(_quadTree), nullptr);
  EXPECT_EQ(NovelRT_QuadTree_getTopRight(_quadTree), nullptr);
  EXPECT_EQ(NovelRT_QuadTree_getBottomLeft(_quadTree), nullptr);
  EXPECT_EQ(NovelRT_QuadTree_getBottomRight(_quadTree), nullptr);
}

TEST_F(InteropQuadTreeTest, insertFiveDoesSubdivideAndPointsAreCorrect) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point0));

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point1));

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point2));

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point3));

  auto point4 = NovelRT_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point4));

  EXPECT_EQ(NovelRT_QuadTree_getPointCount(_quadTree), 0u);

  EXPECT_EQ(NovelRT_QuadTree_getPointCount(NovelRT_QuadTree_getTopLeft(_quadTree)), 2u);
  EXPECT_EQ(NovelRT_QuadTree_getPointCount(NovelRT_QuadTree_getTopRight(_quadTree)), 1u);
  EXPECT_EQ(NovelRT_QuadTree_getPointCount(NovelRT_QuadTree_getBottomLeft(_quadTree)), 1u);
  EXPECT_EQ(NovelRT_QuadTree_getPointCount(NovelRT_QuadTree_getBottomRight(_quadTree)), 1u);

  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_QuadTree_getPoint(NovelRT_QuadTree_getTopLeft(_quadTree), 0), point0));
  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_QuadTree_getPoint(NovelRT_QuadTree_getTopRight(_quadTree), 0), point1));
  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_QuadTree_getPoint(NovelRT_QuadTree_getBottomLeft(_quadTree), 0), point2));
  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_QuadTree_getPoint(NovelRT_QuadTree_getBottomRight(_quadTree), 0), point3));
  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_QuadTree_getPoint(NovelRT_QuadTree_getTopLeft(_quadTree), 1), point4));
}

TEST_F(InteropQuadTreeTest, insertFiveDoesSubdivideAndBoundsAreCorrect) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point0));

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point1));

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point2));

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point3));

  auto point4 = NovelRT_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point4));

  EXPECT_EQ(NovelRT_QuadTree_getPointCount(_quadTree), 0u);

  EXPECT_EQ(NovelRT_QuadTree_getPointCount(NovelRT_QuadTree_getTopLeft(_quadTree)), 2u);
  EXPECT_EQ(NovelRT_QuadTree_getPointCount(NovelRT_QuadTree_getTopRight(_quadTree)), 1u);
  EXPECT_EQ(NovelRT_QuadTree_getPointCount(NovelRT_QuadTree_getBottomLeft(_quadTree)), 1u);
  EXPECT_EQ(NovelRT_QuadTree_getPointCount(NovelRT_QuadTree_getBottomRight(_quadTree)), 1u);

  auto expectedSize = GeoVector2F_create(TEST_WIDTH / 2, TEST_HEIGHT / 2);

  EXPECT_TRUE(checkBoundsForEquality(NovelRT_QuadTree_getBounds(NovelRT_QuadTree_getTopLeft(_quadTree)), GeoBounds_create(GeoVector2F_create(-TEST_WIDTH / 4, TEST_HEIGHT / 4), expectedSize, 0)));
  EXPECT_TRUE(checkBoundsForEquality(NovelRT_QuadTree_getBounds(NovelRT_QuadTree_getTopRight(_quadTree)), GeoBounds_create(GeoVector2F_create(TEST_WIDTH / 4, TEST_HEIGHT / 4), expectedSize, 0)));
  EXPECT_TRUE(checkBoundsForEquality(NovelRT_QuadTree_getBounds(NovelRT_QuadTree_getBottomLeft(_quadTree)), GeoBounds_create(GeoVector2F_create(-TEST_WIDTH / 4, -TEST_HEIGHT / 4), expectedSize, 0)));
  EXPECT_TRUE(checkBoundsForEquality(NovelRT_QuadTree_getBounds(NovelRT_QuadTree_getBottomRight(_quadTree)), GeoBounds_create(GeoVector2F_create(TEST_WIDTH / 4, -TEST_HEIGHT / 4), expectedSize, 0)));
}

TEST_F(InteropQuadTreeTest, insertOutOfBoundsReturnsFalse) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(3840.0f, 2160.0f);
  EXPECT_EQ(false, NovelRT_QuadTree_tryInsert(_quadTree, point0));
}

TEST_F(InteropQuadTreeTest, PointVector_getSizeReturnsCorrectValue) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point0));

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point1));

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point2));

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point3));

  auto point4 = NovelRT_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point4));

  auto allPoints = NovelRT_QuadTree_getIntersectingPoints(_quadTree, NovelRT_QuadTree_getBounds(_quadTree));

  EXPECT_EQ(NovelRT_PointVector_getSize(allPoints), 5u);
}

TEST_F(InteropQuadTreeTest, getIntersectingPointsReturnsAllPoints) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point0));

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point1));

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point2));

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point3));

  auto point4 = NovelRT_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point4));

  auto allPoints = NovelRT_QuadTree_getIntersectingPoints(_quadTree, NovelRT_QuadTree_getBounds(_quadTree));

  EXPECT_EQ(NovelRT_PointVector_getSize(allPoints), 5u);

  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_PointVector_getPointFromIndex(allPoints, 0), point0));
  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_PointVector_getPointFromIndex(allPoints, 1), point4));
  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_PointVector_getPointFromIndex(allPoints, 2), point1));
  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_PointVector_getPointFromIndex(allPoints, 3), point2));
  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_PointVector_getPointFromIndex(allPoints, 4), point3));
}

TEST_F(InteropQuadTreeTest, removeExistingReturnsTrue) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  EXPECT_EQ(true, NovelRT_QuadTree_tryInsert(_quadTree, point0));
  EXPECT_EQ(true, NovelRT_QuadTree_tryRemove(_quadTree, point0));
}

TEST_F(InteropQuadTreeTest, removeNoneExistingReturnsFalse) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  EXPECT_EQ(false, NovelRT_QuadTree_tryRemove(_quadTree, point0));
}

TEST_F(InteropQuadTreeTest, removeOneCausesMergeWhenAdjacentPointCountLessThan5) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point0));

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point1));

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point2));

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point3));

  auto point4 = NovelRT_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point4));

  EXPECT_TRUE(NovelRT_QuadTree_tryRemove(_quadTree, point4));

  EXPECT_EQ(NovelRT_QuadTree_getPointCount(_quadTree), 4u);

  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_QuadTree_getPoint(_quadTree, 0), point0));
  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_QuadTree_getPoint(_quadTree, 1), point1));
  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_QuadTree_getPoint(_quadTree, 2), point2));
  EXPECT_TRUE(checkPointsForEqualityC(NovelRT_QuadTree_getPoint(_quadTree, 3), point3));

  EXPECT_EQ(NovelRT_QuadTree_getTopLeft(_quadTree), nullptr);
  EXPECT_EQ(NovelRT_QuadTree_getTopRight(_quadTree), nullptr);
  EXPECT_EQ(NovelRT_QuadTree_getBottomLeft(_quadTree), nullptr);
  EXPECT_EQ(NovelRT_QuadTree_getBottomRight(_quadTree), nullptr);
}

TEST_F(InteropQuadTreeTest, removeOneDoesNotCauseMergeWhenAdjacentPointCountMoreThan4) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point0));

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point1));

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point2));

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point3));

  auto point4 = NovelRT_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point4));

  auto point5 = NovelRT_QuadTreePoint_createFromFloat(0.5f, 0.5f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point5));

  EXPECT_TRUE(NovelRT_QuadTree_tryRemove(_quadTree, point5));

  EXPECT_EQ(NovelRT_QuadTree_getPointCount(_quadTree), 0u);

  EXPECT_EQ(NovelRT_QuadTree_getPointCount(NovelRT_QuadTree_getTopLeft(_quadTree)), 2u);
  EXPECT_EQ(NovelRT_QuadTree_getPointCount(NovelRT_QuadTree_getTopRight(_quadTree)), 1u);
  EXPECT_EQ(NovelRT_QuadTree_getPointCount(NovelRT_QuadTree_getBottomLeft(_quadTree)), 1u);
  EXPECT_EQ(NovelRT_QuadTree_getPointCount(NovelRT_QuadTree_getBottomRight(_quadTree)), 1u);

  EXPECT_EQ(NovelRT_QuadTree_getPoint(NovelRT_QuadTree_getTopLeft(_quadTree), 0), point0);
  EXPECT_EQ(NovelRT_QuadTree_getPoint(NovelRT_QuadTree_getTopRight(_quadTree), 0), point1);
  EXPECT_EQ(NovelRT_QuadTree_getPoint(NovelRT_QuadTree_getBottomLeft(_quadTree), 0), point2);
  EXPECT_EQ(NovelRT_QuadTree_getPoint(NovelRT_QuadTree_getBottomRight(_quadTree), 0), point3);
  EXPECT_EQ(NovelRT_QuadTree_getPoint(NovelRT_QuadTree_getTopLeft(_quadTree), 1), point4);
}

TEST_F(InteropQuadTreeTest, getIntersectingPointsForQuadTreeBoundsReturnsAll) {
  auto point0 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point0));

  auto point1 = NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point1));

  auto point2 = NovelRT_QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point2));

  auto point3 = NovelRT_QuadTreePoint_createFromFloat(1.0f, -1.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point3));

  auto point4 = NovelRT_QuadTreePoint_createFromFloat(0.0f, 0.0f);
  EXPECT_TRUE(NovelRT_QuadTree_tryInsert(_quadTree, point4));

  auto intersectingPoints = NovelRT_QuadTree_getIntersectingPoints(_quadTree, NovelRT_QuadTree_getBounds(_quadTree));  
  auto intersectingPointsVector = reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(intersectingPoints);

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

