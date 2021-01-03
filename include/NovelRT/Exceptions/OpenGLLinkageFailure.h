// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_EXCEPTIONS_OPENGLLINKAGEFAILUREEXCEPTION_H
#define NOVELRT_EXCEPTIONS_OPENGLLINKAGEFAILUREEXCEPTION_H

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions {
  class OpenGLLinkageFailure final : public std::runtime_error {
  public:
    OpenGLLinkageFailure(uint32_t programId, const std::string& errorMessage) :
      std::runtime_error(std::string("Program with ID \"") + std::to_string(programId) + "\" has encountered an error. Error: " + errorMessage)
    {}
  };
}


#endif //!NOVELRT_EXCEPTIONS_OPENGLLINKAGEFAILUREEXCEPTION_H