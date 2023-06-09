// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtEcs.h>
#include <NovelRT/NovelRT.h>

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
    inline static NovelRT::Core::AtomFactory& entityIdFactory =
        NovelRT::Core::AtomFactoryDatabase::GetFactory("EntityId");

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

            sysOne = [&](Timestamp, Catalogue) { sysOneBool = false; };
            sysTwo = [&](Timestamp, Catalogue) { sysTwoBool = false; };
            sysThree = [&](Timestamp, Catalogue) { sysThreeBool = false; };

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
    EntityId entity = entityIdFactory.GetNext();

    auto cache = Nrt_SystemScheduler_GetComponentCache(scheduler);
    reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().RegisterComponentType<int32_t>(-1, "THROW_AWAY");

    NrtComponentBufferMemoryContainerHandle container = nullptr;
    ASSERT_EQ(Nrt_ComponentCache_GetComponentBufferById(cache, GetComponentTypeId<int32_t>(), &container), NRT_SUCCESS);

    int32_t data = 10;
    Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(container, 0, entity, &data);

    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);

    Nrt_SystemScheduler_RegisterSystem(
        scheduler,
        [](auto, auto catalogue, auto) {
            auto intSystem = reinterpret_cast<Catalogue*>(catalogue)->GetComponentView<int32_t>();

            for (auto [entity, component] : intSystem)
            {
                intSystem.PushComponentUpdateInstruction(entity, 10);
            }
        },
        nullptr);

    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);
    EXPECT_EQ(
        reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(
            entity),
        20);

    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);
    EXPECT_EQ(
        reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(
            entity),
        30);
}

TEST_F(InteropSystemSchedulerTest, IndependentSystemsCanHandleRemainderWithThreeThreads)
{
    TearDown();

    auto cppScheduler = new SystemScheduler(3);
    cppScheduler->SpinThreads();

    cppScheduler->RegisterSystem(sysOne);
    cppScheduler->RegisterSystem(sysTwo);
    cppScheduler->RegisterSystem(sysThree);
    scheduler = reinterpret_cast<NrtSystemSchedulerHandle>(cppScheduler);

    EntityId entity = entityIdFactory.GetNext();

    auto cache = Nrt_SystemScheduler_GetComponentCache(scheduler);
    reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().RegisterComponentType<int32_t>(-1, "THROW_AWAY");

    NrtComponentBufferMemoryContainerHandle container = nullptr;
    ASSERT_EQ(Nrt_ComponentCache_GetComponentBufferById(cache, GetComponentTypeId<int32_t>(), &container), NRT_SUCCESS);

    int32_t data = 10;
    Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(container, 0, entity, &data);

    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);
    EXPECT_EQ(
        reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(
            entity),
        10);

    Nrt_SystemScheduler_RegisterSystem(
        scheduler,
        [](auto, auto catalogue, auto) {
            auto intSystem = reinterpret_cast<Catalogue*>(catalogue)->GetComponentView<int32_t>();

            for (auto [entity, component] : intSystem)
            {
                intSystem.PushComponentUpdateInstruction(entity, 9);
            }
        },
        nullptr);

    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);
    EXPECT_EQ(
        reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(
            entity),
        19);

    Nrt_SystemScheduler_RegisterSystem(
        scheduler,
        [](auto, auto catalogue, auto) {
            auto intSystem = reinterpret_cast<Catalogue*>(catalogue)->GetComponentView<int32_t>();

            for (auto [entity, component] : intSystem)
            {
                intSystem.PushComponentUpdateInstruction(entity, 8);
            }
        },
        nullptr);

    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);
    EXPECT_EQ(
        reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(
            entity),
        36);

    Nrt_SystemScheduler_RegisterSystem(
        scheduler,
        [](auto, auto catalogue, auto) {
            auto intSystem = reinterpret_cast<Catalogue*>(catalogue)->GetComponentView<int32_t>();

            for (auto [entity, component] : intSystem)
            {
                intSystem.PushComponentUpdateInstruction(entity, 7);
            }
        },
        nullptr);

    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);
    EXPECT_EQ(
        reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(
            entity),
        60);

    Nrt_SystemScheduler_RegisterSystem(
        scheduler,
        [](auto, auto catalogue, auto) {
            auto intSystem = reinterpret_cast<Catalogue*>(catalogue)->GetComponentView<int32_t>();

            for (auto [entity, component] : intSystem)
            {
                intSystem.PushComponentUpdateInstruction(entity, 6);
            }
        },
        nullptr);

    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);
    EXPECT_EQ(
        reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(
            entity),
        90);
}

