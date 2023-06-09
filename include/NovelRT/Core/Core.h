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
    class Atom;
    class AtomFactory;
    class AtomHashFunction;
}

// Core dependencies
#include <string>
#include <vector>
#include <atomic>
#include <cstddef>
#include <limits>
#include <cstdint>

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4275)
#endif

#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#if defined(_MSC_VER)
#pragma warning(pop)
#endif


// Core types
#include "Atom.h"
#include "Exceptions/Exceptions.h"
#include "LoggingService.h"
#include "EngineConfig.h"
#include "Utilities/Utilities.h"

#endif // NOVELRT_WINDOWING_H
