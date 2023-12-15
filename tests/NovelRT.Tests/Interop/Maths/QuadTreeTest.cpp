// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtGeoBounds.h>
#include <NovelRT.Interop/Maths/NrtQuadTree.h>
#include <NovelRT.Interop/Maths/NrtQuadTreePoint.h>
#include <NovelRT/NovelRT.h>

#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

static const float TEST_WIDTH = 1920.0f;
static const float TEST_HEIGHT = 1080.0f;

NrtGeoBounds GetCenteredBoundsC(float width, float height)
{
    auto size = GeoVector2F(width, height);
    auto position = GeoVector2F(0, 0);
    GeoBounds* result = new GeoBounds(position, size, 0);
    return *reinterpret_cast<NrtGeoBounds*>(result);
}

bool CheckPointsForEqualityC(NrtQuadTreePointHandle one, NrtQuadTreePointHandle two)
{
    auto left = reinterpret_cast<Maths::QuadTreePoint*>(one);
    auto right = reinterpret_cast<Maths::QuadTreePoint*>(two);
    return left->GetPosition() == right->GetPosition();
}

bool CheckPointsForEqualityCpp(Maths::QuadTreePoint* left, Maths::QuadTreePoint* right)
{
    return left->GetPosition() == right->GetPosition();
}

bool CheckBoundsForEquality(NrtGeoBounds one, NrtGeoBounds two)
{
    auto left = reinterpret_cast<GeoBounds&>(one);
    auto right = reinterpret_cast<GeoBounds&>(two);
    return left == right;
}

class InteropQuadTreeTest : public testing::Test
{
protected:
    NrtQuadTreeHandle _quadTree;

    void SetUp() override
    {
        auto bounds = new NrtGeoBounds{};
        *bounds = GetCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
        _quadTree = Nrt_QuadTree_Create(*bounds);
    }
};

TEST_F(InteropQuadTreeTest, CreateReturnsValidHandle)
{
    EXPECT_NE(reinterpret_cast<Maths::QuadTree*>(Nrt_QuadTree_Create(GetCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT))),
              nullptr);
}

TEST_F(InteropQuadTreeTest, DeleteReturnsSuccessWhenGivenValidHandle)
{
    NrtQuadTreeHandle tree = Nrt_QuadTree_Create(GetCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT));
    EXPECT_EQ(Nrt_QuadTree_Destroy(tree), NRT_SUCCESS);
}

TEST_F(InteropQuadTreeTest, DeleteReturnsNullInstanceFailureWhenGivenNullptr)
{
    ASSERT_EQ(Nrt_QuadTree_Destroy(nullptr), NRT_FAILURE_NULL_INSTANCE_PROVIDED);
}

TEST_F(InteropQuadTreeTest,
       DeleteReturnsAlreadyDeletedOrRemovedFailureWhenPointIsBeingHeldOntoElsewhereAndHasAlreadyBeenDeletedFromCache)
{
    auto handle = reinterpret_cast<Maths::QuadTree*>(Nrt_QuadTree_Create(GetCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT)))
                      ->shared_from_this();
    ASSERT_EQ(Nrt_QuadTree_Destroy(reinterpret_cast<NrtQuadTreeHandle>(handle.get())), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_Destroy(reinterpret_cast<NrtQuadTreeHandle>(handle.get())),
              NRT_FAILURE_ALREADY_DELETED_OR_REMOVED);
}

TEST_F(InteropQuadTreeTest, GetIntersectingPointsReturnsValidPointVectorHandleAndCanAlsoBeDeleted)
{
    NrtPointVectorHandle vec = nullptr;

    int32_t result = Nrt_QuadTree_GetIntersectingPoints(_quadTree, GetCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT), &vec);
    EXPECT_EQ(result, NRT_SUCCESS);
    EXPECT_EQ(Nrt_PointVector_Destroy(vec), NRT_SUCCESS);
}

