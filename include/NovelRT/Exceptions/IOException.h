// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_EXCEPTIONS_IOEXCEPTION_H
#define NOVELRT_EXCEPTIONS_IOEXCEPTION_H

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions {
  class IOException final : public std::runtime_error {
  public:
    IOException(const std::string& fileName) :
      std::runtime_error("Cannot complete IO operation on file \"" + fileName + "\".")
    {}
    IOException(const std::string& fileName, const std::string& message) :
      std::runtime_error(message + " File: \"" + fileName + "\".")
    {}
  };
}


#endif //!NOVELRT_EXCEPTIONS_IOEXCEPTION_H