// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <memory>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

using namespace NovelRT::Experimental::Windowing::Glfw;
using namespace NovelRT::Experimental::Windowing;
using namespace NovelRT::Experimental::Graphics::Vulkan;
using namespace NovelRT::Experimental::Graphics;
using namespace NovelRT;

static LoggingService logging;
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

bool LoadFrame(std::vector<uint8_t>* textureData, uint32_t* tWidth, uint32_t* tHeight)
{
    AVFormatContext* formatContext = avformat_alloc_context();
    if(!formatContext)
    {
        logging.logErrorLine("Could not allocate memory for AV Format Context!");
        return false;
    }

    if(avformat_open_input(&formatContext, "C:\\Users\\krjoh\\Downloads\\gamedev.mp4", NULL, NULL) != 0)
    //if(avformat_open_input(&formatContext, "C:\\Users\\krjoh\\Downloads\\gamedev.mp4", NULL, NULL) != 0)
    {
        logging.logErrorLine("Could not open the provided media file!");
        return false;
    }

    //Find the first valid video stream
    int videoStream = -1;
    AVCodecParameters* codecParams;
    AVCodec* codec;

    for (int i = 0; i < formatContext->nb_streams; i++)
    {
        codecParams = formatContext->streams[i]->codecpar;
        codec = avcodec_find_decoder(codecParams->codec_id);
        if(!codec)
            continue;
        if (codecParams->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStream = i;
            break;
        }
    }
    if (videoStream == -1)
    {
        logging.logErrorLine("Could not find valid video stream!");
        return false;
    }

    //Set up codec context
    AVCodecContext* codecContext = avcodec_alloc_context3(codec);
    if(!codecContext)
    {
        logging.logErrorLine("Could not create codec context!");
        return false;
    }
    if (avcodec_parameters_to_context(codecContext, codecParams) < 0)
    {
        logging.logErrorLine("Could not initialise codec context!");
        return false;
    }
    if (avcodec_open2(codecContext, codec, NULL) < 0)
    {
        logging.logErrorLine("Could not open codec!");
        return false;
    }

    AVFrame* frame = av_frame_alloc();
    if(!frame)
    {
        logging.logErrorLine("Could not create frame!");
        return false;
    }

    AVPacket* packet = av_packet_alloc();
    if(!packet)
    {
        logging.logErrorLine("Could not create packet!");
        return false;
    }

    int response;
    while (av_read_frame(formatContext, packet) >= 0)
    {
        //if packet is related to video stream
        if(packet->stream_index != videoStream)
        {
            continue;
        }
        response = avcodec_send_packet(codecContext, packet);
        if (response < 0)
        {
            logging.logErrorLine("Failed to decode packet!");
            return false;
        }

        response = avcodec_receive_frame(codecContext, frame);
        if(response == AVERROR(EAGAIN) || response == AVERROR_EOF)
        {
            continue;
        }
        else if (response < 0)
        {
            logging.logErrorLine("Failed to decode packet!");
            return false;
        }

        av_packet_unref(packet);
        break;
    }

    SwsContext* scalerContext = sws_getContext(frame->width, frame->height, codecContext->pix_fmt,
                                               frame->width, frame->height, AV_PIX_FMT_RGBA,
                                               SWS_FAST_BILINEAR, NULL, NULL, NULL);

    if (!scalerContext)
    {
        logging.logErrorLine("Failed to init scaler!");
        return false;
    }

    uint8_t* data = new uint8_t[frame->width * frame->height * 4];
    uint8_t* destination[4] = { data, NULL, NULL, NULL};
    int dataLineSize[4] = { frame->width * 4, 0, 0, 0 };

    *tWidth = (uint32_t)frame->width;
    *tHeight = (uint32_t)frame->height;

    sws_scale(scalerContext, frame->data, frame->linesize, 0, frame->height, destination, dataLineSize);



    memcpy(textureData->data(), data, frame->width * frame->height * 4);
    avformat_close_input(&formatContext);
    avformat_free_context(formatContext);
    av_frame_free(&frame);
    av_packet_free(&packet);
    avcodec_free_context(&codecContext);
    return true;
}

int main()
{
    NovelRT::EngineConfig::EnableDebugOutputFromEngineInternals() = false;
    NovelRT::EngineConfig::MinimumInternalLoggingLevel() = NovelRT::LogLevel::Warn;

    //logging = LoggingService();
    //logging.setLogLevel(LogLevel::Debug);
    auto window = new GlfwWindowingDevice();
    auto device = std::shared_ptr<IWindowingDevice>(window);

    device->Initialise(NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(1280, 720));

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
        GraphicsBufferKind::Default, GraphicsResourceAccess::Write, GraphicsResourceAccess::Read, 1280 * 1024 * 4);
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
    auto projectionMatrix = NovelRT::Maths::GeoMatrix4x4F::CreateOrthographic(left, right, bottom, top, 0.1f, 65531.0f);
    auto viewMatrix = NovelRT::Maths::GeoMatrix4x4F::CreateFromLookAt(NovelRT::Maths::GeoVector3F(position.x, position.y, -1.0f),
                                                                      NovelRT::Maths::GeoVector3F(position.x, position.y, 0.0f),
                                                                      NovelRT::Maths::GeoVector3F(0, -1, 0));

    // This is correct for row-major. :]
    auto frameTransform = viewMatrix * projectionMatrix;
    auto primitiveTransform = NovelRT::Maths::GeoMatrix4x4F::getDefaultIdentity();
    primitiveTransform.Scale(NovelRT::Maths::GeoVector2F(1280,720));

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
    //uint8_t* tex = new uint8_t[texturePixels*4];
    std::vector<uint8_t> tex = std::vector<uint8_t>(texturePixels * 4);
    LoadFrame(&tex, &textureWidth, &textureHeight);
    //texturePixels = textureWidth * textureHeight;
    //textureWidth = 256;
    //textureHeight = 256;


    auto texture2D = gfxContext->GetDevice()->GetMemoryAllocator()->CreateTextureWithDefaultArguments(
        GraphicsTextureAddressMode::ClampToEdge, GraphicsTextureKind::TwoDimensional, GraphicsResourceAccess::None,
        GraphicsResourceAccess::Write, textureWidth, textureHeight);
    auto texture2DRegion = texture2D->Allocate(texture2D->GetSize(), 4);
    auto pTextureData = textureStagingBuffer->Map<uint32_t>(texture2DRegion);

    memcpy(pTextureData, tex.data(), tex.size());
    textureStagingBuffer->UnmapAndWrite(texture2DRegion);

    std::vector<GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions{frameTransformRegion, primitiveTransformRegion, texture2DRegion };

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
            context->BeginDrawing(NovelRT::Graphics::RGBAColour(75, 75, 75, 255));
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
