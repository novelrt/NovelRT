// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtEcs.h>
#include <NovelRT/NovelRT.h>

#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;

TEST(InteropComponentBufferMemoryContainerTest, GetDeleteInstructionStateReturnsCorrectState)
{
    int32_t deleteState = -1;
    auto container = Nrt_ComponentBufferMemoryContainer_Create(
        1, &deleteState, sizeof(int32_t), [](auto, auto, auto, auto) {},
        [](auto, auto, auto) -> NrtBool { return NRT_FALSE; }, "THROW_AWAY", nullptr);
    auto deleteInstructionState = Nrt_ComponentBufferMemoryContainer_GetDeleteInstructionState(container);
    EXPECT_EQ(std::memcmp(Nrt_ComponentBufferMemoryContainer_ImmutableDataView_GetDataHandle(deleteInstructionState),
                          &deleteState, sizeof(int32_t)),
              0);

    Nrt_ComponentBufferMemoryContainer_ImmutableDataView_Destroy(deleteInstructionState);
    Nrt_ComponentBufferMemoryContainer_Destroy(container);
}

TEST(InteropComponentBufferMemoryContainerTest, PushComponentUpdateInstructionAddsNewEntryCorrectly)
{
    int32_t deleteState = -1;
    int32_t updateState = 10;
    auto container = Nrt_ComponentBufferMemoryContainer_Create(
        1, &deleteState, sizeof(int32_t), [](auto, auto, auto, auto) {},
        [](auto, auto, auto) -> NrtBool { return NRT_FALSE; }, "THROW_AWAY", nullptr);

    ASSERT_EQ(Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(container, 0, 0, &updateState),
              NRT_SUCCESS);
    std::vector<EntityId> dummyVec{};
    Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame(container,
                                                             reinterpret_cast<NrtEntityIdVectorHandle>(&dummyVec));
    ASSERT_EQ(Nrt_ComponentBufferMemoryContainer_GetImmutableDataLength(container), 1);
    ASSERT_EQ(Nrt_ComponentBufferMemoryContainer_HasComponent(container, 0), NRT_TRUE);
    auto componentView = Nrt_ComponentBufferMemoryContainer_GetComponentUnsafe(container, 0);
    EXPECT_EQ(*reinterpret_cast<const int32_t*>(
                  Nrt_ComponentBufferMemoryContainer_ImmutableDataView_GetDataHandle(componentView)),
              10);

    Nrt_ComponentBufferMemoryContainer_ImmutableDataView_Destroy(componentView);
    Nrt_ComponentBufferMemoryContainer_Destroy(container);
}

TEST(InteropComponentBufferMemoryContainerTest, PushComponentUpdateInstructionUpdatesExistingEntryCorrectly)
{
    int32_t deleteState = -1;
    int32_t updateState = 10;
    auto container = Nrt_ComponentBufferMemoryContainer_Create(
        1, &deleteState, sizeof(int32_t),
        [](auto lhs, auto rhs, auto, auto) {
            *reinterpret_cast<int32_t*>(lhs) += *reinterpret_cast<const int32_t*>(rhs);
        },
        [](auto lhs, auto rhs, auto) {
            return static_cast<NrtBool>(*reinterpret_cast<const int32_t*>(lhs) ==
                                        *reinterpret_cast<const int32_t*>(rhs));
        },
        "THROW_AWAY", nullptr);

    ASSERT_EQ(Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(container, 0, 0, &updateState),
              NRT_SUCCESS);
    std::vector<EntityId> dummyVec{};
    Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame(container,
                                                             reinterpret_cast<NrtEntityIdVectorHandle>(&dummyVec));
    ASSERT_EQ(Nrt_ComponentBufferMemoryContainer_GetImmutableDataLength(container), 1);

    ASSERT_EQ(Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(container, 0, 0, &updateState),
              NRT_SUCCESS);
    Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame(container,
                                                             reinterpret_cast<NrtEntityIdVectorHandle>(&dummyVec));

    ASSERT_EQ(Nrt_ComponentBufferMemoryContainer_HasComponent(container, 0), NRT_TRUE);
    auto componentView = Nrt_ComponentBufferMemoryContainer_GetComponentUnsafe(container, 0);
    EXPECT_EQ(*reinterpret_cast<const int32_t*>(
                  Nrt_ComponentBufferMemoryContainer_ImmutableDataView_GetDataHandle(componentView)),
              20);

    Nrt_ComponentBufferMemoryContainer_ImmutableDataView_Destroy(componentView);
    Nrt_ComponentBufferMemoryContainer_Destroy(container);
}

TEST(InteropComponentBufferMemoryContainerTest, PushComponentUpdateInstructionRemovesEntryCorrectly)
{
    int32_t deleteState = -1;
    int32_t updateState = 10;
    auto container = Nrt_ComponentBufferMemoryContainer_Create(
        1, &deleteState, sizeof(int32_t), [](auto, auto, auto, auto) {},
        [](auto lhs, auto rhs, auto) {
            return static_cast<NrtBool>(*reinterpret_cast<const int32_t*>(lhs) ==
                                        *reinterpret_cast<const int32_t*>(rhs));
        },
        "THROW_AWAY", nullptr);

    ASSERT_EQ(Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(container, 0, 0, &updateState),
              NRT_SUCCESS);
    std::vector<EntityId> dummyVec{};
    Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame(container,
                                                             reinterpret_cast<NrtEntityIdVectorHandle>(&dummyVec));
    ASSERT_EQ(Nrt_ComponentBufferMemoryContainer_GetImmutableDataLength(container), 1);

    ASSERT_EQ(Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(container, 0, 0, &deleteState),
              NRT_SUCCESS);
    Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame(container,
                                                             reinterpret_cast<NrtEntityIdVectorHandle>(&dummyVec));

    EXPECT_EQ(Nrt_ComponentBufferMemoryContainer_GetImmutableDataLength(container), 0);
    EXPECT_EQ(Nrt_ComponentBufferMemoryContainer_HasComponent(container, 0), NRT_FALSE);

    Nrt_ComponentBufferMemoryContainer_Destroy(container);
}

