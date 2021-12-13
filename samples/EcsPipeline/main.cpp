// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <random>

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

    scheduler.RegisterSystem([](auto delta, auto catalogue)
                             {
                                 ComponentView<TransformComponent> transforms = catalogue.GetComponentView<TransformComponent>();

                                 for (auto [entity, transform] : transforms)
                                 {
                                     TransformComponent newComponent{};
                                     newComponent.rotationInEulerAngles = 20 * delta.getSecondsFloat();
                                     transforms.PushComponentUpdateInstruction(entity, newComponent);
                                 }
                             });

    std::shared_ptr<NovelRT::Ecs::Graphics::DefaultRenderingSystem> renderingSystem =
        scheduler.GetRegisteredIEcsSystemAs<NovelRT::Ecs::Graphics::DefaultRenderingSystem>();

    NovelRT::Experimental::Threading::FutureResult<NovelRT::Ecs::Graphics::TextureInfo> textureFuture = renderingSystem->GetOrLoadTexture("novel-chan");

    renderingSystem->ForceVertexTextureFutureResolution();

    //unused(renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler));

    auto buffer = scheduler.GetComponentCache().GetComponentBuffer<TransformComponent>();

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-1000, +1000); // define the range

    float x = 0;
    float y = 0;
    for (int i = 0; i < 1000; ++i)
    {
        EntityId entityToShift = renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);
        buffer.PushComponentUpdateInstruction(0, entityToShift, TransformComponent{NovelRT::Maths::GeoVector3F(distr(gen), distr(gen), 0), 0.0f});
    }

    scheduler.GetComponentCache().PrepAllBuffersForNextFrame(std::vector<EntityId>{});


    DummyUpdateStuff += [&](auto delta) { scheduler.ExecuteIteration(delta); };

    NovelRT::Timing::StepTimer timer;

    auto windowPtr = windowingProvider->GetWindowingDevice();

    while (!windowPtr->GetShouldClose())
    {
        windowPtr->ProcessAllMessages();
        timer.tick(DummyUpdateStuff);
    }

    return 0;
}
