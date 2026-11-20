// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/ComponentBufferMemoryContainer.hpp>
#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <atomic>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;

namespace
{
    ComponentBufferMemoryContainer CreateIntContainer(bool allowMerge, bool allowAssignment, size_t poolSize = 1)
    {
        int32_t deleteState = -1;
        std::optional<std::function<void(void*, const void*, size_t)>> mergeLogic;
        std::optional<std::function<void(void*, const void*, size_t)>> assignmentLogic;
        if (allowMerge)
        {
            mergeLogic = [](void* target, const void* update, size_t)
            { *static_cast<int32_t*>(target) += *static_cast<const int32_t*>(update); };
        }

        if (allowAssignment)
        {
            assignmentLogic = [](void* target, const void* update, size_t)
            { *static_cast<int32_t*>(target) = *static_cast<const int32_t*>(update); };
        }

        return ComponentBufferMemoryContainer(
            poolSize, reinterpret_cast<const std::byte*>(&deleteState), sizeof(int32_t),
            [](const void* lhs, const void* rhs)
            { return *static_cast<const int32_t*>(lhs) == *static_cast<const int32_t*>(rhs); }, mergeLogic,
            assignmentLogic, "THROW_AWAY");
    }
}

TEST(ComponentBufferMemoryContainerTest, PrepComponentBuffersForFrameDoesNotThrow)
{
    int32_t deleteState = -1;

    EXPECT_NO_THROW(ComponentBufferMemoryContainer(
                        1, reinterpret_cast<std::byte*>(&deleteState), sizeof(int32_t), [](const void*, const void*)
                        { return false; }, [](auto, auto, auto) {}, std::nullopt, "THROW_AWAY")
                        .PrepContainerForFrame(std::vector<EntityId>{}));
}

TEST(ComponentBufferMemoryContainerTest, GetDeleteInstructionStateReturnsCorrectState)
{
    int32_t deleteState = -1;

    auto container = ComponentBufferMemoryContainer(
        1, reinterpret_cast<std::byte*>(&deleteState), sizeof(int32_t), nullptr, [](auto, auto, auto) {}, std::nullopt,
        "THROW_AWAY");

    EXPECT_EQ(std::memcmp(container.GetDeleteInstructionState().GetDataHandle(), &deleteState, sizeof(int32_t)), 0);
}

TEST(ComponentBufferMemoryContainerTest, PushComponentUpdateInstructionAddsNewEntryCorrectly)
{
    int32_t deleteState = -1;

    auto container = ComponentBufferMemoryContainer(
        1, reinterpret_cast<std::byte*>(&deleteState), sizeof(int32_t), [](const void*, const void*) { return false; },
        [](auto, auto, auto) {}, std::nullopt, "THROW_AWAY");

    int32_t updateState = 10;

    container.PushComponentUpdateInstruction(0, 0, &updateState);
    container.PrepContainerForFrame(std::vector<EntityId>{});

    ASSERT_EQ(container.GetImmutableDataLength(), 1);
    ASSERT_TRUE(container.HasComponent(0));

    EXPECT_EQ(*reinterpret_cast<const int32_t*>(container.GetComponent(0).GetDataHandle()), 10);
}

TEST(ComponentBufferMemoryContainerTest, PushComponentUpdateInstructionUpdatesExistingEntryCorrectly)
{
    int32_t deleteState = -1;

    auto container = ComponentBufferMemoryContainer(
        1, reinterpret_cast<std::byte*>(&deleteState), sizeof(int32_t), [](const void* lhs, const void* rhs)
        { return *reinterpret_cast<const int32_t*>(lhs) == *reinterpret_cast<const int32_t*>(rhs); },
        [](auto intRoot, auto intUpdate, auto)
        { *reinterpret_cast<int32_t*>(intRoot) += *reinterpret_cast<const int32_t*>(intUpdate); }, std::nullopt,
        "THROW_AWAY");

    int32_t updateState = 10;

    container.PushComponentUpdateInstruction(0, 0, &updateState);
    container.PrepContainerForFrame(std::vector<EntityId>{});
    container.PushComponentUpdateInstruction(0, 0, &updateState);
    container.PrepContainerForFrame(std::vector<EntityId>{});

    ASSERT_EQ(container.GetImmutableDataLength(), 1);
    ASSERT_TRUE(container.HasComponent(0));
    EXPECT_EQ(*reinterpret_cast<const int32_t*>(container.GetComponent(0).GetDataHandle()), 20);
}

TEST(ComponentBufferMemoryContainerTest, PushComponentUpdateInstructionRemovesEntryCorrectly)
{
    int32_t deleteState = -1;

    auto container = ComponentBufferMemoryContainer(
        1, reinterpret_cast<std::byte*>(&deleteState), sizeof(int32_t), [](const void* lhs, const void* rhs)
        { return *reinterpret_cast<const int32_t*>(lhs) == *reinterpret_cast<const int32_t*>(rhs); },
        [](auto, auto, auto) {}, std::nullopt, "THROW_AWAY");

    int32_t updateState = 10;

    container.PushComponentUpdateInstruction(0, 0, &updateState);
    container.PrepContainerForFrame(std::vector<EntityId>{});
    container.PushComponentUpdateInstruction(0, 0, container.GetDeleteInstructionState().GetDataHandle());
    container.PrepContainerForFrame(std::vector<EntityId>{});

    EXPECT_EQ(container.GetImmutableDataLength(), 0);
    EXPECT_FALSE(container.HasComponent(0));
}

