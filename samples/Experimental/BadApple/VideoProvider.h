//
// Created by krjoh on 1/18/2022.
//
#include <NovelRT.h>

//FFMPEG includes
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavutil/opt.h>
}

#ifndef NOVELRT_VIDEOPROVIDER_H
#define NOVELRT_VIDEOPROVIDER_H

class VideoProvider
{
private:
    std::vector<std::vector<uint8_t>> _frames;
    AVFormatContext* _formatContext;
    AVCodecParameters* _videoCodecParams;
    AVCodecParameters* _audioCodecParams;
    AVCodec* _videoCodec;
    AVCodec* _audioCodec;
    AVCodecContext* _videoContext;
    AVCodecContext* _audioContext;
    AVFrame* _frame;
    AVPacket* _packet;
    //AVCodecParser* _parser;
    SwsContext* _scalerContext;
    SwrContext* _samplerContext;
    std::string _url;
    NovelRT::LoggingService _logger;
    int _videoStream = -1;
    int _audioStream = -1;
    bool _audioInit = false;
    std::vector<ALuint> _buffers;
    const size_t BUFFER_SIZE = 1024;
    NovelRT::Audio::AudioService _audioService;
    ALuint buffers[4];
    ALint state = AL_PLAYING;
    ALuint _source;


public:
    VideoProvider(const char* url, bool debugModeEnabled);
    bool Initialise(int* width, int* height);
    void RetrieveNextFrame(uint8_t** buffer, bool* isAudio);
    ~VideoProvider();
    //void UpdateStream();
};



#endif // NOVELRT_VIDEOPROVIDER_H
