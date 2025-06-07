// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

static const float TEST_WIDTH = 1920.0f;
static const float TEST_HEIGHT = 1080.0f;

GeoBounds GetCenteredBounds(float width, float height)
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
        auto bounds = GetCenteredBounds(TEST_WIDTH, TEST_HEIGHT);
        _quadTree = std::make_shared<QuadTree>(bounds);
    }
};

TEST_F(QuadTreeTest, CreateCorrectlySetsBounds)
{
    auto expectedBounds = GetCenteredBounds(TEST_WIDTH, TEST_HEIGHT);
    EXPECT_EQ(_quadTree->GetBounds(), expectedBounds);
}

TEST_F(QuadTreeTest, CreateHasNoPoints)
{
    EXPECT_EQ(_quadTree->GetPointCount(), 0u);
}

TEST_F(QuadTreeTest, CreateHasNoChildren)
{
    EXPECT_EQ(_quadTree->GetTopLeft(), nullptr);
    EXPECT_EQ(_quadTree->GetTopRight(), nullptr);
    EXPECT_EQ(_quadTree->GetBottomLeft(), nullptr);
    EXPECT_EQ(_quadTree->GetBottomRight(), nullptr);
}

TEST_F(QuadTreeTest, GetPointReturnsNullForTooLargeIndex)
{
    EXPECT_EQ(_quadTree->GetPoint(0), nullptr);
    EXPECT_EQ(_quadTree->GetPoint(1), nullptr);
    EXPECT_EQ(_quadTree->GetPoint(2), nullptr);
    EXPECT_EQ(_quadTree->GetPoint(3), nullptr);
}

TEST_F(QuadTreeTest, InsertOneReturnsTrue)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    EXPECT_EQ(true, _quadTree->TryInsert(point0));
}

TEST_F(QuadTreeTest, InsertFourDoesNotSubdivide)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    unused(_quadTree->TryInsert(point0));

    auto point1 = std::make_shared<QuadTreePoint>(1.0f, 1.0f);
    unused(_quadTree->TryInsert(point1));

    auto point2 = std::make_shared<QuadTreePoint>(-1.0f, -1.0f);
    unused(_quadTree->TryInsert(point2));

    auto point3 = std::make_shared<QuadTreePoint>(1.0f, -1.0f);
    unused(_quadTree->TryInsert(point3));

    EXPECT_EQ(_quadTree->GetPointCount(), 4u);

    EXPECT_EQ(_quadTree->GetPoint(0), point0);
    EXPECT_EQ(_quadTree->GetPoint(1), point1);
    EXPECT_EQ(_quadTree->GetPoint(2), point2);
    EXPECT_EQ(_quadTree->GetPoint(3), point3);

    EXPECT_EQ(_quadTree->GetTopLeft(), nullptr);
    EXPECT_EQ(_quadTree->GetTopRight(), nullptr);
    EXPECT_EQ(_quadTree->GetBottomLeft(), nullptr);
    EXPECT_EQ(_quadTree->GetBottomRight(), nullptr);
}

TEST_F(QuadTreeTest, InsertFiveDoesSubdivideAndPointsAreCorrect)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    unused(_quadTree->TryInsert(point0));

    auto point1 = std::make_shared<QuadTreePoint>(1.0f, 1.0f);
    unused(_quadTree->TryInsert(point1));

    auto point2 = std::make_shared<QuadTreePoint>(-1.0f, -1.0f);
    unused(_quadTree->TryInsert(point2));

    auto point3 = std::make_shared<QuadTreePoint>(1.0f, -1.0f);
    unused(_quadTree->TryInsert(point3));

    auto point4 = std::make_shared<QuadTreePoint>(0.0f, 0.0f);
    unused(_quadTree->TryInsert(point4));

    EXPECT_EQ(_quadTree->GetPointCount(), 0u);

    EXPECT_EQ(_quadTree->GetTopLeft()->GetPointCount(), 2u);
    EXPECT_EQ(_quadTree->GetTopRight()->GetPointCount(), 1u);
    EXPECT_EQ(_quadTree->GetBottomLeft()->GetPointCount(), 1u);
    EXPECT_EQ(_quadTree->GetBottomRight()->GetPointCount(), 1u);

    EXPECT_EQ(_quadTree->GetTopLeft()->GetPoint(0), point0);
    EXPECT_EQ(_quadTree->GetTopRight()->GetPoint(0), point1);
    EXPECT_EQ(_quadTree->GetBottomLeft()->GetPoint(0), point2);
    EXPECT_EQ(_quadTree->GetBottomRight()->GetPoint(0), point3);
    EXPECT_EQ(_quadTree->GetTopLeft()->GetPoint(1), point4);
}

