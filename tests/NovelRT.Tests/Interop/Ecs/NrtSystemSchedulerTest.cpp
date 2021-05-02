// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtEcs.h>
#include <NovelRT.h>

#include <atomic>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;
using namespace NovelRT::Timing;

class InteropSystemSchedulerTest : public testing::Test
{
public:
    NrtSystemSchedulerHandle scheduler = nullptr;
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
            auto cppScheduler = new SystemScheduler();

            cppScheduler->SpinThreads();

            sysOne = [&](Timestamp delta, Catalogue) { sysOneBool = false; };
            sysTwo = [&](Timestamp delta, Catalogue) { sysTwoBool = false; };
            sysThree = [&](Timestamp delta, Catalogue) { sysThreeBool = false; };

            cppScheduler->RegisterSystem(sysOne);
            cppScheduler->RegisterSystem(sysTwo);
            cppScheduler->RegisterSystem(sysThree);
            scheduler = reinterpret_cast<NrtSystemSchedulerHandle>(cppScheduler);
        }
    }

    void TearDown() override
    {
        if (scheduler != nullptr)
        {
            Nrt_SystemScheduler_Destroy(scheduler);
            scheduler = nullptr;
        }
    }
};

TEST_F(InteropSystemSchedulerTest, IndependentSystemsCanRun)
{
    EXPECT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);
}

TEST_F(InteropSystemSchedulerTest, IndependentSystemsCanModifyValues)
{
    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);

    EXPECT_FALSE(sysOneBool);
    EXPECT_FALSE(sysTwoBool);
    EXPECT_FALSE(sysThreeBool);
}

TEST_F(InteropSystemSchedulerTest, IndependentSystemsObtainValidCatalogue)
{
    EntityId entity = Atom::getNextEntityId();

    auto cache = Nrt_SystemScheduler_GetComponentCache(scheduler);
    reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().RegisterComponentType<int32_t>(-1);

    NrtComponentBufferMemoryContainerHandle container = nullptr;
    ASSERT_EQ(Nrt_ComponentCache_GetComponentBufferById(cache, GetComponentTypeId<int32_t>(), &container), NRT_SUCCESS);

    int32_t data = 10;
    Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(container, 0, entity, &data);

    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);

    Nrt_SystemScheduler_RegisterSystem(scheduler, [](auto delta, auto catalogue, auto) {
        auto intSystem = reinterpret_cast<Catalogue*>(catalogue)->GetComponentView<int32_t>();

        for (auto [entity, component] : intSystem)
        {
            intSystem.PushComponentUpdateInstruction(entity, 10);
        }
    }, nullptr);

    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);
    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);
    EXPECT_EQ(
        reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(
            entity),
        20);
}
