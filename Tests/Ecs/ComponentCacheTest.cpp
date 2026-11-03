// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentBufferMemoryContainer.hpp>
#include <NovelRT/Ecs/ComponentCache.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>
#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <array>
#include <atomic>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;

class ComponentCacheTest : public testing::Test
{
public:
    ComponentCache cache = ComponentCache(1);

protected:
    void SetUp() override
    {
        cache = ComponentCache(1);
    }
};

TEST_F(ComponentCacheTest, RegisterComponentTypeDoesNotThrow)
{
    EXPECT_NO_THROW(cache.RegisterComponentType<int32_t>(-1, "THROW_AWAY"));
}

TEST_F(ComponentCacheTest, GetComponentBufferReturnsValidBuffer)
{
    cache.RegisterComponentType<int32_t>(-1, "THROW_AWAY");
    auto buffer = cache.GetComponentBuffer<int32_t>();

    buffer.PushComponentUpdateInstruction(0, 0, 10);
    buffer.PrepComponentBufferForFrame(std::vector<EntityId>{});

    for (auto [entity, component] : buffer)
    {
        EXPECT_EQ(component, 10);
    }
}

TEST_F(ComponentCacheTest, PrepAllBuffersForNextFrameUpdatesEntitiesCorrectly)
{
    cache.RegisterComponentType<int32_t>(-1, "THROW_AWAY");
    auto buffer = cache.GetComponentBuffer<int32_t>();

    buffer.PushComponentUpdateInstruction(0, 0, 10);

    ASSERT_NO_THROW(cache.PrepAllBuffersForNextFrame(std::vector<EntityId>{}));
    ASSERT_EQ(buffer.GetComponent(0), 10);

    ASSERT_NO_THROW(cache.PrepAllBuffersForNextFrame(std::vector<EntityId>{0}));

    EXPECT_EQ(buffer.GetImmutableDataLength(), 0);
}

TEST_F(ComponentCacheTest, RegisterComponentTypeWithoutMergeOperatorSupportsAssignmentOnly)
{
    using Component = std::array<int32_t, 1>;

    cache.RegisterComponentType<Component>(Component{-1}, "THROW_AWAY");
    auto buffer = cache.GetComponentBuffer<Component>();

    EXPECT_THROW(buffer.PushComponentUpdateInstruction(0, 0, Component{10}), Exceptions::InvalidOperationException);

    Component state{10};

    buffer.GetUnderlyingContainer()->PushComponentAssignmentInstruction(0, 0, &state);
    cache.PrepAllBuffersForNextFrame({});

    EXPECT_EQ(buffer.GetComponent(0), state);

    state = Component{3};
    buffer.GetUnderlyingContainer()->PushComponentAssignmentInstruction(0, 0, &state);
    cache.PrepAllBuffersForNextFrame({});

    EXPECT_EQ(buffer.GetComponent(0), state);
}

TEST_F(ComponentCacheTest, RegisterComponentTypeUnsafeSupportsAssignmentOnly)
{
    int32_t deleteState = -1;

    auto id = cache.RegisterComponentTypeUnsafe(
        sizeof(int32_t), reinterpret_cast<const std::byte*>(&deleteState), [](const void* lhs, const void* rhs)
        { return *static_cast<const int32_t*>(lhs) == *static_cast<const int32_t*>(rhs); }, std::nullopt,
        [](void* target, const void* update, size_t)
        { *static_cast<int32_t*>(target) = *static_cast<const int32_t*>(update); }, "THROW_AWAY");

    auto buffer = cache.GetComponentBufferById(id);
    int32_t state = 10;

    EXPECT_THROW(buffer->PushComponentUpdateInstruction(0, 0, &state), Exceptions::InvalidOperationException);

    buffer->PushComponentAssignmentInstruction(0, 0, &state);
    cache.PrepAllBuffersForNextFrame({});

    state = 3;
    buffer->PushComponentAssignmentInstruction(0, 0, &state);
    cache.PrepAllBuffersForNextFrame({});

    EXPECT_EQ(*static_cast<const int32_t*>(buffer->GetComponent(0).GetDataHandle()), 3);

    cache.PrepAllBuffersForNextFrame({0});

    EXPECT_FALSE(buffer->HasComponent(0));
}

TEST_F(ComponentCacheTest, RegisterComponentTypeUnsafeWithoutEitherOperationThrows)
{
    int32_t deleteState = -1;

    EXPECT_THROW((void)cache.RegisterComponentTypeUnsafe(
                     sizeof(int32_t), reinterpret_cast<const std::byte*>(&deleteState),
                     [](const void*, const void*) { return false; }, std::nullopt, std::nullopt, "THROW_AWAY"),
                 std::invalid_argument);

    EXPECT_TRUE(cache.GetAllComponentBuffers().empty());
}
