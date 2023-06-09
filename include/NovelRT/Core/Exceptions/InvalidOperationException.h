// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXCEPTIONS_INVALIDOPERATIONEXCEPTION_H
#define NOVELRT_EXCEPTIONS_INVALIDOPERATIONEXCEPTION_H

namespace NovelRT::Core::Exceptions
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
}

#endif //! NOVELRT_EXCEPTIONS_INVALIDOPERATIONEXCEPTION_H
