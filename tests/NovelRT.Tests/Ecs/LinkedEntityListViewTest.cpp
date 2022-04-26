// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>
#include <gtest/gtest.h>

using namespace NovelRT::Ecs;

class LinkedEntityListViewTest : public testing::Test
{
public:
    ComponentCache componentCache = ComponentCache(1);
    EntityCache entityCache = EntityCache(1);
    Catalogue* catalogue = nullptr;
    EntityId rootListId = 0;
    EntityId max = std::numeric_limits<EntityId>::max();

protected:
    void SetUp() override
    {
        static NovelRT::AtomFactory& _entityIdFactory = NovelRT::AtomFactoryDatabase::GetFactory("EntityId");

        componentCache = ComponentCache(1);
        componentCache.RegisterComponentType(LinkedEntityListNodeComponent{false}, "THROW_AWAY");
        rootListId = _entityIdFactory.GetNext();
        componentCache.GetComponentBuffer<LinkedEntityListNodeComponent>().PushComponentUpdateInstruction(
            0, rootListId, LinkedEntityListNodeComponent());
        entityCache = EntityCache(1);

        componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});
        catalogue = new Catalogue(0, componentCache, entityCache);
    }

    void TearDown() override
    {
        delete catalogue;
        catalogue = nullptr;
    }
};

TEST_F(LinkedEntityListViewTest, CanCreateInstance)
{
    EXPECT_NO_THROW(LinkedEntityListView(rootListId, *catalogue));
}

TEST_F(LinkedEntityListViewTest, CanAddNodeUsingAddInsertAtBackInstruction)
{
    EntityId nextId = catalogue->CreateEntity();
    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);
        ASSERT_NO_THROW(view.AddInsertAtBackInstruction(nextId));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    EXPECT_EQ(2, view.GetImmutableDataLength());
    EXPECT_EQ(view.GetComponent(rootListId).previous, max);
    EXPECT_EQ(view.GetComponent(rootListId).next, nextId);
    EXPECT_EQ(view.GetComponent(nextId).previous, rootListId);
    EXPECT_EQ(view.GetComponent(nextId).next, max);
}

TEST_F(LinkedEntityListViewTest, CanAddNodeUsingAddInsertAtFrontInstruction)
{
    EntityId newPreviousId = catalogue->CreateEntity();
    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);
        ASSERT_NO_THROW(view.AddInsertAtFrontInstruction(newPreviousId));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    EXPECT_EQ(2, view.GetImmutableDataLength());
    EXPECT_EQ(view.GetComponent(rootListId).previous, newPreviousId);
    EXPECT_EQ(view.GetComponent(rootListId).next, max);
    EXPECT_EQ(view.GetComponent(newPreviousId).previous, max);
    EXPECT_EQ(view.GetComponent(newPreviousId).next, rootListId);
}

TEST_F(LinkedEntityListViewTest, CanAddNodeUsingAddInsertBeforeIndexInstruction)
{
    EntityId newPreviousId = catalogue->CreateEntity();
    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);
        ASSERT_NO_THROW(view.AddInsertBeforeIndexInstruction(0, newPreviousId));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    EXPECT_EQ(2, view.GetImmutableDataLength());
    EXPECT_EQ(view.GetComponent(rootListId).previous, newPreviousId);
    EXPECT_EQ(view.GetComponent(rootListId).next, max);
    EXPECT_EQ(view.GetComponent(newPreviousId).previous, max);
    EXPECT_EQ(view.GetComponent(newPreviousId).next, rootListId);
}

TEST_F(LinkedEntityListViewTest, CanAddNodeUsingAddInsertAfterIndexInstruction)
{
    EntityId nextId = catalogue->CreateEntity();
    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);
        ASSERT_NO_THROW(view.AddInsertAfterIndexInstruction(0, nextId));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    EXPECT_EQ(2, view.GetImmutableDataLength());
    EXPECT_EQ(view.GetComponent(rootListId).previous, max);
    EXPECT_EQ(view.GetComponent(rootListId).next, nextId);
    EXPECT_EQ(view.GetComponent(nextId).previous, rootListId);
    EXPECT_EQ(view.GetComponent(nextId).next, max);
}

TEST_F(LinkedEntityListViewTest, CanRemoveNodeUsingNodeId)
{
    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);
        ASSERT_NO_THROW(view.AddRemoveNodeInstruction(rootListId));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    EXPECT_EQ(0, view.GetImmutableDataLength());
}

