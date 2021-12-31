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
    InputAction up = input.AddInputAction("Up", "W");
    InputAction down = input.AddInputAction("Down", "S");
    InputAction left = input.AddInputAction("Left", "A");
    InputAction right = input.AddInputAction("Right", "D");
    InputAction fire = input.AddInputAction("Fire", "LeftMouseButton");
    NovelRT::Maths::GeoVector2F pos = NovelRT::Maths::GeoVector2F::zero();

    std::string output = "Mouse Position: {}, {} / Buttons Pressed: ";
    bool outputLine = false;

    DummyUpdateStuff += [&](auto delta) {
        input.Update(delta);
        pos = input.GetMousePosition();

        if (input.IsKeyPressed("Up"))
        {
            output.append("Up, ");
            outputLine = true;
        }
        if (input.IsKeyPressed("Down"))
        {
            output.append("Down, ");
            outputLine = true;
        }
        if (input.IsKeyPressed("Left"))
        {
            output.append("Left, ");
            outputLine = true;
        }
        if (input.IsKeyPressed("Right"))
        {
            output.append("Right, ");
            outputLine = true;
        }
        if (input.IsKeyPressed("Jump"))
        {
            output.append("Jump, ");
            outputLine = true;
        }
        if (input.IsKeyPressed("Fire"))
        {
            output.append("Fire");
            outputLine = true;
        }

        scheduler.ExecuteIteration(delta);
        if(outputLine)
        {
            outputLine = false;
            logger.logInfo(output, pos.x, pos.y);
            output.clear();
            output = "Mouse Position: {}, {} / Buttons Pressed: ";
        }
    };

    NovelRT::Timing::StepTimer timer;

    while (!windowPtr->GetShouldClose())
    {
        windowPtr->ProcessAllMessages();
        timer.tick(DummyUpdateStuff);
        //auto t = timer.getFrameCount();
        //logger.logInfo("Frame count: {}", t);
    }


    return 0;
}
