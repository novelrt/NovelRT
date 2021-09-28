// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Timing;

TEST(ConfiguratorTest, ConfiguratorCanProduceBasicSystemScheduler)
{
    auto scheduler = Configurator().InitialiseAndRegisterComponents();
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
}

TEST(ConfiguratorTest, ConfiguratorCanProduceSystemSchedulerWithDefaultSystems)
{
    auto scheduler = Configurator().WithDefaultSystemsAndComponents().InitialiseAndRegisterComponents();
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
}

TEST(ConfiguratorTest, ConfiguratorCanProduceSystemSchedulerWithCustomComponentAndSystem)
{
    auto lambda = [](Timestamp delta, Catalogue catalogue)
    {
        auto intComponents = catalogue.GetComponentView<int32_t>();
        for (auto [entity, component] : intComponents)
        {
            intComponents.PushComponentUpdateInstruction(entity, 10);
        }
    };

    auto scheduler = Configurator().WithSystems({lambda}).InitialiseAndRegisterComponents<int32_t>(-1);
    scheduler.GetComponentCache().GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(1, 1, 10);
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
    EXPECT_EQ(scheduler.GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(1), 20);
}

TEST(ConfiguratorTest, ConfiguratorCanHandleBothCustomAndDefaultSystemsAndComponents)
{
    auto lambda = [](Timestamp delta, Catalogue catalogue)
    {
      auto intComponents = catalogue.GetComponentView<int32_t>();
      for (auto [entity, component] : intComponents)
      {
          intComponents.PushComponentUpdateInstruction(entity, 10);
      }
    };

    auto scheduler = Configurator().WithSystems({lambda}).WithDefaultSystemsAndComponents().InitialiseAndRegisterComponents<int32_t>(-1);
    scheduler.GetComponentCache().GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(1, 1, 10);
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
    EXPECT_EQ(scheduler.GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(1), 20);
}

TEST(ConfiguratorTest, CanSetWorkerThreadCountWithoutFailing)
{
    auto scheduler = Configurator().WithThreadCount(5).InitialiseAndRegisterComponents();
    ASSERT_NO_THROW(scheduler.ExecuteIteration(Timestamp(0)));
}
