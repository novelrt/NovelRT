// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_FUNCTION_NOT_FOUND_EXCEPTION_H
#define NOVELRT_FUNCTION_NOT_FOUND_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions {
  class FunctionNotFoundException final : public std::runtime_error {
  public:
    FunctionNotFoundException(const std::string &message)
    : std::runtime_error(message)
    {}
    FunctionNotFoundException(const std::string &message, int errorCode)
    : std::runtime_error(message + "Error code:" + std::to_string(errorCode) + ".")
    {}
    FunctionNotFoundException(const std::string &message, const std::string &functionName)
    : std::runtime_error(message + "Function \""+ functionName +"\".")
    {}
    FunctionNotFoundException(const std::string &message, const std::string &functionName, int errorCode)
    : std::runtime_error(message + "Function \""+ functionName +"\". Error code:" + std::to_string(errorCode) + ".")
    {}
  };
}

#endif //NOVELRT_FUNCTION_NOT_FOUND_EXCEPTION_H