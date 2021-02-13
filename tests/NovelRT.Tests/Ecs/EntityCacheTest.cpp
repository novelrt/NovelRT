// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <atomic>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;

class EntityCacheTest : public testing::Test
{
public:
    EntityCache cache = EntityCache(1);

protected:
    void SetUp() override
    {
        cache = EntityCache(1);
    }
};

TEST_F(EntityCacheTest, ProcessEntityDeletionRequestsFromThreadsDoesNotThrow)
{
    EXPECT_NO_THROW(cache.ProcessEntityDeletionRequestsFromThreads());
}

TEST_F(EntityCacheTest, RemoveEntityGetsProcessedCorrectlyForGivenPoolId)
{
    cache.RemoveEntity(0, 0);
    cache.ProcessEntityDeletionRequestsFromThreads();
    EXPECT_EQ(cache.GetEntitiesToRemoveThisFrame().at(0), 0);
}
