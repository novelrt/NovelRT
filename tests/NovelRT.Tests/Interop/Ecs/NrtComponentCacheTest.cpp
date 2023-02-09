// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtEcs.h>
#include <NovelRT/NovelRT.h>

#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;

class InteropComponentCacheTest : public testing::Test
{
public:
    NrtComponentCacheHandle cache = nullptr;

protected:
    void SetUp() override
    {
        cache = Nrt_ComponentCache_Create(1);
    }

    void TearDown() override
    {
        Nrt_ComponentCache_Destroy(cache);
        cache = nullptr;
    }
};

TEST_F(InteropComponentCacheTest, RegisterComponentTypeSucceeds)
{
    int32_t deleteState = -1;
    NrtComponentTypeId id = 0;
    EXPECT_EQ(Nrt_ComponentCache_RegisterComponentTypeUnsafe(
                  cache, sizeof(int32_t), &deleteState, [](auto, auto, auto, auto) {}, [](auto, auto, auto) -> NrtBool {return NRT_FALSE;}, "THROW_AWAY", nullptr, &id),
              NRT_SUCCESS);
}

TEST_F(InteropComponentCacheTest, GetComponentBufferByIdReturnsValidBuffer)
{
    int32_t deleteState = -1;
    NrtComponentTypeId id = 0;
    ASSERT_EQ(Nrt_ComponentCache_RegisterComponentTypeUnsafe(
                  cache, sizeof(int32_t), &deleteState, [](auto, auto, auto, auto) {}, [](auto, auto, auto) -> NrtBool {return NRT_FALSE;}, "THROW_AWAY", nullptr, &id),
              NRT_SUCCESS);

    NrtComponentBufferMemoryContainerHandle buffer = nullptr;
    ASSERT_EQ(Nrt_ComponentCache_GetComponentBufferById(cache, id, &buffer), NRT_SUCCESS);
    int32_t inputData = 10;
    ASSERT_EQ(Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(buffer, 0, 0, &inputData), NRT_SUCCESS);
    std::vector<EntityId> dummyVec{};
    Nrt_ComponentCache_PrepAllBuffersForNextFrame(cache, reinterpret_cast<NrtEntityIdVectorHandle>(&dummyVec));
    auto view = Nrt_ComponentBufferMemoryContainer_GetComponentUnsafe(buffer, 0);
    EXPECT_EQ(
        *reinterpret_cast<const int32_t*>(Nrt_ComponentBufferMemoryContainer_ImmutableDataView_GetDataHandle(view)),
        inputData);
}
