// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <atomic>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;
using namespace NovelRT::Timing;

class SystemSchedulerTest : public testing::Test
{
public:
    SystemScheduler* scheduler = nullptr;
    std::atomic_bool sysOneBool = true;
    std::atomic_bool sysTwoBool = true;
    std::atomic_bool sysThreeBool = true;
    std::function<void(Timestamp, Catalogue)> sysOne;
    std::function<void(Timestamp, Catalogue)> sysTwo;
    std::function<void(Timestamp, Catalogue)> sysThree;

protected:
    void SetUp() override
    {
        sysOneBool = true;
        sysTwoBool = true;
        sysThreeBool = true;

        if (scheduler == nullptr)
        {
            scheduler = new SystemScheduler();

            scheduler->SpinThreads();

            sysOne = [&](Timestamp delta, Catalogue) { sysOneBool = false; };
            sysTwo = [&](Timestamp delta, Catalogue) { sysTwoBool = false; };
            sysThree = [&](Timestamp delta, Catalogue) { sysThreeBool = false; };

            scheduler->RegisterSystem(sysOne);
            scheduler->RegisterSystem(sysTwo);
            scheduler->RegisterSystem(sysThree);
        }
    }

    void TearDown() override
    {
        if (scheduler != nullptr)
        {
            delete scheduler;
            scheduler = nullptr;
        }
    }
};

TEST_F(SystemSchedulerTest, IndependentSystemsCanRun)
{
    EXPECT_NO_THROW(scheduler->ExecuteIteration(Timestamp(0)));
}

TEST_F(SystemSchedulerTest, IndependentSystemsCanModifyValues)
{
    scheduler->ExecuteIteration(Timestamp(0));

    EXPECT_FALSE(sysOneBool);
    EXPECT_FALSE(sysTwoBool);
    EXPECT_FALSE(sysThreeBool);
}

TEST_F(SystemSchedulerTest, IndependentSystemsObtainValidCatalogue)
{
    bool isEqual = false;

    EntityId entity = Atom::getNextEntityId();
    scheduler->GetComponentCache().RegisterComponentType<int32_t>(-1);
    scheduler->GetComponentCache().GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, entity, 10);
    scheduler->ExecuteIteration(Timestamp(0));
    scheduler->RegisterSystem([&](Timestamp delta, Catalogue catalogue) {
        auto intSystem = catalogue.GetComponentView<int32_t>();
        for (auto [entity, component] : intSystem)
        {
            isEqual = component == 10;
            intSystem.PushComponentUpdateInstruction(entity, 10);
        }
    });

    scheduler->ExecuteIteration(Timestamp(0));
    ASSERT_TRUE(isEqual);
    EXPECT_EQ(scheduler->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(entity), 20);

    scheduler->ExecuteIteration(Timestamp(0));
    EXPECT_EQ(scheduler->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(entity), 30);
}

TEST_F(SystemSchedulerTest, IndependentSystemsCanHandleRemainderWithThreeThreads)
{
    TearDown();

    scheduler = new SystemScheduler(3);
    scheduler->SpinThreads();

    EntityId entity = Atom::getNextEntityId();

    scheduler->GetComponentCache().RegisterComponentType<int32_t>(-1);
    scheduler->GetComponentCache().GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, entity, 10);
    scheduler->ExecuteIteration(Timestamp(0));

    scheduler->RegisterSystem(sysOne);
    scheduler->RegisterSystem(sysTwo);
    scheduler->RegisterSystem(sysThree);
    scheduler->RegisterSystem([&](Timestamp delta, Catalogue catalogue) {
        auto intSystem = catalogue.GetComponentView<int32_t>();
        for (auto [entity, component] : intSystem)
        {
            intSystem.PushComponentUpdateInstruction(entity, 9);
        }
    });

    scheduler->ExecuteIteration(Timestamp(0));
    EXPECT_EQ(scheduler->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(entity), 19);

    scheduler->RegisterSystem([&](Timestamp delta, Catalogue catalogue) {
        auto intSystem = catalogue.GetComponentView<int32_t>();
        for (auto [entity, component] : intSystem)
        {
            intSystem.PushComponentUpdateInstruction(entity, 8);
        }
    });

    scheduler->ExecuteIteration(Timestamp(0));
    EXPECT_EQ(scheduler->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(entity), 36);

    scheduler->RegisterSystem([&](Timestamp delta, Catalogue catalogue) {
        auto intSystem = catalogue.GetComponentView<int32_t>();
        for (auto [entity, component] : intSystem)
        {
            intSystem.PushComponentUpdateInstruction(entity, 7);
        }
    });

    scheduler->ExecuteIteration(Timestamp(0));
    EXPECT_EQ(scheduler->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(entity), 60);

    scheduler->RegisterSystem([&](Timestamp delta, Catalogue catalogue) {
        auto intSystem = catalogue.GetComponentView<int32_t>();
        for (auto [entity, component] : intSystem)
        {
            intSystem.PushComponentUpdateInstruction(entity, 6);
        }
    });

    scheduler->ExecuteIteration(Timestamp(0));
    EXPECT_EQ(scheduler->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(entity), 90);
}

TEST_F(SystemSchedulerTest, IndependentSystemsCanHandleManySystems)
{
    EntityId entity = Atom::getNextEntityId();

    scheduler->GetComponentCache().RegisterComponentType<int32_t>(-1);
    scheduler->GetComponentCache().GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, entity, 10);
    scheduler->ExecuteIteration(Timestamp(0));

    for (int i = 0; i < 8; ++i) // 11 total systems
    {
        scheduler->RegisterSystem([&](Timestamp delta, Catalogue catalogue) {
            auto intSystem = catalogue.GetComponentView<int32_t>();
            for (auto [entity, component] : intSystem)
            {
                intSystem.PushComponentUpdateInstruction(entity, 1);
            }
        });
    }

    scheduler->ExecuteIteration(Timestamp(0));
    EXPECT_EQ(scheduler->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(entity), 18);

    for (int i = 0; i < 6; ++i) // 17 total systems
    {
        scheduler->RegisterSystem([&](Timestamp delta, Catalogue catalogue) {
            auto intSystem = catalogue.GetComponentView<int32_t>();
            for (auto [entity, component] : intSystem)
            {
                intSystem.PushComponentUpdateInstruction(entity, 1);
            }
        });
    }

    scheduler->ExecuteIteration(Timestamp(0));
    EXPECT_EQ(scheduler->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(entity), 32);

    for (int i = 0; i < 6; ++i) // 23 total systems
    {
        scheduler->RegisterSystem([&](Timestamp delta, Catalogue catalogue) {
            auto intSystem = catalogue.GetComponentView<int32_t>();
            for (auto [entity, component] : intSystem)
            {
                intSystem.PushComponentUpdateInstruction(entity, 1);
            }
        });
    }

    scheduler->ExecuteIteration(Timestamp(0));
    EXPECT_EQ(scheduler->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(entity), 52);

    for (int i = 0; i < 14; ++i) // 37 total systems
    {
        scheduler->RegisterSystem([&](Timestamp delta, Catalogue catalogue) {
            auto intSystem = catalogue.GetComponentView<int32_t>();
            for (auto [entity, component] : intSystem)
            {
                intSystem.PushComponentUpdateInstruction(entity, 1);
            }
        });
    }

    scheduler->ExecuteIteration(Timestamp(0));
    EXPECT_EQ(scheduler->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(entity), 86);
}
