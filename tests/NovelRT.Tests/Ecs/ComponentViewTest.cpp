
// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <atomic>

using namespace NovelRT;
using namespace NovelRT::Ecs;

class ComponentViewTest : public testing::Test
{
    public:
    ComponentView<int32_t>* testView = nullptr;
    ComponentBuffer<int32_t> testBuffer = ComponentBuffer<int32_t>(1, -1);

    protected:
    void SetUp() override
    {
        testBuffer = ComponentBuffer<int32_t>(1, -1);
        testView = new ComponentView<int32_t>(0, testBuffer);
    }

    void TearDown() override
    {
        delete testView;
        testView = nullptr;
    }
};

TEST_F(ComponentViewTest, CanReadImmutableDataSetCorrectly)
{
    testBuffer.PushComponentUpdateInstruction(0, 0, 10);
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});

    for (auto [entity, component] : *testView)
    {
        EXPECT_EQ(component, 10);
    }
}

TEST_F(ComponentViewTest, CanPushComponentUpdateInstructionCorrectly)
{
    testBuffer.PushComponentUpdateInstruction(0, 0, 10);
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});
    testView->PushComponentUpdateInstruction(0, 10);
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});

    EXPECT_EQ(testView->GetComponent(0), 20);
}

TEST_F(ComponentViewTest, AddComponentAddsNewComponentCorrectly)
{
    testView->AddComponent(0, 30);
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});
    EXPECT_EQ(testView->GetComponent(0), 30);
}

TEST_F(ComponentViewTest, RemoveComponentRemovesComponentCorrectly)
{
    testView->RemoveComponent(0);
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});
    EXPECT_EQ(testView->GetImmutableDataLength(), 0);
}

TEST_F(ComponentViewTest, TryAddComponentAddsComponentIfEntityDoesNotHaveExistingComponent)
{
    ASSERT_TRUE(testView->TryAddComponent(0, 20));
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});
    EXPECT_EQ(testView->GetComponent(0), 20);
}

TEST_F(ComponentViewTest, TryAddComponentDoesNotAddComponentIfEntityDoesHaveExistingComponentBetweenFrames)
{
    ASSERT_TRUE(testView->TryAddComponent(0, 10));
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});
    ASSERT_FALSE(testView->TryAddComponent(0, 20));
    testBuffer.PrepComponentBufferForFrame(std::vector<EntityId>{});
    EXPECT_EQ(testView->GetComponent(0), 10);
}