// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Timing;

TEST(ConfiguratorTest, ConfiguratorCanProduceBasicSystemScheduler)
{
    auto scheduler = Configurator().InitialiseAndRegisterComponents();
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
}

// TODO: This test can't be used until we have null/dummy plugins.
/*
TEST(ConfiguratorTest, ConfiguratorCanProduceSystemSchedulerWithDefaultSystems)
{
    auto scheduler = Configurator().WithDefaultSystemsAndComponents().InitialiseAndRegisterComponents();
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
}
 */

TEST(ConfiguratorTest, ConfiguratorCanProduceSystemSchedulerWithCustomComponentAndFunctionSystem)
{
    auto lambda = [](Timestamp, Catalogue catalogue) {
        auto intComponents = catalogue.GetComponentView<int32_t>();
        for (auto [entity, component] : intComponents)
        {
            intComponents.PushComponentUpdateInstruction(entity, 10);
        }
    };

    auto scheduler = Configurator().WithSystems({lambda}).InitialiseAndRegisterComponents<int32_t>(
        std::make_tuple(-1, "THROW_AWAY"));
    scheduler.GetComponentCache().GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 1, 10);
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
    EXPECT_EQ(scheduler.GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(1), 20);
}

TEST(ConfiguratorTest, ConfiguratorCanProduceSystemSchedulerWithCustomComponentAndIEcsSystem)
{
    class TestSystem : public IEcsSystem
    {
    public:
        void Update(NovelRT::Timing::Timestamp, Catalogue catalogue) final
        {
            auto intComponents = catalogue.GetComponentView<int32_t>();
            for (auto [entity, component] : intComponents)
            {
                intComponents.PushComponentUpdateInstruction(entity, 10);
            }
        }
    };

    auto tester = std::make_shared<TestSystem>();

    auto scheduler = Configurator().WithSystems({tester}).InitialiseAndRegisterComponents<int32_t>(
        std::make_tuple(-1, "THROW_AWAY"));
    scheduler.GetComponentCache().GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 1, 10);
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
    EXPECT_EQ(scheduler.GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(1), 20);
}

// TODO: This test can't be used until we have null/dummy plugins.
/*
TEST(ConfiguratorTest, ConfiguratorCanHandleBothCustomAndDefaultSystemsAndComponents)
{
    auto lambda = [](Timestamp delta, Catalogue catalogue) {
        auto intComponents = catalogue.GetComponentView<int32_t>();
        for (auto [entity, component] : intComponents)
        {
            intComponents.PushComponentUpdateInstruction(entity, 10);
        }
    };

    auto scheduler =
        Configurator().WithSystems({lambda}).WithDefaultSystemsAndComponents().InitialiseAndRegisterComponents<int32_t>(
            -1);
    scheduler.GetComponentCache().GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 1, 10);
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
    EXPECT_EQ(scheduler.GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(1), 20);
}
 */

TEST(ConfiguratorTest, CanSetWorkerThreadCountWithoutFailing)
{
    auto scheduler = Configurator().WithThreadCount(5).InitialiseAndRegisterComponents();
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
}