TEST(ComponentBufferMemoryContainerTest, ForRangeSupportWorksCorrectly)
{
    int32_t deleteState = -1;

    auto container = ComponentBufferMemoryContainer(
        1, reinterpret_cast<std::byte*>(&deleteState), sizeof(int32_t), [](const void*, const void*) { return false; },
        [](auto, auto, auto) {}, std::nullopt, "THROW_AWAY");
    int32_t updateState = 10;

    container.PushComponentUpdateInstruction(0, 0, &updateState);
    container.PushComponentUpdateInstruction(0, 1, &updateState);
    container.PushComponentUpdateInstruction(0, 2, &updateState);
    container.PrepContainerForFrame(std::vector<EntityId>{});

    for (auto [entity, intComponent] : container)
    {
        EXPECT_EQ(*reinterpret_cast<const int32_t*>(intComponent.GetDataHandle()), 10);
    }
}

TEST(ComponentBufferMemoryContainerTest, ConcurrentAccessWorksCorrectly)
{
    int32_t deleteState = -1;

    auto container = ComponentBufferMemoryContainer(
        2, reinterpret_cast<std::byte*>(&deleteState), sizeof(int32_t), [](const void* lhs, const void* rhs)
        { return *reinterpret_cast<const int32_t*>(lhs) == *reinterpret_cast<const int32_t*>(rhs); },
        [](auto intRoot, auto intUpdate, auto)
        { *reinterpret_cast<int32_t*>(intRoot) += *reinterpret_cast<const int32_t*>(intUpdate); }, std::nullopt,
        "THROW_AWAY");

    int32_t updateState = 10;

    for (size_t i = 0; i < 2000; ++i)
    {
        container.PushComponentUpdateInstruction(0, i, &updateState);
    }

    container.PrepContainerForFrame(std::vector<EntityId>{});

    std::thread threadOne(
        [&]()
        {
            for (size_t i = 0; i < 2000; ++i)
            {
                container.PushComponentUpdateInstruction(0, i, &updateState);
            }
        });

    std::thread threadTwo(
        [&]()
        {
            for (size_t i = 0; i < 2000; ++i)
            {
                container.PushComponentUpdateInstruction(1, i, &updateState);
            }
        });

    threadOne.join();
    threadTwo.join();

    container.PrepContainerForFrame(std::vector<EntityId>{});

    for (auto [entity, intComponent] : container)
    {
        EXPECT_EQ(*reinterpret_cast<const int32_t*>(intComponent.GetDataHandle()), 30);
    }
}

TEST(ComponentBufferMemoryContainerTest, ConstructionWithoutEitherOperationThrows)
{
    EXPECT_THROW(CreateIntContainer(false, false), std::invalid_argument);
}

TEST(ComponentBufferMemoryContainerTest, UnsupportedInstructionsThrowWithoutAddingEntry)
{
    auto assignmentOnly = CreateIntContainer(false, true);
    auto mergeOnly = CreateIntContainer(true, false);
    int32_t state = 10;

    EXPECT_THROW(assignmentOnly.PushComponentUpdateInstruction(0, 0, &state), Exceptions::InvalidOperationException);
    EXPECT_THROW(mergeOnly.PushComponentAssignmentInstruction(0, 0, &state), Exceptions::InvalidOperationException);

    assignmentOnly.PrepContainerForFrame({});
    mergeOnly.PrepContainerForFrame({});

    EXPECT_FALSE(assignmentOnly.HasComponent(0));
    EXPECT_FALSE(mergeOnly.HasComponent(0));
}

TEST(ComponentBufferMemoryContainerTest, AssignmentIsDeferredAndReplacesExistingState)
{
    for (bool allowMerge : {false, true})
    {
        SCOPED_TRACE(allowMerge);
        auto container = CreateIntContainer(allowMerge, true);
        int32_t state = 5;
        container.PushComponentAssignmentInstruction(0, 0, &state);
        EXPECT_FALSE(container.HasComponent(0));
        container.PrepContainerForFrame({});
        ASSERT_TRUE(container.HasComponent(0));
        EXPECT_EQ(*static_cast<const int32_t*>(container.GetComponent(0).GetDataHandle()), 5);

        state = 10;
        container.PushComponentAssignmentInstruction(0, 0, &state);
        EXPECT_EQ(*static_cast<const int32_t*>(container.GetComponent(0).GetDataHandle()), 5);

        container.PrepContainerForFrame({});
        EXPECT_EQ(*static_cast<const int32_t*>(container.GetComponent(0).GetDataHandle()), 10);

        container.PrepContainerForFrame({});
        EXPECT_EQ(*static_cast<const int32_t*>(container.GetComponent(0).GetDataHandle()), 10);
    }
}

