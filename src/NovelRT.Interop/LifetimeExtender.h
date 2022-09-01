// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_LIFETIMEEXTENDER_H
#define NOVELRT_INTEROP_LIFETIMEEXTENDER_H
#include <memory>
#include <vector>
/*
 * Extends the lifetime of objects contained in a shared_ptr.
 * This lets the API consumer take ownership of an object without double indirection.
 */
namespace NovelRT::Interop::Lifetime
{
    template<typename T> [[nodiscard]] std::vector<std::shared_ptr<T>>& AliveObjects() noexcept
    {
        static std::vector<std::shared_ptr<T>> aliveObjects{};

        return aliveObjects;
    }

    template<typename T> void KeepAlive(std::shared_ptr<T>&& object) noexcept
    {
        AliveObjects<T>().emplace_back(std::move(object));
    }

    template<typename T> void KeepAlive(const std::shared_ptr<T>& object) noexcept
    {
        AliveObjects<T>().emplace_back(object);
    }

    template<typename T> [[nodiscard]] std::shared_ptr<T> Find(T* object) noexcept
    {
        for (auto& aliveObject : AliveObjects<T>())
        {
            if (aliveObject.get() == object)
            {
                return aliveObject;
            }
        }
        return nullptr;
    }

    template<typename T> bool Release(T* object) noexcept
    {
        auto& aliveObjects = AliveObjects<T>();
        for (auto it = aliveObjects.begin(); it != aliveObjects.end(); ++it)
        {
            if ((*it).get() == object)
            {
                aliveObjects.erase(it);
                return true;
            }
        }
        return false;
    }
}

#endif // NOVELRT_INTEROP_LIFETIMEEXTENDER_H
