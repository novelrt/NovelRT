// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::UI
{
    UISystem::UISystem(std::shared_ptr<NovelRT::PluginManagement::IUIPluginProvider> uiPluginProvider,
        std::shared_ptr<NovelRT::Ecs::Graphics::DefaultRenderingSystem> renderingSystem):
        _uiProvider(std::move(uiPluginProvider->GetUIProvider()))
    {
        _uiProvider->Initialise(renderingSystem->GetCurrentGraphicsDevice(),
            renderingSystem->GetCurrentWindowingPluginProvider()->GetWindowingDevice(),
            renderingSystem->GetCurrentGraphicsProvider(),
            renderingSystem->GetExistingDefaultPipelineInfo()->gpuPipeline.GetUnderlyingSharedPtr());

        renderingSystem->UIRenderEvent += [&](auto system, NovelRT::Ecs::Graphics::DefaultRenderingSystem::UIRenderEventArgs args)
        {
            unused(system);
            _uiProvider->Begin();

            _uiProvider->UIEvent(*_uiProvider);

            _uiProvider->End(args.graphicsDevice->GetCurrentContext());
        };
    }

    void UISystem::Update(Timing::Timestamp delta, Ecs::Catalogue catalogue)
    {
        unused(delta);
        unused(catalogue);
    }
}
