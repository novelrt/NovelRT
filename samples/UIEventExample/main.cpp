// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <memory>

#include <NovelRT/Graphics/Vulkan/VulkansGraphicsBackendTraits.hpp>

using namespace NovelRT::Ecs;
using namespace NovelRT::Input;
using namespace NovelRT::PluginManagement;

NovelRT::Utilities::Event<NovelRT::Timing::Timestamp> DummyUpdateStuff;

int main()
{
    NovelRT::LoggingService logger = NovelRT::LoggingService();
    logger.setLogLevel(NovelRT::LogLevel::Info);

    DefaultPluginSelector selector;
    auto windowingProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IWindowingPluginProvider>();
    auto inputProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IInputPluginProvider>();
    auto scheduler =
        Configurator<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>()
            .WithDefaultSystemsAndComponents()
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<
                                IGraphicsPluginProvider<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>>())
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

            redTextureFuture =
                renderingSystem->LoadTextureDataRaw<uint32_t>("exampleTex", pTextureData, 100, 100, uuids::uuid{});
        }
    });

    std::vector<NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>> inputResourceRegions{};
    std::optional<NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>> transformRegion;

    // we cache the primitive here so its kept alive long enough so that Vulkan can execute the relevant cmd lists
    std::shared_ptr<NovelRT::Graphics::GraphicsPrimitive> primitive = nullptr;

    renderingSystem->UIRenderEvent += [&](auto system, DefaultRenderingSystem::UIRenderEventArgs args) {
        inputResourceRegions.clear();
        if (!squareVertexFuture.IsValid() || !squareVertexFuture.IsValueCreated())
        {
            return;
        }

        if (!redTextureFuture.IsValid() || !redTextureFuture.IsValueCreated())
        {
            return;
        }

        auto dummyRegion = NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>(
            0, nullptr, args.graphicsDevice, false, 0, 0);

        auto& systemRef = system.get();
        auto pipeline = systemRef.GetExistingPipelineInfo("default");

        if (!transformRegion.has_value())
        {
            // this is the quickest way to get the constant buffer region that the shader expects since we don't rely on
            // ECS transform data here.
            transformRegion =
                args.resourceManager.AllocateConstantBufferRegion(sizeof(NovelRT::Maths::GeoMatrix4x4F) * 1000);
            auto ptr = args.resourceManager.MapConstantBufferRegionForWriting<NovelRT::Maths::GeoMatrix4x4F>(
                transformRegion.value());

            // im only adding 3 transforms for this example.
            auto matrixToInsert = NovelRT::Maths::GeoMatrix4x4F::GetDefaultIdentity();
            matrixToInsert.Translate(NovelRT::Maths::GeoVector3F(0, 250, 0));
            matrixToInsert.Scale(NovelRT::Maths::GeoVector2F::Uniform(500));
            ptr[0] = matrixToInsert;
            matrixToInsert = NovelRT::Maths::GeoMatrix4x4F::GetDefaultIdentity();
            matrixToInsert.Translate(NovelRT::Maths::GeoVector3F(700, -300, 0));
            matrixToInsert.Scale(NovelRT::Maths::GeoVector2F::Uniform(500));
            ptr[1] = matrixToInsert;
            matrixToInsert = NovelRT::Maths::GeoMatrix4x4F::GetDefaultIdentity();
            matrixToInsert.Translate(NovelRT::Maths::GeoVector3F(700, 250, 0));
            matrixToInsert.Scale(NovelRT::Maths::GeoVector2F::Uniform(500));
            ptr[2] = matrixToInsert;

            args.resourceManager.UnmapAndWriteAllConstantBuffers();
        }

        inputResourceRegions.emplace_back(args.frameMatrixConstantBufferRegion);
        inputResourceRegions.emplace_back(transformRegion.value());

        // nothing else will touch this so we can just access the concurrent pointer in this example without a lock.
        // Usually you'd need a std::scoped_guard however.
        inputResourceRegions.emplace_back(redTextureFuture.GetValue().gpuTextureRegion);

        primitive = args.graphicsDevice->CreatePrimitive(pipeline->gpuPipeline.GetUnderlyingSharedPtr(),
                                                         squareVertexFuture.GetValue().gpuVertexRegion,
                                                         sizeof(TexturedVertex), dummyRegion, 0, inputResourceRegions);
        args.graphicsContext->Draw(primitive, 3);
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
