// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_CORE_UTILITIES_EVENT_H
#define NOVELRT_CORE_UTILITIES_EVENT_H

namespace NovelRT::Core::Utilities
{
    template<typename... TArgs> class EventHandler
    {
    private:
        NovelRT::Core::Atom _id;
        std::function<void(TArgs...)> _function;
        inline static NovelRT::Core::AtomFactory& _eventIdFactory = NovelRT::Core::AtomFactoryDatabase::GetFactory("EventHandler");

    public:
        EventHandler() : EventHandler(nullptr)
        {
        }

        explicit EventHandler(const std::function<void(TArgs...)>& function)
            : _id((function != nullptr) ? _eventIdFactory.GetNext() : NovelRT::Core::Atom()), _function(function)
        {
        }

        void operator()(TArgs... args) const
        {
            _function(std::forward<TArgs>(args)...);
        }

        NovelRT::Core::Atom getId() const noexcept
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

    template<typename... TArgs> class Event
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
            if (handler.getId() != NovelRT::Core::Atom())
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
            if (handler.getId() == NovelRT::Core::Atom())
                return;

            auto match = std::find(_handlers.cbegin(), _handlers.cend(), handler);

            if (match != _handlers.cend())
                _handlers.erase(match);
        }

        void operator-=(NovelRT::Core::Atom atom)
        {
            if (NovelRT::Core::Atom == NovelRT::Core::Atom())
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
}
#endif // NOVELRT_CORE_UTILITIES_EVENT_H
