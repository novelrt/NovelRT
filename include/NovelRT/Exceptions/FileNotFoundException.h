// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_FILE_NOT_FOUND_EXCEPTION_H
#define NOVELRT_FILE_NOT_FOUND_EXCEPTION_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Exceptions {
  class FileNotFoundException final : public std::runtime_error {
  public:
    FileNotFoundException(const std::string &file)
    : std::runtime_error("File failed to load. File path: " + file)
    {}
    FileNotFoundException(const std::string &file, const std::string &message)
    : std::runtime_error(message + " File path: " + file)
    {}
  };
} // namespace NovelRT::Exceptions

#endif //NOVELRT_FILE_NOT_FOUND_EXCEPTION_H