#include "DummyRenderingServiceFactory.h"
//  using NRTRenderingServiceFactoryCreatorPtr = std::add_pointer<Graphics::IRenderingServiceFactory*()>::type;
extern "C"
{
  NovelRT::Graphics::IRenderingServiceFactory* createRenderingServiceFactory() {
    return new DummyRenderingServiceFactory();
  }
}
