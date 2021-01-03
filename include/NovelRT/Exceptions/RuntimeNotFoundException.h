// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXCEPTIONS_RUNTIMENOTFOUNDEXCEPTION_H
#define NOVELRT_EXCEPTIONS_RUNTIMENOTFOUNDEXCEPTION_H

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions
{
    class RuntimeNotFoundException final : public std::runtime_error
    {
      public:
        RuntimeNotFoundException(const std::string& message) : std::runtime_error(message)
        {
        }
    };
} // namespace NovelRT::Exceptions

#endif //! NOVELRT_EXCEPTIONS_RUNTIMENOTFOUNDEXCEPTION_H