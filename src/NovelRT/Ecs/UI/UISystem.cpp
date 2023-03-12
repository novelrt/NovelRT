// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::UI
{
    UISystem::UISystem(std::shared_ptr<NovelRT::PluginManagement::IUIPluginProvider> uiPluginProvider,
        std::shared_ptr<NovelRT::Ecs::Input::InputSystem> inputSystem,
        std::shared_ptr<NovelRT::Ecs::Graphics::DefaultRenderingSystem> renderingSystem,
        std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader> resourceLoader):
        _uiProvider(std::move(uiPluginProvider->GetUIProvider())))
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
        auto uiPanels = catalogue.GetComponentView<NovelRT::UI::UIPanel>();
        _uiProvider->Update();
        unused(delta);

        for(auto [entity, panel] : uiPanels)
        {
            LinkedEntityListView view(panel.RootElementId, catalogue);
            _uiProvider->GeneratePanelCommand(panel, view);
        }

        _uiProvider->CommandListFinished() = true;
    }


    NovelRT::UI::UIText UISystem::CreateTextElement(Ecs::SystemScheduler& scheduler, NovelRT::UI::UIPanel& panel)
    {
        NovelRT::UI::UIText text = NovelRT::UI::UIText{};
        Ecs::Catalogue catalogue(0, scheduler.GetComponentCache(), scheduler.GetEntityCache());
        EntityId id = catalogue.CreateEntity();
        text.Entity = id;
        LinkedEntityListView view(panel.RootElementId, catalogue);
        catalogue.GetComponentView<NovelRT::UI::UIText>().PushComponentUpdateInstruction(id, text);
        view.AddInsertAtBackInstruction(id);
        return text;
    }
}
