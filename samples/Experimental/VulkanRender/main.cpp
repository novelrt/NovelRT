// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <memory>

using namespace NovelRT::Windowing::Glfw;
using namespace NovelRT::Windowing;
using namespace NovelRT::Graphics::Vulkan;
using namespace NovelRT::Graphics;

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

    NovelRT::LoggingService logger = NovelRT::LoggingService();
    logger.setLogLevel(NovelRT::LogLevel::Info);

#if NOVELRT_MOLTENVK_VENDORED
    auto icdPath = NovelRT::Utilities::Misc::getExecutablePath() / "MoltenVK_icd.json";
    setenv("VK_ICD_FILENAMES", icdPath.c_str(), 0);
    logger.logInfo("macOS detected - setting VK_ICD_FILENAMES to path: {}", icdPath.c_str());
#endif

    auto window = new GlfwWindowingDevice();
    auto device = std::shared_ptr<IWindowingDevice>(window);

    device->Initialise(NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(400, 400));

    auto vulkanProvider = std::make_shared<VulkanGraphicsProvider>();

    VulkanGraphicsAdapterSelector selector;
    std::shared_ptr<VulkanGraphicsSurfaceContext> surfaceContext =
        std::make_shared<VulkanGraphicsSurfaceContext>(device, vulkanProvider);

    std::shared_ptr<GraphicsAdapter> adapter = selector.GetDefaultRecommendedAdapter(vulkanProvider, surfaceContext);

    auto gfxDevice = adapter->CreateDevice(surfaceContext, 2);
    auto gfxContext = gfxDevice->GetCurrentContext();

    auto vertexStagingBuffer = gfxDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
        GraphicsBufferKind::Default, GraphicsResourceAccess::Write, GraphicsResourceAccess::Read, 64 * 1024);
    auto textureStagingBuffer = gfxDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
        GraphicsBufferKind::Default, GraphicsResourceAccess::Write, GraphicsResourceAccess::Read, 64 * 1024 * 4);
    auto vertexBuffer = gfxDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
        GraphicsBufferKind::Vertex, GraphicsResourceAccess::None, GraphicsResourceAccess::Write, 64 * 1024);

    auto vertShaderData = LoadSpv("vert.spv");
    auto pixelShaderData = LoadSpv("frag.spv");

    gfxContext->BeginFrame();
    std::vector<GraphicsPipelineInputElement> elements{
        GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector3F), GraphicsPipelineInputElementKind::Position,
                                     12),
        GraphicsPipelineInputElement(typeid(NovelRT::Maths::GeoVector2F),
                                     GraphicsPipelineInputElementKind::TextureCoordinate, 8)};

    std::vector<GraphicsPipelineInput> inputs{GraphicsPipelineInput(elements)};
    std::vector<GraphicsPipelineResource> resources{
        GraphicsPipelineResource(GraphicsPipelineResourceKind::Texture, ShaderProgramVisibility::Pixel)};

    auto signature = gfxDevice->CreatePipelineSignature(
        GraphicsPipelineBlendFactor::SrcAlpha, GraphicsPipelineBlendFactor::OneMinusSrcAlpha, inputs, resources);
    auto vertShaderProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Vertex, vertShaderData);
    auto pixelShaderProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Pixel, pixelShaderData);
    auto pipeline = gfxDevice->CreatePipeline(signature, vertShaderProg, pixelShaderProg);
    auto dummyRegion = GraphicsMemoryRegion<GraphicsResource>(0, nullptr, gfxDevice, false, 0, 0);

    auto vertexBufferRegion = vertexBuffer->Allocate(sizeof(TexturedVertex) * 3, 16);

    auto pVertexBuffer = vertexStagingBuffer->Map<TexturedVertex>(vertexBufferRegion);

    pVertexBuffer[0] = TexturedVertex{NovelRT::Maths::GeoVector3F(0, 1, 0), NovelRT::Maths::GeoVector2F(0.5f, 0.0f)};
    pVertexBuffer[1] = TexturedVertex{NovelRT::Maths::GeoVector3F(1, -1, 0), NovelRT::Maths::GeoVector2F(1.0f, 1.0f)};
    pVertexBuffer[2] = TexturedVertex{NovelRT::Maths::GeoVector3F(-1, -1, 0), NovelRT::Maths::GeoVector2F(0.0f, 1.0f)};

    vertexStagingBuffer->UnmapAndWrite(vertexBufferRegion);
    gfxContext->Copy(vertexBuffer, vertexStagingBuffer);

    uint32_t textureWidth = 256;
    uint32_t textureHeight = 256;
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

    std::vector<GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions{texture2DRegion};

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
            auto primitive = gfxDevice->CreatePrimitive(pipeline, vertexBufferRegion, sizeof(TexturedVertex),
                                                        dummyRegion, 0, inputResourceRegions);
            context->Draw(primitive);
            context->EndDrawing();
            context->EndFrame();
            gfxDevice->PresentFrame();
            gfxDevice->WaitForIdle();
        }
    }

    return 0;
}
