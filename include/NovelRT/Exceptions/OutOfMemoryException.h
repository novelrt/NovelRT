// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_OUT_OF_MEMORY_EXCEPTION_H
#define NOVELRT_OUT_OF_MEMORY_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions {
  class OutOfMemoryException final : public std::runtime_error {
    public:
    OutOfMemoryException(const std::string &message)
    : std::runtime_error(message)
    {}
  };
}

#endif //NOVELRT_OUT_OF_MEMORY_EXCEPTION_H