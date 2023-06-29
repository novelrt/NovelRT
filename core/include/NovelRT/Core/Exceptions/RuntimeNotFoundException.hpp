#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

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
}
