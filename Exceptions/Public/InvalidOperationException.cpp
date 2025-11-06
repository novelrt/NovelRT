// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

module;

#include <stdexcept>
#include <string>

export module NovelRT.Exceptions:InvalidOperationException;

export namespace NovelRT::Exceptions
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
