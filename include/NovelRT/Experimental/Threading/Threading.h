// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_THREADING_H
#define NOVELRT_EXPERIMENTAL_THREADING_H

// Threading dependencies.
#include <atomic>
#include "../../Exceptions/Exceptions.h"

/**
 * @brief The experimental Threading API.
 */
namespace NovelRT::Experimental::Threading
{
    class VolatileState;
}

// Threading types.
#include "VolatileState.h"

#endif // !NOVELRT_EXPERIMENTAL_THREADING_H
