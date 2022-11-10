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
    auto originalBuffer{ CFStringGetCStringPtr(input, kCFStringEncodingUTF8) };
    if (originalBuffer)
        return originalBuffer;

    // Copy the data out to a local buffer.
    auto lengthInUtf16{ CFStringGetLength(input) };
    auto maxLengthInUtf8{ CFStringGetMaximumSizeForEncoding(lengthInUtf16,
        kCFStringEncodingUTF8) + 1 }; // <-- leave room for null terminator
    std::vector<char> localBuffer(maxLengthInUtf8);

    if (CFStringGetCString(input, localBuffer.data(), maxLengthInUtf8, maxLengthInUtf8))
        return localBuffer.data();

    return {};
}
#endif


    std::filesystem::path Misc::getExecutablePath()
    {
#if defined(WIN32)
        wchar_t path[MAX_PATH + 1];
        auto pathLength = GetModuleFileNameW(nullptr, path, MAX_PATH);

        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
            auto lpCmdLine = GetCommandLineW();

            int32_t argc;
            auto argv = CommandLineToArgvW(lpCmdLine, &argc);

            return (argc > 0) ? argv[0] : std::filesystem::current_path();
        }

        path[pathLength] = L'\0';
        return path;
#else
        char path[PATH_MAX + 1];
        auto pathLength = readlink("/proc/self/exe", path, PATH_MAX);

        if ((pathLength < 0) || (pathLength == PATH_MAX))
        {
#ifdef __APPLE__
            std::filesystem::path path = std::filesystem::current_path();
            if(path.string().find("Contents") == std::string::npos)
            {
            // We've run via bundling
                CFBundleRef mainBundle = CFBundleGetMainBundle();
                CFURLRef bundleUrl = CFBundleCopyExecutableURL(mainBundle);
                CFStringRef macPath = CFURLCopyFileSystemPath(bundleUrl, kCFURLPOSIXPathStyle);
                path = CFStringToStdString(macPath);
                return path.parent_path();
            }
            else
            {
                return std::filesystem::current_path();
            }
#endif
            // TODO: Get command line from /proc/self/cmdline
            return std::filesystem::current_path();
        }

        path[pathLength] = '\0';
        return path;
#endif
    }
} // namespace NovelRT::Utilities
