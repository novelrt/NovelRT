// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INITIALIZATION_FAILURE_EXCEPTION_H
#define NOVELRT_INITIALIZATION_FAILURE_EXCEPTION_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Exceptions {
  class InitialisationFailureException final : public std::runtime_error {
  public:
    InitialisationFailureException(const std::string &message)
    : std::runtime_error(message)
    {}
    InitialisationFailureException(const std::string &message, const std::string &arguments)
    : std::runtime_error(message + " error: " + arguments)
    {}
    InitialisationFailureException(const std::string &message, const int argument)
    : InitialisationFailureException(message, std::to_string(argument))
    {}
  };
}

#endif //NOVELRT_INITIALIZATION_FAILURE_EXCEPTION_H