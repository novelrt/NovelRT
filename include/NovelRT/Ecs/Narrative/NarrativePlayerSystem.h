// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NARRATIVEPLAYERSYSTEM_H
#define NOVELRT_NARRATIVEPLAYERSYSTEM_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Narrative
{
    class NarrativePlayerSystem final : public IEcsSystem
    {
    private:
        fabulist::runtime::runtime _runtime;
        std::optional<fabulist::runtime::story> _storyInstance;
        std::optional<fabulist::runtime::state> _storyInstanceState;
        std::optional<fabulist::runtime::state::state_update> _lastUpdatedState;
        std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> _resourceLoaderPluginProvider;
        EntityId _narrativeStoryStateTrackerEntityId;

        void BeginPlay(ComponentView<RequestNarrativeScriptExecutionComponent>& requestView);
    
    public:
        explicit NarrativePlayerSystem(std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceLoaderPluginProvider) noexcept;

        void Update(Timing::Timestamp delta, Catalogue catalogue) final;
    };
}

#endif // NOVELRT_NARRATIVEPLAYERSYSTEM_H