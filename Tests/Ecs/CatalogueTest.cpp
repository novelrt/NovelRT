// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentCache.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EntityAllocator.hpp>
#include <NovelRT/Ecs/EntityCache.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>
#include <NovelRT/Ecs/SystemScheduler.hpp>
#include <gtest/gtest.h>
#include <limits>
#include <ranges>

using namespace NovelRT;
using namespace NovelRT::Ecs;

class CatalogueTest : public testing::Test
{
public:
    SystemScheduler systemScheduler;
    EntityCache& entityCache = systemScheduler.GetEntityCache();
    ComponentCache& componentCache = systemScheduler.GetComponentCache();
    EntityAllocator& entityAllocator = systemScheduler.GetEntityAllocator();
    Catalogue* catalogue = nullptr;
    EntityId createdEntity = 0ULL;

protected:
    void SetUp() override
    {
        componentCache.RegisterComponentType<int32_t>(-1, "THROW_AWAY");
        componentCache.RegisterComponentType<size_t>(std::numeric_limits<size_t>::max(), "THROW_AWAY_AGAIN");
        componentCache.RegisterComponentType<char>('e', "THROW_AWAY_AGAIN_AGAIN");

        createdEntity = systemScheduler.GetEntityAllocator().Allocate().Id;

        componentCache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, createdEntity, 10);
        componentCache.GetComponentBuffer<size_t>().PushComponentUpdateInstruction(0, createdEntity, 100);
        componentCache.GetComponentBuffer<char>().PushComponentUpdateInstruction(0, createdEntity, 'a');

        componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});
        catalogue = new Catalogue(0, systemScheduler);
    }

    void TearDown() override
    {
        delete catalogue;
        catalogue = nullptr;
    }
};

TEST_F(CatalogueTest, CanGetValidComponentView)
{
    auto charBuffer = catalogue->GetComponentView<char>();

    for (auto [entity, charComponent] : charBuffer)
    {
        EXPECT_EQ(charComponent, 'a');
    }
}

TEST_F(CatalogueTest, CanGetValidComponentViewCollectionTuple)
{
    auto [charBuffer, intBuffer, sizeTBuffer] = catalogue->GetComponentViews<char, int32_t, size_t>();

    for (auto [entity, charComponent] : charBuffer)
    {
        EXPECT_EQ(charComponent, 'a');
    }

    for (auto [entity, intComponent] : intBuffer)
    {
        EXPECT_EQ(intComponent, 10);
    }

    for (auto [entity, sizeTComponent] : sizeTBuffer)
    {
        EXPECT_EQ(sizeTComponent, 100);
    }
}

TEST_F(CatalogueTest, CanRemoveComponentFromEntityBasedOnView)
{
    auto buffer = catalogue->GetComponentView<int32_t>();

    for (auto [entity, component] : buffer)
    {
        buffer.RemoveComponent(entity);
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});
    EXPECT_EQ(buffer.GetImmutableDataLength(), 0);
}

TEST_F(CatalogueTest, CanHandleEntityDeletionBetweenFrames)
{
    catalogue->DeleteEntity(createdEntity);
    entityCache.ProcessEntityDeletionRequestsFromThreads();

    const auto& handles = entityCache.GetEntitiesToRemoveThisFrame();

    std::vector<EntityId> idsToDelete{};
    idsToDelete.reserve(handles.size());

    auto validHandles =
        handles | std::views::filter([&](const EntityHandle& handle) { return entityAllocator.IsValid(handle); });

    std::ranges::transform(validHandles, std::back_inserter(idsToDelete), &EntityHandle::Id);

    componentCache.PrepAllBuffersForNextFrame(idsToDelete);

    EXPECT_EQ(catalogue->GetComponentView<int32_t>().GetImmutableDataLength(), 0);
    EXPECT_EQ(catalogue->GetComponentView<char>().GetImmutableDataLength(), 0);
    EXPECT_EQ(catalogue->GetComponentView<size_t>().GetImmutableDataLength(), 0);
}

TEST_F(CatalogueTest, CanHandleEntityDeletionInSameFrame)
{
    EntityId id = catalogue->CreateEntity().Id;
    catalogue->DeleteEntity(id);
    entityCache.ProcessEntityDeletionRequestsFromThreads();

    const auto& handles = entityCache.GetEntitiesToRemoveThisFrame();

    std::vector<EntityId> idsToDelete{};
    idsToDelete.reserve(handles.size());

    auto validHandles =
        handles | std::views::filter([&](const EntityHandle& handle) { return entityAllocator.IsValid(handle); });

    std::ranges::transform(validHandles, std::back_inserter(idsToDelete), &EntityHandle::Id);

    componentCache.PrepAllBuffersForNextFrame(idsToDelete);
    EXPECT_EQ(catalogue->GetComponentView<int32_t>().GetImmutableDataLength(), 1);
    EXPECT_EQ(catalogue->GetComponentView<char>().GetImmutableDataLength(), 1);
    EXPECT_EQ(catalogue->GetComponentView<size_t>().GetImmutableDataLength(), 1);
}
