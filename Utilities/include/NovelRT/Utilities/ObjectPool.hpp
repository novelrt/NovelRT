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
        ObjectPoolRef(std::shared_ptr<T> object, ObjectPool<T>& owningPool) noexcept
            : _object(std::move(object)), _owningPool(owningPool)
        {
        }

        ~ObjectPoolRef() noexcept
        {
            _owningPool.Return(this);
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

            return ObjectPoolRef<T>(_objects.pop_front(), *this);
        }

        void Return(ObjectPoolRef<T>* ref)
        {
            if (&ref->GetOwningPool() != this)
            {
                return; // how did you get here?
            }

            _objects.emplace_back(ref->GetObject());
        }
    };
}