TEST_F(QuadTreeTest, InsertFiveDoesSubdivideAndBoundsAreCorrect)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    unused(_quadTree->TryInsert(point0));

    auto point1 = std::make_shared<QuadTreePoint>(1.0f, 1.0f);
    unused(_quadTree->TryInsert(point1));

    auto point2 = std::make_shared<QuadTreePoint>(-1.0f, -1.0f);
    unused(_quadTree->TryInsert(point2));

    auto point3 = std::make_shared<QuadTreePoint>(1.0f, -1.0f);
    unused(_quadTree->TryInsert(point3));

    auto point4 = std::make_shared<QuadTreePoint>(0.0f, 0.0f);
    unused(_quadTree->TryInsert(point4));

    EXPECT_EQ(_quadTree->GetPointCount(), 0u);

    EXPECT_EQ(_quadTree->GetTopLeft()->GetPointCount(), 2u);
    EXPECT_EQ(_quadTree->GetTopRight()->GetPointCount(), 1u);
    EXPECT_EQ(_quadTree->GetBottomLeft()->GetPointCount(), 1u);
    EXPECT_EQ(_quadTree->GetBottomRight()->GetPointCount(), 1u);

    auto expectedSize = GeoVector2F(TEST_WIDTH / 2, TEST_HEIGHT / 2);

    EXPECT_EQ(_quadTree->GetTopLeft()->GetBounds(),
              GeoBounds(GeoVector2F(-TEST_WIDTH / 4, TEST_HEIGHT / 4), expectedSize, 0));
    EXPECT_EQ(_quadTree->GetTopRight()->GetBounds(),
              GeoBounds(GeoVector2F(TEST_WIDTH / 4, TEST_HEIGHT / 4), expectedSize, 0));
    EXPECT_EQ(_quadTree->GetBottomLeft()->GetBounds(),
              GeoBounds(GeoVector2F(-TEST_WIDTH / 4, -TEST_HEIGHT / 4), expectedSize, 0));
    EXPECT_EQ(_quadTree->GetBottomRight()->GetBounds(),
              GeoBounds(GeoVector2F(TEST_WIDTH / 4, -TEST_HEIGHT / 4), expectedSize, 0));
}

TEST_F(QuadTreeTest, InsertOutOfBoundsReturnsFalse)
{
    auto point0 = std::make_shared<QuadTreePoint>(3840.0f, 2160.0f);
    EXPECT_EQ(false, _quadTree->TryInsert(point0));
}

TEST_F(QuadTreeTest, GetIntersectingPointsReturnsAllPoints)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    unused(_quadTree->TryInsert(point0));

    auto point1 = std::make_shared<QuadTreePoint>(1.0f, 1.0f);
    unused(_quadTree->TryInsert(point1));

    auto point2 = std::make_shared<QuadTreePoint>(-1.0f, -1.0f);
    unused(_quadTree->TryInsert(point2));

    auto point3 = std::make_shared<QuadTreePoint>(1.0f, -1.0f);
    unused(_quadTree->TryInsert(point3));

    auto point4 = std::make_shared<QuadTreePoint>(0.0f, 0.0f);
    unused(_quadTree->TryInsert(point4));

    auto intersectingPoints = _quadTree->GetIntersectingPoints(_quadTree->GetBounds());

    EXPECT_EQ(intersectingPoints.size(), 5u);

    EXPECT_EQ(intersectingPoints[0], point0);
    EXPECT_EQ(intersectingPoints[1], point4);
    EXPECT_EQ(intersectingPoints[2], point1);
    EXPECT_EQ(intersectingPoints[3], point2);
    EXPECT_EQ(intersectingPoints[4], point3);
}

TEST_F(QuadTreeTest, RemoveExistingReturnsTrue)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    unused(_quadTree->TryInsert(point0));

    EXPECT_EQ(true, _quadTree->TryRemove(point0));
}

TEST_F(QuadTreeTest, RemoveNoneExistingReturnsFalse)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    EXPECT_EQ(false, _quadTree->TryRemove(point0));
}

