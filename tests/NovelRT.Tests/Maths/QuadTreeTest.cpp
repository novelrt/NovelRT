// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

static const float TEST_WIDTH = 1920.0f;
static const float TEST_HEIGHT = 1080.0f;

GeoBounds getCenteredBounds(float width, float height)
{
    auto size = GeoVector2F(width, height);
    auto position = GeoVector2F(0, 0);
    return GeoBounds(position, size, 0);
}

class QuadTreeTest : public testing::Test
{
protected:
    std::shared_ptr<QuadTree> _quadTree;

    void SetUp() override
    {
        auto bounds = getCenteredBounds(TEST_WIDTH, TEST_HEIGHT);
        _quadTree = std::make_shared<QuadTree>(bounds);
    }
};

TEST_F(QuadTreeTest, createCorrectlySetsBounds)
{
    auto expectedBounds = getCenteredBounds(TEST_WIDTH, TEST_HEIGHT);
    EXPECT_EQ(_quadTree->getBounds(), expectedBounds);
}

TEST_F(QuadTreeTest, createHasNoPoints)
{
    EXPECT_EQ(_quadTree->getPointCount(), 0u);
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

TEST_F(QuadTreeTest, insertOneReturnsTrue)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    EXPECT_EQ(true, _quadTree->tryInsert(point0));
}

TEST_F(QuadTreeTest, insertFourDoesNotSubdivide)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    _quadTree->tryInsert(point0);

    auto point1 = std::make_shared<QuadTreePoint>(1.0f, 1.0f);
    _quadTree->tryInsert(point1);

    auto point2 = std::make_shared<QuadTreePoint>(-1.0f, -1.0f);
    _quadTree->tryInsert(point2);

    auto point3 = std::make_shared<QuadTreePoint>(1.0f, -1.0f);
    _quadTree->tryInsert(point3);

    EXPECT_EQ(_quadTree->getPointCount(), 4u);

    EXPECT_EQ(_quadTree->getPoint(0), point0);
    EXPECT_EQ(_quadTree->getPoint(1), point1);
    EXPECT_EQ(_quadTree->getPoint(2), point2);
    EXPECT_EQ(_quadTree->getPoint(3), point3);

    EXPECT_EQ(_quadTree->getTopLeft(), nullptr);
    EXPECT_EQ(_quadTree->getTopRight(), nullptr);
    EXPECT_EQ(_quadTree->getBottomLeft(), nullptr);
    EXPECT_EQ(_quadTree->getBottomRight(), nullptr);
}

TEST_F(QuadTreeTest, insertFiveDoesSubdivideAndPointsAreCorrect)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    _quadTree->tryInsert(point0);

    auto point1 = std::make_shared<QuadTreePoint>(1.0f, 1.0f);
    _quadTree->tryInsert(point1);

    auto point2 = std::make_shared<QuadTreePoint>(-1.0f, -1.0f);
    _quadTree->tryInsert(point2);

    auto point3 = std::make_shared<QuadTreePoint>(1.0f, -1.0f);
    _quadTree->tryInsert(point3);

    auto point4 = std::make_shared<QuadTreePoint>(0.0f, 0.0f);
    _quadTree->tryInsert(point4);

    EXPECT_EQ(_quadTree->getPointCount(), 0u);

    EXPECT_EQ(_quadTree->getTopLeft()->getPointCount(), 2u);
    EXPECT_EQ(_quadTree->getTopRight()->getPointCount(), 1u);
    EXPECT_EQ(_quadTree->getBottomLeft()->getPointCount(), 1u);
    EXPECT_EQ(_quadTree->getBottomRight()->getPointCount(), 1u);

    EXPECT_EQ(_quadTree->getTopLeft()->getPoint(0), point0);
    EXPECT_EQ(_quadTree->getTopRight()->getPoint(0), point1);
    EXPECT_EQ(_quadTree->getBottomLeft()->getPoint(0), point2);
    EXPECT_EQ(_quadTree->getBottomRight()->getPoint(0), point3);
    EXPECT_EQ(_quadTree->getTopLeft()->getPoint(1), point4);
}

