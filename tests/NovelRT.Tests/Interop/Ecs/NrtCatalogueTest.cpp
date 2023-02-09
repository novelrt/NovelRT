// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <limits>

#include <NovelRT.Interop/Ecs/NrtEcs.h>
#include <NovelRT/NovelRT.h>

#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;

class InteropCatalogueTest : public testing::Test
{
public:
    NrtComponentCacheHandle componentCache = nullptr;
    NrtEntityCacheHandle entityCache = nullptr;
    NrtCatalogueHandle catalogue = nullptr;

    NrtComponentTypeId intComponentTypeId = 0;
    NrtComponentTypeId sizeTComponentTypeId = 0;
    NrtComponentTypeId charComponentTypeId = 0;

    std::vector<EntityId> entityIdVector{};

protected:
    void SetUp() override
    {
        componentCache = Nrt_ComponentCache_Create(1);
        entityCache = Nrt_EntityCache_Create(1);
        catalogue = Nrt_Catalogue_Create(0, componentCache, entityCache);
        int32_t intDeleteState = -1;
        size_t sizeTDeleteState = std::numeric_limits<size_t>::max();
        char charDeleteState = 'e';

        Nrt_ComponentCache_RegisterComponentTypeUnsafe(
            componentCache, sizeof(int32_t), &intDeleteState,
            [](auto lhs, auto rhs, auto, auto) {
                auto intLhs = reinterpret_cast<int32_t*>(lhs);
                auto intRhs = reinterpret_cast<const int32_t*>(rhs);
                *intLhs += *intRhs;
            },
            [](auto lhs, auto rhs, auto) {
                auto intLhs = reinterpret_cast<const int32_t*>(lhs);
                auto intRhs = reinterpret_cast<const int32_t*>(rhs);

                return static_cast<NrtBool>(*intLhs == *intRhs);
            },
            "THROW_AWAY", nullptr, &intComponentTypeId);

        Nrt_ComponentCache_RegisterComponentTypeUnsafe(
            componentCache, sizeof(size_t), &sizeTDeleteState,
            [](auto lhs, auto rhs, auto, auto) {
                auto sizeTLhs = reinterpret_cast<size_t*>(lhs);
                auto sizeTRhs = reinterpret_cast<const size_t*>(rhs);
                *sizeTLhs += *sizeTRhs;
            },
            [](auto lhs, auto rhs, auto) {
                auto sizeTLhs = reinterpret_cast<const size_t*>(lhs);
                auto sizeTRhs = reinterpret_cast<const size_t*>(rhs);

                return static_cast<NrtBool>(*sizeTLhs == *sizeTRhs);
            },
            "THROW_AWAY_AGAIN", nullptr, &sizeTComponentTypeId);

        Nrt_ComponentCache_RegisterComponentTypeUnsafe(
            componentCache, sizeof(char), &charDeleteState, [](auto, auto, auto, auto) {}, [](auto, auto, auto) -> NrtBool {return NRT_FALSE;}, "THROW_AWAY_AGAIN_AGAIN",
            nullptr, &charComponentTypeId);

        auto compViewInt = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, intComponentTypeId);
        auto compViewSizeT = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, sizeTComponentTypeId);
        auto compViewChar = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, charComponentTypeId);

        int32_t intInput = 10;
        size_t sizeTInput = 100;
        char charInput = 'a';

        Nrt_UnsafeComponentView_PushComponentUpdateInstruction(compViewInt, 0, &intInput);
        Nrt_UnsafeComponentView_PushComponentUpdateInstruction(compViewSizeT, 0, &sizeTInput);
        Nrt_UnsafeComponentView_PushComponentUpdateInstruction(compViewChar, 0, &charInput);

        Nrt_ComponentCache_PrepAllBuffersForNextFrame(componentCache,
                                                      reinterpret_cast<NrtEntityIdVectorHandle>(&entityIdVector));
    }

    void TearDown() override
    {
        Nrt_ComponentCache_Destroy(componentCache);
        Nrt_EntityCache_Destroy(entityCache);
        Nrt_Catalogue_Destroy(catalogue);
    }
};

TEST_F(InteropCatalogueTest, CanGetValidComponentView)
{
    auto compView = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, charComponentTypeId);
    NrtSparseSetMemoryContainer_ConstIteratorHandle beginIterator = nullptr;
    NrtSparseSetMemoryContainer_ConstIteratorHandle endIterator = Nrt_UnsafeComponentView_end(compView);

    for (beginIterator = Nrt_UnsafeComponentView_begin(compView);
         Nrt_SparseSetMemoryContainer_ConstIterator_NotEqual(beginIterator, endIterator) == NRT_TRUE;
         Nrt_SparseSetMemoryContainer_ConstIterator_MoveNext(beginIterator))
    {
        size_t outputId = 0;
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle itView = nullptr;
        ASSERT_EQ(Nrt_SparseSetMemoryContainer_ConstIterator_GetValuePair(beginIterator, &outputId, &itView),
                  NRT_SUCCESS);

        char result = 'z';
        Nrt_SparseSetMemoryContainer_ConstByteIteratorView_CopyFromLocation(itView, &result);

        EXPECT_EQ(result, 'a');

        Nrt_SparseSetMemoryContainer_ConstByteIteratorView_Destroy(itView);
    }

    Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(beginIterator);
    Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(endIterator);

    Nrt_UnsafeComponentView_Destroy(compView);
}

