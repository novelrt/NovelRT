// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::UI
{
    UISystem::UISystem(std::shared_ptr<PluginManagement::IUIPluginProvider> uiPluginProvider,
                       std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingPluginProvider,
                       std::shared_ptr<PluginManagement::IGraphicsPluginProvider> graphicsPluginProvider,
                       std::shared_ptr<PluginManagement::IInputPluginProvider> inputPluginProvider)
        : _uiProvider(uiPluginProvider->GetUIProvider())
    {
        _uiProvider->Initialise(windowingPluginProvider->GetWindowingDevice(),
                                graphicsPluginProvider->GetGraphicsProvider(), inputPluginProvider->GetInputService());
    }

    void UISystem::Update(Timing::Timestamp delta, Ecs::Catalogue catalogue)
    {
        UNREFERENCED_PARAMETER(catalogue);

        _uiProvider->BeginFrame(delta.getSecondsDouble());
        _uiProvider->EndFrame();
    }
}
