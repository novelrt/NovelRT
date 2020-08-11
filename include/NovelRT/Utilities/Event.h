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
            _id(Atom::getNextEventHandlerId()),
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

  public:
    Event() : _handlers(std::vector<EventHandler<TArgs...>>()) {
    }

    size_t getHandlerCount() const {
      return _handlers.size();
    }

    const EventHandler<TArgs...>& operator+=(const EventHandler<TArgs...>& handler) {
      if (handler.getId() != Atom()) {
        return _handlers.emplace_back(handler);
      }
      return handler;
    }

    const EventHandler<TArgs...>& operator+=(const std::function<void(TArgs...)>& function) {
      auto handler = EventHandler<TArgs...>(function);
      return *this += handler;
    }

    const EventHandler<TArgs...>& operator+=(std::function<void(TArgs...)>&& function) {
      auto handler = EventHandler<TArgs...>(function);
      return *this += handler;
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
