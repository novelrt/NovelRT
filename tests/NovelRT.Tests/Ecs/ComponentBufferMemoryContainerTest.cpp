// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <atomic>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;

TEST(ComponentBufferMemoryContainerTest, PrepComponentBuffersForFrameDoesNotThrow)
{
    int32_t deleteState = -1;
    EXPECT_NO_THROW(ComponentBufferMemoryContainer(
                        1, &deleteState, sizeof(int32_t), [](auto, auto, auto) {}, [](const void*, const void*) { return false; }, "THROW_AWAY")
                        .PrepContainerForFrame(std::vector<EntityId>{}));
}

TEST(ComponentBufferMemoryContainerTest, GetDeleteInstructionStateReturnsCorrectState)
{
    int32_t deleteState = -1;
    auto container = ComponentBufferMemoryContainer(1, &deleteState, sizeof(int32_t), nullptr, nullptr, "THROW_AWAY");
    EXPECT_EQ(std::memcmp(container.GetDeleteInstructionState().GetDataHandle(), &deleteState, sizeof(int32_t)), 0);
}

TEST(ComponentBufferMemoryContainerTest, PushComponentUpdateInstructionAddsNewEntryCorrectly)
{
    int32_t deleteState = -1;
    auto container = ComponentBufferMemoryContainer(
        1, &deleteState, sizeof(int32_t), [](auto, auto, auto) {}, [](const void*, const void*) { return false; }, "THROW_AWAY");
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
        1, &deleteState, sizeof(int32_t),
        [](auto intRoot, auto intUpdate, auto) {
            *reinterpret_cast<int32_t*>(intRoot) += *reinterpret_cast<const int32_t*>(intUpdate);
        },
        [](const void* lhs, const void* rhs) {
            return *reinterpret_cast<const int32_t*>(lhs) == *reinterpret_cast<const int32_t*>(rhs);
        },
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
        1, &deleteState, sizeof(int32_t), [](auto, auto, auto) {}, [](const void* lhs, const void* rhs) { 
            return *reinterpret_cast<const int32_t*>(lhs) == *reinterpret_cast<const int32_t*>(rhs);
 }, "THROW_AWAY");
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
        1, &deleteState, sizeof(int32_t), [](auto, auto, auto) {}, [](const void*, const void*) { return false; }, "THROW_AWAY");
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
        2, &deleteState, sizeof(int32_t),
        [](auto intRoot, auto intUpdate, auto) {
            *reinterpret_cast<int32_t*>(intRoot) += *reinterpret_cast<const int32_t*>(intUpdate);
        },
        [](const void* lhs, const void* rhs) {
            return *reinterpret_cast<const int32_t*>(lhs) == *reinterpret_cast<const int32_t*>(rhs);
        },
        "THROW_AWAY");
    int32_t updateState = 10;

    for (size_t i = 0; i < 2000; ++i)
    {
        container.PushComponentUpdateInstruction(0, i, &updateState);
    }

    container.PrepContainerForFrame(std::vector<EntityId>{});

    std::thread threadOne([&]() {
        for (size_t i = 0; i < 2000; ++i)
        {
            container.PushComponentUpdateInstruction(0, i, &updateState);
        }
    });

    std::thread threadTwo([&]() {
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
