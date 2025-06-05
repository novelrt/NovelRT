#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Utilities/Span.hpp>

#include <string>
#include <vector>

namespace NovelRT::Utilities
{
    [[nodiscard]] std::vector<const char*> GetStringSpanAsCharPtrVector(
        const NovelRT::Utilities::Span<const std::string>& target) noexcept;

    std::vector<std::string> SplitString(const std::string& targetString, const std::string& delimiter) noexcept;
}
