// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_CORE_H
#define NOVELRT_CORE_H

/**
 * @brief The baseline functionality used across NovelRT modules.
 */
namespace NovelRT::Core
{
    enum class LogLevel;
    class LoggingService;
}

// Windowing dependencies

// Windowing types
#include "Atom.h"
#include "Exceptions/Exceptions.h"
#include "LoggingService.h"

#endif // NOVELRT_WINDOWING_H
