// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UTILITIES_LAZY_H
#define NOVELRT_UTILITIES_LAZY_H

#include <functional>
#include <optional>

namespace NovelRT::Utilities
{
    template<typename T> class Lazy
    {
    private:
        std::function<T()> _delegate;
        std::optional<T> _actual;

    public:
        Lazy(std::function<T()> delegate) : _delegate(delegate), _actual()
        {
        }
        Lazy(T eagerStartValue, std::function<T()> delegate)
            : _delegate(delegate), _actual(eagerStartValue)
        {
        }

        T& getActual()
        {
            if (!isCreated())
            {
                _actual = _delegate();
            }

            return _actual.value();
        }

        void reset() noexcept
        {
            _actual.reset();
        }

        void reset(T newExplicitValue) noexcept
        {
            _actual = newExplicitValue;
        }

        [[nodiscard]] bool isCreated() const noexcept
        {
            return _actual.has_value();
        }
    };

    template<typename T> class Lazy<std::unique_ptr<T>>
    {
    private:
        std::function<T*()> _delegate;
        std::unique_ptr<T> _actual;

    public:
        explicit Lazy(std::function<T*()> delegate) : _delegate(delegate), _actual(std::unique_ptr<T>(nullptr))
        {
        }

        T* getActual()
        {
            if (!isCreated())
            {
                _actual = std::unique_ptr<T>(_delegate());
            }

            return _actual.get();
        }

        void reset() noexcept
        {
            _actual = nullptr;
        }

        void reset(T* newExplicitValue) noexcept
        {
            _actual.reset(newExplicitValue);
        }

        bool isCreated() const noexcept
        {
            return _actual != nullptr;
        }
    };

    template<typename T, typename Deleter> class Lazy<std::unique_ptr<T, Deleter>>
    {
    private:
        std::function<T*()> _delegate;
        std::unique_ptr<T, Deleter> _actual;

    public:
        Lazy(std::function<T*()> delegate, Deleter deleter)
            : _delegate(delegate), _actual(std::unique_ptr<T, Deleter>(nullptr, deleter))
        {
        }

        T* getActual()
        {
            if (!isCreated())
            {
                _actual = std::unique_ptr<T, Deleter>(_delegate(), _actual.get_deleter());
            }

            return _actual.get();
        }

        void reset() noexcept
        {
            _actual = nullptr;
        }

        void reset(T* newExplicitValue) noexcept
        {
            _actual.reset(newExplicitValue);
        }

        bool isCreated() const noexcept
        {
            return _actual != nullptr;
        }
    };
} // namespace NovelRT::Utilities
#endif // NOVELRT_UTILITIES_LAZY_H