TEST_F(InteropQuadTreeTest, GetIntersectingPointsReturnsNullInstanceFailureWhenGivenNullPtrForInput)
{
    NrtGeoBounds expectedBounds = GetCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
    NrtPointVectorHandle outputVector = nullptr;

    ASSERT_EQ(Nrt_QuadTree_GetIntersectingPoints(nullptr, expectedBounds, &outputVector),
              NRT_FAILURE_NULL_INSTANCE_PROVIDED);
}

TEST_F(InteropQuadTreeTest, GetIntersectingPointsReturnsNullptrFailureWhenGivenNullPtrForOutput)
{
    NrtGeoBounds expectedBounds = GetCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);

    ASSERT_EQ(Nrt_QuadTree_GetIntersectingPoints(_quadTree, expectedBounds, nullptr),
              NRT_FAILURE_NULL_ARGUMENT_PROVIDED);
}

TEST_F(InteropQuadTreeTest, GetIntersectingPointsReturnsNullInstanceFailureWhenGivenNullPtrForBothInputAndOutput)
{
    NrtGeoBounds expectedBounds = GetCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);

    ASSERT_EQ(Nrt_QuadTree_GetIntersectingPoints(nullptr, expectedBounds, nullptr), NRT_FAILURE_NULL_INSTANCE_PROVIDED);
}

TEST_F(InteropQuadTreeTest, GetBoundsGetsCorrectBounds)
{
    NrtGeoBounds expectedBounds = GetCenteredBoundsC(TEST_WIDTH, TEST_HEIGHT);
    NrtGeoBounds actualBounds = Nrt_GeoBounds_Zero();
    actualBounds = Nrt_QuadTree_GetBounds(_quadTree);

    EXPECT_TRUE(CheckBoundsForEquality(actualBounds, expectedBounds));
}

TEST_F(InteropQuadTreeTest, GetPointCountReturnsZeroWhenTreeHasNoPoints)
{
    EXPECT_EQ(Nrt_QuadTree_GetPointCount(_quadTree), 0u);
}

TEST_F(InteropQuadTreeTest, GetPointMethodsReturnsNullptrWhenTreeHasNoChildren)
{
    NrtQuadTreeHandle topLeft = nullptr;
    NrtQuadTreeHandle topRight = nullptr;
    NrtQuadTreeHandle bottomLeft = nullptr;
    NrtQuadTreeHandle bottomRight = nullptr;

    ASSERT_EQ(Nrt_QuadTree_GetTopLeft(_quadTree, &topLeft), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetTopRight(_quadTree, &topRight), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetBottomLeft(_quadTree, &bottomLeft), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetBottomRight(_quadTree, &bottomRight), NRT_SUCCESS);

    EXPECT_EQ(topLeft, nullptr);
    EXPECT_EQ(topRight, nullptr);
    EXPECT_EQ(bottomLeft, nullptr);
    EXPECT_EQ(bottomRight, nullptr);
}

TEST_F(InteropQuadTreeTest, GetPointReturnsNullForTooLargeIndex)
{
    NrtQuadTreePointHandle point0 = nullptr;
    NrtQuadTreePointHandle point1 = nullptr;
    NrtQuadTreePointHandle point2 = nullptr;
    NrtQuadTreePointHandle point3 = nullptr;

    ASSERT_EQ(Nrt_QuadTree_GetPoint(_quadTree, 0, &point0), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetPoint(_quadTree, 1, &point1), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetPoint(_quadTree, 2, &point2), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetPoint(_quadTree, 3, &point3), NRT_SUCCESS);

    EXPECT_EQ(point0, nullptr);
    EXPECT_EQ(point1, nullptr);
    EXPECT_EQ(point2, nullptr);
    EXPECT_EQ(point3, nullptr);
}

TEST_F(InteropQuadTreeTest, GetPointReturnsNullInstanceFailureWhenGivenNullptrForInput)
{
    NrtQuadTreePointHandle point = nullptr;

    ASSERT_EQ(Nrt_QuadTree_GetPoint(nullptr, 0, &point), NRT_FAILURE_NULL_INSTANCE_PROVIDED);
}

