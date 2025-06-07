// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXCEPTIONS_NOTINITIALISEDEXCEPTION_H
#define NOVELRT_EXCEPTIONS_NOTINITIALISEDEXCEPTION_H

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions
{
    class NotInitialisedException final : public std::runtime_error
    {
    public:
        NotInitialisedException(const std::string& functionName)
            : std::runtime_error("Service has not been initialised before attempting operation: " + functionName + ".")
        {
        }
        NotInitialisedException(const std::string& functionName, const std::string& message)
            : std::runtime_error("Service has not been initialised before attempting operation: " + functionName +
                                 ". " + message)
        {
        }
    };
}

#endif //! NOVELRT_EXCEPTIONS_NOTINITIALISEDEXCEPTION_H