// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXCEPTIONS_KEYNOTFOUNDEXCEPTION_H
#define NOVELRT_EXCEPTIONS_KEYNOTFOUNDEXCEPTION_H

#include <stdexcept>

namespace NovelRT::Core::Exceptions
{
    class KeyNotFoundException : public std::runtime_error
    {
    public:
        explicit KeyNotFoundException() : std::runtime_error("The specified key was not found in the collection.")
        {
        }

        explicit KeyNotFoundException(const std::string& message) : std::runtime_error(message)
        {
        }
    };
}

#endif //! NOVELRT_EXCEPTIONS_KEYNOTFOUNDEXCEPTION_H
