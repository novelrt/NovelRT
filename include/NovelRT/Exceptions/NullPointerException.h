// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NULL_POINTER_EXCEPTION_EXCEPTION_H
#define NOVELRT_NULL_POINTER_EXCEPTION_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions {
  class NullPointerException final : public std::runtime_error {
  public:
  NullPointerException() :
      std::runtime_error("Object pointer not set to an instance of an object.")
    {}
    NullPointerException(const std::string& message) :
      std::runtime_error("Object pointer not set to an instance of an object." + message)
    {}
  };
}

#endif //NOVELRT_NULL_POINTER_EXCEPTION_EXCEPTION_H