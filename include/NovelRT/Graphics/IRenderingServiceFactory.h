// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_IRENDERINGSERVICEFACTORY_H
#define NOVELRT_GRAPHICS_IRENDERINGSERVICEFACTORY_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  class IRenderingServiceFactory {
  public:
    virtual std::shared_ptr<IRenderingService> create() = 0;

  };
}

#endif //!NOVELRT_GRAPHICS_IRENDERINGSERVICEFACTORY_H