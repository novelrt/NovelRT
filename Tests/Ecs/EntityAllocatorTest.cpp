// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EntityAllocator.hpp>
#include <NovelRT/Ecs/EntityHandle.hpp>
#include <NovelRT/Exceptions/KeyNotFoundException.hpp>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;

class EntityAllocatorTest : public testing::Test
{
public:
    EntityAllocator Allocator;
};

TEST_F(EntityAllocatorTest, AllocateReturnsValidEntityHandle)
{
    const auto entity = Allocator.Allocate();

    EXPECT_TRUE(Allocator.IsValid(entity));
}

TEST_F(EntityAllocatorTest, AllocateReturnsDifferentIdsForAllocatedEntities)
{
    const auto firstEntity = Allocator.Allocate();
    const auto secondEntity = Allocator.Allocate();

    EXPECT_NE(firstEntity.Id, secondEntity.Id);
    EXPECT_TRUE(Allocator.IsValid(firstEntity));
    EXPECT_TRUE(Allocator.IsValid(secondEntity));
}

TEST_F(EntityAllocatorTest, FreeInvalidatesEntityHandle)
{
    const auto entity = Allocator.Allocate();
    Allocator.Free(entity);

    EXPECT_FALSE(Allocator.IsValid(entity));
}

TEST_F(EntityAllocatorTest, AllocateRecyclesFreedEntityWithNewGeneration)
{
    const auto entity = Allocator.Allocate();
    Allocator.Free(entity);
    const auto recycledEntity = Allocator.Allocate();

    EXPECT_EQ(recycledEntity.Id, entity.Id);
    EXPECT_EQ(recycledEntity.Generation, entity.Generation + 1);
    EXPECT_TRUE(Allocator.IsValid(recycledEntity));
    EXPECT_FALSE(Allocator.IsValid(entity));
}

TEST_F(EntityAllocatorTest, FreeIgnoresRepeatedRequests)
{
    const auto entity = Allocator.Allocate();

    Allocator.Free(entity);
    Allocator.Free(entity);

    const auto firstEntity = Allocator.Allocate();
    const auto secondEntity = Allocator.Allocate();

    EXPECT_NE(firstEntity.Id, secondEntity.Id);
    EXPECT_TRUE(Allocator.IsValid(firstEntity));
    EXPECT_TRUE(Allocator.IsValid(secondEntity));
}

TEST_F(EntityAllocatorTest, FreeIgnoresStaleHandles)
{
    const auto entity = Allocator.Allocate();
    Allocator.Free(entity);
    const auto recycledEntity = Allocator.Allocate();

    ASSERT_EQ(entity.Id, recycledEntity.Id);
    ASSERT_NE(entity.Generation, recycledEntity.Generation);

    Allocator.Free(entity);

    EXPECT_TRUE(Allocator.IsValid(recycledEntity));

    const auto nextEntity = Allocator.Allocate();

    EXPECT_NE(nextEntity.Id, recycledEntity.Id);
}

TEST_F(EntityAllocatorTest, FreeIgnoresUntrackedEntities)
{
    EntityAllocator otherAllocator;
    const auto entity = otherAllocator.Allocate();

    EXPECT_NO_THROW(Allocator.Free(entity));
    EXPECT_FALSE(Allocator.IsValid(entity));

    const auto allocatedEntity = Allocator.Allocate();

    EXPECT_NE(allocatedEntity.Id, entity.Id);
    EXPECT_TRUE(Allocator.IsValid(allocatedEntity));
}

TEST_F(EntityAllocatorTest, CreateHandleForAllocatedReturnsCurrentHandle)
{
    const auto entity = Allocator.Allocate();
    Allocator.Free(entity);
    const auto recycledEntity = Allocator.Allocate();

    const auto handle = Allocator.CreateHandleForAllocated(recycledEntity.Id);

    EXPECT_EQ(handle.Id, recycledEntity.Id);
    EXPECT_EQ(handle.Generation, recycledEntity.Generation);
}

TEST_F(EntityAllocatorTest, CreateHandleForAllocatedThrowsForFreedEntity)
{
    const auto entity = Allocator.Allocate();
    Allocator.Free(entity);

    EXPECT_THROW(static_cast<void>(Allocator.CreateHandleForAllocated(entity.Id)), Exceptions::KeyNotFoundException);
}

TEST_F(EntityAllocatorTest, CreateHandleForAllocatedThrowsForUntrackedEntity)
{
    EntityAllocator otherAllocator;
    const auto entity = otherAllocator.Allocate();

    EXPECT_THROW(static_cast<void>(Allocator.CreateHandleForAllocated(entity.Id)), Exceptions::KeyNotFoundException);
}
