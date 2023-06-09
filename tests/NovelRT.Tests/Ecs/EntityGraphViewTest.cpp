// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>
#include <gtest/gtest.h>

using namespace NovelRT::Ecs;

class EntityGraphViewTest : public testing::Test
{
public:
    ComponentCache componentCache = ComponentCache(1);
    EntityCache entityCache = EntityCache(1);
    Catalogue* catalogue = nullptr;
    EntityId parentId = 0;
    EntityId childId = 0;
    EntityId max = std::numeric_limits<EntityId>::max();

protected:
    void SetUp() override
    {
        static NovelRT::Core::AtomFactory& _entityIdFactory =
            NovelRT::Core::AtomFactoryDatabase::GetFactory("EntityId");

        componentCache = ComponentCache(1);
        componentCache.RegisterComponentType(LinkedEntityListNodeComponent{false}, "THROW_AWAY");
        componentCache.RegisterComponentType(EntityGraphComponent{false}, "THROW_AWAY_AGAIN");
        parentId = _entityIdFactory.GetNext();
        childId = _entityIdFactory.GetNext();
        entityCache = EntityCache(1);
        componentCache.GetComponentBuffer<EntityGraphComponent>().PushComponentUpdateInstruction(
            0, parentId, EntityGraphComponent{true, max, childId});
        componentCache.GetComponentBuffer<EntityGraphComponent>().PushComponentUpdateInstruction(
            0, childId, EntityGraphComponent{true, parentId, max});
        componentCache.GetComponentBuffer<LinkedEntityListNodeComponent>().PushComponentUpdateInstruction(
            0, childId, LinkedEntityListNodeComponent());

        componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});
        catalogue = new Catalogue(0, componentCache, entityCache);
    }

    void TearDown() override
    {
        delete catalogue;
        catalogue = nullptr;
    }
};

TEST_F(EntityGraphViewTest, CanCreateEntityGraphView)
{
    ASSERT_NO_THROW(EntityGraphView(*catalogue, parentId,
                                    catalogue->GetComponentView<EntityGraphComponent>().GetComponentUnsafe(parentId)));
}

TEST_F(EntityGraphViewTest, CanAddNewEntityAsChild)
{
    EntityId newChild = catalogue->CreateEntity();
    {
        EntityGraphView view(*catalogue, parentId,
                             catalogue->GetComponentView<EntityGraphComponent>().GetComponentUnsafe(parentId));
        ASSERT_NO_THROW(view.AddInsertChildInstruction(newChild));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);

    EntityGraphView view(*catalogue, parentId,
                         catalogue->GetComponentView<EntityGraphComponent>().GetComponentUnsafe(parentId));

    auto children = view.GetOriginalChildren();

    EXPECT_EQ(children[0].get().GetRawEntityId(), childId);
    EXPECT_EQ(children[1].get().GetRawEntityId(), newChild);
}

TEST_F(EntityGraphViewTest, CanRemoveExistingChild)
{
    {
        EntityGraphView view(*catalogue, parentId,
                             catalogue->GetComponentView<EntityGraphComponent>().GetComponentUnsafe(parentId));
        ASSERT_NO_THROW(view.AddRemoveChildInstruction(childId));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);

    EntityGraphView view(*catalogue, parentId,
                         catalogue->GetComponentView<EntityGraphComponent>().GetComponentUnsafe(parentId));

    EXPECT_FALSE(view.HasChildren());
    EXPECT_EQ(view.GetOriginalChildren().size(), 0);
}

TEST_F(EntityGraphViewTest, CanAddAndRemoveChildren)
{
    EntityId newChild = catalogue->CreateEntity();
    {
        EntityGraphView view(*catalogue, parentId,
                             catalogue->GetComponentView<EntityGraphComponent>().GetComponentUnsafe(parentId));
        ASSERT_NO_THROW(view.AddInsertChildInstruction(newChild));
        ASSERT_NO_THROW(view.AddRemoveChildInstruction(childId));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);

    EntityGraphView view(*catalogue, parentId,
                         catalogue->GetComponentView<EntityGraphComponent>().GetComponentUnsafe(parentId));

    auto children = view.GetOriginalChildren();

    EXPECT_EQ(children[0].get().GetRawEntityId(), newChild);
}

TEST_F(EntityGraphViewTest, CanRemoveAndAddChildren)
{
    EntityId newChild = catalogue->CreateEntity();
    {
        EntityGraphView view(*catalogue, parentId,
                             catalogue->GetComponentView<EntityGraphComponent>().GetComponentUnsafe(parentId));
        ASSERT_NO_THROW(view.AddRemoveChildInstruction(childId));
        ASSERT_NO_THROW(view.AddInsertChildInstruction(newChild));
    }

    componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    delete catalogue;
    catalogue = new Catalogue(0, componentCache, entityCache);

    EntityGraphView view(*catalogue, parentId,
                         catalogue->GetComponentView<EntityGraphComponent>().GetComponentUnsafe(parentId));

    auto children = view.GetOriginalChildren();

    EXPECT_EQ(children[0].get().GetRawEntityId(), newChild);
}
