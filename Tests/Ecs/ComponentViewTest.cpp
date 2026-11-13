
// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentBufferMemoryContainer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EntityAllocator.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>
#include <NovelRT/Ecs/SystemScheduler.hpp>
#include <atomic>
#include <gtest/gtest.h>
#include <utility>

using namespace NovelRT;
using namespace NovelRT::Ecs;

class ComponentViewTest : public testing::Test
{
public:
    ComponentView<int32_t>* testView = nullptr;
    ComponentBuffer<int32_t> testBuffer = ComponentBuffer<int32_t>(1, -1, "THROW_AWAY");
    EntityAllocator entityAllocator;
    EntityId testEntityId = 0;

protected:
    void SetUp() override
    {
        testBuffer = ComponentBuffer<int32_t>(1, -1, "THROW_AWAY");
        testEntityId = entityAllocator.Allocate().Id;
        testView = new ComponentView<int32_t>(0, testBuffer, entityAllocator);
    }

    void TearDown() override
    {
        delete testView;
        testView = nullptr;
    }
};

TEST_F(ComponentViewTest, CanReadImmutableDataSetCorrectly)
{
    testBuffer.PushComponentUpdateInstruction(0, testEntityId, 10);
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});

    for (auto [entity, component] : *testView)
    {
        EXPECT_EQ(component, 10);
    }
}

TEST_F(ComponentViewTest, CanPushComponentUpdateInstructionCorrectly)
{
    testBuffer.PushComponentUpdateInstruction(0, testEntityId, 10);
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});
    testView->PushComponentUpdateInstruction(testEntityId, 10);
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});

    EXPECT_EQ(testView->GetComponent(testEntityId), 20);
}

TEST_F(ComponentViewTest, AddComponentAddsNewComponentCorrectly)
{
    testView->AddComponent(testEntityId, 30);
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});
    EXPECT_EQ(testView->GetComponent(testEntityId), 30);
}

TEST_F(ComponentViewTest, RemoveComponentRemovesComponentCorrectly)
{
    testView->RemoveComponent(testEntityId);
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});
    EXPECT_EQ(testView->GetImmutableDataLength(), 0);
}

TEST_F(ComponentViewTest, TryAddComponentAddsComponentIfEntityDoesNotHaveExistingComponent)
{
    ASSERT_TRUE(testView->TryAddComponent(testEntityId, 20));
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});
    EXPECT_EQ(testView->GetComponent(testEntityId), 20);
}

TEST_F(ComponentViewTest, TryAddComponentDoesNotAddComponentIfEntityDoesHaveExistingComponentBetweenFrames)
{
    ASSERT_TRUE(testView->TryAddComponent(testEntityId, 10));
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});
    ASSERT_FALSE(testView->TryAddComponent(testEntityId, 20));
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});
    EXPECT_EQ(testView->GetComponent(testEntityId), 10);
}

TEST_F(ComponentViewTest, ComponentReadWriteOperationsForEntityHandlesWorkAsExpected)
{
    const EntityHandle& entity = entityAllocator.Allocate();
    testView->AddComponent(entity, 10);
    testBuffer.PrepComponentBufferForFrame({});

    const auto& view = *testView;
    int32_t component = -1;

    EXPECT_TRUE(view.HasComponent(entity));
    EXPECT_TRUE(view.TryGetComponent(entity, component));
    EXPECT_EQ(component, 10);
    EXPECT_EQ(view.GetComponent(entity), 10);
    EXPECT_EQ(view.GetComponentUnsafe(entity), 10);

    testView->PushComponentUpdateInstruction(entity, 5);
    testBuffer.PrepComponentBufferForFrame({});

    EXPECT_EQ(view.GetComponent(entity), 15);

    testView->RemoveComponent(entity);
    testBuffer.PrepComponentBufferForFrame({});

    EXPECT_FALSE(view.HasComponent(entity));
    EXPECT_THROW(static_cast<void>(view.GetComponent(entity)), Exceptions::KeyNotFoundException);

    testView->AddComponent(entity);
    testBuffer.PrepComponentBufferForFrame({});

    EXPECT_EQ(view.GetComponent(entity), 0);
}

