// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_DEBUG_METRICSLEVEL_H
#define NOVELRT_DEBUG_METRICSLEVEL_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Debug {
  enum class MetricsLevel : int32_t
  {
    None = 0,
    FramesPerSecond = 1,
    HardwareUsage = 2,
    RenderingStatistics = 3,
  };
}

#endif //NOVELRT_DEBUG_METRICSLEVEL_H
