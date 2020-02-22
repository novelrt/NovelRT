// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

static const float TEST_WIDTH = 1920.0f;
static const float TEST_HEIGHT = 1080.0f;

struct SimpleQuadTreePoint : QuadTreePoint {
  GeoVector<float> position;

  SimpleQuadTreePoint(float x, float y) {
    position = GeoVector<float>(x, y);
  }

  const GeoVector<float>& getPosition() const noexcept override {
    return position;
  }
};

typedef QuadTree<SimpleQuadTreePoint> SimpleQuadTree;

GeoBounds getCenteredBounds(float width, float height) {
  auto size = GeoVector<float>(width, height);
  auto position = GeoVector<float>(0, 0);
  return GeoBounds(position, size, 0);
}

class QuadTreeTest : public testing::Test {
protected:
  std::unique_ptr<SimpleQuadTree> _quadTree;

  void SetUp() override {
    auto bounds = getCenteredBounds(TEST_WIDTH, TEST_HEIGHT);
    _quadTree = std::make_unique<SimpleQuadTree>(bounds);
  }
};

TEST_F(QuadTreeTest, createCorrectlySetsBounds)
{
  auto expectedBounds = getCenteredBounds(TEST_WIDTH, TEST_HEIGHT);
  EXPECT_EQ(_quadTree->getBounds(), expectedBounds);
}

TEST_F(QuadTreeTest, createHasNoPoints)
{
  EXPECT_EQ(_quadTree->getPointCount(), 0);
}

TEST_F(QuadTreeTest, createHasNoChildren)
{
  EXPECT_EQ(_quadTree->getTopLeft(), nullptr);
  EXPECT_EQ(_quadTree->getTopRight(), nullptr);
  EXPECT_EQ(_quadTree->getBottomLeft(), nullptr);
  EXPECT_EQ(_quadTree->getBottomRight(), nullptr);
}

TEST_F(QuadTreeTest, getPointReturnsNullForTooLargeIndex)
{
  EXPECT_EQ(_quadTree->getPoint(0), nullptr);
  EXPECT_EQ(_quadTree->getPoint(1), nullptr);
  EXPECT_EQ(_quadTree->getPoint(2), nullptr);
  EXPECT_EQ(_quadTree->getPoint(3), nullptr);
}

TEST_F(QuadTreeTest, insertFourDoesNotSubdivide) {
  auto point0 = std::make_shared<SimpleQuadTreePoint>(-1.0f, 1.0f);
  _quadTree->tryInsert(point0);

  auto point1 = std::make_shared<SimpleQuadTreePoint>(1.0f, 1.0f);
  _quadTree->tryInsert(point1);

  auto point2 = std::make_shared<SimpleQuadTreePoint>(-1.0f, -1.0f);
  _quadTree->tryInsert(point2);

  auto point3 = std::make_shared<SimpleQuadTreePoint>(1.0f, -1.0f);
  _quadTree->tryInsert(point3);

  EXPECT_EQ(_quadTree->getPointCount(), 4);

  EXPECT_EQ(_quadTree->getPoint(0), point0);
  EXPECT_EQ(_quadTree->getPoint(1), point1);
  EXPECT_EQ(_quadTree->getPoint(2), point2);
  EXPECT_EQ(_quadTree->getPoint(3), point3);

  EXPECT_EQ(_quadTree->getTopLeft(), nullptr);
  EXPECT_EQ(_quadTree->getTopRight(), nullptr);
  EXPECT_EQ(_quadTree->getBottomLeft(), nullptr);
  EXPECT_EQ(_quadTree->getBottomRight(), nullptr);
}

