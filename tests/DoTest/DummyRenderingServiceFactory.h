// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef DUMMYRENDERINGSERVICEFACTORY_H
#define DUMMYRENDERINGSERVICEFACTORY_H

#include <NovelRT.h>

class DummyRenderingServiceFactory : public NovelRT::Graphics::IRenderingServiceFactory {
public:
  inline std::shared_ptr<NovelRT::Graphics::IRenderingService> create() override {
      return nullptr;
  }
};

#endif
