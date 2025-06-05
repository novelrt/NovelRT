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
}
