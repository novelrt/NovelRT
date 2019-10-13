// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELRTUTILITIES_H
#define NOVELRT_NOVELRTUTILITIES_H

namespace NovelRT {
class NovelUtilities {
public:
  static const int SDL_SUCCESS = 0;
};
}

#define NOVELRT_EVENT(eventName, eventArgsType)                                                                   \
public:                                                                                                           \
  void subscribeTo##eventName(std::function<void(const eventArgsType&)> delegate) {                               \
    _##eventName##EventDelegates.push_back(delegate);                                                             \
  }                                                                                                               \
  void unsubscribeFrom##eventName(std::function<void(const eventArgsType&)> delegate) {                           \
    _##eventName##EventDelegates.erase(std::remove_if(_##eventName##EventDelegates.begin(),                       \
          _##eventName##EventDelegates.end(), [delegate](const std::function<void(const eventArgsType&)> x) {     \
            auto result = x.target<void(const eventArgsType&)>() == delegate.target<void(const eventArgsType&)>();\
            return result;                                                                                        \
    }), _##eventName##EventDelegates.end());                                                                      \
  }                                                                                                               \
protected:                                                                                                        \
  void raise##eventName(const eventArgsType& eventArgs) {                                                         \
    erase##eventName##NullSubscribers();                                                                          \
    for (auto& delegate : _##eventName##EventDelegates) {                                                         \
      delegate(eventArgs);                                                                                        \
    }                                                                                                             \
  }                                                                                                               \
private:                                                                                                          \
  std::vector<std::function<void(const eventArgsType&)>> _##eventName##EventDelegates;                            \
  void erase##eventName##NullSubscribers() {                                                                      \
        _##eventName##EventDelegates.erase(std::remove_if(_##eventName##EventDelegates.begin(),                   \
            _##eventName##EventDelegates.end(), [](std::function<void(const eventArgsType&)> x) {                 \
            auto result = x == nullptr;                                                                           \
            return result;                                                                                        \
    }), _##eventName##EventDelegates.end());                                                                      \
  }                                                                                                               \

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


#endif //NOVELRT_NOVELRTUTILITIES_H
