// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXCEPTIONS_NOTSUPPORTEDEXCEPTION_H
#define NOVELRT_EXCEPTIONS_NOTSUPPORTEDEXCEPTION_H

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions
{
    class NotSupportedException final : public std::runtime_error
    {
    public:
        NotSupportedException() : std::runtime_error("The current operation is not supported.")
        {
        }
        NotSupportedException(const std::string& message) : std::runtime_error(message)
        {
        }
    };
} 

#endif //! NOVELRT_EXCEPTIONS_NOTSUPPORTEDEXCEPTION_H