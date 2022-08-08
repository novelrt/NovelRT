// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PERSISTENCE_CHAPTER_H
#define NOVELRT_PERSISTENCE_CHAPTER_H

#ifndef NOVELRT_PERSISTENCE_H
#error NovelRT does not support including types explicitly by default. Please include Persistence.h instead for the Persistence namespace subset.
#endif

namespace NovelRT::Persistence
{
    class Chapter final : public Persistable
    {
    private:
        std::map<std::string, Ecs::SparseSetMemoryContainer> _componentCacheData;
        Ecs::SparseSet<Ecs::EntityId, uuids::uuid> _entityUuidIdentifiers;
        std::unordered_map<uuids::uuid, Ecs::EntityId> _entityUuidInverseIdentifiers;

    public:
        Chapter() noexcept;

        explicit Chapter(gsl::span<std::shared_ptr<Ecs::ComponentBufferMemoryContainer>> componentCacheData, const Ecs::SparseSet<Ecs::EntityId, uuids::uuid>& entityUuidIdentifiers) noexcept;

        void ToEcsInstance(Ecs::SystemScheduler& instance) const;

        [[nodiscard]] static Chapter FromEcsInstance(const Ecs::SystemScheduler& instance) noexcept;

        [[nodiscard]] ResourceManagement::BinaryPackage ToFileData() const final;

        void LoadFileData(const ResourceManagement::BinaryPackage& data) final;
    };
}

#endif // NOVELRT_PERSISTENCE_CHAPTER_H