TEST_F(InteropCatalogueTest, CanRemoveComponentFromEntityBasedOnView)
{
    auto compView = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, intComponentTypeId);
    NrtSparseSetMemoryContainer_ConstIteratorHandle beginIterator = nullptr;
    NrtSparseSetMemoryContainer_ConstIteratorHandle endIterator = Nrt_UnsafeComponentView_end(compView);

    for (beginIterator = Nrt_UnsafeComponentView_begin(compView);
         Nrt_SparseSetMemoryContainer_ConstIterator_NotEqual(beginIterator, endIterator) == NRT_TRUE;
         Nrt_SparseSetMemoryContainer_ConstIterator_MoveNext(beginIterator))
    {
        size_t outputId = 0;
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle itView = nullptr;
        ASSERT_EQ(Nrt_SparseSetMemoryContainer_ConstIterator_GetValuePair(beginIterator, &outputId, &itView),
                  NRT_SUCCESS);

        ASSERT_EQ(Nrt_UnsafeComponentView_RemoveComponent(compView, outputId), NRT_SUCCESS);
        Nrt_SparseSetMemoryContainer_ConstByteIteratorView_Destroy(itView);
    }

    Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(beginIterator);
    Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(endIterator);
    Nrt_ComponentCache_PrepAllBuffersForNextFrame(componentCache,
                                                  reinterpret_cast<NrtEntityIdVectorHandle>(&entityIdVector));

    NrtComponentBufferMemoryContainerHandle ptr = nullptr;
    ASSERT_EQ(Nrt_ComponentCache_GetComponentBufferById(componentCache, intComponentTypeId, &ptr), NRT_SUCCESS);
    EXPECT_EQ(Nrt_ComponentBufferMemoryContainer_GetImmutableDataLength(ptr), 0);

    Nrt_UnsafeComponentView_Destroy(compView);
}

TEST_F(InteropCatalogueTest, CanHandleEntityDeletionBetweenFrames)
{
    Nrt_Catalogue_DeleteEntity(catalogue, 0);
    Nrt_EntityCache_ProcessEntityDeletionRequestsFromThreads(entityCache);
    Nrt_ComponentCache_PrepAllBuffersForNextFrame(componentCache,
                                                  Nrt_EntityCache_GetEntitiesToRemoveThisFrame(entityCache));

    auto compViewInt = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, intComponentTypeId);
    auto compViewChar = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, charComponentTypeId);
    auto compViewSizeT = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, sizeTComponentTypeId);

    EXPECT_EQ(Nrt_UnsafeComponentView_GetImmutableDataLength(compViewInt), 0);
    EXPECT_EQ(Nrt_UnsafeComponentView_GetImmutableDataLength(compViewChar), 0);
    EXPECT_EQ(Nrt_UnsafeComponentView_GetImmutableDataLength(compViewSizeT), 0);

    Nrt_UnsafeComponentView_Destroy(compViewInt);
    Nrt_UnsafeComponentView_Destroy(compViewChar);
    Nrt_UnsafeComponentView_Destroy(compViewSizeT);
}

TEST_F(InteropCatalogueTest, CanHandleEntityDeletionInSameFrame)
{
    auto id = Nrt_Catalogue_CreateEntity(catalogue);
    Nrt_Catalogue_DeleteEntity(catalogue, id);
    Nrt_EntityCache_ProcessEntityDeletionRequestsFromThreads(entityCache);
    Nrt_ComponentCache_PrepAllBuffersForNextFrame(componentCache,
                                                  Nrt_EntityCache_GetEntitiesToRemoveThisFrame(entityCache));

    auto compViewInt = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, intComponentTypeId);
    auto compViewChar = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, charComponentTypeId);
    auto compViewSizeT = Nrt_Catalogue_GetComponentViewByIdUnsafe(catalogue, sizeTComponentTypeId);

    EXPECT_EQ(Nrt_UnsafeComponentView_GetImmutableDataLength(compViewInt), 1);
    EXPECT_EQ(Nrt_UnsafeComponentView_GetImmutableDataLength(compViewChar), 1);
    EXPECT_EQ(Nrt_UnsafeComponentView_GetImmutableDataLength(compViewSizeT), 1);

    Nrt_UnsafeComponentView_Destroy(compViewInt);
    Nrt_UnsafeComponentView_Destroy(compViewChar);
    Nrt_UnsafeComponentView_Destroy(compViewSizeT);
}

TEST_F(InteropCatalogueTest, GetComponentViewByIdReturnsOutOfRangeFailureWhenOutOfRange)
{
    NrtUnsafeComponentViewHandle handleResult = nullptr;
    auto result = Nrt_Catalogue_GetComponentViewById(catalogue, 5000, &handleResult);
    ASSERT_EQ(result, NRT_FAILURE_ARGUMENT_OUT_OF_RANGE);
}
