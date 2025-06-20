#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions
{
    class OutOfMemoryException final : public std::runtime_error
    {
    public:
        OutOfMemoryException() : std::runtime_error("Insufficient memory to continue the execution of the program.")
        {
        }

        explicit OutOfMemoryException(const std::string& message) : std::runtime_error(message)
        {
        }
    };
}
