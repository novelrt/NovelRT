// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentBufferMemoryContainer.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>
#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <array>
#include <atomic>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;

TEST(ComponentBufferTest, PrepComponentBuffersForFrameDoesNotThrow)
{
    EXPECT_NO_THROW(ComponentBuffer<int32_t>(1, -1, "THROW_AWAY").PrepComponentBufferForFrame(std::vector<EntityId>{}));
}

TEST(ComponentBufferTest, GetDeleteInstructionStateReturnsCorrectState)
{
    EXPECT_EQ(ComponentBuffer<int32_t>(1, -1, "THROW_AWAY").GetDeleteInstructionState(), -1);
}

TEST(ComponentBufferTest, GetComponentUnsafeGetsComponentWithValidKey)
{
    auto buffer = ComponentBuffer<int32_t>(1, -1, "THROW_AWAY");
    buffer.PushComponentUpdateInstruction(0, 0, 10);
    buffer.PrepComponentBufferForFrame(std::vector<EntityId>{});

    ASSERT_EQ(buffer.GetImmutableDataLength(), 1);
    ASSERT_TRUE(buffer.HasComponent(0));
    EXPECT_EQ(buffer.GetComponentUnsafe(0), 10);
}

TEST(ComponentBufferTest, PushComponentUpdateInstructionAddsNewEntryCorrectly)
{
    auto buffer = ComponentBuffer<int32_t>(1, -1, "THROW_AWAY");
    buffer.PushComponentUpdateInstruction(0, 0, 10);
    buffer.PrepComponentBufferForFrame(std::vector<EntityId>{});

    ASSERT_EQ(buffer.GetImmutableDataLength(), 1);
    ASSERT_TRUE(buffer.HasComponent(0));
    EXPECT_EQ(buffer.GetComponent(0), 10);
}

TEST(ComponentBufferTest, PushComponentUpdateInstructionUpdatesExistingEntryCorrectly)
{
    auto buffer = ComponentBuffer<int32_t>(1, -1, "THROW_AWAY");
    buffer.PushComponentUpdateInstruction(0, 0, 10);
    buffer.PrepComponentBufferForFrame(std::vector<EntityId>{});
    buffer.PushComponentUpdateInstruction(0, 0, 10);
    buffer.PrepComponentBufferForFrame(std::vector<EntityId>{});

    ASSERT_EQ(buffer.GetImmutableDataLength(), 1);
    EXPECT_EQ(buffer.GetComponent(0), 20);
}

TEST(ComponentBufferTest, PushComponentUpdateInstructionRemovesEntryCorrectly)
{
    auto buffer = ComponentBuffer<int32_t>(1, -1, "THROW_AWAY");
    buffer.PushComponentUpdateInstruction(0, 0, 10);
    buffer.PrepComponentBufferForFrame(std::vector<EntityId>{});
    buffer.PushComponentUpdateInstruction(0, 0, -1);
    buffer.PrepComponentBufferForFrame(std::vector<EntityId>{});

    EXPECT_EQ(buffer.GetImmutableDataLength(), 0);
}

TEST(ComponentBufferTest, ForRangeSupportWorksCorrectly)
{
    auto buffer = ComponentBuffer<int32_t>(1, -1, "THROW_AWAY");
    buffer.PushComponentUpdateInstruction(0, 0, 10);
    buffer.PushComponentUpdateInstruction(0, 1, 10);
    buffer.PushComponentUpdateInstruction(0, 2, 10);
    buffer.PrepComponentBufferForFrame(std::vector<EntityId>{});

    for (auto [entity, intComponent] : buffer)
    {
        EXPECT_EQ(intComponent, 10);
    }
}

TEST(ComponentBufferTest, ConcurrentAccessWorksCorrectly)
{
    auto container = ComponentBuffer<int32_t>(2, -1, "THROW_AWAY");

    for (size_t i = 0; i < 2000; i++)
    {
        container.PushComponentUpdateInstruction(0, i, 10);
    }

    container.PrepComponentBufferForFrame(std::vector<EntityId>{});

    std::thread threadOne(
        [&]()
        {
            for (size_t i = 0; i < 2000; i++)
            {
                container.PushComponentUpdateInstruction(0, i, 10);
            }
        });

    std::thread threadTwo(
        [&]()
        {
            for (size_t i = 0; i < 2000; i++)
            {
                container.PushComponentUpdateInstruction(1, i, 10);
            }
        });

    threadOne.join();
    threadTwo.join();

    container.PrepComponentBufferForFrame(std::vector<EntityId>{});

    for (auto [entity, intComponent] : container)
    {
        EXPECT_EQ(intComponent, 30);
    }
}

TEST(ComponentBufferTest, CanAccessValidUnderlyingContainer)
{
    auto container = ComponentBuffer<int32_t>(1, -1, "THROW_AWAY");

    for (size_t i = 0; i < 10; i++)
    {
        container.PushComponentUpdateInstruction(0, i, 10);
    }

    EXPECT_EQ(container.GetUnderlyingContainer()->GetImmutableDataLength(), container.GetImmutableDataLength());
}

TEST(ComponentBufferTest, TypeWithoutMergeOperatorSupportsAssignmentOnly)
{
    using Component = std::array<int32_t, 1>;
    auto buffer = ComponentBuffer<Component>(1, Component{-1}, "THROW_AWAY");

    EXPECT_THROW(buffer.PushComponentUpdateInstruction(0, 0, Component{10}), Exceptions::InvalidOperationException);

    auto container = buffer.GetUnderlyingContainer();
    Component state{10};
    container->PushComponentAssignmentInstruction(0, 0, &state);
    buffer.PrepComponentBufferForFrame({});

    EXPECT_EQ(buffer.GetComponent(0), state);

    state = Component{3};
    container->PushComponentAssignmentInstruction(0, 0, &state);
    buffer.PrepComponentBufferForFrame({});

    EXPECT_EQ(buffer.GetComponent(0), state);
}

TEST(ComponentBufferTest, TypeWithoutAssignmentOperatorSupportsMergeOnly)
{
    struct MergeOnlyComponent
    {
        int32_t value;

        explicit MergeOnlyComponent(int32_t initialValue) : value(initialValue)
        {
        }

        MergeOnlyComponent(const MergeOnlyComponent&) = default;
        MergeOnlyComponent& operator=(const MergeOnlyComponent&) = delete;

        void operator+=(const MergeOnlyComponent& update)
        {
            value += update.value;
        }

        bool operator==(const MergeOnlyComponent&) const = default;
    };

    auto buffer = ComponentBuffer<MergeOnlyComponent>(1, MergeOnlyComponent{-1}, "THROW_AWAY");
    MergeOnlyComponent state{10};

    EXPECT_THROW(buffer.GetUnderlyingContainer()->PushComponentAssignmentInstruction(0, 0, &state),
                 Exceptions::InvalidOperationException);

    buffer.PushComponentUpdateInstruction(0, 0, state);
    buffer.PrepComponentBufferForFrame({});
    buffer.PushComponentUpdateInstruction(0, 0, state);
    buffer.PrepComponentBufferForFrame({});

    EXPECT_EQ(buffer.GetComponent(0).value, 20);
}
