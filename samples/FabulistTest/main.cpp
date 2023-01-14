// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::PluginManagement;

NovelRT::Utilities::Event<NovelRT::Timing::Timestamp> DummyUpdateStuff;

int main()
{
    DefaultPluginSelector selector;
    auto windowingProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IWindowingPluginProvider>();

    NovelRT::LoggingService logger = NovelRT::LoggingService();
    logger.setLogLevel(NovelRT::LogLevel::Info);

    NovelRT::EngineConfig::EnableEditorMode() = true;

    auto scheduler =
        Configurator()
            .WithDefaultSystemsAndComponents()
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IGraphicsPluginProvider>())
            .WithPluginProvider(windowingProvider)
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IUIPluginProvider>())
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IResourceManagementPluginProvider>())
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IInputPluginProvider>())
            .InitialiseAndRegisterComponents();

    std::shared_ptr<NovelRT::Ecs::UI::UISystem> ui = scheduler.GetRegisteredIEcsSystemAs<NovelRT::Ecs::UI::UISystem>();
    auto uiProvider = ui->GetProvider();
    std::stringstream ss;
    ss << "Fabulist runtime " << fabulist::runtime::get_version_string() << "\n";
    ss << "Application average " << 1000.0f / ImGui::GetIO().Framerate << "ms/frame (" << ImGui::GetIO().Framerate <<
        " FPS)" << std::endl;
    //ss << windowingProvider->GetWindowingDevice()->GetWidth() << ", " << windowingProvider->GetWindowingDevice()->GetHeight() << "\n";
    auto textbox = uiProvider->CreateTextbox("fabulist-text", ss.str(), false,
        NovelRT::Maths::GeoVector2F(0, 300), NovelRT::Maths::GeoVector2F(540, 216), 16.0f);
    auto namebox = uiProvider->CreateTextbox("fabulist-name", "Fabulist", false,
        NovelRT::Maths::GeoVector2F(0, 0), NovelRT::Maths::GeoVector2F(186, 32), 18.0f);
    textbox->State() = NovelRT::UI::UIElementState::Shown;
    namebox->State() = NovelRT::UI::UIElementState::Shown;
    namebox->BackgroundColour() = NovelRT::Graphics::RGBAColour(255, 0, 0, 255);

    std::shared_ptr<NovelRT::Ecs::Graphics::DefaultRenderingSystem> renderingSystem =
        scheduler.GetRegisteredIEcsSystemAs<NovelRT::Ecs::Graphics::DefaultRenderingSystem>();

    NovelRT::Threading::FutureResult<NovelRT::Ecs::Graphics::TextureInfo> textureFuture =
        renderingSystem->GetOrLoadTexture("novel-chan");

    renderingSystem->ForceVertexTextureFutureResolution();

    auto transformBuffer = scheduler.GetComponentCache().GetComponentBuffer<TransformComponent>();
    auto entityGraphBuffer = scheduler.GetComponentCache().GetComponentBuffer<EntityGraphComponent>();

    EntityId parentEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    EntityId childEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    EntityId childOfChildEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    transformBuffer.PushComponentUpdateInstruction(
        0, childEntity,
        TransformComponent{NovelRT::Maths::GeoVector3F(200, 200, 0), NovelRT::Maths::GeoVector2F::Zero(), 0});
    transformBuffer.PushComponentUpdateInstruction(
        0, childOfChildEntity,
        TransformComponent{NovelRT::Maths::GeoVector3F(200, 200, 0), NovelRT::Maths::GeoVector2F::Zero(), 0});
    entityGraphBuffer.PushComponentUpdateInstruction(0, childEntity, EntityGraphComponent{true, parentEntity, 0});
    entityGraphBuffer.PushComponentUpdateInstruction(0, childOfChildEntity, EntityGraphComponent{true, childEntity, 0});

    scheduler.RegisterSystem([](auto delta, auto catalogue) {
        ComponentView<TransformComponent> transforms = catalogue.template GetComponentView<TransformComponent>();

        for (auto [entity, transform] : transforms)
        {
            TransformComponent newComponent{};
            newComponent.rotationInRadians = NovelRT::Maths::Utilities::DegreesToRadians(20 * delta.getSecondsFloat());
            newComponent.scale = NovelRT::Maths::GeoVector2F::Zero();
            transforms.PushComponentUpdateInstruction(entity, newComponent);
        }
    });

    scheduler.GetComponentCache().PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    DummyUpdateStuff += [&](auto delta) { scheduler.ExecuteIteration(delta); };

    NovelRT::Timing::StepTimer timer;

    auto windowPtr = windowingProvider->GetWindowingDevice();
    windowPtr->SetWindowTitle("Fabulist Test");

    while (!windowPtr->GetShouldClose())
    {
        windowPtr->ProcessAllMessages();
        timer.tick(DummyUpdateStuff);
        ss.str(std::string());
        ss << "Application average " << 1000.0f / ImGui::GetIO().Framerate << "ms/frame (" << ImGui::GetIO().Framerate
           << " FPS)" << std::endl;
        textbox->Text() = ss.str();
    }

    return 0;
}
