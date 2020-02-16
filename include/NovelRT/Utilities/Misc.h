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
    static inline const std::string CONSOLE_LOG_GENERIC = "NovelRT";
    static inline const std::string CONSOLE_LOG_APP = "Application";
    static inline const std::string CONSOLE_LOG_DOTNET = ".NET";
    static inline const std::string CONSOLE_LOG_GFX = "GFX";
    static inline const std::string CONSOLE_LOG_AUDIO = "Audio";
    static inline const std::string CONSOLE_LOG_INPUT = "Input";
    static inline const std::string CONSOLE_LOG_WINDOWING = "WindowManager";

    static std::filesystem::path getExecutablePath();

    static std::filesystem::path getExecutableDirPath() {
      return getExecutablePath().parent_path();
    }
  };
}

#define NOVELRT_EVENT(eventName, eventArgsType)                                                                    \
public:                                                                                                            \
  void subscribeTo##eventName(std::function<void(const eventArgsType&)> delegate) {                                \
    _i##eventName##EventDelegates.push_back(delegate);                                                             \
  }                                                                                                                \
  void unsubscribeFrom##eventName(std::function<void(const eventArgsType&)> delegate) {                            \
    _i##eventName##EventDelegates.erase(std::remove_if(_i##eventName##EventDelegates.begin(),                      \
          _i##eventName##EventDelegates.end(), [delegate](const std::function<void(const eventArgsType&)> x) {     \
            auto result = x.target<void(const eventArgsType&)>() == delegate.target<void(const eventArgsType&)>(); \
            return result;                                                                                         \
    }), _i##eventName##EventDelegates.end());                                                                      \
  }                                                                                                                \
protected:                                                                                                         \
  void raise##eventName(const eventArgsType& eventArgs) {                                                          \
    erase##eventName##NullSubscribers();                                                                           \
    for (auto& delegate : _i##eventName##EventDelegates) {                                                         \
      delegate(eventArgs);                                                                                         \
    }                                                                                                              \
  }                                                                                                                \
private:                                                                                                           \
  std::vector<std::function<void(const eventArgsType&)>> _i##eventName##EventDelegates;                            \
  void erase##eventName##NullSubscribers() {                                                                       \
        _i##eventName##EventDelegates.erase(std::remove_if(_i##eventName##EventDelegates.begin(),                  \
            _i##eventName##EventDelegates.end(), [](std::function<void(const eventArgsType&)> x) {                 \
            auto result = x == nullptr;                                                                            \
            return result;                                                                                         \
    }), _i##eventName##EventDelegates.end());                                                                      \
  }                                                                                                                \

#define NOVELRT_VALUE_EVENT(eventName, eventArgsType)                                                          \
public:                                                                                                            \
  void subscribeTo##eventName(std::function<void(eventArgsType)> delegate) {                                      \
    _i##eventName##EventDelegates.push_back(delegate);                                                             \
  }                                                                                                                \
  void unsubscribeFrom##eventName(std::function<void(eventArgsType)> delegate) {                                  \
    _i##eventName##EventDelegates.erase(std::remove_if(_i##eventName##EventDelegates.begin(),                      \
          _i##eventName##EventDelegates.end(), [delegate](std::function<void(eventArgsType)> x) {           \
            auto result = x.target<void(eventArgsType)>() == delegate.target<void(eventArgsType)>();             \
            return result;                                                                                         \
    }), _i##eventName##EventDelegates.end());                                                                      \
  }                                                                                                                \
protected:                                                                                                         \
  void raise##eventName(eventArgsType eventArgs) {                                                          \
    erase##eventName##NullSubscribers();                                                                           \
    for (auto& delegate : _i##eventName##EventDelegates) {                                                         \
      delegate(eventArgs);                                                                                         \
    }                                                                                                              \
  }                                                                                                                \
private:                                                                                                           \
  std::vector<std::function<void(eventArgsType)>> _i##eventName##EventDelegates;                            \
  void erase##eventName##NullSubscribers() {                                                                       \
        _i##eventName##EventDelegates.erase(std::remove_if(_i##eventName##EventDelegates.begin(),                  \
            _i##eventName##EventDelegates.end(), [](std::function<void(eventArgsType)> x) {                 \
            auto result = x == nullptr;                                                                            \
            return result;                                                                                         \
    }), _i##eventName##EventDelegates.end());                                                                      \
  }                                                                                                                \

#define NOVELRT_PARAMETERLESS_EVENT(eventName)                                                                    \
public:                                                                                                           \
  void subscribeTo##eventName(std::function<void()> delegate) {                                                   \
    _##eventName##EventDelegates.push_back(delegate);                                                             \
  }                                                                                                               \
  void unsubscribeFrom##eventName(std::function<void()> delegate) {                                               \
    _##eventName##EventDelegates.erase(std::remove_if(_##eventName##EventDelegates.begin(),                       \
          _##eventName##EventDelegates.end(), [delegate](const std::function<void()> x) {                         \
            auto result = x.target<void()>() == delegate.target<void()>();                                        \
            return result;                                                                                        \
    }), _##eventName##EventDelegates.end());                                                                      \
  }                                                                                                               \
protected:                                                                                                        \
  void raise##eventName() {                                                                                       \
    erase##eventName##NullSubscribers();                                                                          \
    for (auto& delegate : _##eventName##EventDelegates) {                                                         \
      delegate();                                                                                                 \
    }                                                                                                             \
  }                                                                                                               \
private:                                                                                                          \
  std::vector<std::function<void()>> _##eventName##EventDelegates;                                                \
  void erase##eventName##NullSubscribers() {                                                                      \
        _##eventName##EventDelegates.erase(std::remove_if(_##eventName##EventDelegates.begin(),                   \
            _##eventName##EventDelegates.end(), [](std::function<void()> x) {                                     \
            auto result = x == nullptr;                                                                           \
            return result;                                                                                        \
    }), _##eventName##EventDelegates.end());                                                                      \
  }                                                                                                               \

#endif //NOVELRT_UTILITIES_MISC_H
