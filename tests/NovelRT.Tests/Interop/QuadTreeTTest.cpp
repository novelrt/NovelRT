// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/Maths/QuadTree_t.h"


using namespace NovelRT;
using namespace NovelRT::Maths;

static const float TEST_WIDTH = 1920.0f;
static const float TEST_HEIGHT = 1080.0f;

GeoBounds_t getCenteredBoundsC(float width, float height) {
  auto size = GeoVector2<float>(width, height);
  auto position = GeoVector2<float>(0, 0);
  GeoBounds* result = new GeoBounds(position, size, 0);
  return reinterpret_cast<GeoBounds_t&>(*result);
}

bool checkPointsForEqualityC(QuadTreePoint_t one, QuadTreePoint_t two) {
  auto left = reinterpret_cast<Maths::QuadTreePoint*>(one);
  auto right = reinterpret_cast<Maths::QuadTreePoint*>(two);
  return left->getPosition() == right->getPosition();
}

bool checkPointsForEqualityCpp(Maths::QuadTreePoint* left, Maths::QuadTreePoint* right) {
  return left->getPosition() == right->getPosition();
}

bool checkBoundsForEquality(GeoBounds_t one, GeoBounds_t two) {
  auto left = reinterpret_cast<GeoBounds&>(one);
  auto right = reinterpret_cast<GeoBounds&>(two);
  return left == right;
}

class InteropQuadTreeTest : public testing::Test {
protected:
  QuadTree_t _quadTree;

  void SetUp() override {
    auto bounds = new GeoBounds_t{};
    *bounds = getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
    _quadTree = QuadTree_create(*bounds);
  }

};

TEST_F(InteropQuadTreeTest, createCorrectlySetsBounds) {
  auto expectedBounds = getCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
  EXPECT_TRUE(checkBoundsForEquality(QuadTree_getBounds(_quadTree), expectedBounds));
}

 TEST_F(InteropQuadTreeTest, createHasNoPoints)
 {
   EXPECT_EQ(QuadTree_getPointCount(_quadTree), 0u);
 }

  TEST_F(InteropQuadTreeTest, createHasNoChildren)
  {
    EXPECT_EQ(QuadTree_getTopLeft(_quadTree), nullptr);
    EXPECT_EQ(QuadTree_getTopRight(_quadTree), nullptr);
    EXPECT_EQ(QuadTree_getBottomLeft(_quadTree), nullptr);
    EXPECT_EQ(QuadTree_getBottomRight(_quadTree), nullptr);
  }

 TEST_F(InteropQuadTreeTest, getPointReturnsNullForTooLargeIndex)
 {
   EXPECT_EQ(QuadTree_getPoint(_quadTree, 0), nullptr);
   EXPECT_EQ(QuadTree_getPoint(_quadTree, 1), nullptr);
   EXPECT_EQ(QuadTree_getPoint(_quadTree, 2), nullptr);
   EXPECT_EQ(QuadTree_getPoint(_quadTree, 3), nullptr);
 }

 TEST_F(InteropQuadTreeTest, insertOneReturnsTrue) {
   auto point0 = QuadTreePoint_createFromFloat(-1.0f, 1.0f);
   EXPECT_EQ(true, QuadTree_tryInsert(_quadTree, point0));
 }

 TEST_F(InteropQuadTreeTest, insertFourDoesNotSubdivide) {
   auto point0 = QuadTreePoint_createFromFloat(-1.0f, 1.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point0));

   auto point1 = QuadTreePoint_createFromFloat(1.0f, 1.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point1));

   auto point2 = QuadTreePoint_createFromFloat(-1.0f, -1.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point2));

   auto point3 = QuadTreePoint_createFromFloat(1.0f, -1.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point3));

   ASSERT_EQ(QuadTree_getPointCount(_quadTree), 4u);

   EXPECT_TRUE(checkPointsForEqualityC(QuadTree_getPoint(_quadTree, 0), point0));
   EXPECT_TRUE(checkPointsForEqualityC(QuadTree_getPoint(_quadTree, 1), point1));
   EXPECT_TRUE(checkPointsForEqualityC(QuadTree_getPoint(_quadTree, 2), point2));
   EXPECT_TRUE(checkPointsForEqualityC(QuadTree_getPoint(_quadTree, 3), point3));

   EXPECT_EQ(QuadTree_getTopLeft(_quadTree), nullptr);
   EXPECT_EQ(QuadTree_getTopRight(_quadTree), nullptr);
   EXPECT_EQ(QuadTree_getBottomLeft(_quadTree), nullptr);
   EXPECT_EQ(QuadTree_getBottomRight(_quadTree), nullptr);
 }

