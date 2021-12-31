// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <memory>

using namespace NovelRT::Experimental::Input::Glfw;
using namespace NovelRT::Experimental::Input;

using namespace NovelRT::Ecs;
using namespace NovelRT::PluginManagement;

NovelRT::Utilities::Event<NovelRT::Timing::Timestamp> DummyUpdateStuff;

int main()
{
    DefaultPluginSelector selector;
    auto windowingProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IWindowingPluginProvider>();

    auto scheduler =
        Configurator()
            .WithDefaultSystemsAndComponents()
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IGraphicsPluginProvider>())
            .WithPluginProvider(windowingProvider)
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IResourceManagementPluginProvider>())
            .InitialiseAndRegisterComponents();

    std::shared_ptr<NovelRT::Ecs::Graphics::DefaultRenderingSystem> renderingSystem =
        scheduler.GetRegisteredIEcsSystemAs<NovelRT::Ecs::Graphics::DefaultRenderingSystem>();

    NovelRT::Experimental::Threading::FutureResult<NovelRT::Ecs::Graphics::TextureInfo> textureFuture =
        renderingSystem->GetOrLoadTexture("novel-chan");

    renderingSystem->ForceVertexTextureFutureResolution();

    // unused(renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(),
    // scheduler));

    auto transformBuffer = scheduler.GetComponentCache().GetComponentBuffer<TransformComponent>();
    auto entityGraphBuffer = scheduler.GetComponentCache().GetComponentBuffer<EntityGraphComponent>();

    EntityId parentEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    EntityId childEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    transformBuffer.PushComponentUpdateInstruction(0, childEntity, TransformComponent{ NovelRT::Maths::GeoVector3F(200, 200, 0), NovelRT::Maths::GeoVector2F::zero(), 0 });

    entityGraphBuffer.PushComponentUpdateInstruction(0, childEntity, EntityGraphComponent{parentEntity, 0});

    scheduler.RegisterSystem(
        [](auto delta, auto catalogue)
        {
            ComponentView<TransformComponent> transforms = catalogue.GetComponentView<TransformComponent>();

            for (auto [entity, transform] : transforms)
            {
                TransformComponent newComponent{};
                newComponent.rotationInEulerAngles = 20 * delta.getSecondsFloat();
                transforms.PushComponentUpdateInstruction(entity, newComponent);
            }
        });

    scheduler.GetComponentCache().PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    //Input begins here
    auto input = GlfwInputService();
    auto logger = NovelRT::LoggingService();
    auto windowPtr = windowingProvider->GetWindowingDevice();
    input.Initialise(reinterpret_cast<void*>(windowPtr->GetHandle()));
    InputAction space = input.AddInputAction("Jump", "Space");

    DummyUpdateStuff += [&](auto delta) {
        input.Update(delta);
        if (input.IsKeyHeld("Jump"))
        {
           logger.logInfo("Action: {}, Key: {}, State: Held", space.actionName, space.pairedKey.GetKeyName());
        }
        else if (input.IsKeyPressed("Jump"))
        {
            logger.logInfo("Action: {}, Key: {}, State: Pressed", space.actionName, space.pairedKey.GetKeyName());
        }

        scheduler.ExecuteIteration(delta);
    };

    NovelRT::Timing::StepTimer timer;

    while (!windowPtr->GetShouldClose())
    {
        windowPtr->ProcessAllMessages();
        timer.tick(DummyUpdateStuff);
        auto t = timer.getFrameCount();
        logger.logInfo("Frame count: {}", t);
    }


    return 0;
}
