// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PERSISTENCE_CHAPTER_H
#define NOVELRT_PERSISTENCE_CHAPTER_H

#ifndef NOVELRT_PERSISTENCE_CHAPTER_H
#error NovelRT does not support including types explicitly by default. Please include Persistence.h instead for the Persistence namespace subset.
#endif

namespace NovelRT::Persistence
{
    class Chapter final : public IPersistable
    {
    private:
        std::map<std::string, Ecs::SparseSetMemoryContainer> _componentCacheData;

    public:
        Chapter() noexcept;

        explicit Chapter(gsl::span<std::shared_ptr<Ecs::ComponentBufferMemoryContainer>> componentCacheData) noexcept;

        void ToEcsInstance(Ecs::ComponentCache& componentCache) const;

        [[nodiscard]] static Chapter FromEcsInstance(const Ecs::ComponentCache& componentCache) noexcept;

        [[nodiscard]] ResourceManagement::BinaryPackage ToFileData() const noexcept final;

        void LoadFileData(const ResourceManagement::BinaryPackage& data) final;
    };
}

#endif // NOVELRT_PERSISTENCE_CHAPTER_H
