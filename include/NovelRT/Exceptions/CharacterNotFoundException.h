// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_CHARACTER_NOT_FOUND_EXCEPTION_H
#define NOVELRT_CHARACTER_NOT_FOUND_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace NovelRT::Exceptions {
  class CharacterNotFoundException final : public std::runtime_error {
  public:
    CharacterNotFoundException(const std::string &message, const char c)
    : std::runtime_error(message +" character: " + c)
    {}
  };
}


#endif //NOVELRT_CHARACTER_NOT_FOUND_EXCEPTION_H