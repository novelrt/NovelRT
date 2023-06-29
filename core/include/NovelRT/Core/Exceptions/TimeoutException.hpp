#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <chrono>
#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions
{
    class TimeoutException : public std::runtime_error
    {
    public:
        explicit TimeoutException(uint64_t milliseconds)
            : std::runtime_error("An operation exceeded the specified timeout window of " +
                                 std::to_string(milliseconds) + " milliseconds.")
        {
        }
    };
}

#endif // NOVELRT_EXCEPTIONS_TIMEOUTEXCEPTION_H