TEST_F(ComponentViewTest, TryOperationsForEntityHandlesWorkAsExpected)
{
    const EntityHandle& entity = entityAllocator.Allocate();

    EXPECT_FALSE(testView->TryRemoveComponent(entity));
    ASSERT_TRUE(testView->TryAddComponent(entity));

    testBuffer.PrepComponentBufferForFrame({});

    EXPECT_EQ(testView->GetComponent(entity), 0);
    EXPECT_FALSE(testView->TryAddComponent(entity, 10));

    ASSERT_TRUE(testView->TryRemoveComponent(entity));

    testBuffer.PrepComponentBufferForFrame({});

    EXPECT_FALSE(testView->HasComponent(entity));
    EXPECT_FALSE(testView->TryRemoveComponent(entity));

    int32_t component = 123;

    EXPECT_FALSE(testView->TryGetComponent(entity, component));
    EXPECT_EQ(component, 123);
}

TEST_F(ComponentViewTest, StaleHandlesCannotReadOrModifyAReplacementEntity)
{
    const auto stale = entityAllocator.Allocate();
    entityAllocator.Free(stale);
    const auto replacement = entityAllocator.Allocate();

    ASSERT_EQ(stale.Id, replacement.Id);
    ASSERT_NE(stale.Generation, replacement.Generation);

    testView->AddComponent(replacement, 10);
    testBuffer.PrepComponentBufferForFrame({});
    testView->PushComponentUpdateInstruction(replacement, 5);

    EXPECT_THROW(testView->PushComponentUpdateInstruction(stale, 100), Exceptions::KeyNotFoundException);
    EXPECT_THROW(testView->AddComponent(stale, 100), Exceptions::KeyNotFoundException);
    EXPECT_THROW(testView->RemoveComponent(stale), Exceptions::KeyNotFoundException);

    EXPECT_THROW(static_cast<void>(testView->GetComponent(stale)), Exceptions::KeyNotFoundException);
    EXPECT_THROW(static_cast<void>(testView->GetComponentUnsafe(stale)), Exceptions::KeyNotFoundException);

    EXPECT_FALSE(testView->HasComponent(stale));
    EXPECT_FALSE(testView->TryAddComponent(stale, 100));
    EXPECT_FALSE(testView->TryRemoveComponent(stale));

    int32_t component = 123;

    EXPECT_FALSE(testView->TryGetComponent(stale, component));
    EXPECT_EQ(component, 123);

    testBuffer.PrepComponentBufferForFrame({});

    EXPECT_EQ(testView->GetComponent(replacement), 15);
}

TEST_F(ComponentViewTest, FreedHandlesAreRejectedBeforeTheirIdsAreReused)
{
    const auto entity = entityAllocator.Allocate();
    testView->AddComponent(entity, 10);
    testBuffer.PrepComponentBufferForFrame({});
    entityAllocator.Free(entity);

    EXPECT_TRUE(testBuffer.HasComponent(entity.Id));
    EXPECT_FALSE(testView->HasComponent(entity.Id));
    EXPECT_FALSE(testView->HasComponent(entity));

    EXPECT_FALSE(testView->TryAddComponent(entity, 5));

    EXPECT_FALSE(testView->TryRemoveComponent(entity));

    EXPECT_THROW(testView->PushComponentUpdateInstruction(entity, 5), Exceptions::KeyNotFoundException);

    EXPECT_THROW(static_cast<void>(testView->GetComponent(entity)), Exceptions::KeyNotFoundException);
    EXPECT_THROW(static_cast<void>(testView->GetComponent(entity.Id)), Exceptions::KeyNotFoundException);
}

