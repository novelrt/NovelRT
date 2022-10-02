// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>
#include <NovelRT/Persistence/Persistence.h>
#include <gtest/gtest.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Persistence;

TEST(ChapterTest, CanPackageAndUnpackageCorrectly)
{
    ComponentCache cache(1);
    EntityCache entityCache(1);
    cache.RegisterComponentType<int32_t>(-1, "MyExampleIntBuffer");
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 1, 10);
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 7, 20);
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 15, 30);
    cache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    auto buffers = cache.GetAllComponentBuffers();
    Chapter chapter(buffers);

    auto package = chapter.ToFileData();

    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 1, -1);
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 7, -1);
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 15, -1);
    cache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    chapter.LoadFileData(package);

    chapter.ToEcsInstance(cache, entityCache);
    cache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    auto buffer = cache.GetComponentBuffer<int32_t>();
    EXPECT_EQ(buffer.GetComponentUnsafe(1), 10);
    EXPECT_EQ(buffer.GetComponentUnsafe(7), 20);
    EXPECT_EQ(buffer.GetComponentUnsafe(15), 30);
}

TEST(ChapterTest, CanPackageAndUnpackageCorrectlyWithDuplicate)
{
    ComponentCache cache(1);
    EntityCache entityCache(1);
    cache.RegisterComponentType<int32_t>(-1, "MyExampleIntBuffer");
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 1, 10);
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 7, 20);
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 15, 30);
    entityCache.AddEntity(0, 1);
    entityCache.AddEntity(0, 7);
    entityCache.AddEntity(0, 15);
    cache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});
    entityCache.ProcessEntityRegistrationRequestsFromThreads();
    entityCache.ApplyEntityDeletionRequestsToRegisteredEntities();

    auto buffers = cache.GetAllComponentBuffers();
    Chapter chapter(buffers);

    auto package = chapter.ToFileData();

    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 1, 40);
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 7, 50);
    cache.GetComponentBuffer<int32_t>().PushComponentUpdateInstruction(0, 15, 60);
    cache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});
    entityCache.ProcessEntityRegistrationRequestsFromThreads();
    entityCache.ApplyEntityDeletionRequestsToRegisteredEntities();

    chapter.LoadFileData(package);

    chapter.ToEcsInstance(cache, entityCache);
    cache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});
    entityCache.ProcessEntityRegistrationRequestsFromThreads();
    entityCache.ApplyEntityDeletionRequestsToRegisteredEntities();

    auto buffer = cache.GetComponentBuffer<int32_t>();
    EXPECT_EQ(buffer.GetComponentUnsafe(1), 50);
    EXPECT_EQ(buffer.GetComponentUnsafe(7), 70);
    EXPECT_EQ(buffer.GetComponentUnsafe(15), 90);

    bool tenFound = false;
    bool twentyFound = false;
    bool thirtyFound = false;
    bool rubbishDataFound = false;

    for(auto&& [entity, component] : buffer)
    {
        switch (entity)
        {
            case 1:
            case 7:
            case 15:
                continue;

            default:
                switch (component)
                {
                    case 10:
                        tenFound = true;
                        break;
                    case 20:
                        twentyFound = true;
                        break;
                    case 30:
                        thirtyFound = true;
                        break;
                    default:
                        rubbishDataFound = true;
                        break;
                }
        }
    }

    EXPECT_TRUE(tenFound);
    EXPECT_TRUE(twentyFound);
    EXPECT_TRUE(thirtyFound);
    EXPECT_FALSE(rubbishDataFound);
}
