// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <atomic>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;

class CatalogueTest : public testing::Test
{
public:
    ComponentCache componentCache = ComponentCache(1);
    EntityCache entityCache = EntityCache(1);
    Catalogue* catalogue = nullptr;

protected:
    void SetUp() override
    {
        componentCache = ComponentCache(1);
        entityCache = EntityCache(1);
        componentCache.RegisterComponentType<int32_t>(-1);
        componentCache.RegisterComponentType<size_t>(-1);
        componentCache.RegisterComponentType<char>('e');

        componentCache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 0, 10);
        componentCache.GetComponentBuffer<size_t>().PushComponentUpdateInstruction(0, 0, 100);
        componentCache.GetComponentBuffer<char>().PushComponentUpdateInstruction(0, 0, 'a');

        componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});
        catalogue = new Catalogue(0, componentCache, entityCache);
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
    catalogue->DeleteEntity(0);
    entityCache.ProcessEntityDeletionRequestsFromThreads();
    componentCache.PrepAllBuffersForNextFrame(entityCache.GetEntitiesToRemoveThisFrame());
    EXPECT_EQ(catalogue->GetComponentView<int32_t>().GetImmutableDataLength(), 0);
    EXPECT_EQ(catalogue->GetComponentView<char>().GetImmutableDataLength(), 0);
    EXPECT_EQ(catalogue->GetComponentView<size_t>().GetImmutableDataLength(), 0);
}

TEST_F(CatalogueTest, CanHandleEntityDeletionInSameFrame)
{
    EntityId id = catalogue->CreateEntity();
    catalogue->DeleteEntity(id);
    entityCache.ProcessEntityDeletionRequestsFromThreads();
    componentCache.PrepAllBuffersForNextFrame(entityCache.GetEntitiesToRemoveThisFrame());
    EXPECT_EQ(catalogue->GetComponentView<int32_t>().GetImmutableDataLength(), 1);
    EXPECT_EQ(catalogue->GetComponentView<char>().GetImmutableDataLength(), 1);
    EXPECT_EQ(catalogue->GetComponentView<size_t>().GetImmutableDataLength(), 1);
}