TEST(InteropComponentBufferMemoryContainerTest, IterationWorksCorrectly)
{
    int32_t deleteState = -1;
    int32_t updateState = 10;
    auto container = Nrt_ComponentBufferMemoryContainer_Create(
        1, &deleteState, sizeof(int32_t), [](auto, auto, auto, auto) {},
        [](auto, auto, auto) -> NrtBool { return NRT_FALSE; }, "THROW_AWAY", nullptr);

    ASSERT_EQ(Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(container, 0, 0, &updateState),
              NRT_SUCCESS);
    ASSERT_EQ(Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(container, 0, 1, &updateState),
              NRT_SUCCESS);
    ASSERT_EQ(Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(container, 0, 2, &updateState),
              NRT_SUCCESS);

    std::vector<EntityId> dummyVec{};
    Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame(container,
                                                             reinterpret_cast<NrtEntityIdVectorHandle>(&dummyVec));

    NrtSparseSetMemoryContainer_ConstIteratorHandle beginIt = nullptr;
    NrtSparseSetMemoryContainer_ConstIteratorHandle endIt = Nrt_ComponentBufferMemoryContainer_end(container);

    for (beginIt = Nrt_ComponentBufferMemoryContainer_begin(container);
         Nrt_SparseSetMemoryContainer_ConstIterator_NotEqual(beginIt, endIt) == NRT_TRUE;
         Nrt_SparseSetMemoryContainer_ConstIterator_MoveNext(beginIt))
    {
        size_t outputId = 0;
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle dataView = nullptr;
        Nrt_SparseSetMemoryContainer_ConstIterator_GetValuePair(beginIt, &outputId, &dataView);

        EXPECT_EQ(*reinterpret_cast<const int32_t*>(
                      Nrt_SparseSetMemoryContainer_ConstByteIteratorView_GetDataHandle(dataView)),
                  10);

        Nrt_SparseSetMemoryContainer_ConstByteIteratorView_Destroy(dataView);
    }

    Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(beginIt);
    Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(endIt);

    Nrt_ComponentBufferMemoryContainer_Destroy(container);
}

TEST(InteropComponentBufferMemoryContainerTest, ConcurrentAccessWorksCorrectly)
{
    int32_t deleteState = -1;
    int32_t updateState = 10;
    auto container = Nrt_ComponentBufferMemoryContainer_Create(
        2, &deleteState, sizeof(int32_t),
        [](auto lhs, auto rhs, auto, auto) {
            *reinterpret_cast<int32_t*>(lhs) += *reinterpret_cast<const int32_t*>(rhs);
        },
        [](auto lhs, auto rhs, auto) {
            return static_cast<NrtBool>(*reinterpret_cast<const int32_t*>(lhs) ==
                                        *reinterpret_cast<const int32_t*>(rhs));
        },
        "THROW_AWAY", nullptr);

    for (int i = 0; i < 2000; ++i)
    {
        Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(container, 0, i, &updateState);
    }

    std::vector<EntityId> dummyVec{};
    Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame(container,
                                                             reinterpret_cast<NrtEntityIdVectorHandle>(&dummyVec));

    std::thread threadOne([&]() {
        for (size_t i = 0; i < 2000; ++i)
        {
            Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(container, 0, i, &updateState);
        }
    });

    std::thread threadTwo([&]() {
        for (size_t i = 0; i < 2000; ++i)
        {
            Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(container, 1, i, &updateState);
        }
    });

    threadOne.join();
    threadTwo.join();

    Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame(container,
                                                             reinterpret_cast<NrtEntityIdVectorHandle>(&dummyVec));

    NrtSparseSetMemoryContainer_ConstIteratorHandle beginIt = nullptr;
    NrtSparseSetMemoryContainer_ConstIteratorHandle endIt = Nrt_ComponentBufferMemoryContainer_end(container);

    for (beginIt = Nrt_ComponentBufferMemoryContainer_begin(container);
         Nrt_SparseSetMemoryContainer_ConstIterator_NotEqual(beginIt, endIt) == NRT_TRUE;
         Nrt_SparseSetMemoryContainer_ConstIterator_MoveNext(beginIt))
    {
        size_t outputId = 0;
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle dataView = nullptr;
        Nrt_SparseSetMemoryContainer_ConstIterator_GetValuePair(beginIt, &outputId, &dataView);

        EXPECT_EQ(*reinterpret_cast<const int32_t*>(
                      Nrt_SparseSetMemoryContainer_ConstByteIteratorView_GetDataHandle(dataView)),
                  30);

        Nrt_SparseSetMemoryContainer_ConstByteIteratorView_Destroy(dataView);
    }

    Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(beginIt);
    Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(endIt);

    Nrt_ComponentBufferMemoryContainer_Destroy(container);
}
