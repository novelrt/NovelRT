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
    std::filesystem::path finalPath = NovelRT::Utilities::Misc::getExecutableDirPath() / "Resources" / "Shaders" / relativeTarget;
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

int main()
{
    NovelRT::EngineConfig::EnableDebugOutputFromEngineInternals() = true;
    NovelRT::EngineConfig::MinimumInternalLoggingLevel() = NovelRT::LogLevel::Warn;

    auto device = std::shared_ptr<IWindowingDevice>(new GlfwWindowingDevice());

    device->Initialise(NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(400, 400));

    auto vulkanProvider = std::make_shared<VulkanGraphicsProvider>();


    VulkanGraphicsAdapterSelector selector;
    std::shared_ptr<VulkanGraphicsSurfaceContext> surfaceContext = std::make_shared<VulkanGraphicsSurfaceContext>(device, vulkanProvider);

    std::shared_ptr<GraphicsAdapter> adapter = selector.GetDefaultRecommendedAdapter(vulkanProvider, surfaceContext);

    auto gfxDevice = adapter->CreateDevice(surfaceContext, 1);
    auto gfxContext = gfxDevice->GetCurrentContext();

    auto vertShaderData = LoadSpv("vert.spv");
    auto pixelShaderData = LoadSpv("frag.spv");

    auto vertShaderProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Vertex, vertShaderData);
    auto pixelShaderProg = gfxDevice->CreateShaderProgram("main", ShaderProgramKind::Pixel, pixelShaderData);
    auto signature = gfxDevice->CreatePipelineSignature(gsl::span<GraphicsPipelineInput>{}, gsl::span<GraphicsPipelineResource>{});
    auto pipeline = gfxDevice->CreatePipeline(signature, vertShaderProg, pixelShaderProg);
    auto dummyRegion = GraphicsMemoryRegion<GraphicsResource>(0, nullptr, gfxDevice, false,0, 0);

    auto vertexBuffer = gfxDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(GraphicsBufferKind::Vertex, GraphicsResourceCpuAccessKind::CpuToGpu, 64 * 1024);
    auto vertexStagingBuffer = gfxDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(GraphicsBufferKind::Default, GraphicsResourceCpuAccessKind::GpuOnly, 64 * 1024);
    auto vertexBufferRegion = vertexBuffer->Allocate(sizeof(NovelRT::Maths::GeoVector3F) * 3, 16);
    auto pVertexBuffer = vertexStagingBuffer->Map<NovelRT::Maths::GeoVector3F>(vertexBufferRegion);

    pVertexBuffer[0] = NovelRT::Maths::GeoVector3F(0, 1, 0);
    pVertexBuffer[1] = NovelRT::Maths::GeoVector3F(1, -1, 0);
    pVertexBuffer[2] = NovelRT::Maths::GeoVector3F(-1, -1, 0);

    vertexStagingBuffer->UnmapAndWrite(vertexBufferRegion);
    gfxContext->Copy(vertexBuffer, vertexStagingBuffer);

    gfxContext->BeginFrame();
    auto primitive = gfxDevice->CreatePrimitive(pipeline, vertexBufferRegion, sizeof(NovelRT::Maths::GeoVector3F), dummyRegion, 0, gsl::span<const GraphicsMemoryRegion<GraphicsResource>>{});
    gfxContext->EndFrame();

    gfxDevice->Signal(gfxContext->GetFence());
    gfxDevice->WaitForIdle();

    int fuck = 0;
    std::cin >> fuck;
    return 0;
}