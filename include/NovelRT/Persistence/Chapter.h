// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PERSISTENCE_CHAPTER_H
#define NOVELRT_PERSISTENCE_CHAPTER_H

#ifndef NOVELRT_PERSISTENCE_CHAPTER_H
#error NovelRT does not support including types explicitly by default. Please include Persistence.h instead for the Persistence namespace subset.
#endif

namespace NovelRT::Persistence
{
    class Chapter
    {
    private:
        std::vector<Ecs::SparseSetMemoryContainer> _componentCacheData;

    public:
        explicit Chapter(gsl::span<Ecs::SparseSetMemoryContainer> componentCacheData);

        void ToEcsInstance(Ecs::ComponentCache& componentCache) const;

        [[nodiscard]] static Chapter FromEcsInstance(const Ecs::ComponentCache& componentCache);
    };
}

#endif // NOVELRT_PERSISTENCE_CHAPTER_H
