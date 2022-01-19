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
}

#ifndef NOVELRT_VIDEOPROVIDER_H
#define NOVELRT_VIDEOPROVIDER_H

class VideoProvider
{
private:
    std::vector<std::vector<uint8_t>> _frames;
    AVFormatContext* _formatContext;
    AVCodecParameters* _codecParams;
    AVCodec* _codec;
    AVCodecContext* _codecContext;
    AVFrame* _frame;
    AVPacket* _packet;
    SwsContext* _scalerContext;
    std::string _url;
    NovelRT::LoggingService _logger;
    int _currentFrame;
    int _response;
    int _videoStream = -1;
    int _frameCount;
    int _averageFps;

public:
    VideoProvider(const char* url, bool debugModeEnabled);
    bool Initialise(int* width, int* height);
    void RetrieveNextFrame(uint8_t** buffer);
    ~VideoProvider();
};

#endif // NOVELRT_VIDEOPROVIDER_H
