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
        : _graphicsPluginProvider(std::move(graphicsPluginProvider)),
          _windowingPluginProvider(std::move(windowingPluginProvider)),
          _resourceManagementPluginProvider(std::move(resourceManagementPluginProvider))
    {
        _windowingPluginProvider->GetWindowingDevice()->Initialise(Windowing::WindowMode::Windowed,
                                                                   Maths::GeoVector2F(400, 400));

        EngineConfig::EnableDebugOutputFromEngineInternals() = true;
        EngineConfig::MinimumInternalLoggingLevel() = LogLevel::Warn;

        _surfaceContext = _graphicsPluginProvider->CreateSurfaceContext(_windowingPluginProvider->GetWindowingDevice());
        _graphicsAdapter = _graphicsPluginProvider->GetDefaultSelectedGraphicsAdapterForContext(_surfaceContext);
        _graphicsDevice = _graphicsAdapter->CreateDevice(_surfaceContext, 1);

        auto resourceLoader = _resourceManagementPluginProvider->GetResourceLoader();
        auto vertShaderData = resourceLoader->LoadShaderSource("vert.spv");
        auto pixelShaderData = resourceLoader->LoadShaderSource("frag.spv");

        _elements = {
            Experimental::Graphics::GraphicsPipelineInputElement(
                typeid(NovelRT::Maths::GeoVector3F), Experimental::Graphics::GraphicsPipelineInputElementKind::Position,
                12),
            Experimental::Graphics::GraphicsPipelineInputElement(
                typeid(NovelRT::Maths::GeoVector2F),
                Experimental::Graphics::GraphicsPipelineInputElementKind::TextureCoordinate, 8)};

        _inputs = {
            Experimental::Graphics::GraphicsPipelineInput(_elements)};

        _resources = {
            Experimental::Graphics::GraphicsPipelineResource(
                Experimental::Graphics::GraphicsPipelineResourceKind::Texture,
                Experimental::Graphics::ShaderProgramVisibility::Pixel)};

        auto vertexShaderProgram = _graphicsDevice->CreateShaderProgram(
            "main", Experimental::Graphics::ShaderProgramKind::Vertex, vertShaderData);
        auto pixelShaderProgram = _graphicsDevice->CreateShaderProgram(
            "main", Experimental::Graphics::ShaderProgramKind::Pixel, pixelShaderData);
        auto signature = _graphicsDevice->CreatePipelineSignature(_inputs, _resources);
        auto pipeline = _graphicsDevice->CreatePipeline(signature, vertexShaderProgram, pixelShaderProgram);
        _vertexBuffer = _graphicsDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
            Experimental::Graphics::GraphicsBufferKind::Vertex, Experimental::Graphics::GraphicsResourceAccess::None,
            Experimental::Graphics::GraphicsResourceAccess::Write, 64 * 1024);
        _vertexStagingBuffer = _graphicsDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
            Experimental::Graphics::GraphicsBufferKind::Default, Experimental::Graphics::GraphicsResourceAccess::Write,
            Experimental::Graphics::GraphicsResourceAccess::Read, 64 * 1024);
        _textureStagingBuffer = _graphicsDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
            Experimental::Graphics::GraphicsBufferKind::Default, Experimental::Graphics::GraphicsResourceAccess::Write,
            Experimental::Graphics::GraphicsResourceAccess::Read, 64 * 1024 * 4);

        auto vertexBufferRegion = _vertexBuffer->Allocate(sizeof(TexturedVertexTest) * 3, 16);

        auto graphicsContext = _graphicsDevice->GetCurrentContext();

        _graphicsDevice->Signal(graphicsContext->GetFence());
        graphicsContext->BeginFrame();
        auto pVertexBuffer = _vertexStagingBuffer->Map<TexturedVertexTest>(vertexBufferRegion);

        pVertexBuffer[0] = TexturedVertexTest{Maths::GeoVector3F(0, 1, 0), Maths::GeoVector2F(1.0f, 0.0f)};
        pVertexBuffer[1] = TexturedVertexTest{Maths::GeoVector3F(1, -1, 0), Maths::GeoVector2F(0.0f, 1.0f)};
        pVertexBuffer[2] = TexturedVertexTest{Maths::GeoVector3F(-1, -1, 0), Maths::GeoVector2F(0.0f, 0.0f)};

        _vertexStagingBuffer->UnmapAndWrite(vertexBufferRegion);
        graphicsContext->Copy(_vertexBuffer, _vertexStagingBuffer);

        uint32_t textureWidth = 256;
        uint32_t textureHeight = 256;
        uint32_t texturePixels = textureWidth * textureHeight;
        uint32_t cellWidth = textureWidth / 8;
        uint32_t cellHeight = textureHeight / 8;

        _texture2D = graphicsContext->GetDevice()->GetMemoryAllocator()->CreateTextureWithDefaultArguments(
            Experimental::Graphics::GraphicsTextureKind::TwoDimensional,
            Experimental::Graphics::GraphicsResourceAccess::None, Experimental::Graphics::GraphicsResourceAccess::Write,
            textureWidth, textureHeight);
        auto texture2DRegion = _texture2D->Allocate(_texture2D->GetSize(), 4);
        auto pTextureData = _textureStagingBuffer->Map<uint32_t>(texture2DRegion);

        for (uint32_t n = 0; n < texturePixels; n++)
        {
            auto x = n % textureWidth;
            auto y = n / textureWidth;

            pTextureData[n] = (x / cellWidth % 2) == (y / cellHeight % 2) ? 0xFF000000 : 0xFFFFFFFF;
        }

        _textureStagingBuffer->UnmapAndWrite(texture2DRegion);

        _inputResourceRegions = {texture2DRegion};

        graphicsContext->Copy(_texture2D, _textureStagingBuffer);
        auto dummyRegion = Experimental::Graphics::GraphicsMemoryRegion<Experimental::Graphics::GraphicsResource>(0, nullptr, _graphicsDevice, false, 0, 0);
        _primitive = _graphicsDevice->CreatePrimitive(pipeline, vertexBufferRegion, sizeof(TexturedVertexTest), dummyRegion, 0,
                                                    _inputResourceRegions);
        graphicsContext->EndFrame();
        //_graphicsDevice->Signal(graphicsContext->GetFence());
    }

    void DefaultRenderingSystem::Update(Timing::Timestamp /*delta*/, Ecs::Catalogue /*catalogue*/)
    {
        auto graphicsContext = _graphicsDevice->GetCurrentContext();
        _graphicsDevice->Signal(graphicsContext->GetFence());
        graphicsContext->BeginFrame();
        graphicsContext->BeginDrawing(NovelRT::Graphics::RGBAColour(0, 0, 255, 255));
        graphicsContext->Draw(_primitive);
        graphicsContext->EndDrawing();
        graphicsContext->EndFrame();
        _graphicsDevice->PresentFrame();
        _graphicsDevice->WaitForIdle();
        graphicsContext->GetFence()->Reset();
    }
}
