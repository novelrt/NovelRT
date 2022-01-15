// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <memory>

using namespace NovelRT::Experimental::Windowing::Glfw;
using namespace NovelRT::Experimental::Windowing;
using namespace NovelRT::Experimental::Graphics::Vulkan;
using namespace NovelRT::Experimental::Graphics;

#include <iostream>
#include <vector>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

static SwsContext* sws_ctx;
static std::shared_ptr<GraphicsContext> gfxContext;
static std::shared_ptr<GraphicsDevice> gfxDevice;

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

static void logging(const char *fmt, ...)
{
    va_list args;
    fprintf( stderr, "LOG: " );
    va_start( args, fmt );
    vfprintf( stderr, fmt, args );
    va_end( args );
    fprintf( stderr, "\n" );
}

static int decode_packet(AVPacket *pPacket, AVCodecContext *pCodecContext, AVFrame *pFrame, std::shared_ptr<GraphicsBuffer> textureStagingBuffer)
{
    // Supply raw packet data as input to a decoder
    // https://ffmpeg.org/doxygen/trunk/group__lavc__decoding.html#ga58bc4bf1e0ac59e27362597e467efff3
    int response = avcodec_send_packet(pCodecContext, pPacket);

    if (response < 0) {
        logging("Error while sending a packet to the decoder: %s");
        return response;
    }

    while (response >= 0)
    {
        // Return decoded output data (into a frame) from a decoder
        // https://ffmpeg.org/doxygen/trunk/group__lavc__decoding.html#ga11e6542c4e66d3028668788a1a74217c
        response = avcodec_receive_frame(pCodecContext, pFrame);
        if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
            break;
        } else if (response < 0) {
            logging("Error while receiving a frame from the decoder: %s");
            return response;
        }

        if (response >= 0) {
            logging(
                "Frame %d (type=%c, size=%d bytes, format=%d) pts %d key_frame %d [DTS %d]",
                pCodecContext->frame_number,
                av_get_picture_type_char(pFrame->pict_type),
                pFrame->pkt_size,
                pFrame->format,
                pFrame->pts,
                pFrame->key_frame,
                pFrame->coded_picture_number
            );

            AVFrame rgbFrame;
            rgbFrame.linesize[0] = pFrame->width * 4;
            rgbFrame.data[0] = (uint8_t*)malloc(rgbFrame.linesize[0] * pFrame->height);

            // convert to rgb maybe?
            sws_scale(sws_ctx, pFrame->data, pFrame->linesize, 0, pFrame->height, rgbFrame.data,
                      rgbFrame.linesize);

            auto video_dst_bufsize_RGB = av_image_alloc(rgbFrame.data, rgbFrame.linesize, pFrame->width,
                                                        pFrame->height, AV_PIX_FMT_BGR32, 1);

            logging("video_dst_bufsize %d", video_dst_bufsize_RGB);


            char frame_filename[1024];
            snprintf(frame_filename, sizeof(frame_filename), "%s-%d.pgm", "frame", pCodecContext->frame_number);
            // Check if the frame is a planar YUV 4:2:0, 12bpp
            // That is the format of the provided .mp4 file
            // RGB formats will definitely not give a gray image
            // Other YUV image may do so, but untested, so give a warning
            if (pFrame->format != AV_PIX_FMT_YUV420P)
            {
                logging("Warning: the generated file may not be a grayscale image, but could e.g. be just the R component if the video format is RGB");
            }

            auto texture2D = gfxContext->GetDevice()->GetMemoryAllocator()->CreateTextureWithDefaultArguments(
                    GraphicsTextureAddressMode::Repeat, GraphicsTextureKind::TwoDimensional,
                    GraphicsResourceAccess::None, GraphicsResourceAccess::Write, pFrame->width,
                    pFrame->height);

            auto texture2DRegion = texture2D->Allocate(texture2D->GetSize(), 4);
            auto pTextureData = textureStagingBuffer->Map<uint32_t>(texture2DRegion);

            auto rLength = sizeof(rgbFrame.data[0]);
            auto gLength = sizeof(rgbFrame.data[1]);
            auto bLength = sizeof(rgbFrame.data[2]);
            auto aLength = sizeof(rgbFrame.data[3]);

            if (rLength == gLength && bLength == aLength && rLength == aLength)
            {
                logging("Sizes match properly!");
            }
            else
            {
                logging("Size mismatch! r:%d\tg:%d\tb:%d\ta:%d", rLength, gLength, bLength, aLength);
                return -10;
            }

            for (uint32_t n = 0; n < (uint32_t)rLength; n++)
            {
                // auto x = n % textureWidth;
                // auto y = n / textureWidth;

                pTextureData[n] = rgbFrame.data[0][n] | (rgbFrame.data[1][n] << 8) |
                                  (rgbFrame.data[2][n] << 16) | (rgbFrame.data[3][n] << 24);
                // pTextureData[n] = (x / cellWidth % 2) == (y / cellHeight % 2) ? 0xFF000000 : 0xFFFFFFFF;
            }

            textureStagingBuffer->UnmapAndWrite(texture2DRegion);
            auto context = gfxDevice->GetCurrentContext();
            context->Copy(texture2D, textureStagingBuffer);

            // save a grayscale frame into a .pgm file
            //save_gray_frame(pFrame->data[0], pFrame->linesize[0], pFrame->width, pFrame->height, frame_filename);
        }
    }
    return 0;
}

