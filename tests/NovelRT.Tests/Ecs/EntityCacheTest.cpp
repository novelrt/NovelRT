// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
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

TEST_F(EntityCacheTest, AddEntityAddsEntityCorrectly)
{
    cache.AddEntity(0, 10);
    cache.ProcessEntityRegistrationRequestsFromThreads();
    EXPECT_NE(std::find(cache.GetRegisteredEntities().begin(), cache.GetRegisteredEntities().end(), 10ULL), cache.GetRegisteredEntities().end());
}

TEST_F(EntityCacheTest, AddEntityAddsEntityCorrectlyMultipleTimes)
{
    cache.AddEntity(0, 10);
    cache.ProcessEntityRegistrationRequestsFromThreads();

    cache.AddEntity(0, 20);
    cache.ProcessEntityRegistrationRequestsFromThreads();

    EXPECT_NE(std::find(cache.GetRegisteredEntities().begin(), cache.GetRegisteredEntities().end(), 10ULL), cache.GetRegisteredEntities().end());
    EXPECT_NE(std::find(cache.GetRegisteredEntities().begin(), cache.GetRegisteredEntities().end(), 20ULL), cache.GetRegisteredEntities().end());
}

TEST_F(EntityCacheTest, ProcessEntityDeletionRequestsFromThreadsDoesNotThrow)
{
    EXPECT_NO_THROW(cache.ProcessEntityDeletionRequestsFromThreads());
}

TEST_F(EntityCacheTest, RemoveEntityGetsProcessedCorrectlyForGivenPoolId)
{
    cache.RemoveEntity(0, 0);
    cache.ProcessEntityDeletionRequestsFromThreads();
    EXPECT_EQ(cache.GetEntitiesToRemoveThisFrame().at(0), Atom(0));
}

TEST_F(EntityCacheTest, ApplyEntityDeletionRequestsToRegisteredEntitiesAppliesEntityDeletionCorrectly)
{
    cache.AddEntity(0, 10);
    cache.AddEntity(0, 20);
    cache.AddEntity(0, 30);
    cache.ProcessEntityRegistrationRequestsFromThreads();

    cache.RemoveEntity(0, 10);
    cache.ProcessEntityDeletionRequestsFromThreads();
    cache.ApplyEntityDeletionRequestsToRegisteredEntities();

    ASSERT_EQ(std::find(cache.GetRegisteredEntities().begin(), cache.GetRegisteredEntities().end(), 10ULL), cache.GetRegisteredEntities().end());
    EXPECT_NE(std::find(cache.GetRegisteredEntities().begin(), cache.GetRegisteredEntities().end(), 20ULL), cache.GetRegisteredEntities().end());
    EXPECT_NE(std::find(cache.GetRegisteredEntities().begin(), cache.GetRegisteredEntities().end(), 30ULL), cache.GetRegisteredEntities().end());
}