TEST_F(InteropQuadTreeTest, GetPointReturnsNullptrFailureWhenGivenNullptrForOutput)
{
    ASSERT_EQ(Nrt_QuadTree_GetPoint(_quadTree, 0, nullptr), NRT_FAILURE_NULL_ARGUMENT_PROVIDED);
}

TEST_F(InteropQuadTreeTest, GetPointReturnsNullInstanceFailureWhenGivenNullptrForInputAndOutput)
{
    ASSERT_EQ(Nrt_QuadTree_GetPoint(nullptr, 0, nullptr), NRT_FAILURE_NULL_INSTANCE_PROVIDED);
}

TEST_F(InteropQuadTreeTest, InsertOneReturnsTrue)
{
    auto point0 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, 1.0f);
    ASSERT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point0));
}

TEST_F(InteropQuadTreeTest, InsertFourDoesNotSubdivide)
{
    auto point0 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, 1.0f);

    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point0));

    auto point1 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, 1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point1));

    auto point2 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point2));

    auto point3 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point3));

    ASSERT_EQ(Nrt_QuadTree_GetPointCount(_quadTree), 4u);

    NrtQuadTreePointHandle outputPointResult0 = nullptr;
    NrtQuadTreePointHandle outputPointResult1 = nullptr;
    NrtQuadTreePointHandle outputPointResult2 = nullptr;
    NrtQuadTreePointHandle outputPointResult3 = nullptr;

    ASSERT_EQ(Nrt_QuadTree_GetPoint(_quadTree, 0, &outputPointResult0), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetPoint(_quadTree, 1, &outputPointResult1), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetPoint(_quadTree, 2, &outputPointResult2), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetPoint(_quadTree, 3, &outputPointResult3), NRT_SUCCESS);

    EXPECT_TRUE(CheckPointsForEqualityC(outputPointResult0, point0));
    EXPECT_TRUE(CheckPointsForEqualityC(outputPointResult1, point1));
    EXPECT_TRUE(CheckPointsForEqualityC(outputPointResult2, point2));
    EXPECT_TRUE(CheckPointsForEqualityC(outputPointResult3, point3));

    NrtQuadTreeHandle outputCornerTreeTopLeft = nullptr;
    NrtQuadTreeHandle outputCornerTreeTopRight = nullptr;
    NrtQuadTreeHandle outputCornerTreeBottomLeft = nullptr;
    NrtQuadTreeHandle outputCornerTreeBottomRight = nullptr;

    ASSERT_EQ(Nrt_QuadTree_GetTopLeft(_quadTree, &outputCornerTreeTopLeft), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetTopRight(_quadTree, &outputCornerTreeTopRight), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetBottomLeft(_quadTree, &outputCornerTreeBottomLeft), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetBottomRight(_quadTree, &outputCornerTreeBottomRight), NRT_SUCCESS);

    EXPECT_EQ(outputCornerTreeTopLeft, nullptr);
    EXPECT_EQ(outputCornerTreeTopRight, nullptr);
    EXPECT_EQ(outputCornerTreeBottomLeft, nullptr);
    EXPECT_EQ(outputCornerTreeBottomRight, nullptr);
}