int main()
{
    NovelRT::EngineConfig::EnableDebugOutputFromEngineInternals() = false;
    NovelRT::EngineConfig::MinimumInternalLoggingLevel() = NovelRT::LogLevel::Warn;

    auto window = new GlfwWindowingDevice();
    auto device = std::shared_ptr<IWindowingDevice>(window);

    device->Initialise(NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(12800, 720));

    auto vulkanProvider = std::make_shared<VulkanGraphicsProvider>();

    VulkanGraphicsAdapterSelector selector;
    std::shared_ptr<VulkanGraphicsSurfaceContext> surfaceContext =
        std::make_shared<VulkanGraphicsSurfaceContext>(device, vulkanProvider);

    std::shared_ptr<GraphicsAdapter> adapter = selector.GetDefaultRecommendedAdapter(vulkanProvider, surfaceContext);

    gfxDevice = adapter->CreateDevice(surfaceContext, 2);
    auto graphicsResourceManager = NovelRT::Experimental::Graphics::GraphicsResourceManager(gfxDevice);
    gfxContext = gfxDevice->GetCurrentContext();

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

    //FFMPEG STUFF
    std::cout << "Allocating memory for format context" << std::endl;
    AVFormatContext *pFormatContext = avformat_alloc_context();
    if(!pFormatContext)
    {
        std::cerr << "Could not allocate memory for format context!" << std::endl;
        return -1;
    }

    //Open file and read header
    //we pass NULL to input format to autodetect
    //we pass NULL to AVdictionary for demuxer
    std::cout << "Opening file and loading format container..." << std::endl;
    if(avformat_open_input(&pFormatContext, "C:\\Users\\krjoh\\Downloads\\badapple.mp4", NULL, NULL) != 0)
    {
        std::cerr << "Could not open file!" << std::endl;
        return -2;
    }

    //Since we read the header, we now can access certain information
    std::cout << "Format: " << pFormatContext->iformat->name << std::endl;
    std::cout << "Duration: " << (pFormatContext->duration / AV_TIME_BASE) << " seconds" << std::endl;

    //Read packets from format to get stream info
    if(avformat_find_stream_info(pFormatContext, NULL) < 0)
    {
        std::cerr << "Could not get the stream info!" << std::endl;
        return -3;
    }

    AVCodec* pCodec = NULL;
    AVCodecParameters* codecParams = NULL;
    int video_stream_index = -1;

    for(int i = 0; i < pFormatContext->nb_streams; i++)
    {
        AVCodecParameters *pLocalCodecParameters =  NULL;
        pLocalCodecParameters = pFormatContext->streams[i]->codecpar;
        logging("AVStream->time_base before open coded %d/%d\n", pFormatContext->streams[i]->time_base.num, pFormatContext->streams[i]->time_base.den);
        logging("AVStream->r_frame_rate before open coded %d/%d\n", pFormatContext->streams[i]->r_frame_rate.num, pFormatContext->streams[i]->r_frame_rate.den);
        logging("AVStream->start_time %\n" PRId64, pFormatContext->streams[i]->start_time);
        logging("AVStream->duration %\n" PRId64, pFormatContext->streams[i]->duration);

        logging("finding the proper decoder (CODEC)\n");

        AVCodec *pLocalCodec = NULL;

        // finds the registered decoder for a codec ID
        // https://ffmpeg.org/doxygen/trunk/group__lavc__decoding.html#ga19a0ca553277f019dd5b0fec6e1f9dca
        pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);

        if (pLocalCodec==NULL) {
            logging("ERROR unsupported codec!\n");
            // In this example if the codec is not found we just skip it
            continue;
        }

        // when the stream is a video we store its index, codec parameters and codec
        if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO) {
            if (video_stream_index == -1) {
                video_stream_index = i;
                pCodec = pLocalCodec;
                codecParams = pLocalCodecParameters;
            }

            logging("Video Codec: resolution %d x %d", pLocalCodecParameters->width, pLocalCodecParameters->height);
        } else if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO) {
            logging("Audio Codec: %d channels, sample rate %d", pLocalCodecParameters->channels, pLocalCodecParameters->sample_rate);
        }

        // print its name, id and bitrate
        logging("\tCodec %s ID %d bit_rate %lld\n", pLocalCodec->name, pLocalCodec->id, pLocalCodecParameters->bit_rate);

    }

    if (video_stream_index == -1) {
        logging("File does not contain a video stream!");
        return -1;
    }
    
    // https://ffmpeg.org/doxygen/trunk/structAVCodecContext.html
    AVCodecContext *pCodecContext = avcodec_alloc_context3(pCodec);
    if (!pCodecContext)
    {
        logging("failed to allocated memory for AVCodecContext");
        return -1;
    }

    // Fill the codec context based on the values from the supplied codec parameters
    // https://ffmpeg.org/doxygen/trunk/group__lavc__core.html#gac7b282f51540ca7a99416a3ba6ee0d16
    if (avcodec_parameters_to_context(pCodecContext, codecParams) < 0)
    {
        logging("failed to copy codec params to codec context");
        return -1;
    }

    // Initialize the AVCodecContext to use the given AVCodec.
    // https://ffmpeg.org/doxygen/trunk/group__lavc__core.html#ga11f785a188d7d9df71621001465b0f1d
    if (avcodec_open2(pCodecContext, pCodec, NULL) < 0)
    {
        logging("failed to open codec through avcodec_open2");
        return -1;
    }

    // https://ffmpeg.org/doxygen/trunk/structAVFrame.html
    AVFrame *pFrame = av_frame_alloc();
    if (!pFrame)
    {
        logging("failed to allocated memory for AVFrame");
        return -1;
    }
    // https://ffmpeg.org/doxygen/trunk/structAVPacket.html
    AVPacket *pPacket = av_packet_alloc();
    if (!pPacket)
    {
        logging("failed to allocated memory for AVPacket");
        return -1;
    }

    sws_ctx = sws_getContext(pCodecContext->width, pCodecContext->height,AV_PIX_FMT_YUV420P, pCodecContext->width, pCodecContext->height, AV_PIX_FMT_BGR32, SWS_LANCZOS | SWS_ACCURATE_RND, 0, 0, 0);

    int response = 0;
    //int how_many_packets_to_process = 8;

    //Get gfx going for frame 0

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
            //auto x = n % textureWidth;
            //auto y = n / textureWidth;

            pTextureData[n] = 0xFF000000;
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
            // fill the Packet with data from the Stream
            // https://ffmpeg.org/doxygen/trunk/group__lavf__decoding.html#ga4fdb3084415a82e3810de6ee60e46a61

            gfxContext->BeginFrame();
            gfxContext->BeginDrawing(NovelRT::Graphics::RGBAColour(0, 0, 0,0));

            if (av_read_frame(pFormatContext, pPacket) >= 0)
            {
                // if it's the video stream
                if (pPacket->stream_index == video_stream_index)
                {
                    response = decode_packet(pPacket, pCodecContext, pFrame, textureStagingBuffer);
                    if (response < 0)
                        break;
                }
            }

            gfxContext->EndDrawing();
            gfxContext->EndFrame();
            gfxDevice->PresentFrame();
            gfxDevice->WaitForIdle();
            av_packet_unref(pPacket);
        }
    }

    //Clean up the resources
    avformat_close_input(&pFormatContext);
    av_packet_free(&pPacket);
    av_frame_free(&pFrame);
    avcodec_free_context(&pCodecContext);

    return 0;
}
