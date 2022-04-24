// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PERSISTENCE_CHAPTER_H
#define NOVELRT_PERSISTENCE_CHAPTER_H

namespace NovelRT::Persistence
{
    class Chapter
    {
    private:
        std::vector<Ecs::SparseSetMemoryContainer> _componentCacheData;

    public:
        Chapter(gsl::span<Ecs::EntityId> entityCacheData, gsl::span<Ecs::SparseSetMemoryContainer> componentCacheData);

        void ToEcsInstance(Ecs::ComponentCache& componentCache) const;

        [[nodiscard]] static Chapter FromEcsInstance(const Ecs::ComponentCache& componentCache);
    };
}

#endif // NOVELRT_PERSISTENCE_CHAPTER_H
