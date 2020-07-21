#include <NovelRT.h>

extern "C"
{
  NovelRT::Graphics::IRenderingService* createRenderingService(NovelRT::NovelRunner* const /*runner*/) {
    return nullptr;
  }
}
