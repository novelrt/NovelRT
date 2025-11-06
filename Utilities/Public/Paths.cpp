module;

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <filesystem>

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

module NovelRT.Utilities:Paths;

namespace NovelRT::Utilities
{
    /**
     * @brief Gets the path to the executable.
     *
     * @return The path to the executable.
     */
    export std::filesystem::path GetExecutablePath()
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
            if (path.string().find("Contents") == std::string::npos)
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

    /**
     * @brief Gets the path to the directory that contains the executable. <br/>
     * For example, `/home/stuff/game/best-game-executable` will return `/home/stuff/game`
     *
     * @return The path to the directory that contains the executable.
     */
    export std::filesystem::path GetExecutableDirPath()
    {
        return GetExecutablePath().parent_path();
    }
}
