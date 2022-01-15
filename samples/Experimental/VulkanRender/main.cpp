// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <memory>

using namespace NovelRT::Experimental::Windowing::Glfw;
using namespace NovelRT::Experimental::Windowing;
using namespace NovelRT::Experimental::Graphics::Vulkan;
using namespace NovelRT::Experimental::Graphics;

std::vector<uint8_t> LoadSpv(std::filesystem::path relativeTarget)
{
    std::filesystem::path finalPath =
        NovelRT::Utilities::Misc::getExecutableDirPath() / "Resources" / "Shaders" / relativeTarget;
    std::ifstream file(finalPath.string(), std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw NovelRT::Exceptions::FileNotFoundException(finalPath.string());
    }

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<uint8_t> buffer(fileSize);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
    file.close();

    return buffer;
}

struct TexturedVertex
{
    NovelRT::Maths::GeoVector3F Position;
    NovelRT::Maths::GeoVector2F UV;
};

int main()
{
    NovelRT::EngineConfig::EnableDebugOutputFromEngineInternals() = false;
    NovelRT::EngineConfig::MinimumInternalLoggingLevel() = NovelRT::LogLevel::Warn;

    auto window = new GlfwWindowingDevice();
    auto device = std::shared_ptr<IWindowingDevice>(window);

    device->Initialise(NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(400, 400));

    auto vulkanProvider = std::make_shared<VulkanGraphicsProvider>();

    VulkanGraphicsAdapterSelector selector;
    std::shared_ptr<VulkanGraphicsSurfaceContext> surfaceContext =
        std::make_shared<VulkanGraphicsSurfaceContext>(device, vulkanProvider);

    std::shared_ptr<GraphicsAdapter> adapter = selector.GetDefaultRecommendedAdapter(vulkanProvider, surfaceContext);

    auto gfxDevice = adapter->CreateDevice(surfaceContext, 2);
    auto graphicsResourceManager = NovelRT::Experimental::Graphics::GraphicsResourceManager(gfxDevice);
    auto gfxContext = gfxDevice->GetCurrentContext();

    auto vertexStagingBuffer = gfxDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
        GraphicsBufferKind::Default, GraphicsResourceAccess::Write, GraphicsResourceAccess::Read, 64 * 1024);
    auto textureStagingBuffer = gfxDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
        GraphicsBufferKind::Default, GraphicsResourceAccess::Write, GraphicsResourceAccess::Read, 64 * 1024 * 4);
    auto vertexBuffer = gfxDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
        GraphicsBufferKind::Vertex, GraphicsResourceAccess::None, GraphicsResourceAccess::Write, 64 * 1024);

    auto vertShaderData = LoadSpv("vert.spv");
    auto pixelShaderData = LoadSpv("frag.spv");

    auto size = device->GetSize();
    float width = size.x;
    float height = size.y;
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    float left = -halfWidth;
    float right = +halfWidth;
    float top = -halfHeight;
    float bottom = +halfHeight;

    auto position = NovelRT::Maths::GeoVector2F::zero();
    auto projectionMatrix = NovelRT::Maths::GeoMatrix4x4F::CreateOrthographic(left, right, bottom, top, 0.1f, 65535.0f);
    auto viewMatrix = NovelRT::Maths::GeoMatrix4x4F::CreateFromLookAt(NovelRT::Maths::GeoVector3F(position.x, position.y, -1.0f),
                                                             NovelRT::Maths::GeoVector3F(position.x, position.y, 0.0f),
                                                             NovelRT::Maths::GeoVector3F(0, -1, 0));

    // This is correct for row-major. :]
    auto frameTransform = viewMatrix * projectionMatrix;
    auto primitiveTransform = NovelRT::Maths::GeoMatrix4x4F::getDefaultIdentity();
    primitiveTransform.Scale(NovelRT::Maths::GeoVector2F(200,200));

    auto frameTransformRegion = graphicsResourceManager.LoadConstantBufferDataToNewRegion(
        &frameTransform, sizeof(NovelRT::Maths::GeoMatrix4x4F));

    auto primitiveTransformRegion = graphicsResourceManager.LoadConstantBufferDataToNewRegion(&primitiveTransform, sizeof(NovelRT::Maths::GeoMatrix4x4F));

    gfxContext->BeginFrame();
    std::vector<GraphicsPipelineInputElement> elements{
        GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector3F), GraphicsPipelineInputElementKind::Position,
                                     12),
        GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F),
                                     GraphicsPipelineInputElementKind::TextureCoordinate, 8)};

    std::vector<GraphicsPipelineInput> inputs{GraphicsPipelineInput(elements)};
