// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INVALID_OPERATION_EXCEPTION_H
#define NOVELRT_INVALID_OPERATION_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions
{
    class InvalidOperationException final : public std::runtime_error
    {
      public:
        InvalidOperationException() : std::runtime_error("The current operation is invalid.")
        {
        }
        InvalidOperationException(const std::string& message)
            : std::runtime_error("The current operation is invalid. " + message)
        {
        }
    };
} // namespace NovelRT::Exceptions

#endif // NOVELRT_INVALID_OPERATION_EXCEPTION_H