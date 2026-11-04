#include <NovelRT/Utilities/Paths.hpp>
#include <NovelRT/Utilities/Strings.hpp>

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>
#elif defined(__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#else
#include <limits.h>
#include <unistd.h>
#endif

namespace NovelRT::Utilities
{
    std::filesystem::path GetExecutablePath()
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
            CFBundleRef mainBundle = CFBundleGetMainBundle();
            if (mainBundle != nullptr)
            {
                CFURLRef bundleUrl = CFBundleCopyExecutableURL(mainBundle);
                if (bundleUrl != nullptr)
                {
                    CFStringRef macPath = CFURLCopyFileSystemPath(bundleUrl, kCFURLPOSIXPathStyle);
                    if(macPath != nullptr)
                    {
                        //We've dunked into a bundle
                        std::filesystem::path path = CFStringToStdString(macPath);
                        CFRelease(macPath);
                        CFRelease(bundleUrl);
                        return path;
                    }
                    CFRelease(bundleUrl);
                }
            }
            //if we get here, we fall back to assuming we ran via cmdline.
#endif
            // TODO: Get command line from /proc/self/cmdline
            return std::filesystem::current_path();
        }

        path[pathLength] = '\0';
        return path;
#endif
    }

    std::filesystem::path GetExecutableDirPath()
    {
        return GetExecutablePath().parent_path();
    }
}
