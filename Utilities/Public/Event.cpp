module;

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <algorithm>
#include <functional>
#include <vector>

export module NovelRT.Utilities:Event;
import :Atom;

namespace NovelRT::Utilities
{
    export template<typename... TArgs>
    class EventHandler
    {
    private:
        Atom _id;
        std::function<void(TArgs...)> _function;
        inline static AtomFactory& _eventIdFactory = AtomFactoryDatabase::GetFactory("EventHandler");

    public:
        EventHandler() : EventHandler(nullptr)
        {
        }

        explicit EventHandler(const std::function<void(TArgs...)>& function)
            : _id((function != nullptr) ? _eventIdFactory.GetNext() : Atom()), _function(function)
        {
        }

        void operator()(TArgs... args) const
        {
            _function(std::forward<TArgs>(args)...);
        }

        Atom getId() const noexcept
        {
            return _id;
        }

        bool operator==(const EventHandler<TArgs...>& other) const noexcept
        {
            return _id == other._id;
        }

        bool operator!=(const EventHandler<TArgs...>& other) const noexcept
        {
            return _id != other._id;
        }
    };

    export template<>
    class EventHandler<void>
    {
    private:
        Atom _id;
        std::function<void()> _function;
        inline static AtomFactory& _eventIdFactory = AtomFactoryDatabase::GetFactory("EventHandler");

    public:
        EventHandler() : EventHandler(nullptr)
        {
        }

        explicit EventHandler(const std::function<void(void)>& function)
        : _id((function != nullptr) ? _eventIdFactory.GetNext() : Atom()), _function(function)
        {
        }

        void operator()() const
        {
            _function();
        }

        Atom getId() const noexcept
        {
            return _id;
        }

        bool operator==(const EventHandler<void>& other) const noexcept
        {
            return _id == other._id;
        }

        bool operator!=(const EventHandler<void>& other) const noexcept
        {
            return _id != other._id;
        }
    };

    export template<typename... TArgs>
    class Event
    {
    private:
        std::vector<EventHandler<TArgs...>> _handlers;

    public:
        Event() : _handlers(std::vector<EventHandler<TArgs...>>())
        {
        }

        size_t getHandlerCount() const noexcept
        {
            return _handlers.size();
        }

        void operator+=(const EventHandler<TArgs...>& handler)
        {
            if (handler.getId() != Atom())
            {
                _handlers.emplace_back(handler);
            }
        }

        void operator+=(const std::function<void(TArgs...)>& function)
        {
            auto handler = EventHandler<TArgs...>(function);
            *this += handler;
        }

        void operator-=(const EventHandler<TArgs...>& handler)
        {
            if (handler.getId() == Atom())
                return;

            auto match = std::find(_handlers.cbegin(), _handlers.cend(), handler);

            if (match != _handlers.cend())
                _handlers.erase(match);
        }

        void operator-=(Atom atom)
        {
            if (atom == Atom())
                return;

            for (auto it = _handlers.begin(); it != _handlers.end(); ++it)
            {
                if (it->getId() == atom)
                {
                    _handlers.erase(it); // Remove the current item
                    return;
                }
            }
        }

        void operator()(TArgs... args) const
        {
            auto handlers = _handlers;

            for (auto handler : handlers)
            {
                handler(args...);
            }
        }
    };

    export template<>
    class Event<void>
    {
    private:
        std::vector<EventHandler<void>> _handlers;

    public:
        Event() : _handlers(std::vector<EventHandler<void>>())
        {
        }

        size_t getHandlerCount() const noexcept
        {
            return _handlers.size();
        }

        void operator+=(const EventHandler<void>& handler)
        {
            if (handler.getId() != Atom())
            {
                _handlers.emplace_back(handler);
            }
        }

        void operator+=(const std::function<void()>& function)
        {
            auto handler = EventHandler<void>(function);
            *this += handler;
        }

        void operator-=(const EventHandler<void>& handler)
        {
            if (handler.getId() == Atom())
                return;

            auto match = std::find(_handlers.cbegin(), _handlers.cend(), handler);

            if (match != _handlers.cend())
                _handlers.erase(match);
        }

        void operator-=(Atom atom)
        {
            if (atom == Atom())
                return;

            for (auto it = _handlers.begin(); it != _handlers.end(); ++it)
            {
                if (it->getId() == atom)
                {
                    _handlers.erase(it); // Remove the current item
                    return;
                }
            }
        }

        void operator()() const
        {
            auto handlers = _handlers;

            for (auto handler : handlers)
            {
                handler();
            }
        }
    };
}