TEST_F(QuadTreeTest, insertFiveDoesSubdivideAndBoundsAreCorrect)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    _quadTree->tryInsert(point0);

    auto point1 = std::make_shared<QuadTreePoint>(1.0f, 1.0f);
    _quadTree->tryInsert(point1);

    auto point2 = std::make_shared<QuadTreePoint>(-1.0f, -1.0f);
    _quadTree->tryInsert(point2);

    auto point3 = std::make_shared<QuadTreePoint>(1.0f, -1.0f);
    _quadTree->tryInsert(point3);

    auto point4 = std::make_shared<QuadTreePoint>(0.0f, 0.0f);
    _quadTree->tryInsert(point4);

    EXPECT_EQ(_quadTree->getPointCount(), 0u);

    EXPECT_EQ(_quadTree->getTopLeft()->getPointCount(), 2u);
    EXPECT_EQ(_quadTree->getTopRight()->getPointCount(), 1u);
    EXPECT_EQ(_quadTree->getBottomLeft()->getPointCount(), 1u);
    EXPECT_EQ(_quadTree->getBottomRight()->getPointCount(), 1u);

    auto expectedSize = GeoVector2F(TEST_WIDTH / 2, TEST_HEIGHT / 2);

    EXPECT_EQ(_quadTree->getTopLeft()->getBounds(),
              GeoBounds(GeoVector2F(-TEST_WIDTH / 4, TEST_HEIGHT / 4), expectedSize, 0));
    EXPECT_EQ(_quadTree->getTopRight()->getBounds(),
              GeoBounds(GeoVector2F(TEST_WIDTH / 4, TEST_HEIGHT / 4), expectedSize, 0));
    EXPECT_EQ(_quadTree->getBottomLeft()->getBounds(),
              GeoBounds(GeoVector2F(-TEST_WIDTH / 4, -TEST_HEIGHT / 4), expectedSize, 0));
    EXPECT_EQ(_quadTree->getBottomRight()->getBounds(),
              GeoBounds(GeoVector2F(TEST_WIDTH / 4, -TEST_HEIGHT / 4), expectedSize, 0));
}

TEST_F(QuadTreeTest, insertOutOfBoundsReturnsFalse)
{
    auto point0 = std::make_shared<QuadTreePoint>(3840.0f, 2160.0f);
    EXPECT_EQ(false, _quadTree->tryInsert(point0));
}

TEST_F(QuadTreeTest, getIntersectingPointsReturnsAllPoints)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    _quadTree->tryInsert(point0);

    auto point1 = std::make_shared<QuadTreePoint>(1.0f, 1.0f);
    _quadTree->tryInsert(point1);

    auto point2 = std::make_shared<QuadTreePoint>(-1.0f, -1.0f);
    _quadTree->tryInsert(point2);

    auto point3 = std::make_shared<QuadTreePoint>(1.0f, -1.0f);
    _quadTree->tryInsert(point3);

    auto point4 = std::make_shared<QuadTreePoint>(0.0f, 0.0f);
    _quadTree->tryInsert(point4);

    auto intersectingPoints = _quadTree->getIntersectingPoints(_quadTree->getBounds());

    EXPECT_EQ(intersectingPoints.size(), 5u);

    EXPECT_EQ(intersectingPoints[0], point0);
    EXPECT_EQ(intersectingPoints[1], point4);
    EXPECT_EQ(intersectingPoints[2], point1);
    EXPECT_EQ(intersectingPoints[3], point2);
    EXPECT_EQ(intersectingPoints[4], point3);
}

TEST_F(QuadTreeTest, removeExistingReturnsTrue)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    _quadTree->tryInsert(point0);

    EXPECT_EQ(true, _quadTree->tryRemove(point0));
}

TEST_F(QuadTreeTest, removeNoneExistingReturnsFalse)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    EXPECT_EQ(false, _quadTree->tryRemove(point0));
}

