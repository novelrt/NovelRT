// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_THREADING_H
#define NOVELRT_EXPERIMENTAL_THREADING_H

// Threading dependencies.
#include "../../Exceptions/Exceptions.h"
#include <atomic>
#ifndef __TBB_PREVIEW_MUTEXES
#define __TBB_PREVIEW_MUTEXES 1
#endif
#include <oneapi/tbb/mutex.h>
#include <optional>
#include <memory>
#include <mutex>

/**
 * @brief The experimental Threading API.
 */
namespace NovelRT::Experimental::Threading
{
    class VolatileState;
}

// Threading types.
#include "VolatileState.h"
#include "ConcurrentSharedPtr.h"
#include "FutureResult.h"

#endif // !NOVELRT_EXPERIMENTAL_THREADING_H