TEST(ComponentBufferMemoryContainerTest, RepeatedAssignmentsKeepLastState)
{
    auto container = CreateIntContainer(false, true);
    int32_t state = 10;
    container.PushComponentAssignmentInstruction(0, 0, &state);
    state = 3;
    container.PushComponentAssignmentInstruction(0, 0, &state);
    container.PrepContainerForFrame({});

    ASSERT_EQ(container.GetImmutableDataLength(), 1);
    EXPECT_EQ(*static_cast<const int32_t*>(container.GetComponent(0).GetDataHandle()), 3);
}

TEST(ComponentBufferMemoryContainerTest, AssignmentRejectsInvalidPoolId)
{
    auto container = CreateIntContainer(false, true);
    int32_t state = 10;

    EXPECT_THROW(container.PushComponentAssignmentInstruction(1, 0, &state), std::out_of_range);
}

TEST(ComponentBufferMemoryContainerTest, AssignmentCanRemoveComponentUsingDeleteState)
{
    auto container = CreateIntContainer(false, true);
    int32_t state = 10;

    container.PushComponentAssignmentInstruction(0, 0, &state);
    container.PrepContainerForFrame({});

    ASSERT_TRUE(container.HasComponent(0));

    container.PushComponentAssignmentInstruction(0, 0, container.GetDeleteInstructionState().GetDataHandle());
    container.PrepContainerForFrame({});

    EXPECT_FALSE(container.HasComponent(0));
    EXPECT_EQ(container.GetImmutableDataLength(), 0);
}

TEST(ComponentBufferMemoryContainerTest, AssignmentThenMergePreservesBothOperations)
{
    for (size_t mergePool : {0u, 1u})
    {
        SCOPED_TRACE(mergePool);
        auto container = CreateIntContainer(true, true, 2);
        int32_t initial = 5;
        container.PushComponentUpdateInstruction(0, 0, &initial);
        container.PrepContainerForFrame({});

        int32_t assignment = 10;
        int32_t update = 3;

        container.PushComponentAssignmentInstruction(0, 0, &assignment);
        container.PushComponentUpdateInstruction(mergePool, 0, &update);
        container.PrepContainerForFrame({});

        int32_t result = *static_cast<const int32_t*>(container.GetComponent(0).GetDataHandle());

        if (mergePool == 0)
        {
            EXPECT_EQ(result, 13);
        }
        else
        {
            // Resolution order across workers is not guaranteed, so we check for it like this instead.
            // The streaming operator here lets us append the value for diagnostic reasons should the test fail.
            EXPECT_TRUE(result == 13 || result == 10) << result;
        }
    }
}

TEST(ComponentBufferMemoryContainerTest, MergeThenAssignmentDiscardsEarlierState)
{
    for (size_t assignmentPool : {0u, 1u})
    {
        SCOPED_TRACE(assignmentPool);

        auto container = CreateIntContainer(true, true, 2);
        int32_t initial = 5;

        container.PushComponentUpdateInstruction(0, 0, &initial);
        container.PrepContainerForFrame({});

        int32_t update = 3;
        int32_t assignment = 10;

        container.PushComponentUpdateInstruction(0, 0, &update);
        container.PushComponentAssignmentInstruction(assignmentPool, 0, &assignment);
        container.PrepContainerForFrame({});

        int32_t result = *static_cast<const int32_t*>(container.GetComponent(0).GetDataHandle());

        if (assignmentPool == 0)
        {
            EXPECT_EQ(result, 10);
        }
        else
        {
            // Resolution order across workers is not guaranteed.
            EXPECT_TRUE(result == 13 || result == 10) << result;
        }
    }
}

TEST(ComponentBufferMemoryContainerTest, AssignmentFlagsFollowDenseOrderAndResetBetweenFrames)
{
    auto container = CreateIntContainer(true, true);
    int32_t initial = 5;

    container.PushComponentUpdateInstruction(0, 7, &initial);
    container.PushComponentUpdateInstruction(0, 2, &initial);
    container.PrepContainerForFrame({});

    int32_t update = 3;
    int32_t assignment = 10;

    container.PushComponentUpdateInstruction(0, 7, &update);
    container.PushComponentUpdateInstruction(0, 2, &update);
    container.PushComponentAssignmentInstruction(0, 2, &assignment);
    container.PrepContainerForFrame({});

    EXPECT_EQ(*static_cast<const int32_t*>(container.GetComponent(7).GetDataHandle()), 8);
    EXPECT_EQ(*static_cast<const int32_t*>(container.GetComponent(2).GetDataHandle()), 10);

    container.PushComponentUpdateInstruction(0, 2, &update);
    container.PushComponentUpdateInstruction(0, 7, &update);
    container.PrepContainerForFrame({});

    EXPECT_EQ(*static_cast<const int32_t*>(container.GetComponent(2).GetDataHandle()), 13);
    EXPECT_EQ(*static_cast<const int32_t*>(container.GetComponent(7).GetDataHandle()), 11);
}