TEST_F(InteropQuadTreeTest, InsertFiveDoesSubdivideAndPointsAreCorrect)
{
    auto point0 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, 1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point0));

    auto point1 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, 1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point1));

    auto point2 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point2));

    auto point3 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point3));

    auto point4 = Nrt_QuadTreePoint_CreateFromFloat(0.0f, 0.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point4));

    ASSERT_EQ(Nrt_QuadTree_GetPointCount(_quadTree), 0u);

    NrtQuadTreeHandle treeOutputTopLeft = nullptr;
    NrtQuadTreeHandle treeOutputTopRight = nullptr;
    NrtQuadTreeHandle treeOutputBottomLeft = nullptr;
    NrtQuadTreeHandle treeOutputBottomRight = nullptr;

    int32_t treeResultTopLeft = Nrt_QuadTree_GetTopLeft(_quadTree, &treeOutputTopLeft);
    int32_t treeResultTopRight = Nrt_QuadTree_GetTopRight(_quadTree, &treeOutputTopRight);
    int32_t treeResultBottomLeft = Nrt_QuadTree_GetBottomLeft(_quadTree, &treeOutputBottomLeft);
    int32_t treeResultBottomRight = Nrt_QuadTree_GetBottomRight(_quadTree, &treeOutputBottomRight);

    ASSERT_EQ(treeResultTopLeft, NRT_SUCCESS);
    ASSERT_EQ(treeResultTopRight, NRT_SUCCESS);
    ASSERT_EQ(treeResultBottomLeft, NRT_SUCCESS);
    ASSERT_EQ(treeResultBottomRight, NRT_SUCCESS);

    size_t outputChildTreeSizeTopLeft = Nrt_QuadTree_GetPointCount(treeOutputTopLeft);
    size_t outputChildTreeSizeTopRight = Nrt_QuadTree_GetPointCount(treeOutputTopRight);
    size_t outputChildTreeSizeBottomLeft = Nrt_QuadTree_GetPointCount(treeOutputBottomLeft);
    size_t outputChildTreeSizeBottomRight = Nrt_QuadTree_GetPointCount(treeOutputBottomRight);

    EXPECT_EQ(outputChildTreeSizeTopLeft, 2u);
    EXPECT_EQ(outputChildTreeSizeTopRight, 1u);
    EXPECT_EQ(outputChildTreeSizeBottomLeft, 1u);
    EXPECT_EQ(outputChildTreeSizeBottomRight, 1u);

    NrtQuadTreePointHandle outputPointResultTopLeft = nullptr;
    NrtQuadTreePointHandle outputPointResultTopRight = nullptr;
    NrtQuadTreePointHandle outputPointResultBottomLeft = nullptr;
    NrtQuadTreePointHandle outputPointResultBottomRight = nullptr;
    NrtQuadTreePointHandle outputPointResultTopLeftTwo = nullptr;

    Nrt_QuadTree_GetPoint(treeOutputTopLeft, 0, &outputPointResultTopLeft);
    Nrt_QuadTree_GetPoint(treeOutputTopRight, 0, &outputPointResultTopRight);
    Nrt_QuadTree_GetPoint(treeOutputBottomLeft, 0, &outputPointResultBottomLeft);
    Nrt_QuadTree_GetPoint(treeOutputBottomRight, 0, &outputPointResultBottomRight);
    Nrt_QuadTree_GetPoint(treeOutputTopLeft, 1, &outputPointResultTopLeftTwo);

    EXPECT_TRUE(CheckPointsForEqualityC(outputPointResultTopLeft, point0));
    EXPECT_TRUE(CheckPointsForEqualityC(outputPointResultTopRight, point1));
    EXPECT_TRUE(CheckPointsForEqualityC(outputPointResultBottomLeft, point2));
    EXPECT_TRUE(CheckPointsForEqualityC(outputPointResultBottomRight, point3));
    EXPECT_TRUE(CheckPointsForEqualityC(outputPointResultTopLeftTwo, point4));
}