TEST_F(InteropSystemSchedulerTest, IndependentSystemsCanHandleManySystems)
{
    EntityId entity = entityIdFactory.GetNext();

    auto cache = Nrt_SystemScheduler_GetComponentCache(scheduler);
    reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().RegisterComponentType<int32_t>(-1, "THROW_AWAY");

    NrtComponentBufferMemoryContainerHandle container = nullptr;
    ASSERT_EQ(Nrt_ComponentCache_GetComponentBufferById(cache, GetComponentTypeId<int32_t>(), &container), NRT_SUCCESS);

    int32_t data = 10;
    Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(container, 0, entity, &data);

    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);

    for (int i = 0; i < 8; ++i) // 11 total systems
        Nrt_SystemScheduler_RegisterSystem(
            scheduler,
            [](auto, auto catalogue, auto) {
                auto intSystem = reinterpret_cast<Catalogue*>(catalogue)->GetComponentView<int32_t>();

                for (auto [entity, component] : intSystem)
                {
                    intSystem.PushComponentUpdateInstruction(entity, 1);
                }
            },
            nullptr);

    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);
    EXPECT_EQ(
        reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(
            entity),
        18);

    for (int i = 0; i < 6; ++i) // 17 total systems
        Nrt_SystemScheduler_RegisterSystem(
            scheduler,
            [](auto, auto catalogue, auto) {
                auto intSystem = reinterpret_cast<Catalogue*>(catalogue)->GetComponentView<int32_t>();

                for (auto [entity, component] : intSystem)
                {
                    intSystem.PushComponentUpdateInstruction(entity, 1);
                }
            },
            nullptr);

    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);
    EXPECT_EQ(
        reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(
            entity),
        32);

    for (int i = 0; i < 6; ++i) // 23 total systems
        Nrt_SystemScheduler_RegisterSystem(
            scheduler,
            [](auto, auto catalogue, auto) {
                auto intSystem = reinterpret_cast<Catalogue*>(catalogue)->GetComponentView<int32_t>();

                for (auto [entity, component] : intSystem)
                {
                    intSystem.PushComponentUpdateInstruction(entity, 1);
                }
            },
            nullptr);

    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);
    EXPECT_EQ(
        reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(
            entity),
        52);

    for (int i = 0; i < 14; ++i) // 37 total systems
        Nrt_SystemScheduler_RegisterSystem(
            scheduler,
            [](auto, auto catalogue, auto) {
                auto intSystem = reinterpret_cast<Catalogue*>(catalogue)->GetComponentView<int32_t>();

                for (auto [entity, component] : intSystem)
                {
                    intSystem.PushComponentUpdateInstruction(entity, 1);
                }
            },
            nullptr);

    ASSERT_EQ(Nrt_SystemScheduler_ExecuteIteration(scheduler, 0), NRT_SUCCESS);
    EXPECT_EQ(
        reinterpret_cast<SystemScheduler*>(scheduler)->GetComponentCache().GetComponentBuffer<int32_t>().GetComponent(
            entity),
        86);
}

TEST_F(InteropSystemSchedulerTest, ThreadsAreSpinningReturnsCorrectValue)
{
    EXPECT_TRUE(Nrt_SystemScheduler_GetThreadsAreSpinning(scheduler));
}

TEST_F(InteropSystemSchedulerTest, ShutDownForcesSchedulerIntoCorrectState)
{
    ASSERT_TRUE(Nrt_SystemScheduler_GetThreadsAreSpinning(scheduler));
    ASSERT_EQ(Nrt_SystemScheduler_ShutDown(scheduler), NRT_SUCCESS);
    EXPECT_FALSE(Nrt_SystemScheduler_GetThreadsAreSpinning(scheduler));
}
