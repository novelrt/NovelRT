// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_CATALOGUE_H
#define NOVELRT_ECS_CATALOGUE_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    /**
     * @brief A thread-aware context into the current state of the ECS instance that created an instance of this object.
     * You should not be instantiating this yourself in a regular setup.
     *
     * When inside a system, an instance of this object is provided alongside the current delta time as a
     * Timing::Timestamp and should be used to query and modify the ECS state.
     */
    class Catalogue
    {
    private:
        size_t _poolId;
        ComponentCache& _componentCache;
        EntityCache& _entityCache;
        std::vector<EntityId> _createdEntitiesThisFrame;

    public:
        /**
         * @brief Constructs a new Catalogue object with context of the ECS instance and thread state.
         *
         * @param poolId The pool ID being used by the thread creating this catalogue instance.
         * @param componentCache The storage object for all the components in this particular ECS instance.
         * @param entityCache The storage object for all modifications being made directly to entities themselves (such
         * as a delete instruction).
         */
        Catalogue(size_t poolId, ComponentCache& componentCache, EntityCache& entityCache) noexcept;

        /**
         * @brief Gets a view into the ComponentCache for the specified component type based on the context of the
         * Catalogue.
         *
         * While this method is not const due to implementation details, this method does not actually directly modify
         * the catalogue or any underlying data itself. As such, the returned view should not be discarded. Calling this
         * method without actively using the returned view has no effect and introduces overhead.
         *
         * @tparam TComponent The component type the view should be exposing.
         * @return A ComponentView<TComponent> instance that has its threading context set to the current thread.
         */
        template<typename TComponent>[[nodiscard]] ComponentView<TComponent> GetComponentView() noexcept
        {
            return ComponentView<TComponent>(_poolId, _componentCache.GetComponentBuffer<TComponent>());
        }

        /**
         * @brief Gets a variadic tuple of views into the ComponentCache for the specified component types based on the
         * context of the Catalogue. This is a multi component version of Catalogue::GetComponentView.
         *
         * While this method is not const, this method does not actually directly modify the catalogue or any underlying
         * data itself. As such, the returned tuple should not be discarded. Calling this method without actively using
         * the returned tuple has no effect and introduces overhead.
         *
         * @tparam TComponents The component types the views should be exposing.
         * @return A std::tuple<ComponentView<TComponents>...> containing multiple ComponentView<TComponent> instances
         * that has their threading contexts set to the current thread.
         */
        template<typename... TComponents>
        [[nodiscard]] std::tuple<ComponentView<TComponents>...> GetComponentViews() const noexcept
        {
            return std::make_tuple(
                ComponentView<TComponents>(_poolId, _componentCache.GetComponentBuffer<TComponents>())...);
        }

        /**
         * @brief Gets a typeless view into a memory container.
         *
         * The returned type, UnsafeComponentView, is considered an unsafe type by nature. Only call this in contexts
         * where interop is required.
         *
         * @param componentTypeId The component ID to search for
         * @return A typeless component view into the ComponentBuffer's inner memory container, represented as an
         * UnsafeComponentView.
         * @exceptions std::out_of_range if the supplied ID is not present within the container.
         */
        [[nodiscard]] UnsafeComponentView GetComponentViewById(ComponentTypeId componentTypeId);

        /**
         * @brief Creates a new EntityId for use within the ECS.
         *
         * If you discard the returned EntityId, the entity will simply be lost to the ECS and will have no effect.
         *
         * @return The newly created entity.
         */
        [[nodiscard]] EntityId CreateEntity() noexcept;

        /**
         * @brief Marks an entity for deletion when the current update cycle is resolved. In the next immutable ECS
         * state, this entity will not exist.
         *
         * @param entity The entity to delete.
         */
        void DeleteEntity(EntityId entity) noexcept;
    };
}

#endif //! NOVELRT_ECS_CATALOGUE_H