TEST_F(InteropQuadTreeTest, InsertFiveDoesSubdivideAndBoundsAreCorrect)
{
    auto point0 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, 1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point0));

    auto point1 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, 1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point1));

    auto point2 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point2));

    auto point3 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point3));

    auto point4 = Nrt_QuadTreePoint_CreateFromFloat(0.0f, 0.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point4));

    ASSERT_EQ(Nrt_QuadTree_GetPointCount(_quadTree), 0u);

    NrtQuadTreeHandle treeOutputTopLeft = nullptr;
    NrtQuadTreeHandle treeOutputTopRight = nullptr;
    NrtQuadTreeHandle treeOutputBottomLeft = nullptr;
    NrtQuadTreeHandle treeOutputBottomRight = nullptr;

    int32_t treeResultTopLeft = Nrt_QuadTree_GetTopLeft(_quadTree, &treeOutputTopLeft);
    int32_t treeResultTopRight = Nrt_QuadTree_GetTopRight(_quadTree, &treeOutputTopRight);
    int32_t treeResultBottomLeft = Nrt_QuadTree_GetBottomLeft(_quadTree, &treeOutputBottomLeft);
    int32_t treeResultBottomRight = Nrt_QuadTree_GetBottomRight(_quadTree, &treeOutputBottomRight);

    ASSERT_EQ(treeResultTopLeft, NRT_SUCCESS);
    ASSERT_EQ(treeResultTopRight, NRT_SUCCESS);
    ASSERT_EQ(treeResultBottomLeft, NRT_SUCCESS);
    ASSERT_EQ(treeResultBottomRight, NRT_SUCCESS);

    size_t outputChildTreeSizeTopLeft = Nrt_QuadTree_GetPointCount(treeOutputTopLeft);
    size_t outputChildTreeSizeTopRight = Nrt_QuadTree_GetPointCount(treeOutputTopRight);
    size_t outputChildTreeSizeBottomLeft = Nrt_QuadTree_GetPointCount(treeOutputBottomLeft);
    size_t outputChildTreeSizeBottomRight = Nrt_QuadTree_GetPointCount(treeOutputBottomRight);

    EXPECT_EQ(outputChildTreeSizeTopLeft, 2u);
    EXPECT_EQ(outputChildTreeSizeTopRight, 1u);
    EXPECT_EQ(outputChildTreeSizeBottomLeft, 1u);
    EXPECT_EQ(outputChildTreeSizeBottomRight, 1u);

    auto expectedSize = NrtGeoVector2F{TEST_WIDTH / 2, TEST_HEIGHT / 2};

    NrtGeoBounds outputBoundsTopLeft = Nrt_QuadTree_GetBounds(treeOutputTopLeft);
    NrtGeoBounds outputBoundsTopRight = Nrt_QuadTree_GetBounds(treeOutputTopRight);
    NrtGeoBounds outputBoundsBottomLeft = Nrt_QuadTree_GetBounds(treeOutputBottomLeft);
    NrtGeoBounds outputBoundsBottomRight = Nrt_QuadTree_GetBounds(treeOutputBottomRight);

    EXPECT_TRUE(CheckBoundsForEquality(
        outputBoundsTopLeft, NrtGeoBounds{NrtGeoVector2F{-TEST_WIDTH / 4, TEST_HEIGHT / 4}, expectedSize, 0}));
    EXPECT_TRUE(CheckBoundsForEquality(outputBoundsTopRight,
                                       NrtGeoBounds{NrtGeoVector2F{TEST_WIDTH / 4, TEST_HEIGHT / 4}, expectedSize, 0}));
    EXPECT_TRUE(CheckBoundsForEquality(
        outputBoundsBottomLeft, NrtGeoBounds{NrtGeoVector2F{-TEST_WIDTH / 4, -TEST_HEIGHT / 4}, expectedSize, 0}));
    EXPECT_TRUE(CheckBoundsForEquality(
        outputBoundsBottomRight, NrtGeoBounds{NrtGeoVector2F{TEST_WIDTH / 4, -TEST_HEIGHT / 4}, expectedSize, 0}));
}

TEST_F(InteropQuadTreeTest, InsertOutOfBoundsReturnsFalse)
{
    auto point0 = Nrt_QuadTreePoint_CreateFromFloat(3840.0f, 2160.0f);

    EXPECT_EQ(NRT_FALSE, Nrt_QuadTree_TryInsert(_quadTree, point0));
}

TEST_F(InteropQuadTreeTest, PointVector_GetSizeReturnsCorrectValue)
{
    auto point0 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, 1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point0));

    auto point1 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, 1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point1));

    auto point2 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point2));

    auto point3 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point3));

    auto point4 = Nrt_QuadTreePoint_CreateFromFloat(0.0f, 0.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point4));

    NrtGeoBounds inputGeoBounds = Nrt_QuadTree_GetBounds(_quadTree);
    NrtPointVectorHandle resultVector = nullptr;

    ASSERT_EQ(Nrt_QuadTree_GetIntersectingPoints(_quadTree, inputGeoBounds, &resultVector), NRT_SUCCESS);
    EXPECT_EQ(Nrt_PointVector_GetSize(resultVector), 5u);
}

