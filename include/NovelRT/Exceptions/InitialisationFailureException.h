// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INITIALIZATION_FAILURE_EXCEPTION_H
#define NOVELRT_INITIALIZATION_FAILURE_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions
{
    class InitialisationFailureException final : public std::runtime_error
    {
      public:
        InitialisationFailureException() : std::runtime_error("Service could not be initialised.")
        {
        }
        InitialisationFailureException(const std::string& message)
            : std::runtime_error("Service could not be initialised. " + message)
        {
        }
        InitialisationFailureException(const std::string& message, const std::string& arguments)
            : std::runtime_error("Service could not be initialised. " + message + " error: " + arguments)
        {
        }
        InitialisationFailureException(const std::string& message, const int32_t argument)
            : InitialisationFailureException("Service could not be initialised. " + message, std::to_string(argument))
        {
        }
    };
} // namespace NovelRT::Exceptions

#endif // NOVELRT_INITIALIZATION_FAILURE_EXCEPTION_H