// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_UTILITIES_EVENT_H
#define NOVELRT_UTILITIES_EVENT_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Utilities {
  template<typename... TArgs>
  class EventHandler {
  private:
    static std::atomic_uintptr_t _nextId;

    uintptr_t _id;
    std::function<void(TArgs...)> _function;

  public:
    EventHandler() : EventHandler(nullptr) {
    }

    EventHandler(const std::function<void(TArgs...)>& function) :
      _id((function != nullptr) ? _nextId++ : 0),
      _function(function) {
    }

    void operator()(TArgs... args) const {
      _function(std::forward<TArgs>(args)...);
    }

    uintptr_t getId() const {
      return _id;
    }

    bool operator==(const EventHandler<TArgs...>& other) const {
      return _id == other._id;
    }

    bool operator!=(const EventHandler<TArgs...>& other) const {
      return _id != other._id;
    }
  };

  template <typename... TArgs> std::atomic_uintptr_t EventHandler<TArgs...>::_nextId(1);

  template<typename... TArgs>
  class Event {
  private:
    std::vector<EventHandler<TArgs...>> _handlers;

  public:
    Event() : _handlers(std::vector<EventHandler<TArgs...>>()) {
    }

    size_t getHandlerCount() const {
      return _handlers.size();
    }

    void operator+=(const EventHandler<TArgs...>& handler) {
      if (handler.getId() != 0) {
        _handlers.emplace_back(handler);
      }
    }

    void operator+=(const std::function<void(TArgs...)>& function) {
      EventHandler<TArgs...> handler = function;
      *this += handler;
    }

    void operator-=(const EventHandler<TArgs...>& handler) {
      if (handler.getId() == 0)
        return;

      auto match = std::find(_handlers.cbegin(), _handlers.cend(), handler);

      if (match != _handlers.cend())
        _handlers.erase(match);
    }

    void operator()(TArgs... args) const {
      for (auto& handler : _handlers) {
        handler(args...);
      }
    }
  };
}
#endif //NOVELRT_UTILITIES_EVENT_H
