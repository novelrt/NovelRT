//
// Created by krjoh on 1/18/2022.
//

#include "VideoProvider.h"

VideoProvider::VideoProvider(const char* url, bool debugModeEnabled)
{
    _url = url;
    _logger = NovelRT::LoggingService();
    _logger.setLogLevel(debugModeEnabled ? NovelRT::LogLevel::Debug : NovelRT::LogLevel::Warn);
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
        _videoCodecParams = _formatContext->streams[i]->codecpar;
        _videoCodec = avcodec_find_decoder(_videoCodecParams->codec_id);
        if(!_videoCodec)
            continue;
        if (_videoCodecParams->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            _videoStream = i;
            *width = _videoCodecParams->width;
            *height = _videoCodecParams->height;
            break;
        }
    }
    if (_videoStream == -1)
    {
        _logger.logErrorLine("Could not find valid video stream!");
        return false;
    }
    for (int i = 0; i < _formatContext->nb_streams; i++)
    {
        _audioCodecParams = _formatContext->streams[i]->codecpar;
        _audioCodec = avcodec_find_decoder(_audioCodecParams->codec_id);
        if(!_audioCodec)
            continue;
        if (_audioCodecParams->codec_type == AVMEDIA_TYPE_AUDIO && _audioStream < 0)
        {
            _audioStream = i;
            break;
        }
    }
    if (_audioStream == -1)
    {
        _logger.logErrorLine("Could not find valid audio stream!");
        return false;
    }

    //Set up _codec context
    _videoContext = avcodec_alloc_context3(_videoCodec);
    _audioContext = avcodec_alloc_context3(_audioCodec);
    if(!_videoContext || !_audioContext)
    {
        _logger.logErrorLine("Could not create codec context!");
        return false;
    }
    if (avcodec_parameters_to_context(_videoContext, _videoCodecParams) < 0)
    {
        _logger.logErrorLine("Could not initialise _codec context!");
        return false;
    }
    if (avcodec_parameters_to_context(_audioContext, _audioCodecParams) < 0)
    {
        _logger.logErrorLine("Could not initialise _codec context!");
        return false;
    }
    if (avcodec_open2(_videoContext, _videoCodec, NULL) < 0)
    {
        _logger.logErrorLine("Could not open _codec!");
        return false;
    }
//    _audioCodec = avcodec_find_decoder(AV_CODEC_ID_AAC);
//    if (!_audioCodec)
    if (avcodec_open2(_audioContext, _audioCodec, NULL) < 0)
    {
        _logger.logErrorLine("Could not initialize codec!");
        return false;
    }
    if(avcodec_open2(_audioContext, _audioCodec, NULL) < 0)
        {
            _logger.logErrorLine("Could not open codec!");
            return false;
        }
//
//    //Assign audio info to struct
//    _info = AudioInfo(_audioContext->sample_rate, _audioContext->channels, 1024);

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

//    _parser = av_parser_init(_audioCodec->id);
//    if(!_parser)
//    {
//        _logger.logErrorLine("Could not create parser!");
//        return false;
//    }

    _samplerContext = swr_alloc();
    av_opt_set_int(_samplerContext, "in_channel_layout",    2, 0);
    av_opt_set_int(_samplerContext, "in_sample_rate",       _audioContext->sample_rate, 0);
    av_opt_set_sample_fmt(_samplerContext, "in_sample_fmt", _audioContext->sample_fmt, 0);
    av_opt_set_int(_samplerContext, "out_channel_layout",    1, 0);
    av_opt_set_int(_samplerContext, "out_sample_rate",       44100, 0);
    av_opt_set_sample_fmt(_samplerContext, "out_sample_fmt", AV_SAMPLE_FMT_U8, 0);
    int ret = swr_init(_samplerContext);
    if (ret < 0)
    {
                _logger.logErrorLine("Could not init resampler!");
                return false;

            }
    _audioService.InitializeAudio();

    _buffers = std::vector<ALuint>();
    _audioInit = true;

    //alGenBuffers(4, buffers);
    alGenSources(1, &_source);

    alSourcePlay(_source);

    return true;
}

