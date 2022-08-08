// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>
#include <NovelRT/Persistence/Persistence.h>
#include <gtest/gtest.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Persistence;

TEST(ChapterTest, CanPackageAndUnpackageCorrectly)
{
    SystemScheduler scheduler(1);
    auto& cache = scheduler.GetComponentCache();
    cache.RegisterComponentType<int32_t>(-1, "MyExampleIntBuffer");
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 1, 10);
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 7, 20);
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 15, 30);
    cache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    auto buffers = cache.GetAllComponentBuffers();
    Chapter chapter(buffers, SparseSet<EntityId, uuids::uuid>{});

    auto package = chapter.ToFileData();

    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 1, -1);
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 7, -1);
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 15, -1);
    cache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    chapter.LoadFileData(package);

    chapter.ToEcsInstance(scheduler);
    cache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    auto buffer = cache.GetComponentBuffer<int32_t>();
    EXPECT_EQ(buffer.GetComponentUnsafe(1), 10);
    EXPECT_EQ(buffer.GetComponentUnsafe(7), 20);
    EXPECT_EQ(buffer.GetComponentUnsafe(15), 30);
}
