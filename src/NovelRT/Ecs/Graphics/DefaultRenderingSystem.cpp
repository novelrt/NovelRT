// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>
#include <NovelRT/Experimental/Graphics/Graphics.h>

namespace NovelRT::Ecs::Graphics
{
    DefaultRenderingSystem::DefaultRenderingSystem(
        std::shared_ptr<PluginManagement::IGraphicsPluginProvider> graphicsPluginProvider,
        std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingPluginProvider,
        std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceManagementPluginProvider)
        : _resourceManager([&]() { return Experimental::Graphics::GraphicsResourceManager(_graphicsDevice); }),
          _graphicsPluginProvider(std::move(graphicsPluginProvider)),
          _windowingPluginProvider(std::move(windowingPluginProvider)),
          _resourceManagementPluginProvider(std::move(resourceManagementPluginProvider))
    {
        _windowingPluginProvider->GetWindowingDevice()->Initialise(Windowing::WindowMode::Windowed,
                                                                   Maths::GeoVector2F(400, 400));

        EngineConfig::EnableDebugOutputFromEngineInternals() = true;
        EngineConfig::MinimumInternalLoggingLevel() = LogLevel::Warn;

        _surfaceContext = _graphicsPluginProvider->CreateSurfaceContext(_windowingPluginProvider->GetWindowingDevice());
        _graphicsAdapter = _graphicsPluginProvider->GetDefaultSelectedGraphicsAdapterForContext(_surfaceContext);
        _graphicsDevice = _graphicsAdapter->CreateDevice(_surfaceContext, 2);

        auto resourceLoader = _resourceManagementPluginProvider->GetResourceLoader();
        auto vertShaderData = resourceLoader->LoadShaderSource("vert.spv");
        auto pixelShaderData = resourceLoader->LoadShaderSource("frag.spv");

        _elements = {Experimental::Graphics::GraphicsPipelineInputElement(
                         typeid(NovelRT::Maths::GeoVector3F),
                         Experimental::Graphics::GraphicsPipelineInputElementKind::Position, 12),
                     Experimental::Graphics::GraphicsPipelineInputElement(
                         typeid(NovelRT::Maths::GeoVector2F),
                         Experimental::Graphics::GraphicsPipelineInputElementKind::TextureCoordinate, 8)};

        _inputs = {Experimental::Graphics::GraphicsPipelineInput(_elements)};

        _resources = {Experimental::Graphics::GraphicsPipelineResource(
            Experimental::Graphics::GraphicsPipelineResourceKind::Texture,
            Experimental::Graphics::ShaderProgramVisibility::Pixel)};

        auto vertexShaderProgram = _graphicsDevice->CreateShaderProgram(
            "main", Experimental::Graphics::ShaderProgramKind::Vertex, vertShaderData);
        auto pixelShaderProgram = _graphicsDevice->CreateShaderProgram(
            "main", Experimental::Graphics::ShaderProgramKind::Pixel, pixelShaderData);
        auto signature = _graphicsDevice->CreatePipelineSignature(
            Experimental::Graphics::GraphicsPipelineBlendFactor::SrcAlpha,
            Experimental::Graphics::GraphicsPipelineBlendFactor::OneMinusSrcAlpha, _inputs, _resources);
        auto pipeline = _graphicsDevice->CreatePipeline(signature, vertexShaderProgram, pixelShaderProgram);

        auto graphicsContext = _graphicsDevice->GetCurrentContext();

        graphicsContext->BeginFrame();
        auto pVertexBuffer = std::vector<TexturedVertexTest>{
            TexturedVertexTest{Maths::GeoVector3F(-1, 1, 0), Maths::GeoVector2F(0.0f, 0.0f)},
            TexturedVertexTest{Maths::GeoVector3F(1, 1, 0), Maths::GeoVector2F(1.0f, 0.0f)},
            TexturedVertexTest{Maths::GeoVector3F(1, -1, 0), Maths::GeoVector2F(1.0f, 1.0f)},
            TexturedVertexTest{Maths::GeoVector3F(1, -1, 0), Maths::GeoVector2F(1.0f, 1.0f)},
            TexturedVertexTest{Maths::GeoVector3F(-1, -1, 0), Maths::GeoVector2F(0.0f, 1.0f)},
            TexturedVertexTest{Maths::GeoVector3F(-1, 1, 0), Maths::GeoVector2F(0.0f, 0.0f)}};

        auto& resourceManager = _resourceManager.getActual();
        auto vertexBufferRegion = resourceManager.LoadVertexData(gsl::span<TexturedVertexTest>(pVertexBuffer));

        auto texture = resourceLoader->LoadTexture("novel-chan.png");

        auto texture2DRegion =
            resourceManager.LoadTextureData(texture, Experimental::Graphics::GraphicsTextureAddressMode::ClampToEdge,
                                            Experimental::Graphics::GraphicsTextureKind::TwoDimensional);

        std::vector<Experimental::Graphics::GraphicsMemoryRegion<Experimental::Graphics::GraphicsResource>>
            inputResourceRegions{texture2DRegion};

        auto dummyRegion = Experimental::Graphics::GraphicsMemoryRegion<Experimental::Graphics::GraphicsResource>(
            0, nullptr, _graphicsDevice, false, 0, 0);

        _primitive = _graphicsDevice->CreatePrimitive(pipeline, vertexBufferRegion, sizeof(TexturedVertexTest),
                                                      dummyRegion, 0, inputResourceRegions);
        graphicsContext->EndFrame();
        _graphicsDevice->Signal(graphicsContext->GetFence());
        _graphicsDevice->WaitForIdle();
    }

    void DefaultRenderingSystem::Update(Timing::Timestamp /*delta*/, Ecs::Catalogue /*catalogue*/)
    {
        auto context = _graphicsDevice->GetCurrentContext();
        context->BeginFrame();
        context->BeginDrawing(NovelRT::Graphics::RGBAColour(0, 0, 255, 255));
        context->Draw(_primitive);
        context->EndDrawing();
        context->EndFrame();
        _graphicsDevice->PresentFrame();
        _graphicsDevice->WaitForIdle();
    }
}
