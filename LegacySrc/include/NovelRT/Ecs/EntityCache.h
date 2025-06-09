// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_ENTITYCACHE_H
#define NOVELRT_ECS_ENTITYCACHE_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    /**
     * @brief A cache for storing entity update instructions concurrently. In a regular ECS instance, you should not be
     * instantiating this yourself.
     *
     */
    class EntityCache
    {
    private:
        std::vector<std::vector<EntityId>> _removalUpdateVectors;
        std::vector<EntityId> _entitiesToRemoveThisFrame;
        std::vector<std::vector<EntityId>> _registrationUpdateVectors;
        std::vector<EntityId> _registeredEntities;

    public:
        /**
         * @brief Constructs a new instance of EntityCache with the given thread pool size.
         *
         * @param poolSize The amount of worker threads to allocate for.
         */
        EntityCache(size_t poolSize) noexcept;

        /**
         * @brief Fetches an immutable reference to the entities to be deleted this particular iteration of the ECS.
         *
         * While this method is not marked as const, it does not modify the object directly.
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return The collection of EntityId instances to delete, by reference.
         */
        [[nodiscard]] inline std::vector<EntityId>& GetEntitiesToRemoveThisFrame() noexcept
        {
            return _entitiesToRemoveThisFrame;
        }

        /**
         * @brief Returns all registered entities in this instance of EntityCache. This data is based off of the root,
         * read-only data.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return a std::vector<EntityId>& containing all entities currently registered to this cache.
         */
        [[nodiscard]] inline const std::vector<EntityId>& GetRegisteredEntities() const noexcept
        {
            return _registeredEntities;
        }

        /**
         * @brief Registers a new entity to this particular instance of EntityCache.
         *
         *
         * @param poolId The current worker thread's pool ID the registration instruction is coming from.
         * @param newEntity The new entity to register.
         */
        void AddEntity(size_t poolId, EntityId newEntity) noexcept;

        /**
         * @brief Queues an entity for removal in the next frame.
         *
         * @param poolId The current worker thread's pool ID the removal instruction is coming from.
         * @param entityToRemove The EntityId to delete.
         */
        void RemoveEntity(size_t poolId, EntityId entityToRemove) noexcept;

        /**
         * @brief Propagates deletion requests from worker threads to the main thread. Once this is called, the data can
         * be accessed from EntityCache::GetEntitiesToRemoveThisFrame.
         *
         * In a standard ECS instance, this method should not be called by the developer.
         */
        void ProcessEntityDeletionRequestsFromThreads() noexcept;

        /**
         * @brief Applies entity deletion to the currently registered entities.
         *
         * In a standard ECS instance, this method should not be called by the developer.
         */
        void ApplyEntityDeletionRequestsToRegisteredEntities() noexcept;

        /**
         * @brief propagates registration requests from worker threads to the main thread. Once this is called,
         * the data can be accessed from EntityCache::GetRegisteredEntities.
         *
         * In a standard ECS instance, this method should not be called by the developer.
         */
        void ProcessEntityRegistrationRequestsFromThreads() noexcept;
    };
}

#endif //! NOVELRT_ECS_ENTITYCACHE_H