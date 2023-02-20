// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::UI
{
    UISystem::UISystem(std::shared_ptr<NovelRT::PluginManagement::IUIPluginProvider> uiPluginProvider,
        std::shared_ptr<NovelRT::Ecs::Input::InputSystem> inputSystem,
        std::shared_ptr<NovelRT::Ecs::Graphics::DefaultRenderingSystem> renderingSystem,
        std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader> resourceLoader):
        _uiProvider(std::move(uiPluginProvider->GetUIProvider()))
    {
        _uiProvider->Initialise(resourceLoader, renderingSystem->GetCurrentGraphicsDevice(),
            renderingSystem->GetCurrentWindowingPluginProvider()->GetWindowingDevice(),
            inputSystem->GetInputDevice(),
            renderingSystem->GetCurrentGraphicsProvider(),
            renderingSystem->GetExistingDefaultPipelineInfo()->gpuPipeline.GetUnderlyingSharedPtr());

        renderingSystem->UIRenderEvent += [&](auto system, NovelRT::Ecs::Graphics::DefaultRenderingSystem::UIRenderEventArgs args)
        {
            unused(system);
            _uiProvider->Begin();
            _uiProvider->Render();
            _uiProvider->End(args.graphicsDevice->GetCurrentContext());
        };
    }

    void UISystem::Update(Timing::Timestamp delta, Ecs::Catalogue catalogue)
    {
        unused(delta);
        unused(catalogue);
        _uiProvider->Update();
    }
}
