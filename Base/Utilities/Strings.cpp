#include <NovelRT/Utilities/Strings.hpp>

namespace NovelRT::Utilities
{
    [[nodiscard]] std::vector<const char*> GetStringSpanAsCharPtrVector(
        const NovelRT::Utilities::Span<const std::string>& target) noexcept
    {
        size_t extensionLength = target.size();
        std::vector<const char*> targetPtrs{};
        targetPtrs.reserve(extensionLength);

        for (auto&& extension : target)
        {
            targetPtrs.emplace_back(extension.c_str());
        }

        return targetPtrs;
    }

    std::vector<std::string> SplitString(const std::string& targetString,
                                         const std::string& delimiter) noexcept
    {
        std::vector<std::string> returnVec{};
        size_t start = 0;
        size_t end = targetString.find(delimiter);

        while (end != std::string::npos)
        {
            returnVec.emplace_back(targetString.substr(start, end - start));
            start = end + delimiter.size();
            end = targetString.find(delimiter, start);
        }

        returnVec.emplace_back(targetString.substr(start)); // THIS LINE ANGERS ME

        return returnVec;
    }
}
