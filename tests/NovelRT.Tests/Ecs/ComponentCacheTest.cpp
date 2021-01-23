// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <atomic>

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
    EXPECT_NO_THROW(cache.RegisterComponentType<int32_t>(NAN));
}

TEST_F(ComponentCacheTest, GetComponentBufferReturnsValidBuffer)
{
    cache.RegisterComponentType<int32_t>(NAN);
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
    cache.RegisterComponentType<int32_t>(NAN);
    auto buffer = cache.GetComponentBuffer<int32_t>();
    buffer.PushComponentUpdateInstruction(0, 0, 10);
    ASSERT_NO_THROW(cache.PrepAllBuffersForNextFrame(std::vector<EntityId>{}));
    ASSERT_EQ(buffer.GetComponent(0), 10);
    ASSERT_NO_THROW(cache.PrepAllBuffersForNextFrame(std::vector<EntityId>{0}));
    EXPECT_EQ(buffer.GetImmutableDataLength(), 0);
}