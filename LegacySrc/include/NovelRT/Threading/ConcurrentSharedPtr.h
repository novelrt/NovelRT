// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_CONCURRENTSHAREDPTR_H
#define NOVELRT_CONCURRENTSHAREDPTR_H

#ifndef NOVELRT_THREADING_H
#error NovelRT does not support including types explicitly by default. Please include Threading.h instead for the Threading namespace subset.
#endif

namespace NovelRT::Threading
{
    template<typename TValue> class ConcurrentSharedPtr
    {
    private:
        std::shared_ptr<TValue> _value;
        std::shared_ptr<tbb::mutex> _mutex;

    public:
        ConcurrentSharedPtr(std::shared_ptr<TValue> value, std::shared_ptr<tbb::mutex> mutex)
            : _value(std::move(value)), _mutex(std::move(mutex))
        {
        }

        explicit ConcurrentSharedPtr(std::shared_ptr<TValue> value)
            : _value(std::move(value)), _mutex(std::make_shared<tbb::mutex>())
        {
        }

        ConcurrentSharedPtr(std::nullptr_t) noexcept : _value(nullptr), _mutex(std::make_shared<tbb::mutex>())
        {
        }

        TValue* operator->()
        {
            return _value.get();
        }

        const TValue* operator->() const
        {
            return _value.get();
        }

        void lock()
        {
            _mutex->lock();
        }

        void unlock()
        {
            _mutex->unlock();
        }

        [[nodiscard]] std::shared_ptr<TValue>& GetUnderlyingSharedPtr() noexcept
        {
            return _value;
        }

        [[nodiscard]] const std::shared_ptr<TValue>& GetUnderlyingSharedPtr() const noexcept
        {
            return _value;
        }

        [[nodiscard]] std::shared_ptr<tbb::mutex>& GetMutex() noexcept
        {
            return _mutex;
        }

        [[nodiscard]] const std::shared_ptr<tbb::mutex>& GetMutex() const noexcept
        {
            return _mutex;
        }

        [[nodiscard]] TValue* get() noexcept
        {
            return _value.get();
        }

        [[nodiscard]] const TValue* get() const noexcept
        {
            return _value.get();
        }

        [[nodiscard]] TValue& operator*() noexcept
        {
            return *_value;
        }

        [[nodiscard]] const TValue& operator*() const noexcept
        {
            return *_value;
        }

        [[nodiscard]] bool operator!=(const ConcurrentSharedPtr<TValue>& other) const noexcept
        {
            return !(*this == other);
        }
    };

    template<typename TValue>
    [[nodiscard]] bool operator==(const ConcurrentSharedPtr<TValue>& lhs,
                                  const ConcurrentSharedPtr<TValue>& rhs) noexcept
    {
        return (lhs.GetUnderlyingSharedPtr() == rhs.GetUnderlyingSharedPtr()) && (lhs.GetMutex() == rhs.GetMutex());
    }

    template<typename TValue>
    [[nodiscard]] bool operator==(const ConcurrentSharedPtr<TValue>& lhs, std::nullptr_t) noexcept
    {
        return lhs.GetUnderlyingSharedPtr() == nullptr;
    }

    template<typename TValue>
    [[nodiscard]] bool operator==(std::nullptr_t, const ConcurrentSharedPtr<TValue>& rhs) noexcept
    {
        return rhs.GetUnderlyingSharedPtr() == nullptr;
    }

    template<typename TValue>
    [[nodiscard]] bool operator!=(const ConcurrentSharedPtr<TValue>& lhs, std::nullptr_t) noexcept
    {
        return lhs.GetUnderlyingSharedPtr() != nullptr;
    }

    template<typename TValue>
    [[nodiscard]] bool operator!=(std::nullptr_t, const ConcurrentSharedPtr<TValue>& rhs) noexcept
    {
        return rhs.GetUnderlyingSharedPtr() != nullptr;
    }

    template<typename TValue, typename... TArgs>
    [[nodiscard]] static ConcurrentSharedPtr<TValue> MakeConcurrentShared(TArgs&&... args)
    {
        return ConcurrentSharedPtr<TValue>(std::make_shared<TValue>(std::forward(args)...),
                                           std::make_shared<tbb::mutex>());
    }
}

#endif // NOVELRT_CONCURRENTSHAREDPTR_H