TEST_F(QuadTreeTest, removeOneCausesMergeWhenAdjacentPointCountLessThan5)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    _quadTree->tryInsert(point0);

    auto point1 = std::make_shared<QuadTreePoint>(1.0f, 1.0f);
    _quadTree->tryInsert(point1);

    auto point2 = std::make_shared<QuadTreePoint>(-1.0f, -1.0f);
    _quadTree->tryInsert(point2);

    auto point3 = std::make_shared<QuadTreePoint>(1.0f, -1.0f);
    _quadTree->tryInsert(point3);

    auto point4 = std::make_shared<QuadTreePoint>(0.0f, 0.0f);
    _quadTree->tryInsert(point4);

    _quadTree->tryRemove(point4);

    EXPECT_EQ(_quadTree->getPointCount(), 4u);

    EXPECT_EQ(_quadTree->getPoint(0), point0);
    EXPECT_EQ(_quadTree->getPoint(1), point1);
    EXPECT_EQ(_quadTree->getPoint(2), point2);
    EXPECT_EQ(_quadTree->getPoint(3), point3);

    EXPECT_EQ(_quadTree->getTopLeft(), nullptr);
    EXPECT_EQ(_quadTree->getTopRight(), nullptr);
    EXPECT_EQ(_quadTree->getBottomLeft(), nullptr);
    EXPECT_EQ(_quadTree->getBottomRight(), nullptr);
}

TEST_F(QuadTreeTest, removeOneDoesNotCauseMergeWhenAdjacentPointCountMoreThan4)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    _quadTree->tryInsert(point0);

    auto point1 = std::make_shared<QuadTreePoint>(1.0f, 1.0f);
    _quadTree->tryInsert(point1);

    auto point2 = std::make_shared<QuadTreePoint>(-1.0f, -1.0f);
    _quadTree->tryInsert(point2);

    auto point3 = std::make_shared<QuadTreePoint>(1.0f, -1.0f);
    _quadTree->tryInsert(point3);

    auto point4 = std::make_shared<QuadTreePoint>(0.0f, 0.0f);
    _quadTree->tryInsert(point4);

    auto point5 = std::make_shared<QuadTreePoint>(0.5f, 0.5f);
    _quadTree->tryInsert(point5);

    _quadTree->tryRemove(point5);

    EXPECT_EQ(_quadTree->getPointCount(), 0u);

    EXPECT_EQ(_quadTree->getTopLeft()->getPointCount(), 2u);
    EXPECT_EQ(_quadTree->getTopRight()->getPointCount(), 1u);
    EXPECT_EQ(_quadTree->getBottomLeft()->getPointCount(), 1u);
    EXPECT_EQ(_quadTree->getBottomRight()->getPointCount(), 1u);

    EXPECT_EQ(_quadTree->getTopLeft()->getPoint(0), point0);
    EXPECT_EQ(_quadTree->getTopRight()->getPoint(0), point1);
    EXPECT_EQ(_quadTree->getBottomLeft()->getPoint(0), point2);
    EXPECT_EQ(_quadTree->getBottomRight()->getPoint(0), point3);
    EXPECT_EQ(_quadTree->getTopLeft()->getPoint(1), point4);

    EXPECT_EQ(_quadTree->getTopLeft()->getPoint(0), point0);
    EXPECT_EQ(_quadTree->getTopRight()->getPoint(0), point1);
    EXPECT_EQ(_quadTree->getBottomLeft()->getPoint(0), point2);
    EXPECT_EQ(_quadTree->getBottomRight()->getPoint(0), point3);
    EXPECT_EQ(_quadTree->getTopLeft()->getPoint(1), point4);
}

TEST_F(QuadTreeTest, getIntersectingPointsForQuadTreeBoundsReturnsAll)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    _quadTree->tryInsert(point0);

    auto point1 = std::make_shared<QuadTreePoint>(1.0f, 1.0f);
    _quadTree->tryInsert(point1);

    auto point2 = std::make_shared<QuadTreePoint>(-1.0f, -1.0f);
    _quadTree->tryInsert(point2);

    auto point3 = std::make_shared<QuadTreePoint>(1.0f, -1.0f);
    _quadTree->tryInsert(point3);

    auto point4 = std::make_shared<QuadTreePoint>(0.0f, 0.0f);
    _quadTree->tryInsert(point4);

    auto intersectingPoints = _quadTree->getIntersectingPoints(_quadTree->getBounds());
    EXPECT_EQ(intersectingPoints.size(), 5u);

    EXPECT_EQ(intersectingPoints[0], point0);
    EXPECT_EQ(intersectingPoints[1], point4);
    EXPECT_EQ(intersectingPoints[2], point1);
    EXPECT_EQ(intersectingPoints[3], point2);
    EXPECT_EQ(intersectingPoints[4], point3);
}
