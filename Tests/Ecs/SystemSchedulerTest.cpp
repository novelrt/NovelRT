// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include "gtest/gtest.h"
#include <NovelRT/Utilities/Macros.hpp>
#include <NovelRT/Ecs/SystemScheduler.hpp>
#include <NovelRT/Ecs/ComponentBufferMemoryContainer.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>
#include <NovelRT/Timing/Timestamp.hpp>
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
    inline static NovelRT::AtomFactory& entityIdFactory = NovelRT::AtomFactoryDatabase::GetFactory("EntityId");

protected:
    virtual uint32_t ThreadsToSpin() const { return 0; }

    void SetUp() override
    {
        sysOneBool = true;
        sysTwoBool = true;
        sysThreeBool = true;

        if (scheduler == nullptr)
        {
            scheduler = new SystemScheduler(ThreadsToSpin());

            sysOne = [&](Timestamp, Catalogue) { sysOneBool = false; };
            sysTwo = [&](Timestamp, Catalogue) { sysTwoBool = false; };
            sysThree = [&](Timestamp, Catalogue) { sysThreeBool = false; };

            unused(scheduler->RegisterSystem(sysOne));
            unused(scheduler->RegisterSystem(sysTwo));
            unused(scheduler->RegisterSystem(sysThree));
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
    EXPECT_NO_THROW(scheduler->ExecuteIteration(Timestamp()));
}

TEST_F(SystemSchedulerTest, IndependentSystemsCanModifyValues)
{
    scheduler->ExecuteIteration(Timestamp());

    EXPECT_FALSE(sysOneBool);
    EXPECT_FALSE(sysTwoBool);
    EXPECT_FALSE(sysThreeBool);
}

TEST_F(SystemSchedulerTest, IndependentSystemsObtainValidCatalogue)
{
    bool isEqual = false;

    EntityId entity = entityIdFactory.GetNext();
    scheduler->GetComponentCache().RegisterComponentType<int32_t>(-1, "THROW_AWAY");
    scheduler->GetComponentCache().GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, entity, 10);
    unused(scheduler->RegisterSystem([&](Timestamp, Catalogue catalogue) {
        auto intSystem = catalogue.GetComponentView<int32_t>();
        for (auto [entity, component] : intSystem)
        {
            std::cout << "omg! " << entity << " " << component;

            isEqual = component == 10;
            intSystem.PushComponentUpdateInstruction(entity, 10);
        }
    }));

    // We need to submit our initial component update (PushComponentUpdateInstruction).
    // Otherwise, systems will run without recognizing the [entity, component] pair.
    std::vector<EntityId> deletedEntities;
    scheduler->GetComponentCache().PrepAllBuffersForNextFrame(deletedEntities);

    scheduler->ExecuteIteration(Timestamp());
    ASSERT_TRUE(isEqual);
    EXPECT_EQ(scheduler->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(entity), 20);

    scheduler->ExecuteIteration(Timestamp());
    EXPECT_EQ(scheduler->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(entity), 30);
}

// Parameterized with the amount of threads to spin
class SystemSchedulerThreadsTest : public SystemSchedulerTest, public testing::WithParamInterface<uint32_t> {
    protected:
        uint32_t ThreadsToSpin() const override { return GetParam(); }
};
TEST_P(SystemSchedulerThreadsTest, HandlesLargeAmountOfSystemsOnVariousAmountsOfThreads)
{
    EntityId entity = entityIdFactory.GetNext();

    scheduler->GetComponentCache().RegisterComponentType<int32_t>(-1, "THROW_AWAY");
    scheduler->GetComponentCache().GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, entity, 10);

    // We need to submit our initial component update (PushComponentUpdateInstruction).
    // Otherwise, systems will run without recognizing the [entity, component] pair.
    std::vector<EntityId> deletedEntities;
    scheduler->GetComponentCache().PrepAllBuffersForNextFrame(deletedEntities);

    for (int i = 0; i < 253; ++i) // 256 total systems
    {
        unused(scheduler->RegisterSystem([&](Timestamp, Catalogue catalogue) {
            auto intSystem = catalogue.GetComponentView<int32_t>();
            for (auto [entity, component] : intSystem)
            {
                intSystem.PushComponentUpdateInstruction(entity, 1);
            }
        }));
    }

    scheduler->ExecuteIteration(Timestamp());
    EXPECT_EQ(scheduler->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(entity), 253 + 10);
}

INSTANTIATE_TEST_SUITE_P(SystemScheduler, SystemSchedulerThreadsTest, testing::Values(1, 2, 3, 4, 8, 16, 32));
