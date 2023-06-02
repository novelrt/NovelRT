// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXCEPTIONS_FILENOTFOUNDEXCEPTION_H
#define NOVELRT_EXCEPTIONS_FILENOTFOUNDEXCEPTION_H

#include <stdexcept>
#include <string>

namespace NovelRT::Core::Exceptions
{
    class FileNotFoundException final : public std::runtime_error
    {
    public:
        FileNotFoundException(const std::string& filePath)
            : std::runtime_error("File failed to load. File path: \"" + filePath + "\".")
        {
        }
        FileNotFoundException(const std::string& filePath, const std::string& message)
            : std::runtime_error(message + " File path: \"" + filePath + "\".")
        {
        }
    };
}

#endif //! NOVELRT_EXCEPTIONS_FILENOTFOUNDEXCEPTION_H