TEST_F(InteropQuadTreeTest, insertFiveDoesSubdivideAndPointsAreCorrect) {
  auto point0 = QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point0));

   auto point1 = QuadTreePoint_createFromFloat(1.0f, 1.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point1));

   auto point2 = QuadTreePoint_createFromFloat(-1.0f, -1.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point2));

   auto point3 = QuadTreePoint_createFromFloat(1.0f, -1.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point3));

   auto point4 = QuadTreePoint_createFromFloat(0.0f, 0.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point4));

   EXPECT_EQ(QuadTree_getPointCount(_quadTree), 0u);

   EXPECT_EQ(QuadTree_getPointCount(QuadTree_getTopLeft(_quadTree)), 2u);
   EXPECT_EQ(QuadTree_getPointCount(QuadTree_getTopRight(_quadTree)), 1u);
   EXPECT_EQ(QuadTree_getPointCount(QuadTree_getBottomLeft(_quadTree)), 1u);
   EXPECT_EQ(QuadTree_getPointCount(QuadTree_getBottomRight(_quadTree)), 1u);

   EXPECT_TRUE(checkPointsForEqualityC(QuadTree_getPoint(QuadTree_getTopLeft(_quadTree), 0), point0));
   EXPECT_TRUE(checkPointsForEqualityC(QuadTree_getPoint(QuadTree_getTopRight(_quadTree), 0), point1));
   EXPECT_TRUE(checkPointsForEqualityC(QuadTree_getPoint(QuadTree_getBottomLeft(_quadTree), 0), point2));
   EXPECT_TRUE(checkPointsForEqualityC(QuadTree_getPoint(QuadTree_getBottomRight(_quadTree), 0), point3));
   EXPECT_TRUE(checkPointsForEqualityC(QuadTree_getPoint(QuadTree_getTopLeft(_quadTree), 1), point4));
 }

 TEST_F(InteropQuadTreeTest, insertFiveDoesSubdivideAndBoundsAreCorrect) {
   auto point0 = QuadTreePoint_createFromFloat(-1.0f, 1.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point0));

   auto point1 = QuadTreePoint_createFromFloat(1.0f, 1.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point1));

   auto point2 = QuadTreePoint_createFromFloat(-1.0f, -1.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point2));

   auto point3 = QuadTreePoint_createFromFloat(1.0f, -1.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point3));

   auto point4 = QuadTreePoint_createFromFloat(0.0f, 0.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point4));

   EXPECT_EQ(QuadTree_getPointCount(_quadTree), 0u);

   EXPECT_EQ(QuadTree_getPointCount(QuadTree_getTopLeft(_quadTree)), 2u);
   EXPECT_EQ(QuadTree_getPointCount(QuadTree_getTopRight(_quadTree)), 1u);
   EXPECT_EQ(QuadTree_getPointCount(QuadTree_getBottomLeft(_quadTree)), 1u);
   EXPECT_EQ(QuadTree_getPointCount(QuadTree_getBottomRight(_quadTree)), 1u);

   auto expectedSize = GeoVector2F_create(TEST_WIDTH / 2, TEST_HEIGHT / 2);

   EXPECT_TRUE(checkBoundsForEquality(QuadTree_getBounds(QuadTree_getTopLeft(_quadTree)), GeoBounds_create(GeoVector2F_create(-TEST_WIDTH / 4, TEST_HEIGHT / 4), expectedSize, 0)));
   EXPECT_TRUE(checkBoundsForEquality(QuadTree_getBounds(QuadTree_getTopRight(_quadTree)), GeoBounds_create(GeoVector2F_create(TEST_WIDTH / 4, TEST_HEIGHT / 4), expectedSize, 0)));
   EXPECT_TRUE(checkBoundsForEquality(QuadTree_getBounds(QuadTree_getBottomLeft(_quadTree)), GeoBounds_create(GeoVector2F_create(-TEST_WIDTH / 4, -TEST_HEIGHT / 4), expectedSize, 0)));
   EXPECT_TRUE(checkBoundsForEquality(QuadTree_getBounds(QuadTree_getBottomRight(_quadTree)), GeoBounds_create(GeoVector2F_create(TEST_WIDTH / 4, -TEST_HEIGHT / 4), expectedSize, 0)));
 }

 TEST_F(InteropQuadTreeTest, insertOutOfBoundsReturnsFalse) {
   auto point0 = QuadTreePoint_createFromFloat(3840.0f, 2160.0f);
   EXPECT_EQ(false, QuadTree_tryInsert(_quadTree, point0));
 }

 TEST_F(InteropQuadTreeTest, getIntersectingPointsReturnsAllPoints) {
   auto point0 = QuadTreePoint_createFromFloat(-1.0f, 1.0f);
   auto point0Cpp = reinterpret_cast<std::shared_ptr<Maths::QuadTreePoint>&>(point0);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point0));

   auto point1 = QuadTreePoint_createFromFloat(1.0f, 1.0f);
   auto point1Cpp = reinterpret_cast<std::shared_ptr<Maths::QuadTreePoint>&>(point1);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point1));

   auto point2 = QuadTreePoint_createFromFloat(-1.0f, -1.0f);
   auto point2Cpp = reinterpret_cast<std::shared_ptr<Maths::QuadTreePoint>&>(point2);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point2));

   auto point3 = QuadTreePoint_createFromFloat(1.0f, -1.0f);
   auto point3Cpp = reinterpret_cast<std::shared_ptr<Maths::QuadTreePoint>&>(point3);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point3));

   auto point4 = QuadTreePoint_createFromFloat(0.0f, 0.0f);
   auto point4Cpp = reinterpret_cast<std::shared_ptr<Maths::QuadTreePoint>&>(point4);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point4));

   auto allPoints = QuadTree_getIntersectingPoints(_quadTree, QuadTree_getBounds(_quadTree));
   auto intersectingPoints = reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(allPoints);
   
   EXPECT_EQ(intersectingPoints->size(), 5u);

   EXPECT_TRUE(checkPointsForEqualityCpp(intersectingPoints->at(0).get(), point0Cpp.get()));
   EXPECT_TRUE(checkPointsForEqualityCpp(intersectingPoints->at(1).get(), point4Cpp.get()));
   EXPECT_TRUE(checkPointsForEqualityCpp(intersectingPoints->at(2).get(), point1Cpp.get()));
   EXPECT_TRUE(checkPointsForEqualityCpp(intersectingPoints->at(3).get(), point2Cpp.get()));
   EXPECT_TRUE(checkPointsForEqualityCpp(intersectingPoints->at(4).get(), point3Cpp.get()));
 }

 TEST_F(InteropQuadTreeTest, removeExistingReturnsTrue) {
   auto point0 = QuadTreePoint_createFromFloat(-1.0f, 1.0f);
   EXPECT_EQ(true, QuadTree_tryInsert(_quadTree, point0));

   EXPECT_EQ(true, QuadTree_tryRemove(_quadTree, point0));
 }

 TEST_F(InteropQuadTreeTest, removeNoneExistingReturnsFalse) {
   auto point0 = QuadTreePoint_createFromFloat(-1.0f, 1.0f);
   EXPECT_EQ(false, QuadTree_tryRemove(_quadTree, point0));
 }

 TEST_F(InteropQuadTreeTest, removeOneCausesMergeWhenAdjacentPointCountLessThan5) {
   auto point0 = QuadTreePoint_createFromFloat(-1.0f, 1.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point0));

   auto point1 = QuadTreePoint_createFromFloat(1.0f, 1.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point1));

   auto point2 = QuadTreePoint_createFromFloat(-1.0f, -1.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point2));

   auto point3 = QuadTreePoint_createFromFloat(1.0f, -1.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point3));

   auto point4 = QuadTreePoint_createFromFloat(0.0f, 0.0f);
   EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point4));

   EXPECT_TRUE(QuadTree_tryRemove(_quadTree, point4));

   auto aaaaa = reinterpret_cast<Maths::QuadTree*>(_quadTree);
   EXPECT_EQ(QuadTree_getPointCount(_quadTree), 4u);

   EXPECT_TRUE(checkPointsForEqualityC(QuadTree_getPoint(_quadTree, 0), point0));
   EXPECT_TRUE(checkPointsForEqualityC(QuadTree_getPoint(_quadTree, 1), point1));
   EXPECT_TRUE(checkPointsForEqualityC(QuadTree_getPoint(_quadTree, 2), point2));
   EXPECT_TRUE(checkPointsForEqualityC(QuadTree_getPoint(_quadTree, 3), point3));

   EXPECT_EQ(QuadTree_getTopLeft(_quadTree), nullptr);
   EXPECT_EQ(QuadTree_getTopRight(_quadTree), nullptr);
   EXPECT_EQ(QuadTree_getBottomLeft(_quadTree), nullptr);
   EXPECT_EQ(QuadTree_getBottomRight(_quadTree), nullptr);
 }

