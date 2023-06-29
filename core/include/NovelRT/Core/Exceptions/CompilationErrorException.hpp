#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions
{
    class CompilationErrorException final : public std::runtime_error
    {
    public:
        CompilationErrorException(const std::string& fileName, const std::string& errorMessage)
            : std::runtime_error("Failed to compile \"" + fileName + "\". Error: " + errorMessage)
        {
        }
    };
}