TEST_F(InteropQuadTreeTest, PointVector_DeleteReturnsNullInstanceFailureWhenGivenNullptr)
{
    ASSERT_EQ(Nrt_PointVector_Destroy(nullptr), NRT_FAILURE_NULL_INSTANCE_PROVIDED);
}

TEST_F(InteropQuadTreeTest, GetIntersectingPointsReturnsAllPoints)
{
    auto point0 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, 1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point0));

    auto point1 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, 1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point1));

    auto point2 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point2));

    auto point3 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point3));

    auto point4 = Nrt_QuadTreePoint_CreateFromFloat(0.0f, 0.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point4));

    NrtGeoBounds outputGeoBounds = Nrt_QuadTree_GetBounds(_quadTree);
    NrtPointVectorHandle resultVector = nullptr;

    ASSERT_EQ(Nrt_QuadTree_GetIntersectingPoints(_quadTree, outputGeoBounds, &resultVector), NRT_SUCCESS);

    NrtQuadTreePointHandle outputPoint0 = nullptr;
    NrtQuadTreePointHandle outputPoint1 = nullptr;
    NrtQuadTreePointHandle outputPoint2 = nullptr;
    NrtQuadTreePointHandle outputPoint3 = nullptr;
    NrtQuadTreePointHandle outputPoint4 = nullptr;

    ASSERT_EQ(Nrt_PointVector_GetPointFromIndex(resultVector, 0, &outputPoint0), NRT_SUCCESS);
    ASSERT_EQ(Nrt_PointVector_GetPointFromIndex(resultVector, 1, &outputPoint1), NRT_SUCCESS);
    ASSERT_EQ(Nrt_PointVector_GetPointFromIndex(resultVector, 2, &outputPoint2), NRT_SUCCESS);
    ASSERT_EQ(Nrt_PointVector_GetPointFromIndex(resultVector, 3, &outputPoint3), NRT_SUCCESS);
    ASSERT_EQ(Nrt_PointVector_GetPointFromIndex(resultVector, 4, &outputPoint4), NRT_SUCCESS);

    EXPECT_TRUE(CheckPointsForEqualityC(outputPoint0, point0));
    EXPECT_TRUE(CheckPointsForEqualityC(outputPoint1, point4));
    EXPECT_TRUE(CheckPointsForEqualityC(outputPoint2, point1));
    EXPECT_TRUE(CheckPointsForEqualityC(outputPoint3, point2));
    EXPECT_TRUE(CheckPointsForEqualityC(outputPoint4, point3));
}

TEST_F(InteropQuadTreeTest, RemoveExistingReturnsTrue)
{
    auto point0 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, 1.0f);

    ASSERT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point0));
    EXPECT_TRUE(Nrt_QuadTree_TryRemove(_quadTree, point0));
}

TEST_F(InteropQuadTreeTest, RemoveNoneExistingReturnsFalse)
{
    auto point0 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, 1.0f);
    EXPECT_FALSE(Nrt_QuadTree_TryRemove(_quadTree, point0));
}