TEST_F(ComponentViewTest, HandlesFromAnotherAllocatorAreRejected)
{
    EntityAllocator otherAllocator;
    const auto entity = otherAllocator.Allocate();
    testBuffer.PushComponentUpdateInstruction(0, entity.Id, 10);
    testBuffer.PrepComponentBufferForFrame({});

    EXPECT_TRUE(testBuffer.HasComponent(entity.Id));
    EXPECT_FALSE(testView->HasComponent(entity.Id));
    EXPECT_FALSE(testView->HasComponent(entity));

    EXPECT_FALSE(testView->TryRemoveComponent(entity));
    EXPECT_FALSE(testView->TryRemoveComponent(entity.Id));

    EXPECT_FALSE(testView->TryAddComponent(entity.Id, 5));

    EXPECT_THROW(testView->AddComponent(entity, 5), Exceptions::KeyNotFoundException);
    EXPECT_THROW(testView->AddComponent(entity.Id, 5), Exceptions::KeyNotFoundException);

    EXPECT_THROW(testView->PushComponentUpdateInstruction(entity.Id, 5), Exceptions::KeyNotFoundException);

    EXPECT_THROW(testView->RemoveComponent(entity.Id), Exceptions::KeyNotFoundException);

    EXPECT_THROW(static_cast<void>(testView->GetComponent(entity)), Exceptions::KeyNotFoundException);
    EXPECT_THROW(static_cast<void>(testView->GetComponent(entity.Id)), Exceptions::KeyNotFoundException);
    EXPECT_THROW(static_cast<void>(testView->GetComponentUnsafe(entity.Id)), Exceptions::KeyNotFoundException);

    int32_t component = 123;

    EXPECT_FALSE(testView->TryGetComponent(entity.Id, component));
    EXPECT_EQ(component, 123);
    EXPECT_EQ(testBuffer.GetComponent(entity.Id), 10);
}

TEST_F(ComponentViewTest, NumericIdsResolveTheCurrentGeneration)
{
    const auto original = entityAllocator.Allocate();
    entityAllocator.Free(original);
    const auto replacement = entityAllocator.Allocate();

    ASSERT_EQ(original.Id, replacement.Id);

    EXPECT_TRUE(testView->TryAddComponent(original.Id, 10));

    testBuffer.PrepComponentBufferForFrame({});

    EXPECT_TRUE(testView->HasComponent(original.Id));
    EXPECT_EQ(testView->GetComponent(original.Id), 10);
    EXPECT_EQ(testView->GetComponentUnsafe(original.Id), 10);
    EXPECT_FALSE(testView->TryAddComponent(original.Id, 20));

    testView->PushComponentUpdateInstruction(original.Id, 5);
    testBuffer.PrepComponentBufferForFrame({});

    EXPECT_EQ(testView->GetComponent(replacement), 15);

    int32_t component = -1;

    EXPECT_TRUE(testView->TryGetComponent(original.Id, component));
    EXPECT_EQ(component, 15);

    EXPECT_TRUE(testView->TryRemoveComponent(original.Id));

    testBuffer.PrepComponentBufferForFrame({});

    EXPECT_FALSE(testView->HasComponent(original.Id));
}

TEST(ComponentViewCatalogueTest, BothViewFactoriesUseTheCatalogueAllocator)
{
    SystemScheduler scheduler(1);
    Catalogue catalogue(0, scheduler);
    auto& cache = scheduler.GetComponentCache();
    cache.RegisterComponentType<int32_t>(-1, "HANDLE_VIEW_INT32");
    cache.RegisterComponentType<int64_t>(-1, "HANDLE_VIEW_INT64");
    const auto entity = catalogue.CreateEntity();

    auto singleView = catalogue.GetComponentView<int32_t>();
    singleView.AddComponent(entity, 10);
    auto [intView, longView] = catalogue.GetComponentViews<int32_t, int64_t>();
    intView.PushComponentUpdateInstruction(entity, 5);
    longView.AddComponent(entity, 20);
    cache.PrepAllBuffersForNextFrame({});

    EXPECT_EQ(singleView.GetComponent(entity), 15);
    EXPECT_EQ(intView.GetComponent(entity), 15);
    EXPECT_EQ(longView.GetComponent(entity), 20);

    scheduler.GetEntityAllocator().Free(entity);
    EXPECT_FALSE(singleView.HasComponent(entity));
    EXPECT_FALSE(intView.HasComponent(entity));
    EXPECT_FALSE(longView.HasComponent(entity));
}
