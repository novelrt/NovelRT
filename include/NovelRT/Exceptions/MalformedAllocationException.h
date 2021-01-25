// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXCEPTIONS_MALFORMEDALLOCATIONEXCEPTION_H
#define NOVELRT_EXCEPTIONS_MALFORMEDALLOCATIONEXCEPTION_H

#include <stdexcept>

namespace NovelRT::Exceptions
{
    class MalformedAllocationException : public std::runtime_error
    {
    public:
        MalformedAllocationException()
            : std::runtime_error("A dynamic allocation ended up being malformed or entered an illegal state.")
        {
        }
    };
} // namespace NovelRT::Exceptions

#endif // NOVELRT_EXCEPTIONS_MALFORMEDALLOCATIONEXCEPTION_H