TEST_F(QuadTreeTest, RemoveOneCausesMergeWhenAdjacentPointCountLessThan5)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    unused(_quadTree->TryInsert(point0));

    auto point1 = std::make_shared<QuadTreePoint>(1.0f, 1.0f);
    unused(_quadTree->TryInsert(point1));

    auto point2 = std::make_shared<QuadTreePoint>(-1.0f, -1.0f);
    unused(_quadTree->TryInsert(point2));

    auto point3 = std::make_shared<QuadTreePoint>(1.0f, -1.0f);
    unused(_quadTree->TryInsert(point3));

    auto point4 = std::make_shared<QuadTreePoint>(0.0f, 0.0f);
    unused(_quadTree->TryInsert(point4));

    unused(_quadTree->TryRemove(point4));

    EXPECT_EQ(_quadTree->GetPointCount(), 4u);

    EXPECT_EQ(_quadTree->GetPoint(0), point0);
    EXPECT_EQ(_quadTree->GetPoint(1), point1);
    EXPECT_EQ(_quadTree->GetPoint(2), point2);
    EXPECT_EQ(_quadTree->GetPoint(3), point3);

    EXPECT_EQ(_quadTree->GetTopLeft(), nullptr);
    EXPECT_EQ(_quadTree->GetTopRight(), nullptr);
    EXPECT_EQ(_quadTree->GetBottomLeft(), nullptr);
    EXPECT_EQ(_quadTree->GetBottomRight(), nullptr);
}

TEST_F(QuadTreeTest, RemoveOneDoesNotCauseMergeWhenAdjacentPointCountMoreThan4)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    unused(_quadTree->TryInsert(point0));

    auto point1 = std::make_shared<QuadTreePoint>(1.0f, 1.0f);
    unused(_quadTree->TryInsert(point1));

    auto point2 = std::make_shared<QuadTreePoint>(-1.0f, -1.0f);
    unused(_quadTree->TryInsert(point2));

    auto point3 = std::make_shared<QuadTreePoint>(1.0f, -1.0f);
    unused(_quadTree->TryInsert(point3));

    auto point4 = std::make_shared<QuadTreePoint>(0.0f, 0.0f);
    unused(_quadTree->TryInsert(point4));

    auto point5 = std::make_shared<QuadTreePoint>(0.5f, 0.5f);
    unused(_quadTree->TryInsert(point5));

    unused(_quadTree->TryRemove(point5));

    EXPECT_EQ(_quadTree->GetPointCount(), 0u);

    EXPECT_EQ(_quadTree->GetTopLeft()->GetPointCount(), 2u);
    EXPECT_EQ(_quadTree->GetTopRight()->GetPointCount(), 1u);
    EXPECT_EQ(_quadTree->GetBottomLeft()->GetPointCount(), 1u);
    EXPECT_EQ(_quadTree->GetBottomRight()->GetPointCount(), 1u);

    EXPECT_EQ(_quadTree->GetTopLeft()->GetPoint(0), point0);
    EXPECT_EQ(_quadTree->GetTopRight()->GetPoint(0), point1);
    EXPECT_EQ(_quadTree->GetBottomLeft()->GetPoint(0), point2);
    EXPECT_EQ(_quadTree->GetBottomRight()->GetPoint(0), point3);
    EXPECT_EQ(_quadTree->GetTopLeft()->GetPoint(1), point4);

    EXPECT_EQ(_quadTree->GetTopLeft()->GetPoint(0), point0);
    EXPECT_EQ(_quadTree->GetTopRight()->GetPoint(0), point1);
    EXPECT_EQ(_quadTree->GetBottomLeft()->GetPoint(0), point2);
    EXPECT_EQ(_quadTree->GetBottomRight()->GetPoint(0), point3);
    EXPECT_EQ(_quadTree->GetTopLeft()->GetPoint(1), point4);
}

TEST_F(QuadTreeTest, GetIntersectingPointsForQuadTreeBoundsReturnsAll)
{
    auto point0 = std::make_shared<QuadTreePoint>(-1.0f, 1.0f);
    unused(_quadTree->TryInsert(point0));

    auto point1 = std::make_shared<QuadTreePoint>(1.0f, 1.0f);
    unused(_quadTree->TryInsert(point1));

    auto point2 = std::make_shared<QuadTreePoint>(-1.0f, -1.0f);
    unused(_quadTree->TryInsert(point2));

    auto point3 = std::make_shared<QuadTreePoint>(1.0f, -1.0f);
    unused(_quadTree->TryInsert(point3));

    auto point4 = std::make_shared<QuadTreePoint>(0.0f, 0.0f);
    unused(_quadTree->TryInsert(point4));

    auto intersectingPoints = _quadTree->GetIntersectingPoints(_quadTree->GetBounds());
    EXPECT_EQ(intersectingPoints.size(), 5u);

    EXPECT_EQ(intersectingPoints[0], point0);
    EXPECT_EQ(intersectingPoints[1], point4);
    EXPECT_EQ(intersectingPoints[2], point1);
    EXPECT_EQ(intersectingPoints[3], point2);
    EXPECT_EQ(intersectingPoints[4], point3);
}