TEST_F(QuadTreeTest, insertFiveDoesSubdivideAndPointsAreCorrect) {
  auto point0 = std::make_shared<SimpleQuadTreePoint>(-1.0f, 1.0f);
  _quadTree->tryInsert(point0);

  auto point1 = std::make_shared<SimpleQuadTreePoint>(1.0f, 1.0f);
  _quadTree->tryInsert(point1);

  auto point2 = std::make_shared<SimpleQuadTreePoint>(-1.0f, -1.0f);
  _quadTree->tryInsert(point2);

  auto point3 = std::make_shared<SimpleQuadTreePoint>(1.0f, -1.0f);
  _quadTree->tryInsert(point3);

  auto point4 = std::make_shared<SimpleQuadTreePoint>(0.0f, 0.0f);
  _quadTree->tryInsert(point4);

  EXPECT_EQ(_quadTree->getPointCount(), 0);

  EXPECT_EQ(_quadTree->getTopLeft()->getPointCount(), 2);
  EXPECT_EQ(_quadTree->getTopRight()->getPointCount(), 1);
  EXPECT_EQ(_quadTree->getBottomLeft()->getPointCount(), 1);
  EXPECT_EQ(_quadTree->getBottomRight()->getPointCount(), 1);

  EXPECT_EQ(_quadTree->getTopLeft()->getPoint(0), point0);
  EXPECT_EQ(_quadTree->getTopRight()->getPoint(0), point1);
  EXPECT_EQ(_quadTree->getBottomLeft()->getPoint(0), point2);
  EXPECT_EQ(_quadTree->getBottomRight()->getPoint(0), point3);
  EXPECT_EQ(_quadTree->getTopLeft()->getPoint(1), point4);
}

TEST_F(QuadTreeTest, insertFiveDoesSubdivideAndBoundsAreCorrect) {
  auto point0 = std::make_shared<SimpleQuadTreePoint>(-1.0f, 1.0f);
  _quadTree->tryInsert(point0);

  auto point1 = std::make_shared<SimpleQuadTreePoint>(1.0f, 1.0f);
  _quadTree->tryInsert(point1);

  auto point2 = std::make_shared<SimpleQuadTreePoint>(-1.0f, -1.0f);
  _quadTree->tryInsert(point2);

  auto point3 = std::make_shared<SimpleQuadTreePoint>(1.0f, -1.0f);
  _quadTree->tryInsert(point3);

  auto point4 = std::make_shared<SimpleQuadTreePoint>(0.0f, 0.0f);
  _quadTree->tryInsert(point4);

  EXPECT_EQ(_quadTree->getPointCount(), 0);

  EXPECT_EQ(_quadTree->getTopLeft()->getPointCount(), 2);
  EXPECT_EQ(_quadTree->getTopRight()->getPointCount(), 1);
  EXPECT_EQ(_quadTree->getBottomLeft()->getPointCount(), 1);
  EXPECT_EQ(_quadTree->getBottomRight()->getPointCount(), 1);

  auto expectedSize = GeoVector(TEST_WIDTH / 2, TEST_HEIGHT / 2);

  EXPECT_EQ(_quadTree->getTopLeft()->getBounds(), GeoBounds(GeoVector<float>(-TEST_WIDTH / 4, TEST_HEIGHT / 4), expectedSize, 0));
  EXPECT_EQ(_quadTree->getTopRight()->getBounds(), GeoBounds(GeoVector<float>(TEST_WIDTH / 4, TEST_HEIGHT / 4), expectedSize, 0));
  EXPECT_EQ(_quadTree->getBottomLeft()->getBounds(), GeoBounds(GeoVector<float>(-TEST_WIDTH / 4, -TEST_HEIGHT / 4), expectedSize, 0));
  EXPECT_EQ(_quadTree->getBottomRight()->getBounds(), GeoBounds(GeoVector<float>(TEST_WIDTH / 4, -TEST_HEIGHT / 4), expectedSize, 0));
}

TEST_F(QuadTreeTest, getIntersectingPointsReturnsAllPoints) {
  auto point0 = std::make_shared<SimpleQuadTreePoint>(-1.0f, 1.0f);
  _quadTree->tryInsert(point0);

  auto point1 = std::make_shared<SimpleQuadTreePoint>(1.0f, 1.0f);
  _quadTree->tryInsert(point1);

  auto point2 = std::make_shared<SimpleQuadTreePoint>(-1.0f, -1.0f);
  _quadTree->tryInsert(point2);

  auto point3 = std::make_shared<SimpleQuadTreePoint>(1.0f, -1.0f);
  _quadTree->tryInsert(point3);

  auto point4 = std::make_shared<SimpleQuadTreePoint>(0.0f, 0.0f);
  _quadTree->tryInsert(point4);

  auto intersectingPoints = _quadTree->getIntersectingPoints(_quadTree->getBounds());

  EXPECT_EQ(intersectingPoints.size(), 5);

  EXPECT_EQ(intersectingPoints[0], point0);
  EXPECT_EQ(intersectingPoints[1], point4);
  EXPECT_EQ(intersectingPoints[2], point1);
  EXPECT_EQ(intersectingPoints[3], point2);
  EXPECT_EQ(intersectingPoints[4], point3);
}