TEST_F(InteropQuadTreeTest, RemoveOneCausesMergeWhenAdjacentPointCountLessThan5)
{
    auto point0 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, 1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point0));

    auto point1 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, 1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point1));

    auto point2 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point2));

    auto point3 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point3));

    auto point4 = Nrt_QuadTreePoint_CreateFromFloat(0.0f, 0.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point4));

    EXPECT_TRUE(Nrt_QuadTree_TryRemove(_quadTree, point4));

    EXPECT_EQ(Nrt_QuadTree_GetPointCount(_quadTree), 4u);

    NrtQuadTreePointHandle newOutputPoint0 = nullptr;
    NrtQuadTreePointHandle newOutputPoint1 = nullptr;
    NrtQuadTreePointHandle newOutputPoint2 = nullptr;
    NrtQuadTreePointHandle newOutputPoint3 = nullptr;

    ASSERT_EQ(Nrt_QuadTree_GetPoint(_quadTree, 0, &newOutputPoint0), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetPoint(_quadTree, 1, &newOutputPoint1), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetPoint(_quadTree, 2, &newOutputPoint2), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetPoint(_quadTree, 3, &newOutputPoint3), NRT_SUCCESS);

    EXPECT_TRUE(CheckPointsForEqualityC(newOutputPoint0, point0));
    EXPECT_TRUE(CheckPointsForEqualityC(newOutputPoint1, point1));
    EXPECT_TRUE(CheckPointsForEqualityC(newOutputPoint2, point2));
    EXPECT_TRUE(CheckPointsForEqualityC(newOutputPoint3, point3));

    NrtQuadTreeHandle newTopLeftTree = nullptr;
    NrtQuadTreeHandle newTopRightTree = nullptr;
    NrtQuadTreeHandle newBottomLeftTree = nullptr;
    NrtQuadTreeHandle newBottomRightTree = nullptr;

    ASSERT_EQ(Nrt_QuadTree_GetTopLeft(_quadTree, &newTopLeftTree), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetTopRight(_quadTree, &newTopRightTree), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetBottomLeft(_quadTree, &newBottomLeftTree), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTree_GetBottomRight(_quadTree, &newBottomRightTree), NRT_SUCCESS);

    EXPECT_EQ(newTopLeftTree, nullptr);
    EXPECT_EQ(newTopLeftTree, nullptr);
    EXPECT_EQ(newTopLeftTree, nullptr);
    EXPECT_EQ(newTopLeftTree, nullptr);
}

TEST_F(InteropQuadTreeTest, RemoveOneDoesNotCauseMergeWhenAdjacentPointCountMoreThan4)
{
    auto point0 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, 1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point0));

    auto point1 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, 1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point1));

    auto point2 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point2));

    auto point3 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point3));

    auto point4 = Nrt_QuadTreePoint_CreateFromFloat(0.0f, 0.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point4));

    auto point5 = Nrt_QuadTreePoint_CreateFromFloat(0.5f, 0.5f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point5));

    EXPECT_TRUE(Nrt_QuadTree_TryRemove(_quadTree, point5));

    EXPECT_EQ(Nrt_QuadTree_GetPointCount(_quadTree), 0u);

    NrtQuadTreeHandle treeOutputTopLeft = nullptr;
    NrtQuadTreeHandle treeOutputTopRight = nullptr;
    NrtQuadTreeHandle treeOutputBottomLeft = nullptr;
    NrtQuadTreeHandle treeOutputBottomRight = nullptr;

    int32_t treeResultTopLeft = Nrt_QuadTree_GetTopLeft(_quadTree, &treeOutputTopLeft);
    int32_t treeResultTopRight = Nrt_QuadTree_GetTopRight(_quadTree, &treeOutputTopRight);
    int32_t treeResultBottomLeft = Nrt_QuadTree_GetBottomLeft(_quadTree, &treeOutputBottomLeft);
    int32_t treeResultBottomRight = Nrt_QuadTree_GetBottomRight(_quadTree, &treeOutputBottomRight);

    ASSERT_EQ(treeResultTopLeft, NRT_SUCCESS);
    ASSERT_EQ(treeResultTopRight, NRT_SUCCESS);
    ASSERT_EQ(treeResultBottomLeft, NRT_SUCCESS);
    ASSERT_EQ(treeResultBottomRight, NRT_SUCCESS);

    size_t outputChildTreeSizeTopLeft = Nrt_QuadTree_GetPointCount(treeOutputTopLeft);
    size_t outputChildTreeSizeTopRight = Nrt_QuadTree_GetPointCount(treeOutputTopRight);
    size_t outputChildTreeSizeBottomLeft = Nrt_QuadTree_GetPointCount(treeOutputBottomLeft);
    size_t outputChildTreeSizeBottomRight = Nrt_QuadTree_GetPointCount(treeOutputBottomRight);

    EXPECT_EQ(outputChildTreeSizeTopLeft, 2u);
    EXPECT_EQ(outputChildTreeSizeTopRight, 1u);
    EXPECT_EQ(outputChildTreeSizeBottomLeft, 1u);
    EXPECT_EQ(outputChildTreeSizeBottomRight, 1u);

    NrtQuadTreePointHandle outputPointResultTopLeft = nullptr;
    NrtQuadTreePointHandle outputPointResultTopRight = nullptr;
    NrtQuadTreePointHandle outputPointResultBottomLeft = nullptr;
    NrtQuadTreePointHandle outputPointResultBottomRight = nullptr;
    NrtQuadTreePointHandle outputPointResultTopLeftTwo = nullptr;

    Nrt_QuadTree_GetPoint(treeOutputTopLeft, 0, &outputPointResultTopLeft);
    Nrt_QuadTree_GetPoint(treeOutputTopRight, 0, &outputPointResultTopRight);
    Nrt_QuadTree_GetPoint(treeOutputBottomLeft, 0, &outputPointResultBottomLeft);
    Nrt_QuadTree_GetPoint(treeOutputBottomRight, 0, &outputPointResultBottomRight);
    Nrt_QuadTree_GetPoint(treeOutputTopLeft, 1, &outputPointResultTopLeftTwo);

    EXPECT_TRUE(CheckPointsForEqualityC(outputPointResultTopLeft, point0));
    EXPECT_TRUE(CheckPointsForEqualityC(outputPointResultTopRight, point1));
    EXPECT_TRUE(CheckPointsForEqualityC(outputPointResultBottomLeft, point2));
    EXPECT_TRUE(CheckPointsForEqualityC(outputPointResultBottomRight, point3));
    EXPECT_TRUE(CheckPointsForEqualityC(outputPointResultTopLeftTwo, point4));
}

