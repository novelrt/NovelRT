// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXCEPTIONS_FUNCTIONNOTFOUNDEXCEPTION_H
#define NOVELRT_EXCEPTIONS_FUNCTIONNOTFOUNDEXCEPTION_H

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions
{
    class FunctionNotFoundException final : public std::runtime_error
    {
      public:
        FunctionNotFoundException() : std::runtime_error("Failed to locate the specified managed function.")
        {
        }
        FunctionNotFoundException(int32_t errorCode)
            : std::runtime_error(std::string("Failed to locate the specified managed function. Error code: ") +
                                 std::to_string(errorCode) + ".")
        {
        }
        FunctionNotFoundException(const std::string& functionName)
            : std::runtime_error(std::string("Failed to locate the specified managed function. Function \"") +
                                 functionName + "\".")
        {
        }
        FunctionNotFoundException(const std::string& message, const std::string& functionName, int32_t errorCode)
            : std::runtime_error(std::string("Failed to locate the specified managed function. Function \"" +
                                             functionName + "\". Error code: ") +
                                 std::to_string(errorCode) + ". " + message)
        {
        }
    };
} // namespace NovelRT::Exceptions

#endif //! NOVELRT_EXCEPTIONS_FUNCTIONNOTFOUNDEXCEPTION_H