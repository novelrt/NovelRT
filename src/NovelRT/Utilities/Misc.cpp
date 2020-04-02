// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

#if defined(WIN32)
#include <shellapi.h>
#else
#include <unistd.h>
#endif

namespace NovelRT::Utilities {
  std::filesystem::path Misc::getExecutablePath() {
#if defined(WIN32)
      wchar_t path[MAX_PATH + 1];
      auto pathLength = GetModuleFileNameW(nullptr, path, MAX_PATH);

      if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
      {
        auto lpCmdLine = GetCommandLineW();

        int argc;
        auto argv = CommandLineToArgvW(lpCmdLine, &argc);

        return (argc > 0) ? argv[0] : std::filesystem::current_path();
      }

      path[pathLength] = L'\0';
      return path;
#elif defined(__APPLE__)
      char *path;
      uint32_t pathLength = 0;
      _NSGetExecutablePath(nullptr, &pathLength);
      path = new char[pathLength];
      if ((pathLength <= 0) || (pathLength >= PATH_MAX))
      {
          return std::filesystem::current_path();
      }
      
      if (_NSGetExecutablePath(path, &pathLength) < 0)
      {
          return std::filesystem::current_path();
      }
      
      char *actualPath = realpath(path, nullptr);
      free(path);
      
      return std::string(actualPath).c_str();
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
}
