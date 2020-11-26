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
    bool sysOneBool;
    bool sysTwoBool;
    bool sysThreeBool;
    std::function<void(Timestamp)> sysOne;
    std::function<void(Timestamp)> sysTwo;
    std::function<void(Timestamp)> sysThree;
    
    protected:
    void SetUp() override
    {
        if (scheduler != nullptr)
        {
            delete scheduler;
        }
        
        scheduler = new SystemScheduler();
        scheduler->SpinThreads();

        sysOne = [&](Timestamp delta) {sysOneBool = true;};
        sysTwo = [&](Timestamp delta) {sysTwoBool = true;};
        sysThree = [&](Timestamp delta) {sysThreeBool = true;};

        scheduler->RegisterSystemForComponent<int>(sysOne);
        scheduler->RegisterSystemForComponent<bool>(sysTwo);
        scheduler->RegisterSystemForComponent<char>(sysThree);
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

TEST_F(SystemSchedulerTest, RunsAllIndependentSystems)
{
    scheduler->ExecuteIteration(Timestamp(0));

    EXPECT_EQ(sysOneBool, true);
    EXPECT_EQ(sysTwoBool, true);
    EXPECT_EQ(sysThreeBool, true);
}