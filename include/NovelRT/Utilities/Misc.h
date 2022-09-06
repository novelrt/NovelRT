// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UTILITIES_MISC_H
#define NOVELRT_UTILITIES_MISC_H

#include <filesystem>
#include <gsl/span>
#include <type_traits>

#define unused(x) (void)(x)

namespace NovelRT::Utilities
{
    class Misc
    {
    public:
        static inline const char* CONSOLE_LOG_GENERIC = "NovelRT";
        static inline const char* CONSOLE_LOG_APP = "Application";
        static inline const char* CONSOLE_LOG_DOTNET = ".NET";
        static inline const char* CONSOLE_LOG_GFX = "GFX";
        static inline const char* CONSOLE_LOG_STATS = "Statistics";
        static inline const char* CONSOLE_LOG_AUDIO = "Audio";
        static inline const char* CONSOLE_LOG_INPUT = "Input";
        static inline const char* CONSOLE_LOG_WINDOWING = "WindowManager";

        /**
         * @brief Gets the path to the executable.
         *
         * @return The path to the executable.
         */
        static std::filesystem::path getExecutablePath();

        /**
         * @brief Gets the path to the directory that contains the executable. <br/>
         * For example, `/home/stuff/game/best-game-executable` will return `/home/stuff/game`
         *
         * @return The path to the directory that contains the executable.
         */
        static std::filesystem::path getExecutableDirPath()
        {
#ifdef __APPLE__
            return getExecutablePath();
#else
            return getExecutablePath().parent_path();
#endif
        }

        [[nodiscard]] static std::vector<const char*> GetStringSpanAsCharPtrVector(
            const gsl::span<const std::string>& target) noexcept
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

        static std::vector<std::string> SplitString(const std::string& targetString,
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
    };
}

template<class T, class U = std::underlying_type_t<T>> constexpr T operator~(T a)
{
    return static_cast<T>(~static_cast<U>(a));
}

template<class T, class U = std::underlying_type_t<T>> constexpr T operator|(T a, T b)
{
    return static_cast<T>((static_cast<U>(a) | static_cast<U>(b)));
}

template<class T, class U = std::underlying_type_t<T>> constexpr T operator&(T a, T b)
{
    return static_cast<T>((static_cast<U>(a) & static_cast<U>(b)));
}

template<class T, class U = std::underlying_type_t<T>> constexpr T operator^(T a, T b)
{
    return static_cast<T>((static_cast<U>(a) ^ static_cast<U>(b)));
}

template<class T, class U = std::underlying_type_t<T>> constexpr T& operator|=(T& a, T b)
{
    return a = static_cast<T>((static_cast<U>(a) | static_cast<U>(b)));
}

template<class T, class U = std::underlying_type_t<T>> constexpr T& operator&=(T& a, T b)
{
    return a = static_cast<T>((static_cast<U>(a) & static_cast<U>(b)));
}

template<class T, class U = std::underlying_type_t<T>> constexpr T& operator^=(T& a, T b)
{
    return a = static_cast<T>((static_cast<U>(a) ^ static_cast<U>(b)));
}

#endif //! NOVELRT_UTILITIES_MISC_H
