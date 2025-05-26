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
        std::optional<NovelRT::Ecs::Catalogue> _catalogueForFrame;
        std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> _resourceLoaderPluginProvider;
        std::optional<EntityId> _narrativeStoryStateTrackerEntityId;
        std::optional<EntityId> _choiceMetadataLinkedListEntityId;
        LoggingService _narrativeLoggingService;
        bool _optionSelected;

        [[nodiscard]] bool BeginPlay(ComponentView<RequestNarrativeScriptExecutionComponent>& requestView);
        void DoNarrativeStoryCleanup();

    public:
        explicit NarrativePlayerSystem(
            std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceLoaderPluginProvider) noexcept;
        void Update(Timing::Timestamp delta, Catalogue catalogue) final;
        void RegisterCustomFunction(const std::string& name, fabulist::runtime::runtime::method_type function);
    };
}

#endif // NOVELRT_NARRATIVEPLAYERSYSTEM_H