TEST_F(LinkedEntityListViewTest, CanAddAndRemoveInSameCommitUsingInsertBeforeIndex)
{
    EntityId previousId = catalogue->CreateEntity();
    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);
        ASSERT_NO_THROW(view.AddInsertBeforeIndexInstruction(0, previousId));
        ASSERT_NO_THROW(view.AddRemoveNodeInstruction(rootListId));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    EXPECT_EQ(1, view.GetImmutableDataLength());
    EXPECT_EQ(view.GetComponent(previousId).previous, max);
    EXPECT_EQ(view.GetComponent(previousId).next, max);
}

TEST_F(LinkedEntityListViewTest, CanRemoveAndAddInSameCommitUsingInsertBeforeIndex)
{
    EntityId previousId = catalogue->CreateEntity();
    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);
        ASSERT_NO_THROW(view.AddRemoveNodeInstruction(rootListId));
        ASSERT_NO_THROW(view.AddInsertBeforeIndexInstruction(0, previousId));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    EXPECT_EQ(1, view.GetImmutableDataLength());
    EXPECT_EQ(view.GetComponent(previousId).previous, max);
    EXPECT_EQ(view.GetComponent(previousId).next, max);
}

TEST_F(LinkedEntityListViewTest, CanAddAndRemoveInSameCommitUsingInsertAfterIndex)
{
    EntityId nextId = catalogue->CreateEntity();
    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);
        ASSERT_NO_THROW(view.AddInsertAfterIndexInstruction(0, nextId));
        ASSERT_NO_THROW(view.AddRemoveNodeInstruction(rootListId));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    EXPECT_EQ(1, view.GetImmutableDataLength());
    EXPECT_EQ(view.GetComponent(nextId).previous, max);
    EXPECT_EQ(view.GetComponent(nextId).next, max);
}

TEST_F(LinkedEntityListViewTest, CanRemoveAndAddInSameCommitUsingInsertAfterIndex)
{
    EntityId nextId = catalogue->CreateEntity();
    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);
        ASSERT_NO_THROW(view.AddRemoveNodeInstruction(rootListId));
        ASSERT_NO_THROW(view.AddInsertAfterIndexInstruction(0, nextId));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    EXPECT_EQ(1, view.GetImmutableDataLength());
    EXPECT_EQ(view.GetComponent(nextId).previous, max);
    EXPECT_EQ(view.GetComponent(nextId).next, max);
}

TEST_F(LinkedEntityListViewTest, CanAddAndRemoveInSameCommitUsingInsertAtBack)
{
    EntityId nextId = catalogue->CreateEntity();
    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);
        ASSERT_NO_THROW(view.AddInsertAtBackInstruction(nextId));
        ASSERT_NO_THROW(view.AddRemoveNodeInstruction(rootListId));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    EXPECT_EQ(1, view.GetImmutableDataLength());
    EXPECT_EQ(view.GetComponent(nextId).previous, max);
    EXPECT_EQ(view.GetComponent(nextId).next, max);
}

TEST_F(LinkedEntityListViewTest, CanRemoveAndAddInSameCommitUsingInsertAtBack)
{
    EntityId nextId = catalogue->CreateEntity();
    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);
        ASSERT_NO_THROW(view.AddRemoveNodeInstruction(rootListId));
        ASSERT_NO_THROW(view.AddInsertAtBackInstruction(nextId));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    EXPECT_EQ(1, view.GetImmutableDataLength());
    EXPECT_EQ(view.GetComponent(nextId).previous, max);
    EXPECT_EQ(view.GetComponent(nextId).next, max);
}

TEST_F(LinkedEntityListViewTest, CanAddAndRemoveInSameCommitUsingInsertAtFront)
{
    EntityId previousId = catalogue->CreateEntity();
    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);
        ASSERT_NO_THROW(view.AddInsertAtFrontInstruction(previousId));
        ASSERT_NO_THROW(view.AddRemoveNodeInstruction(rootListId));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    EXPECT_EQ(1, view.GetImmutableDataLength());
    EXPECT_EQ(view.GetComponent(previousId).previous, max);
    EXPECT_EQ(view.GetComponent(previousId).next, max);
}

TEST_F(LinkedEntityListViewTest, CanRemoveAndAddInSameCommitUsingInsertAtFront)
{
    EntityId previousId = catalogue->CreateEntity();
    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);
        ASSERT_NO_THROW(view.AddRemoveNodeInstruction(rootListId));
        ASSERT_NO_THROW(view.AddInsertAtFrontInstruction(previousId));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    EXPECT_EQ(1, view.GetImmutableDataLength());
    EXPECT_EQ(view.GetComponent(previousId).previous, max);
    EXPECT_EQ(view.GetComponent(previousId).next, max);
}