void VideoProvider::RetrieveNextFrame(uint8_t** buffer, bool* isAudio)
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
            //_logger.logDebugLine("Found video stream");
            *isAudio = false;
            response = avcodec_send_packet(_videoContext, _packet);
            if (response < 0)
            {
                _logger.logErrorLine("Failed to decode packet!");
                return;
            }

            response = avcodec_receive_frame(_videoContext, _frame);
            if (response == AVERROR(EAGAIN) || response == AVERROR_EOF)
            {
                return;
            }
            else if (response < 0)
            {
                _logger.logErrorLine("Failed to decode frame!");
                return;
            }

            _scalerContext = sws_getContext(_frame->width, _frame->height, _videoContext->pix_fmt, _frame->width, _frame->height,
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
        else if(_packet->stream_index == _audioStream)
        {
            //_logger.logDebugLine("Found audio stream packet");
            *isAudio = true;
            response = avcodec_send_packet(_audioContext, _packet);
            if (response < 0)
            {
                _logger.logErrorLine("Failed to decode packet!");
                return;
            }

            response = avcodec_receive_frame(_audioContext, _frame);
            if (response == AVERROR(EAGAIN) || response == AVERROR_EOF)
            {
                return;
            }
            else if (response < 0)
            {
                _logger.logErrorLine("Failed to decode frame!");
                return;
            }

            auto dSize = av_get_bytes_per_sample(_audioContext->sample_fmt);
            if (dSize < 0)
            {
                _logger.logErrorLine("Failed to receive audio frame!");
                return;
            }
            ALuint buf;
            alGenBuffers(1, &buf);


            auto dstNbSamples = av_rescale_rnd(_frame->nb_samples, 44100, _frame->sample_rate, AV_ROUND_UP);
            uint8_t* finalData;
            int lz = 0;
            av_samples_alloc(&finalData, NULL, 1, dstNbSamples, AV_SAMPLE_FMT_U8, 0);


            //uint8_t* finalData = new uint8_t[_frame->nb_samples];
            int ret = swr_convert(_samplerContext, &finalData, dstNbSamples, (const uint8_t**)(_frame->data), _frame->nb_samples);
            if (ret < 0)
                _logger.logErrorLine("Failed to properly convert.");


            //memcpy(&finalData[0], _frame->data, 1024);
            //memcpy(&finalData[0], _frame->data[0], _frame->nb_samples);

            alBufferData(buf, AL_FORMAT_MONO8, finalData, lz, 44100);
            alSourceQueueBuffers(_source, 1, &buf);
            _buffers.insert(_buffers.end(), buf);

            delete[] finalData;
            alSourcePlay(_source);
            av_packet_unref(_packet);
        }
        else
        {
            av_packet_unref(_packet);
        }
    }

    return;
}

//void VideoProvider::StartAudioStream()

//void VideoProvider::UpdateStream()
//{
//    ALint buffersProcessed = 0;
//    //alGetSourcei(source, AL_BUFFERS_PROCESSED, &buffersProcessed);
//
//    if(buffersProcessed <= 0)
//        return;
//
//    while(buffersProcessed--)
//    {
//        ALuint buffer;
//        alSourceUnqueueBuffers(source, 1, &buffer);
//
//        ALsizei dataSize = BUFFER_SIZE;
//
//        char* data = new char[dataSize];
//        std::memset(data, 0, dataSize);
//
//        std::size_t dataSizeToCopy = BUFFER_SIZE;
//        if(cursor + BUFFER_SIZE > soundData.size())
//            dataSizeToCopy = soundData.size() - cursor;
//
//        std::memcpy(&data[0], &soundData[cursor], dataSizeToCopy);
//        cursor += dataSizeToCopy;
//
//        if(dataSizeToCopy < BUFFER_SIZE)
//        {
//            cursor = 0;
//            std::memcpy(&data[dataSizeToCopy], &soundData[cursor], BUFFER_SIZE - dataSizeToCopy);
//            cursor = BUFFER_SIZE - dataSizeToCopy;
//        }
//
//        alBufferData(buffer, format, data, BUFFER_SIZE, sampleRate);
//        alSourceQueueBuffers(source, 1, &buffer);
//
//        delete[] data;
//    }
//}


VideoProvider::~VideoProvider()
{
    if(_audioInit)
    {
        if(!_buffers.empty())
        {
            for(int k = 0; k < _buffers.size(); k++)
            {
                alSourceUnqueueBuffers(_source,1,&_buffers.at(k));
            }
        }
    }

    if (_audioService.isInitialised)
        _audioService.TearDown();
    avformat_close_input(&_formatContext);
    avformat_free_context(_formatContext);
    av_frame_free(&_frame);
    av_packet_free(&_packet);
    avcodec_free_context(&_videoContext);
    _frames.clear();
}