//    std::vector<GraphicsPipelineResource> resources{
//        GraphicsPipelineResource(GraphicsPipelineResourceKind::Texture, ShaderProgramVisibility::Pixel)};

    std::vector<GraphicsPipelineResource> resources = {
        GraphicsPipelineResource(
            GraphicsPipelineResourceKind::ConstantBuffer,
            ShaderProgramVisibility::Vertex),

        GraphicsPipelineResource(
            GraphicsPipelineResourceKind::ConstantBuffer,
            ShaderProgramVisibility::Vertex),

        GraphicsPipelineResource(
            GraphicsPipelineResourceKind::Texture,
            ShaderProgramVisibility::Pixel),
    };

    auto signature = gfxDevice->CreatePipelineSignature(
        GraphicsPipelineBlendFactor::SrcAlpha, GraphicsPipelineBlendFactor::OneMinusSrcAlpha, inputs, resources);
    auto vertShaderProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Vertex, vertShaderData);
    auto pixelShaderProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Pixel, pixelShaderData);
    auto pipeline = gfxDevice->CreatePipeline(signature, vertShaderProg, pixelShaderProg);
    auto dummyRegion = GraphicsMemoryRegion<GraphicsResource>(0, nullptr, gfxDevice, false, 0, 0);

    auto vertexBufferRegion = vertexBuffer->Allocate(sizeof(TexturedVertex) * 6, 16);
    
    auto pVertexBuffer = vertexStagingBuffer->Map<TexturedVertex>(vertexBufferRegion);

    pVertexBuffer[0] = TexturedVertex{NovelRT::Maths::GeoVector3F(-0.5, +0.5, 0), NovelRT::Maths::GeoVector2F(0.0f, 0.0f)};
    pVertexBuffer[1] = TexturedVertex{NovelRT::Maths::GeoVector3F(+0.5, +0.5, 0), NovelRT::Maths::GeoVector2F(1.0f, 0.0f)};
    pVertexBuffer[2] = TexturedVertex{NovelRT::Maths::GeoVector3F(+0.5, -0.5, 0), NovelRT::Maths::GeoVector2F(1.0f, 1.0f)};
    pVertexBuffer[3] = TexturedVertex{NovelRT::Maths::GeoVector3F(+0.5, -0.5, 0), NovelRT::Maths::GeoVector2F(1.0f, 1.0f)};
    pVertexBuffer[4] = TexturedVertex{NovelRT::Maths::GeoVector3F(-0.5, -0.5, 0), NovelRT::Maths::GeoVector2F(0.0f, 1.0f)};
    pVertexBuffer[5] = TexturedVertex{NovelRT::Maths::GeoVector3F(-0.5, +0.5, 0), NovelRT::Maths::GeoVector2F(0.0f, 0.0f)};

    vertexStagingBuffer->UnmapAndWrite(vertexBufferRegion);
    gfxContext->Copy(vertexBuffer, vertexStagingBuffer);

    uint32_t textureWidth = 1280;
    uint32_t textureHeight = 720;
    uint32_t texturePixels = textureWidth * textureHeight;
    uint32_t cellWidth = textureWidth / 8;
    uint32_t cellHeight = textureHeight / 8;

    auto texture2D = gfxContext->GetDevice()->GetMemoryAllocator()->CreateTextureWithDefaultArguments(
        GraphicsTextureAddressMode::Repeat, GraphicsTextureKind::TwoDimensional, GraphicsResourceAccess::None,
        GraphicsResourceAccess::Write, textureWidth, textureHeight);
    auto texture2DRegion = texture2D->Allocate(texture2D->GetSize(), 4);
    auto pTextureData = textureStagingBuffer->Map<uint32_t>(texture2DRegion);

    for (uint32_t n = 0; n < texturePixels; n++)
    {
        auto x = n % textureWidth;
        auto y = n / textureWidth;

        pTextureData[n] = (x / cellWidth % 2) == (y / cellHeight % 2) ? 0xFF000000 : 0xFFFFFFFF;
    }

    textureStagingBuffer->UnmapAndWrite(texture2DRegion);

    std::vector<GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions{frameTransformRegion, primitiveTransformRegion, texture2DRegion};

    gfxContext->Copy(texture2D, textureStagingBuffer);
    gfxContext->EndFrame();
    gfxDevice->Signal(gfxContext->GetFence());
    gfxDevice->WaitForIdle();

    while (!device->GetShouldClose())
    {
        device->ProcessAllMessages();
        if (device->GetIsVisible())
        {
            auto context = gfxDevice->GetCurrentContext();
            context->BeginFrame();
            context->BeginDrawing(NovelRT::Graphics::RGBAColour(0, 0, 255, 255));
            auto primitive = gfxDevice->CreatePrimitive(pipeline, vertexBufferRegion, sizeof(TexturedVertex), dummyRegion, 0,
                                                        inputResourceRegions);
            context->Draw(primitive);
            context->EndDrawing();
            context->EndFrame();
            gfxDevice->PresentFrame();
            gfxDevice->WaitForIdle();
        }
    }

    return 0;
}
