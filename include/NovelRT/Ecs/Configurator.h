// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_CONFIGURATOR_H
#define NOVELRT_ECS_CONFIGURATOR_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    /**
     * @brief A convenience type to help with the creation of an ECS instance.
     */
    class Configurator
    {
    private:
        bool _shouldAddDefaultSystems = false;
        std::optional<uint32_t> _threadCount;
        std::vector<std::function<void(Timing::Timestamp, Catalogue)>> _systems;

        inline void AddDefaultComponentsAndSystems(SystemScheduler& /*target*/)
        {
            // Add default components and systems here when they exist. Uncomment parameter when you do.
        }

    public:
        /**
         * @brief Defines how many worker threads should be configured for this ECS instance.
         *
         * @param threadCount The amount of threads.
         * @returns Configurator& A reference to this to allow method chaining.
         */
       [[nodiscard]] inline Configurator& WithThreadCount(uint32_t threadCount) noexcept
        {
            _threadCount = threadCount;
            return *this;
        }

        /**
         * @brief Configures systems for registration for this ECS instance.
         *
         * @param functions collection of std::function<void(Timing::Timestamp, Catalogue)> instances to attach.
         * @returns Configurator& A reference to this to allow method chaining.
         */
       [[nodiscard]] inline Configurator& WithSystems(std::initializer_list<std::function<void(Timing::Timestamp, Catalogue)>>&& functions) noexcept
        {
            for(auto&& fnptr : functions)
            {
                _systems.emplace_back(fnptr);
            }

            return *this;
        }

        /**
         * @brief enables the default core system implementations that are used by NovelRT by default.
         *
         * @returns Configurator& A reference to this to allow method chaining.
         */
        [[nodiscard]] inline Configurator& WithDefaultSystemsAndComponents() noexcept
        {
            _shouldAddDefaultSystems = true;
            return *this;
        }

        /**
         * @brief Creates the ECS instance and registers component types to it.
         * This is the final method you should call to obtain the ECS instance.
         *
         * @tparam TComponentTypes List of component types to register with this ECS instance.
         * @returns SystemScheduler an instance of the ECS based on the provided configuration.
         */
        template<typename... TComponentTypes>
        [[nodiscard]] SystemScheduler InitialiseAndRegisterComponents(TComponentTypes... deleteInstructionStates)
        {
            SystemScheduler scheduler(_threadCount.value_or(0));

            if (_shouldAddDefaultSystems)
            {
                AddDefaultComponentsAndSystems(scheduler);
            }

            for (auto&& system : _systems)
            {
                scheduler.RegisterSystem(system);
            }

            scheduler.GetComponentCache().RegisterComponentType<TComponentTypes...>(deleteInstructionStates...);
            scheduler.SpinThreads();

            return scheduler;
        }

        /**
         * @brief Creates the ECS instance and registers component types to it.
         * This is the final method you should call to obtain the ECS instance.
         *
         * @returns SystemScheduler an instance of the ECS based on the provided configuration.
         */
        template<>
        [[nodiscard]] SystemScheduler InitialiseAndRegisterComponents()
        {
            SystemScheduler scheduler(_threadCount.value_or(0));

            if (_shouldAddDefaultSystems)
            {
                AddDefaultComponentsAndSystems(scheduler);
            }

            for (auto&& system : _systems)
            {
                scheduler.RegisterSystem(system);
            }

            scheduler.SpinThreads();

            return scheduler;
        }
    };
}

#endif // NOVELRT_ECS_CONFIGURATOR_H
