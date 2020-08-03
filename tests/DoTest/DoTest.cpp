#include "DummyRenderingServiceFactory.h"

extern "C"
{
  NovelRT::Graphics::IRenderingServiceFactory* createRenderingServiceFactory() {
    return nullptr;
  }
}
