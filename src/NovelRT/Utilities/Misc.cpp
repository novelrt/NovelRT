// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>

#if defined(WIN32)
#include <shellapi.h>
#else
#include <unistd.h>
#endif

namespace NovelRT::Utilities
{
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
            // TODO: Get command line from /proc/self/cmdline
            return std::filesystem::current_path();
        }

        path[pathLength] = '\0';
        return path;
#endif
    }
} // namespace NovelRT::Utilities
