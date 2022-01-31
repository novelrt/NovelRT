#include <utility>

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
        std::shared_ptr<PluginManagement::IGraphicsPluginProvider> _graphicsPluginProvider;
        std::shared_ptr<PluginManagement::IWindowingPluginProvider> _windowingPluginProvider;
        std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> _resourceManagementPluginProvider;
        std::shared_ptr<PluginManagement::IInputPluginProvider> _inputPluginProvider;

        inline void AddDefaultComponentsAndSystems(SystemScheduler& target)
        {
            target.GetComponentCache().RegisterComponentType(Graphics::RenderComponent{0, 0, 0, 0, true});

            target.GetComponentCache().RegisterComponentType(EntityGraphComponent{
                false, std::numeric_limits<EntityId>::max(), std::numeric_limits<EntityId>::max()});

            target.GetComponentCache().RegisterComponentType(LinkedEntityListNodeComponent{
                false, std::numeric_limits<EntityId>::max(), std::numeric_limits<EntityId>::max()});

            target.GetComponentCache().RegisterComponentType(
                TransformComponent{Maths::GeoVector3F::uniform(NAN), Maths::GeoVector2F::uniform(NAN), NAN});

            target.RegisterSystem(std::make_shared<Ecs::Graphics::DefaultRenderingSystem>(
                _graphicsPluginProvider, _windowingPluginProvider, _resourceManagementPluginProvider));

            target.GetComponentCache().RegisterComponentType(
                Ecs::Input::InputEventComponent{0, NovelRT::Input::KeyState::Idle, 0, 0});

            target.RegisterSystem(
                std::make_shared<Ecs::Input::InputSystem>(_windowingPluginProvider, _inputPluginProvider));
        }

    public:
        /**
         * @brief Defines how many worker threads should be configured for this ECS instance.
         *
         * @param threadCount The amount of threads.
         * @returns A reference to this to allow method chaining.
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
         * @returns A reference to this to allow method chaining.
         */
        [[nodiscard]] inline Configurator& WithSystems(
            std::initializer_list<std::function<void(Timing::Timestamp, Catalogue)>>&& functions) noexcept
        {
            for (auto&& fnptr : functions)
            {
                _systems.emplace_back(fnptr);
            }

            return *this;
        }

        /**
         * @brief enables the default core system implementations that are used by NovelRT by default.
         *
         * @returns A reference to this to allow method chaining.
         */
        [[nodiscard]] inline Configurator& WithDefaultSystemsAndComponents() noexcept
        {
            _shouldAddDefaultSystems = true;
            return *this;
        }

        /**
         * @brief Specifies a plugin provider object to use for creating the default systems.
         *
         * @tparam TPluginProvider The type of PluginProvider interface this provider implements.
         * @return A reference to this to allow method chaining.
         *
         * @exception Exceptions::NotSupportedException if the plugin provider type is currently not used or supported
         * by default systems.
         */
        template<typename TPluginProvider>
        [[nodiscard]] Configurator& WithPluginProvider(std::shared_ptr<TPluginProvider> /*pluginInstance*/)
        {
            throw Exceptions::NotSupportedException(
                "This plugin provider type is invalid or not supported at this time.");
        }

        /**
         * @brief Specifies a plugin provider object to use for creating the default systems.
         *
         * @tparam TPluginProvider The type of PluginProvider interface this provider implements.
         * @return A reference to this to allow method chaining.
         *
         * @exception Exceptions::NotSupportedException if the plugin provider type is currently not used or supported
         * by default systems.
         */
        template<>
        [[nodiscard]] Configurator& WithPluginProvider<PluginManagement::IGraphicsPluginProvider>(
            std::shared_ptr<PluginManagement::IGraphicsPluginProvider> pluginInstance)
        {
            _graphicsPluginProvider = std::move(pluginInstance);
            return *this;
        }

        /**
         * @brief Specifies a plugin provider object to use for creating the default systems.
         *
         * @tparam TPluginProvider The type of PluginProvider interface this provider implements.
         * @return A reference to this to allow method chaining.
         *
         * @exception Exceptions::NotSupportedException if the plugin provider type is currently not used or supported
         * by default systems.
         */
        template<>
        [[nodiscard]] Configurator& WithPluginProvider<PluginManagement::IWindowingPluginProvider>(
            std::shared_ptr<PluginManagement::IWindowingPluginProvider> pluginInstance)
        {
            _windowingPluginProvider = std::move(pluginInstance);
            return *this;
        }

        /**
         * @brief Specifies a plugin provider object to use for creating the default systems.
         *
         * @tparam TPluginProvider The type of PluginProvider interface this provider implements.
         * @return A reference to this to allow method chaining.
         *
         * @exception Exceptions::NotSupportedException if the plugin provider type is currently not used or supported
         * by default systems.
         */
        template<>
        [[nodiscard]] Configurator& WithPluginProvider<PluginManagement::IResourceManagementPluginProvider>(
            std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> pluginInstance)
        {
            _resourceManagementPluginProvider = std::move(pluginInstance);
            return *this;
        }

        /**
         * @brief Specifies a plugin provider object to use for creating the default systems.
         *
         * @tparam TPluginProvider The type of PluginProvider interface this provider implements.
         * @return A reference to this to allow method chaining.
         *
         * @exception Exceptions::NotSupportedException if the plugin provider type is currently not used or supported
         * by default systems.
         */
        template<>
        [[nodiscard]] Configurator& WithPluginProvider<PluginManagement::IInputPluginProvider>(
            std::shared_ptr<PluginManagement::IInputPluginProvider> pluginInstance)
        {
            _inputPluginProvider = std::move(pluginInstance);
            return *this;
        }

        /**
         * @brief Creates the ECS instance and registers component types to it.
         * This is the final method you should call to obtain the ECS instance.
         *
         * @tparam TComponentTypes List of component types to register with this ECS instance.
         * @param deleteInstructionStates The state of the given component type that signals this component is to be
         * deleted to the ECS.
         * @returns An instance of the ECS SystemScheduler root object based on the provided configuration.
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
         * @returns An instance of the ECS SystemScheduler based on the provided configuration.
         */
        template<>[[nodiscard]] SystemScheduler InitialiseAndRegisterComponents()
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
