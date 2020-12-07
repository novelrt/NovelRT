// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NULL_POINTER_EXCEPTION_EXCEPTION_H
#define NOVELRT_NULL_POINTER_EXCEPTION_EXCEPTION_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Exceptions {
  class NullPointerException final : public std::runtime_error {
  public:
    NullPointerException(const std::string &message)
    : std::runtime_error(message)
    {}
  };
} // namespace NovelRT::Exceptions

#endif //NOVELRT_NULL_POINTER_EXCEPTION_EXCEPTION_H