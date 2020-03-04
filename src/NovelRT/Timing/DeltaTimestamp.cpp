// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Timing {

  DeltaTimestamp::DeltaTimestamp(uint64_t tickDelta, double doubleDelta, float floatDelta) : _tickDelta(tickDelta), _doubleDelta(doubleDelta), _floatDelta(floatDelta) {}

}
