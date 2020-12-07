// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_SERVICE_NOT_INITIALISED_EXCEPTION_H
#define NOVELRT_SERVICE_NOT_INITIALISED_EXCEPTION_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Exceptions
{
  class NotInitialisedException final : public std::runtime_error
  {
  public:
    NotInitialisedException(const std::string &functionName, const std::string &message)
        : std::runtime_error("Unable to continue! Dangerous call being made to " + functionName + ". " + message)
    {}
    NotInitialisedException(const std::string &message)
        : std::runtime_error("Unable to continue! " + message)
    {}
  };
} // namespace NovelRT::Exceptions

#endif //NOVELRT_SERVICE_NOT_INITIALISED_EXCEPTION_H