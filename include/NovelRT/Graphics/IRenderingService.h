// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_IRENDERINGSERVICE_H
#define NOVELRT_GRAPHICS_IRENDERINGSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  class IRenderingService {
  public:
    virtual void doTest() = 0;
  };
}

#endif
