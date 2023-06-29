#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions
{
    class InitialisationFailureException final : public std::runtime_error
    {
    private:
        static inline const std::string defaultMessage =
            "An object, system, or service attempted to be initialised but failed to do so.";

    public:
        InitialisationFailureException() : std::runtime_error(defaultMessage)
        {
        }
        InitialisationFailureException(const std::string& message)
            : std::runtime_error(defaultMessage + " Reason: " + message)
        {
        }
        InitialisationFailureException(const std::string& message, const std::string& arguments)
            : std::runtime_error(defaultMessage + " Reason: " + message + " Error: " + arguments)
        {
        }
        InitialisationFailureException(const std::string& message, const int32_t argument)
            : InitialisationFailureException(message, std::to_string(argument))
        {
        }
    };
}
