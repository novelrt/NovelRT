// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtEcs.h>
#include <NovelRT/NovelRT.h>

#include <atomic>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;

class InteropEntityCacheTest : public testing::Test
{
public:
    NrtEntityCacheHandle cache = nullptr;

protected:
    void SetUp() override
    {
        cache = Nrt_EntityCache_Create(1);
    }

    void TearDown() override
    {
        Nrt_EntityCache_Destroy(cache);
        cache = nullptr;
    }
};

TEST_F(InteropEntityCacheTest, RemoveEntityGetsProcessedCorrectlyForGivenPoolId)
{
    Nrt_EntityCache_RemoveEntity(cache, 0, 0);
    Nrt_EntityCache_ProcessEntityDeletionRequestsFromThreads(cache);
    auto ptr = Nrt_EntityCache_GetEntitiesToRemoveThisFrame(cache);
    EXPECT_EQ(reinterpret_cast<std::vector<EntityId>*>(ptr)->at(0), NovelRT::Core::Atom(0));
}
