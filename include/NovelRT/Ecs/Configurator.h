// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_CONFIGURATOR_H
#define NOVELRT_ECS_CONFIGURATOR_H

namespace NovelRT::Ecs
{
    /**
     * @brief A convenience type to help with the creation of an ECS instance.
     */
    template <typename TGraphicsBackend>
    class Configurator
    {
    private:
        bool _shouldAddDefaultSystems = false;
        std::optional<uint32_t> _threadCount;
        std::vector<std::function<void(Timing::Timestamp, Catalogue)>> _systems;
        std::vector<std::shared_ptr<IEcsSystem>> _iecsSystems;
        std::shared_ptr<PluginManagement::IGraphicsPluginProvider<TGraphicsBackend>> _graphicsPluginProvider;
        std::shared_ptr<PluginManagement::IWindowingPluginProvider> _windowingPluginProvider;
        std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> _resourceManagementPluginProvider;
        std::shared_ptr<PluginManagement::IInputPluginProvider> _inputPluginProvider;

        inline void AddDefaultComponentsAndSystems(SystemScheduler& target)
        {
            target.GetComponentCache().RegisterComponentType(
                EntityGraphComponent{false, std::numeric_limits<EntityId>::max(), std::numeric_limits<EntityId>::max()},
                "NovelRT::Ecs::EntityGraphComponent");

            target.GetComponentCache().RegisterComponentType(
                LinkedEntityListNodeComponent{false, std::numeric_limits<EntityId>::max(),
                                              std::numeric_limits<EntityId>::max()},
                "NovelRT::Ecs::LinkedEntityListNodeComponent");

            target.GetComponentCache().RegisterComponentType(
                TransformComponent{Maths::GeoVector3F::Uniform(NAN), Maths::GeoVector2F::Uniform(NAN), NAN},
                "NovelRT::Ecs::TransformComponent");

            target.GetComponentCache().RegisterComponentType(
                Input::InputEventComponent{0, NovelRT::Input::KeyState::Idle, 0, 0},
                "NovelRT::Ecs::Input::InputEventComponent");

            target.GetComponentCache().RegisterComponentType(
                Narrative::NarrativeStoryStateComponent{Narrative::NarrativeStoryState::Idle, true},
                "NovelRT::Ecs::Narrative::NarrativeStoryStateComponent");

            target.GetComponentCache().RegisterComponentType(
                Narrative::RequestNarrativeScriptExecutionComponent{uuids::uuid(), true},
                "NovelRT::Ecs::Narrative::RequestNarrativeScriptExecutionComponent");

            target.GetComponentCache().RegisterComponentType(Narrative::ChoiceMetadataComponent{0, true},
                                                             "NovelRT::Ecs::Narrative::ChoiceMetadataComponent");

            target.GetComponentCache().RegisterComponentType(Narrative::SelectedChoiceComponent{0, true},
                                                             "NovelRT::Ecs::Narrative::SelectedChoiceComponent");

            target.RegisterSystem(
                std::make_shared<Narrative::NarrativePlayerSystem>(_resourceManagementPluginProvider));

            auto deleteState = Audio::AudioEmitterComponent();
            target.GetComponentCache().RegisterComponentType(deleteState, "NovelRT::Ecs::Audio::AudioEmitterComponent");
            target.GetComponentCache().RegisterComponentType(
                Audio::AudioEmitterStateComponent{Audio::AudioEmitterState::Done},
                "NovelRT::Ecs::Audio::AudioEmitterStateComponent");

            target.RegisterSystem(
                std::make_shared<Ecs::Input::InputSystem>(_windowingPluginProvider, _inputPluginProvider));

            target.RegisterSystem(std::make_shared<Ecs::Audio::AudioSystem>(_resourceManagementPluginProvider));
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
         * @brief Configures systems for registration for this ECS instance (IEcsSystem variant).
         *
         * @param systems collection of IEcsSystem instances to attach.
         * @returns A reference to this to allow method chaining.
         */
        [[nodiscard]] inline Configurator& WithSystems(
            std::initializer_list<std::shared_ptr<IEcsSystem>>&& systems) noexcept
        {
            for (auto&& system : systems)
            {
                _iecsSystems.emplace_back(system);
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
        template <typename TNewGraphicsBackend>
        [[nodiscard]] Configurator<TNewGraphicsBackend> WithPluginProvider(
            std::shared_ptr<PluginManagement::IGraphicsPluginProvider<TNewGraphicsBackend>> pluginInstance)
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
        [[nodiscard]] Configurator& WithPluginProvider(
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
        [[nodiscard]] Configurator& WithPluginProvider(
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
        [[nodiscard]] Configurator& WithPluginProvider(
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
         * @tparam Names List of the names to used for type serialisation.
         * @param deleteInstructionStatesAndSerialisedTypeNames The state of the given component type that signals this
         * component is to be, accompanied by the serialised type name. deleted to the ECS.
         * @returns An instance of the ECS SystemScheduler root object based on the provided configuration.
         */
        template<typename... TComponentTypes>
        [[nodiscard]] SystemScheduler InitialiseAndRegisterComponents(
            std::tuple<TComponentTypes, std::string>... deleteInstructionStatesAndSerialisedTypeNames)
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

            for (auto&& iecsSystem : _iecsSystems)
            {
                scheduler.RegisterSystem(iecsSystem);
            }

            scheduler.GetComponentCache().RegisterComponentType<TComponentTypes...>(
                std::get<0>(deleteInstructionStatesAndSerialisedTypeNames)...,
                std::get<1>(deleteInstructionStatesAndSerialisedTypeNames)...);
            scheduler.SpinThreads();

            return scheduler;
        }

        /**
         * @brief Creates the ECS instance and registers component types to it.
         * This is the final method you should call to obtain the ECS instance.
         *
         * @returns An instance of the ECS SystemScheduler based on the provided configuration.
         */
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

            for (auto&& iecsSystem : _iecsSystems)
            {
                scheduler.RegisterSystem(iecsSystem);
            }

            scheduler.SpinThreads();

            return scheduler;
        }
    };
}

#endif // NOVELRT_ECS_CONFIGURATOR_H
