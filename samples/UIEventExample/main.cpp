// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <memory>
#include <imgui.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Input;
using namespace NovelRT::PluginManagement;

NovelRT::Utilities::Event<NovelRT::Timing::Timestamp> DummyUpdateStuff;

int main()
{
    NovelRT::LoggingService logger = NovelRT::LoggingService();
    logger.setLogLevel(NovelRT::LogLevel::Info);

    DefaultPluginSelector selector;
    auto uiProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IUIPluginProvider>();
    auto windowingProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IWindowingPluginProvider>();
    auto inputProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IInputPluginProvider>();
    auto scheduler =
        Configurator()
            .WithDefaultSystemsAndComponents()
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IGraphicsPluginProvider>())
            .WithPluginProvider(uiProvider)
            .WithPluginProvider(windowingProvider)
            .WithPluginProvider(inputProvider)
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IResourceManagementPluginProvider>())
            .InitialiseAndRegisterComponents();

    std::shared_ptr<NovelRT::Ecs::Graphics::DefaultRenderingSystem> renderingSystem =
        scheduler.GetRegisteredIEcsSystemAs<NovelRT::Ecs::Graphics::DefaultRenderingSystem>();

    using namespace NovelRT::Threading;
    using namespace NovelRT::Ecs;
    using namespace NovelRT::Ecs::Graphics;

    FutureResult<VertexInfo> squareVertexFuture(nullptr, VertexInfo{});
    FutureResult<TextureInfo> redTextureFuture(nullptr, TextureInfo{});

    scheduler.RegisterSystem([&](auto delta, auto catalogue) {
        if (!squareVertexFuture.IsValid())
        {
            auto pVertexBuffer = std::vector<TexturedVertex>{
                TexturedVertex{NovelRT::Maths::GeoVector3F(-0.5, +0.5, 0), NovelRT::Maths::GeoVector2F(0.0f, 0.0f)},
                TexturedVertex{NovelRT::Maths::GeoVector3F(+0.5, +0.5, 0), NovelRT::Maths::GeoVector2F(1.0f, 0.0f)},
                TexturedVertex{NovelRT::Maths::GeoVector3F(+0.5, -0.5, 0), NovelRT::Maths::GeoVector2F(1.0f, 1.0f)},
                TexturedVertex{NovelRT::Maths::GeoVector3F(+0.5, -0.5, 0), NovelRT::Maths::GeoVector2F(1.0f, 1.0f)},
                TexturedVertex{NovelRT::Maths::GeoVector3F(-0.5, -0.5, 0), NovelRT::Maths::GeoVector2F(0.0f, 1.0f)},
                TexturedVertex{NovelRT::Maths::GeoVector3F(-0.5, +0.5, 0), NovelRT::Maths::GeoVector2F(0.0f, 0.0f)}};

            squareVertexFuture = renderingSystem->LoadVertexDataRaw<TexturedVertex>("exampleVert", pVertexBuffer);
        }

        if (!redTextureFuture.IsValid())
        {
            uint32_t colourValue = 0xFF0000FF;
            auto pTextureData = std::vector<uint32_t>();
            pTextureData.reserve(10000);

            for (size_t i = 0; i < 10000; i++)
            {
                pTextureData.emplace_back(colourValue);
            }

            redTextureFuture = renderingSystem->LoadTextureDataRaw<uint32_t>("exampleTex", pTextureData, 100, 100);
        }
    });

    std::vector<NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>> inputResourceRegions{};
    std::optional<NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>> transformRegion;

    // we cache the primitive here so its kept alive long enough so that Vulkan can execute the relevant cmd lists
    std::shared_ptr<NovelRT::Graphics::GraphicsPrimitive> primitive = nullptr;

    renderingSystem->UIRenderEvent += [&](auto system, DefaultRenderingSystem::UIRenderEventArgs args) {
        ImGui::Begin("Hello, Novel-Chan");
        ImGui::End();
    };

    scheduler.GetComponentCache().PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    NovelRT::Timing::StepTimer timer;

    auto windowPtr = windowingProvider->GetWindowingDevice();
    windowPtr->SetWindowTitle("UI Test");

    DummyUpdateStuff += [&](auto delta) { scheduler.ExecuteIteration(delta); };
    while (!windowPtr->GetShouldClose())
    {
        windowPtr->ProcessAllMessages();
        timer.tick(DummyUpdateStuff);
    }

    return 0;
}
