// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

module;

#include <stdexcept>
#include <string>

export module NovelRT.Exceptions:NullPointerException;

namespace NovelRT::Exceptions
{
    export class NullPointerException final : public std::runtime_error
    {
    public:
        NullPointerException() : std::runtime_error("Object pointer not set to an instance of an object.")
        {
        }
        NullPointerException(const std::string& message)
            : std::runtime_error("Object pointer not set to an instance of an object." + message)
        {
        }
    };
}
