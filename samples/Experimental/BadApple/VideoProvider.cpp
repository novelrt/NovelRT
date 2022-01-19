//
// Created by krjoh on 1/18/2022.
//

#include "VideoProvider.h"

VideoProvider::VideoProvider(const char* url, bool debugModeEnabled)
{
    _url = url;
    _logger = NovelRT::LoggingService();
    _logger.setLogLevel(debugModeEnabled ? NovelRT::LogLevel::Debug : NovelRT::LogLevel::Warn);
    _frameCount = 0;
    _averageFps = 0;
}

bool VideoProvider::Initialise(int* width, int* height)
{
    _frames = std::vector<std::vector<uint8_t>>();
    _formatContext = avformat_alloc_context();
    if(!_formatContext)
    {
        _logger.logErrorLine("Could not allocate memory for AV Format Context!");
        return false;
    }

    if(avformat_open_input(&_formatContext, _url.c_str(), NULL, NULL) != 0)
    {
        _logger.logErrorLine("Could not open the provided media file!");
        return false;
    }

    //Find the first valid video stream
    for (int i = 0; i < _formatContext->nb_streams; i++)
    {
        _codecParams = _formatContext->streams[i]->codecpar;
        _codec = avcodec_find_decoder(_codecParams->codec_id);
        if(!_codec)
            continue;
        if (_codecParams->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            _videoStream = i;
            *width = _codecParams->width;
            *height = _codecParams->height;
            break;
        }
    }
    if (_videoStream == -1)
    {
        _logger.logErrorLine("Could not find valid video stream!");
        return false;
    }

    //Set up _codec context
    _codecContext = avcodec_alloc_context3(_codec);
    if(!_codecContext)
    {
        _logger.logErrorLine("Could not create _codec context!");
        return false;
    }
    if (avcodec_parameters_to_context(_codecContext, _codecParams) < 0)
    {
        _logger.logErrorLine("Could not initialise _codec context!");
        return false;
    }
    if (avcodec_open2(_codecContext, _codec, NULL) < 0)
    {
        _logger.logErrorLine("Could not open _codec!");
        return false;
    }

    //Allocate a new _frame and _packet
    _frame = av_frame_alloc();
    if(!_frame)
    {
        _logger.logErrorLine("Could not create _frame!");
        return false;
    }

    _packet = av_packet_alloc();
    if(!_packet)
    {
        _logger.logErrorLine("Could not create _packet!");
        return false;
    }

    return true;
}

void VideoProvider::RetrieveNextFrame(uint8_t** buffer)
{
    if (!(av_read_frame(_formatContext, _packet) >= 0))
    {
        return;
    }
    else
    {
        int response;
        // if _packet is related to video stream
        if (_packet->stream_index == _videoStream)
        {
            response = avcodec_send_packet(_codecContext, _packet);
            if (response < 0)
            {
                _logger.logErrorLine("Failed to decode packet!");
                return;
            }

            response = avcodec_receive_frame(_codecContext, _frame);
            if (response == AVERROR(EAGAIN) || response == AVERROR_EOF)
            {
                return;
            }
            else if (response < 0)
            {
                _logger.logErrorLine("Failed to decode frame!");
                return;
            }

            _scalerContext = sws_getContext(_frame->width, _frame->height, _codecContext->pix_fmt, _frame->width, _frame->height,
                                            AV_PIX_FMT_RGBA, SWS_FAST_BILINEAR, NULL, NULL, NULL);

            if (!_scalerContext)
            {
                _logger.logErrorLine("Failed to init scaler!");
                return;
            }

            uint8_t* data = new uint8_t[_frame->width * _frame->height * 4];
            uint8_t* destination[4] = {data, NULL, NULL, NULL};
            int dataLineSize[4] = {_frame->width * 4, 0, 0, 0};

            sws_scale(_scalerContext, _frame->data, _frame->linesize, 0, _frame->height, destination, dataLineSize);

            memcpy(*buffer, data, _frame->width * _frame->height * 4);
            delete[] data;

            av_packet_unref(_packet);
        }
    }

    return;
}

VideoProvider::~VideoProvider()
{
    avformat_close_input(&_formatContext);
    avformat_free_context(_formatContext);
    av_frame_free(&_frame);
    av_packet_free(&_packet);
    avcodec_free_context(&_codecContext);
    _frames.clear();
}
