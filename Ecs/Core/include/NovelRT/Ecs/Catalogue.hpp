#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/ComponentCache.hpp>
#include <NovelRT/Ecs/EcsUtils.hpp>
#include <NovelRT/Ecs/ImplDetail.hpp>

#include <cstddef>
#include <cstdint>
#include <tuple>
#include <vector>

namespace NovelRT::Ecs
{
    template<typename TComponent>
    class ComponentView;
    class EntityCache;
    class SystemScheduler;
    class UnsafeComponentView;

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
        SystemScheduler& _scheduler;
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
        Catalogue(size_t poolId, SystemScheduler& scheduler) noexcept;

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
        template<typename TComponent>
        [[nodiscard]] ComponentView<TComponent> GetComponentView() noexcept
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
        [[nodiscard]] std::tuple<ComponentView<TComponents>...> GetComponentViews() noexcept
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

        /**
         * @brief Schedules a unit of work to be executed outside of the ECS context, with a completion
         * callback that is executed on the next iteration of the ECS once the work is done.
         *
         * The work functor is executed asynchronously on a separate thread pool and must not interact
         * with the ECS or capture any references to a Catalogue instance, as the behaviour is undefined.
         * The completion functor is executed on the ECS thread pool in the next available iteration,
         * and receives a fresh Catalogue instance with the correct threading context, the current delta time,
         * and the result of the work functor.
         *
         * This is a pure method with respect to the Catalogue itself. Calling this without using the
         * result of the work functor in the completion has no effect and introduces overhead.
         *
         * @tparam TWork The type of the work functor. Must be invocable with no arguments.
         * @tparam TCompletion The type of the completion functor. Must be invocable with a
         * Timing::Timestamp, a Catalogue, and the return type of TWork.
         *
         * @param work A functor to be executed outside of the ECS context. Must not capture or interact
         * with any ECS state.
         * @param completion A functor to be executed on the ECS thread pool once the work is complete.
         * Receives the current delta time, a valid Catalogue instance, and the result of the work functor.
         */
        template<typename TWork, typename TCompletion>
        requires Detail::ValidScheduleWithCompletion<TWork, TCompletion> void ScheduleWithCompletion(
            TWork&& work,
            TCompletion&& completion) noexcept;
    };
}

#include <NovelRT/Ecs/MiscTemplateImpls.hpp> // This has to be here due to template implementation detials - Matt J.
