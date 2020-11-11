// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef DUMMYRENDERINGSERVICEFACTORY_H
#define DUMMYRENDERINGSERVICEFACTORY_H

#include <NovelRT.h>

//these are the best stubs ive ever made seriously wow 10/10
class DummyRenderingService : public NovelRT::Graphics::IRenderingService {
public:
  std::string aaa = "blabla";
};

class DummyRenderingServiceFactory : public NovelRT::Graphics::IRenderingServiceFactory {
public:
  inline std::shared_ptr<NovelRT::Graphics::IRenderingService> create() override {
      return std::static_pointer_cast<NovelRT::Graphics::IRenderingService>(std::make_shared<DummyRenderingService>());
  }
};

#endif
