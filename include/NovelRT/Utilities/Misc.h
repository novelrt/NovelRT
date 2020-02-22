// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_UTILITIES_MISC_H
#define NOVELRT_UTILITIES_MISC_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Utilities {
  class Misc {
  public:
    static const int SDL_SUCCESS = 0;
    static inline const char* CONSOLE_LOG_GENERIC = "NovelRT";
    static inline const char* CONSOLE_LOG_APP = "Application";
    static inline const char* CONSOLE_LOG_DOTNET = ".NET";
    static inline const char* CONSOLE_LOG_GFX = "GFX";
    static inline const char* CONSOLE_LOG_AUDIO = "Audio";
    static inline const char* CONSOLE_LOG_INPUT = "Input";
    static inline const char* CONSOLE_LOG_WINDOWING = "WindowManager";

    static std::filesystem::path getExecutablePath();

    static std::filesystem::path getExecutableDirPath() {
      return getExecutablePath().parent_path();
    }
  };
}

#endif //NOVELRT_UTILITIES_MISC_H
