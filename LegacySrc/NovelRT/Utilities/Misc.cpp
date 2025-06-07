// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>

#if defined(WIN32)
#include <shellapi.h>
#elif defined(__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#else
#include <unistd.h>
#endif

namespace NovelRT::Utilities
{
#ifdef __APPLE__
    /**
     * Converts a CFString to a UTF-8 std::string if possible.
     *
     * @param input A reference to the CFString to convert.
     * @return Returns a std::string containing the contents of CFString converted to UTF-8. Returns
     *  an empty string if the input reference is null or conversion is not possible.
     */
    std::string CFStringToStdString(CFStringRef input)
    {
        if (!input)
            return {};

        // Attempt to access the underlying buffer directly. This only works if no conversion or
        //  internal allocation is required.
        auto originalBuffer{CFStringGetCStringPtr(input, kCFStringEncodingUTF8)};
        if (originalBuffer)
            return originalBuffer;

        // Copy the data out to a local buffer.
        auto lengthInUtf16{CFStringGetLength(input)};
        auto maxLengthInUtf8{CFStringGetMaximumSizeForEncoding(lengthInUtf16, kCFStringEncodingUTF8) +
                             1}; // <-- leave room for null terminator
        std::vector<char> localBuffer(maxLengthInUtf8);

        if (CFStringGetCString(input, localBuffer.data(), maxLengthInUtf8, maxLengthInUtf8))
            return localBuffer.data();

        return {};
    }
#endif
