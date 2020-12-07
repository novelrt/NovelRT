// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_COMPILATION_ERROR_EXCEPTION_H
#define NOVELRT_COMPILATION_ERROR_EXCEPTION_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Exceptions {
  class CompilationErrorException final : public std::runtime_error {
  public:
    CompilationErrorException(const std::string &fileName, const std::string &errorMessage) 
    : std::runtime_error("Failed to compile \"" + fileName + "\". Error: " + errorMessage)
    {}
  };
}


#endif //NOVELRT_COMPILATION_ERROR_EXCEPTION_H