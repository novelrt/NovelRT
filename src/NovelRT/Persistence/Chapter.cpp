// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Persistence/Persistence.h>

namespace NovelRT::Persistence
{
    Chapter::Chapter(gsl::span<Ecs::SparseSetMemoryContainer> componentCacheData)
        : _componentCacheData(
              std::vector<Ecs::SparseSetMemoryContainer>(componentCacheData.begin(), componentCacheData.end()))
    {
    }

    void Chapter::ToEcsInstance(Ecs::ComponentCache& componentCache) const
    {
    }

    Chapter Chapter::FromEcsInstance(const Ecs::ComponentCache& componentCache)
    {
        auto buffers = componentCache.GetAllComponentBuffers();
        std::vector<Ecs::SparseSetMemoryContainer> rootSets{};
        rootSets.reserve(buffers.size());

        for (auto&& buffer : buffers)
        {
            rootSets.emplace_back(buffer->GetReadOnlyContainer());
        }

        return Chapter(rootSets);
    }
}