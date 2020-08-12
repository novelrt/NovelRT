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
    Atom _id;
    std::function<void(TArgs...)> _function;

  public:
    EventHandler() : EventHandler(nullptr) {
    }

    explicit EventHandler(std::function<void(TArgs...)>&& function) :
      _id((function != nullptr) ? Atom::getNextEventHandlerId() : Atom()),
      _function(std::move(function)) {
    }

    explicit EventHandler(const std::function<void(TArgs...)>& function) :
      _id((function != nullptr) ? Atom::getNextEventHandlerId() : Atom()),
      _function(function) {
    }

    void operator()(TArgs... args) const {
      _function(std::forward<TArgs>(args)...);
    }

    Atom getId() const {
      return _id;
    }

    bool operator==(const EventHandler<TArgs...>& other) const {
      return _id == other._id;
    }

    bool operator!=(const EventHandler<TArgs...>& other) const {
      return _id != other._id;
    }
  };

  template<typename... TArgs>
  class Event {
  private:
    std::vector<EventHandler<TArgs...>> _handlers;

    template <typename T>
    void addHandler(T&& handler) {
      if (handler.getId() != Atom()) {
        _handlers.emplace_back(std::forward<T>(handler));
      }
    }

  public:
    Event() : _handlers(std::vector<EventHandler<TArgs...>>()) {
    }

    size_t getHandlerCount() const {
      return _handlers.size();
    }

    void operator+=(const EventHandler<TArgs...>& handler) {
      addHandler(handler);
    }

    void operator+=(EventHandler<TArgs...>&& handler) {
      addHandler(handler);
    }

    void operator+=(const std::function<void(TArgs...)>& function) {
      addHandler(EventHandler<TArgs...>(function));
    }

    void operator+=(std::function<void(TArgs...)>&& function) {
      addHandler(EventHandler<TArgs...>(function));
    }

    void operator-=(const EventHandler<TArgs...>& handler) {
      remove(handler.getId());
    }

    void remove(Atom eventHandlerId) {
      if (eventHandlerId == Atom())
        return;

      for (auto it = _handlers.begin(); it != _handlers.end(); ++it) {
        if (it->getId() == eventHandlerId) {
          _handlers.erase(it);
          return;
        }
      }
    }

    void operator()(TArgs... args) const {
      auto handlers = _handlers;

      for (auto handler : handlers) {
        handler(args...);
      }
    }
  };
}
#endif //NOVELRT_UTILITIES_EVENT_H
