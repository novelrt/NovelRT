// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_UI_UISYSTEM_H
#define NOVELRT_ECS_UI_UISYSTEM_H

#ifndef NOVELRT_ECS_UI_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.UI.h instead for the Ecs.UI namespace subset.
#endif

namespace NovelRT::Ecs::UI
{
    class UISystem : public Ecs::IEcsSystem
    {
    private:
        LoggingService _logger;
        std::shared_ptr<NovelRT::UI::UIProvider> _uiProvider;

    public:
        UISystem(std::shared_ptr<PluginManagement::IUIPluginProvider> uiPluginProvider,
                 std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingPluginProvider,
                 std::shared_ptr<PluginManagement::IGraphicsPluginProvider> graphicsPluginProvider,
                 std::shared_ptr<PluginManagement::IInputPluginProvider> inputPluginProvider);

        void Update(Timing::Timestamp delta, Ecs::Catalogue catalogue) final;
    };
}

#endif // NOVELRT_ECS_INPUT_INPUTSYSTEM_H
