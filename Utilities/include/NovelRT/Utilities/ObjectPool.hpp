#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <deque>
#include <functional>
#include <memory>

namespace NovelRT::Utilities
{
    template<typename T>
    class ObjectPool;

    template<typename T>
    class ObjectPoolRef
    {
    private:
        std::shared_ptr<T> _object;
        std::reference_wrapper<ObjectPool<T>> _owningPool;

    public:
        ObjectPoolRef(std::shared_ptr<T>&& object, ObjectPool<T>& owningPool) noexcept
            : _object(std::move(object)), _owningPool(std::ref(owningPool))
        {
        }

        ObjectPoolRef(const ObjectPoolRef&) = delete;
        ObjectPoolRef& operator=(const ObjectPoolRef&) = delete;

        ObjectPoolRef(ObjectPoolRef&&) = default;
        ObjectPoolRef& operator=(ObjectPoolRef&&) = default;

        ~ObjectPoolRef() noexcept
        {
            _owningPool.get().Return(this);
        }

        T& operator*() const noexcept
        {
            return _object.get();
        }

        T* operator->() const noexcept
        {
            return _object.get();
        }

        [[nodiscard]] std::shared_ptr<T> GetObject() const noexcept
        {
            return _object;
        }

        [[nodiscard]] const ObjectPool<T>& GetOwningPool() const noexcept
        {
            return _owningPool.get();
        }
    };

    template<typename T>
    class ObjectPool
    {
    public:
        using size_type = typename std::deque<std::shared_ptr<T>>::size_type;
        using iterator = typename std::deque<std::shared_ptr<T>>::iterator;
        using const_iterator = typename std::deque<std::shared_ptr<T>>::const_iterator;

    private:
        std::deque<std::shared_ptr<T>> _objects;
        std::function<std::shared_ptr<T>()> _factory;

    public:
        ObjectPool(std::function<std::shared_ptr<T>()> factory) noexcept : _factory(factory)
        {
        }

        ObjectPoolRef<T> Get()
        {
            if (_objects.empty())
            {
                _objects.emplace_back(_factory());
            }

            auto ptr = _objects.front();
            _objects.pop_front();
            return ObjectPoolRef<T>(std::move(ptr), *this);
        }

        void Return(ObjectPoolRef<T>* ref)
        {
            if (&ref->GetOwningPool() != this)
            {
                return; // how did you get here?
            }

            _objects.emplace_back(ref->GetObject());
        }

        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] size_type size() const noexcept
        {
            return _objects.size();
        }

        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] iterator begin() noexcept
        {
            return _objects.begin();
        }

        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] const_iterator begin() const noexcept
        {
            return _objects.begin();
        }

        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] iterator end() noexcept
        {
            return _objects.end();
        }

        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] const_iterator end() const noexcept
        {
            return _objects.end();
        }
    };
}
