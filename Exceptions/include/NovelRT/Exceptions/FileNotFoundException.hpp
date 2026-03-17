#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions
{
    class FileNotFoundException final : public std::runtime_error
    {
    public:
        FileNotFoundException(const std::string& filePath)
            : std::runtime_error("Specified file path does not exist. File path: \"" + filePath + "\".")
        {
        }
        FileNotFoundException(const std::string& filePath, const std::string& message)
            : std::runtime_error(message + " File path: \"" + filePath + "\".")
        {
        }
    };
}
