// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_THREADING_H
#define NOVELRT_THREADING_H

// Threading dependencies.
#include "NovelRT/Exceptions/Exceptions.h"
#include <atomic>
#ifndef __TBB_PREVIEW_MUTEXES
#define __TBB_PREVIEW_MUTEXES 1
#endif
#include <memory>
#include <mutex>
#include <oneapi/tbb/mutex.h>
#include <optional>

/**
 * @brief The experimental Threading API.
 */
namespace NovelRT::Threading
{
    class VolatileState;
}

// Threading types.
#include "ConcurrentSharedPtr.h"
#include "FutureResult.h"
#include "VolatileState.h"

#endif // !NOVELRT_THREADING_H
