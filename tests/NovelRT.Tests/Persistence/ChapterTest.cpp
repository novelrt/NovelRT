// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <gtest/gtest.h>
#include <NovelRT/Persistence/Persistence.h>
#include <NovelRT/Ecs/Ecs.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Persistence;

TEST(ChapterTest, CanPackageAndUnpackageCorrectly)
{
    ComponentCache cache(1);
    cache.RegisterComponentType<int32_t>(-1, "MyExampleIntBuffer");
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 1, 10);
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 7, 20);
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 15, 30);
    cache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    auto buffers = cache.GetAllComponentBuffers();
    Chapter chapter(buffers);

    auto package = chapter.ToFileData();
    chapter.LoadFileData(package);
    chapter.ToEcsInstance(cache);

    auto buffer = cache.GetComponentBuffer<int32_t>();
    EXPECT_EQ(buffer.GetComponentUnsafe(1), 10);
    EXPECT_EQ(buffer.GetComponentUnsafe(7), 20);
    EXPECT_EQ(buffer.GetComponentUnsafe(15), 30);
}