// TEST_F(InteropQuadTreeTest, removeOneDoesNotCauseMergeWhenAdjacentPointCountMoreThan4) {
//   auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
//   _quadTree->tryInsert(point0);
//
//   auto point1 = std::make_shared<QuadTreePoint>(1.0f, 1.0f);
//   _quadTree->tryInsert(point1);
//
//   auto point2 = std::make_shared<QuadTreePoint>(-1.0f, -1.0f);
//   _quadTree->tryInsert(point2);
//
//   auto point3 = std::make_shared<QuadTreePoint>(1.0f, -1.0f);
//   _quadTree->tryInsert(point3);
//
//   auto point4 = std::make_shared<QuadTreePoint>(0.0f, 0.0f);
//   _quadTree->tryInsert(point4);
//
//   auto point5 = std::make_shared<QuadTreePoint>(0.5f, 0.5f);
//   _quadTree->tryInsert(point5);
//
//   _quadTree->tryRemove(point5);
//
//   EXPECT_EQ(_quadTree->getPointCount(), 0u);
//
//   EXPECT_EQ(_quadTree->getTopLeft()->getPointCount(), 2u);
//   EXPECT_EQ(_quadTree->getTopRight()->getPointCount(), 1u);
//   EXPECT_EQ(_quadTree->getBottomLeft()->getPointCount(), 1u);
//   EXPECT_EQ(_quadTree->getBottomRight()->getPointCount(), 1u);
//
//   EXPECT_EQ(_quadTree->getTopLeft()->getPoint(0), point0);
//   EXPECT_EQ(_quadTree->getTopRight()->getPoint(0), point1);
//   EXPECT_EQ(_quadTree->getBottomLeft()->getPoint(0), point2);
//   EXPECT_EQ(_quadTree->getBottomRight()->getPoint(0), point3);
//   EXPECT_EQ(_quadTree->getTopLeft()->getPoint(1), point4);
//
//   EXPECT_EQ(_quadTree->getTopLeft()->getPoint(0), point0);
//   EXPECT_EQ(_quadTree->getTopRight()->getPoint(0), point1);
//   EXPECT_EQ(_quadTree->getBottomLeft()->getPoint(0), point2);
//   EXPECT_EQ(_quadTree->getBottomRight()->getPoint(0), point3);
//   EXPECT_EQ(_quadTree->getTopLeft()->getPoint(1), point4);
// }

TEST_F(InteropQuadTreeTest, getIntersectingPointsForQuadTreeBoundsReturnsAll) {
  auto point0 = QuadTreePoint_createFromFloat(-1.0f, 1.0f);
  EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point0));

  auto point1 = QuadTreePoint_createFromFloat(1.0f, 1.0f);
  EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point1));

  auto point2 = QuadTreePoint_createFromFloat(-1.0f, -1.0f);
  EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point2));

  auto point3 = QuadTreePoint_createFromFloat(1.0f, -1.0f);
  EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point3));

  auto point4 = QuadTreePoint_createFromFloat(0.0f, 0.0f);
  EXPECT_TRUE(QuadTree_tryInsert(_quadTree, point4));

  auto intersectingPoints = QuadTree_getIntersectingPoints(_quadTree, QuadTree_getBounds(_quadTree));  
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

