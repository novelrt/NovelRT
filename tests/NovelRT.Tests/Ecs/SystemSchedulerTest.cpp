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
    EntityCache* entityCache = nullptr;
    ComponentCache* componentCache = nullptr;
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

            sysOne = [&](Timestamp delta, Catalogue catalogue) {
                sysOneBool = false;
                std::cout << "SYSTEM ONE LOG: HELLO" << std::endl;
            };
            sysTwo = [&](Timestamp delta, Catalogue catalogue) {
                sysTwoBool = false;
                std::cout << "SYSTEM TWO LOG: HELLO" << std::endl;
            };
            sysThree = [&](Timestamp delta, Catalogue catalogue) {
                sysThreeBool = false;
                std::cout << "SYSTEM THREE LOG: HELLO" << std::endl;
            };

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

    scheduler->ExecuteIteration(Timestamp(0));
    EXPECT_EQ(scheduler->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(entity), 20);
}