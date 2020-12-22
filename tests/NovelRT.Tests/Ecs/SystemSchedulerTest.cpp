// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <atomic>

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
    std::function<void(Timestamp)> sysOne;
    std::function<void(Timestamp)> sysTwo;
    std::function<void(Timestamp)> sysThree;
    
    protected:
    void SetUp() override
    {
        //Catalogue catalogue()
        //catalogue.CreateEntity().TryAddComponent<int>();
        sysOneBool = true;
        sysTwoBool = true;
        sysThreeBool = true;

        if (scheduler == nullptr)
        {
            delete scheduler;
            scheduler = new SystemScheduler();
        

            scheduler->SpinThreads();

            sysOne = [&](Timestamp delta) {sysOneBool = false; std::cout << "SYSTEM ONE LOG: HELLO" << std::endl;};
            sysTwo = [&](Timestamp delta) {sysTwoBool = false;std::cout << "SYSTEM TWO LOG: HELLO" << std::endl;};
            sysThree = [&](Timestamp delta) {sysThreeBool = false;std::cout << "SYSTEM THREE LOG: HELLO" << std::endl;};

            scheduler->RegisterSystemForComponent<int>(sysOne, [](){});
            scheduler->RegisterSystemForComponent<bool>(sysTwo, [](){});
            scheduler->RegisterSystemForComponent<char>(sysThree, [](){});
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
//
//class TestSystem : public BaseSystem<size_t>
//{
//    protected:
//    void UpdateComponents(Timing::Timestamp deltaTime, SparseSet<EntityId, size_t>& componentData) override
//    {
//        hasRun = true;
//
//        for (auto && [i, j] : componentData)
//        {
//            j = 10;
//        }
//    }
//
//    public:
//    std::atomic_bool hasRun = false;
//};
//
//TEST_F(SystemSchedulerTest, IndependentSystemsCanRun)
//{
//    EXPECT_NO_THROW(scheduler->ExecuteIteration(Timestamp(0)));
//}
//
//TEST_F(SystemSchedulerTest, IndependentSystemsCanModifyValues)
//{
//    scheduler->ExecuteIteration(Timestamp(0));
//    
//    EXPECT_FALSE(sysOneBool);
//    EXPECT_FALSE(sysTwoBool);
//    EXPECT_FALSE(sysThreeBool);
//}
//
//TEST_F(SystemSchedulerTest, CreateSystemForComponentDoesNotThrow)
//{
//    EXPECT_NO_THROW((scheduler->CreateSystemForComponent<TestSystem, size_t>()));
//}
//
//TEST_F(SystemSchedulerTest, CreateSystemForComponentRegistersSystemCorrectly)
//{
//    std::shared_ptr<TestSystem> system = nullptr;
//    ASSERT_NO_THROW((system = scheduler->CreateSystemForComponent<TestSystem, size_t>()));
//    ASSERT_NO_THROW(scheduler->ExecuteIteration(Timestamp(0)));
//
//    EXPECT_EQ(system->hasRun, true);
//}
//
//TEST_F(SystemSchedulerTest, CreateSystemForComponentPropagatesChangesToImmutableViewCorrectly)
//{
//    EntityId entity = 0;
//    std::shared_ptr<TestSystem> system = nullptr;
//    ASSERT_NO_THROW((system = scheduler->CreateSystemForComponent<TestSystem, size_t>()));
//    ASSERT_NO_THROW(system->AddComponent(5, entity));
//    ASSERT_NO_THROW(scheduler->ExecuteIteration(Timestamp(0)));
//    ASSERT_EQ(system->GetComponent(entity), 5);
//    ASSERT_NO_THROW(scheduler->ExecuteIteration(Timestamp(0)));
//
//    EXPECT_EQ(system->GetComponent(entity), 10);
//}
//
//TEST_F(SystemSchedulerTest, HasComponentInBaseSystemReturnsFalseWhenNotProcessedByIteration)
//{
//    EntityId entity = 0;
//    std::shared_ptr<TestSystem> system = nullptr;
//    ASSERT_NO_THROW((system = scheduler->CreateSystemForComponent<TestSystem, size_t>()));
//    ASSERT_NO_THROW(system->AddComponent(5, entity));
//    ASSERT_FALSE(system->hasRun);
//    EXPECT_FALSE(system->HasComponent(entity));
//}
//
//TEST_F(SystemSchedulerTest, HasComponentInBaseSystemReturnsTrueWhenProcessedByIteration)
//{
//    EntityId entity = 0;
//    std::shared_ptr<TestSystem> system = nullptr;
//    ASSERT_NO_THROW((system = scheduler->CreateSystemForComponent<TestSystem, size_t>()));
//    ASSERT_NO_THROW(system->AddComponent(5, entity));
//    ASSERT_NO_THROW(scheduler->ExecuteIteration(Timestamp(0)));
//    ASSERT_TRUE(system->hasRun);
//    EXPECT_TRUE(system->HasComponent(entity));
//}