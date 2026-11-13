// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EntityCache.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>
#include <NovelRT/Ecs/SparseSetMemoryContainer.hpp>
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
    cache.AddEntity(0, EntityHandle{.Id = 10, .Generation = 0});
    cache.ProcessEntityRegistrationRequestsFromThreads();

    EXPECT_NE(std::find(cache.GetRegisteredEntities().begin(), cache.GetRegisteredEntities().end(),
                        EntityHandle{.Id = 10, .Generation = 0}),
              cache.GetRegisteredEntities().end());
}

TEST_F(EntityCacheTest, AddEntityAddsEntityCorrectlyMultipleTimes)
{
    cache.AddEntity(0, EntityHandle{.Id = 10, .Generation = 0});
    cache.ProcessEntityRegistrationRequestsFromThreads();

    cache.AddEntity(0, EntityHandle{.Id = 20, .Generation = 0});
    cache.ProcessEntityRegistrationRequestsFromThreads();

    EXPECT_NE(std::find(cache.GetRegisteredEntities().begin(), cache.GetRegisteredEntities().end(),
                        EntityHandle{.Id = 10, .Generation = 0}),
              cache.GetRegisteredEntities().end());

    EXPECT_NE(std::find(cache.GetRegisteredEntities().begin(), cache.GetRegisteredEntities().end(),
                        EntityHandle{.Id = 20, .Generation = 0}),
              cache.GetRegisteredEntities().end());
}

TEST_F(EntityCacheTest, ProcessEntityDeletionRequestsFromThreadsDoesNotThrow)
{
    EXPECT_NO_THROW(cache.ProcessEntityDeletionRequestsFromThreads());
}

TEST_F(EntityCacheTest, RemoveEntityGetsProcessedCorrectlyForGivenPoolId)
{
    EntityHandle handle{.Id = 0, .Generation = 0};
    cache.RemoveEntity(0, handle);
    cache.ProcessEntityDeletionRequestsFromThreads();

    // MACROS SUCK WHY DOES IT MAKE ME DO THIS AAAAA - Matt J.
    EXPECT_EQ(cache.GetEntitiesToRemoveThisFrame().at(0), handle);
}

TEST_F(EntityCacheTest, ApplyEntityDeletionRequestsToRegisteredEntitiesAppliesEntityDeletionCorrectly)
{
    cache.AddEntity(0, EntityHandle{.Id = 10, .Generation = 0});
    cache.AddEntity(0, EntityHandle{.Id = 20, .Generation = 0});
    cache.AddEntity(0, EntityHandle{.Id = 30, .Generation = 0});
    cache.ProcessEntityRegistrationRequestsFromThreads();

    cache.RemoveEntity(0, EntityHandle{.Id = 10, .Generation = 0});
    cache.ProcessEntityDeletionRequestsFromThreads();
    cache.ApplyEntityDeletionRequestsToRegisteredEntities();

    ASSERT_EQ(std::find(cache.GetRegisteredEntities().begin(), cache.GetRegisteredEntities().end(),
                        EntityHandle{.Id = 10, .Generation = 0}),
              cache.GetRegisteredEntities().end());

    EXPECT_NE(std::find(cache.GetRegisteredEntities().begin(), cache.GetRegisteredEntities().end(),
                        EntityHandle{.Id = 20, .Generation = 0}),
              cache.GetRegisteredEntities().end());

    EXPECT_NE(std::find(cache.GetRegisteredEntities().begin(), cache.GetRegisteredEntities().end(),
                        EntityHandle{.Id = 30, .Generation = 0}),
              cache.GetRegisteredEntities().end());
}
