// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_IO_EXCEPTION_H
#define NOVELRT_IO_EXCEPTION_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Exceptions
{
  class IOException final : public std::runtime_error {
  public:
    IOException(const std::string &fileName) 
    : std::runtime_error("Cannot complete IO operation on file \"" + fileName + "\"")
    {}
    IOException(const std::string &fileName, const std::string &message) 
    : std::runtime_error(message + " File: \"" + fileName + "\".")
    {}
  };
} // namespace NovelRT::Exceptions


#endif //NOVELRT_IO_EXCEPTION_H