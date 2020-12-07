// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_OPENGL_LINKAGE_FAILURE_EXCEPTION_H
#define NOVELRT_OPENGL_LINKAGE_FAILURE_EXCEPTION_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Exceptions {
  class OpenGLLinkageFailure final : public std::runtime_error {
  public:
    OpenGLLinkageFailure(GLuint programId, const std::string &errorMessage) 
    : std::runtime_error(std::string("Program with ID \"") + std::to_string(programId) + "\" has encountered an error. Error: "+ errorMessage)
    {}
  };
}


#endif //NOVELRT_OPENGL_LINKAGE_FAILURE_EXCEPTION_H