TEST_F(LinkedEntityListViewTest, CanAddMultipleItemsAtTheBack)
{
    std::vector<EntityId> committedEntities{};

    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);

        for (size_t i = 0; i < 10; i++)
        {
            EntityId id = catalogue->CreateEntity();
            ASSERT_NO_THROW(view.AddInsertAtBackInstruction(id));
            committedEntities.emplace_back(id);
        }
    }

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    auto [firstEntity, firstComponent] = *view.begin();
    LinkedEntityListView readList(firstEntity, *catalogue);
    auto firstNode = readList[0];
    auto rootListComponent = view.GetComponent(firstNode);

    EntityId previous = rootListComponent.previous;

    for (auto&& node : readList)
    {

        auto component = view.GetComponentUnsafe(node);

        if (node != firstNode)
        {
            EXPECT_EQ(node, previous);
        }

        previous = component.next;
    }
}

TEST_F(LinkedEntityListViewTest, CanAddMultipleItemsAtTheFront)
{
    std::vector<EntityId> committedEntities{};

    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);

        for (size_t i = 0; i < 10; i++)
        {
            EntityId id = catalogue->CreateEntity();
            ASSERT_NO_THROW(view.AddInsertAtFrontInstruction(id));
            committedEntities.emplace_back(id);
        }
    }

    std::reverse(committedEntities.begin(), committedEntities.end());

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    auto [firstEntity, firstComponent] = *view.begin();
    LinkedEntityListView readList(firstEntity, *catalogue);
    auto firstNode = readList[0];
    auto rootListComponent = view.GetComponent(firstNode);

    EntityId previous = rootListComponent.previous;

    for (auto&& node : readList)
    {

        auto component = view.GetComponentUnsafe(node);

        if (node != firstNode)
        {
            EXPECT_EQ(node, previous);
        }

        previous = component.next;
    }
}

TEST_F(LinkedEntityListViewTest, CanAddMultipleItemsAtFrontAndRemoveEntities)
{
    std::vector<EntityId> committedEntities{};

    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);

        for (size_t i = 0; i < 10; i++)
        {
            EntityId id = catalogue->CreateEntity();
            ASSERT_NO_THROW(view.AddInsertAtFrontInstruction(id));
            committedEntities.emplace_back(id);
        }

        view.AddRemoveNodeInstruction(rootListId);
        view.AddRemoveNodeInstruction(committedEntities[2]);
        static_cast<void>(std::remove(committedEntities.begin(), committedEntities.end(), committedEntities[2]));
    }

    std::reverse(committedEntities.begin(), committedEntities.end());

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    auto [firstEntity, firstComponent] = *view.begin();
    LinkedEntityListView readList(firstEntity, *catalogue);
    auto firstNode = readList[0];
    auto rootListComponent = view.GetComponent(firstNode);

    EntityId previous = rootListComponent.previous;

    for (auto&& node : readList)
    {

        auto component = view.GetComponentUnsafe(node);

        if (node != firstNode)
        {
            EXPECT_EQ(node, previous);
        }

        previous = component.next;
    }
}

TEST_F(LinkedEntityListViewTest, CanAddMultipleItemsAtBackAndRemoveEntities)
{
    std::vector<EntityId> committedEntities{};

    // scope for auto commit/delete.
    {
        LinkedEntityListView view(rootListId, *catalogue);

        for (size_t i = 0; i < 10; i++)
        {
            EntityId id = catalogue->CreateEntity();
            ASSERT_NO_THROW(view.AddInsertAtBackInstruction(id));
            committedEntities.emplace_back(id);
        }

        view.AddRemoveNodeInstruction(rootListId);
        view.AddRemoveNodeInstruction(committedEntities[2]);
        static_cast<void>(std::remove(committedEntities.begin(), committedEntities.end(), committedEntities[2]));
    }

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);
    auto view = catalogue->GetComponentView<LinkedEntityListNodeComponent>();

    auto [firstEntity, firstComponent] = *view.begin();
    LinkedEntityListView readList(firstEntity, *catalogue);
    auto firstNode = readList[0];
    auto rootListComponent = view.GetComponent(firstNode);

    EntityId previous = rootListComponent.previous;

    for (auto&& node : readList)
    {

        auto component = view.GetComponentUnsafe(node);

        if (node != firstNode)
        {
            EXPECT_EQ(node, previous);
        }

        previous = component.next;
    }
}