TEST_F(InteropQuadTreeTest, GetIntersectingPointsForQuadTreeBoundsReturnsAll)
{
    auto point0 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, 1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point0));

    auto point1 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, 1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point1));

    auto point2 = Nrt_QuadTreePoint_CreateFromFloat(-1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point2));

    auto point3 = Nrt_QuadTreePoint_CreateFromFloat(1.0f, -1.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point3));

    auto point4 = Nrt_QuadTreePoint_CreateFromFloat(0.0f, 0.0f);
    EXPECT_TRUE(Nrt_QuadTree_TryInsert(_quadTree, point4));

    NrtGeoBounds outputGeoBounds = Nrt_QuadTree_GetBounds(_quadTree);
    NrtPointVectorHandle outputVector = nullptr;

    ASSERT_EQ(Nrt_QuadTree_GetIntersectingPoints(_quadTree, outputGeoBounds, &outputVector), NRT_SUCCESS);
    auto intersectingPointsVector = reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(outputVector);

    EXPECT_EQ(intersectingPointsVector->size(), 5u);

    auto cPoint0 = reinterpret_cast<Maths::QuadTreePoint*>(point0);
    auto cPoint1 = reinterpret_cast<Maths::QuadTreePoint*>(point1);
    auto cPoint2 = reinterpret_cast<Maths::QuadTreePoint*>(point2);
    auto cPoint3 = reinterpret_cast<Maths::QuadTreePoint*>(point3);
    auto cPoint4 = reinterpret_cast<Maths::QuadTreePoint*>(point4);

    EXPECT_TRUE(CheckPointsForEqualityCpp(intersectingPointsVector->at(0).get(), cPoint0));
    EXPECT_TRUE(CheckPointsForEqualityCpp(intersectingPointsVector->at(1).get(), cPoint4));
    EXPECT_TRUE(CheckPointsForEqualityCpp(intersectingPointsVector->at(2).get(), cPoint1));
    EXPECT_TRUE(CheckPointsForEqualityCpp(intersectingPointsVector->at(3).get(), cPoint2));
    EXPECT_TRUE(CheckPointsForEqualityCpp(intersectingPointsVector->at(4).get(), cPoint3));
}
