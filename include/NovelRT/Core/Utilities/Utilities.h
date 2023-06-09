// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_CORE_UTILITIES_H
#define NOVELRT_CORE_UTILITIES_H

// Core::Utilities dependencies
#include <functional>
#include <vector>
#include <filesystem>
#include <type_traits>
#include <memory>

/**
 * @brief Misc. Classes belonging to the NovelRT engine core.
 */
namespace NovelRT::Core::Utilities
{
    template<typename... TArgs> class EventHandler;
    template<typename... TArgs> class Event;
    class Misc;
    template<typename T> class Lazy;
    template<typename T> class Lazy<std::unique_ptr<T>>;
    template<typename T, typename Deleter> class Lazy<std::unique_ptr<T, Deleter>>;
    template<typename TKey, typename TValueType> class KeyValuePair;
}

#ifdef __has_builtin
#define _NOVELRT_CORE_UTILITIES_HAS_BUILTIN_BIT_CAST __has_builtin(__builtin_bit_cast)
#else
#define _NOVELRT_CORE_UTILITIES_HAS_BUILTIN_BIT_CAST false
#endif

#if __has_include(<version>)
#include <version>
#endif

#if __cpp_lib_bit_cast
#include <bit>
#endif

#if NOVELRT_USE_STD_SPAN
#include <span>
#else
#include <gsl/span>
#endif // NOVELRT_USE_STD_SPAN

// Core::Utilities types
#include "Event.h"
#include "KeyValuePair.h"
#include "Lazy.h"
#include "Misc.h"

#endif // NOVELRT_CORE_UTILITIES
