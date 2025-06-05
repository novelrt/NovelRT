#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Utilities/Span.hpp>

#include <string>
#include <vector>

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

namespace NovelRT::Utilities
{
    [[nodiscard]] std::vector<const char*> GetStringSpanAsCharPtrVector(
        const NovelRT::Utilities::Span<const std::string>& target) noexcept;

    std::vector<std::string> SplitString(const std::string& targetString, const std::string& delimiter) noexcept;

#ifdef __APPLE__
    /**
     * Converts a CFString to a UTF-8 std::string if possible.
     *
     * @param input A reference to the CFString to convert.
     * @return Returns a std::string containing the contents of CFString converted to UTF-8. Returns
     *  an empty string if the input reference is null or conversion is not possible.
     */
    std::string CFStringToStdString(CFStringRef input);
#endif
}
