// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UTILITIES_MEMORY_H
#define NOVELRT_UTILITIES_MEMORY_H

#include <NovelRT/Exceptions/Exceptions.h>
#include <cassert>
#include <cstring>
#include <string.h>

namespace NovelRT::Utilities
{
    class Memory
    {
    public:
        static void Copy(void* destination, size_t destinationSize, const void* source, size_t count)
        {
#ifdef WIN32
            errno_t result = memcpy_s(destination, destinationSize, source, count);

            if (result != 0)
            {
                switch (result)
                {
                    case EINVAL:
                        throw Exceptions::InvalidOperationException("Due to invalid values passed in.");
                        break;
                    case ERANGE:
                        throw Exceptions::InvalidOperationException("Argument is out of the allowed range");
                        break;
                    default:
                        throw Exceptions::InvalidOperationException("Unknown error");
                }
            }
#else
            if (destination == nullptr || source == nullptr || count <= 0 || destinationSize < count)
            {
                throw Exceptions::InvalidOperationException("Due to invalid values passed in.");
            }

            memcpy(destination, source, count);
#endif
        }
    };
}

#endif //! NOVELRT_UTILITIES_MEMORY_H
