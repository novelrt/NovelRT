// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_LIFETIMEEXTENDER_H
#define NOVELRT_INTEROP_LIFETIMEEXTENDER_H
#include <memory>
#include <unordered_map>
#include <vector>

// Unfortunately need to include Threading.h for ConcurrentLifetime, as
// the other solution requires include order madness.
// Another solution could be to create ConcurrentLifetimeExtender.h,
// but that's maybe too much, who knows?
#include <NovelRT/Threading/Threading.h>

namespace NovelRT::Interop
{
    /*
     * Extends the lifetime of objects contained in a shared_ptr-like structure.
     * By default, this stores instances of shared_ptr, but can be configured to some
     * other pointer type using the template argument P.
     * This lets the API consumer take ownership of an object without double indirection.
     *
     * This class uses an unordered_map internally, which map pointers to their shared_ptr.
     */
    template<template<typename> typename P = std::shared_ptr> class PtrLifetime
    {
    public:
        PtrLifetime() = delete;

        template<typename T> [[nodiscard]] static std::unordered_map<T*, P<T>>& AliveObjects() noexcept
        {
            static std::unordered_map<T*, P<T>> aliveObjects{};

            return aliveObjects;
        }

        // KeepAlive does nothing if the pointer already exists.
        template<typename T> static void KeepAlive(P<T>&& object) noexcept
        {
            AliveObjects<T>().insert({object.get(), std::move(object)});
        }

        template<typename T> static void KeepAlive(P<T>& object) noexcept
        {
            AliveObjects<T>().insert({object.get(), object});
        }

        template<typename T> [[nodiscard]] static P<T> Find(T* object) noexcept
        {
            auto& alive = AliveObjects<T>();
            if (auto finding = alive.find(object); finding != alive.end())
            {
                return finding->second;
            }
            else
            {
                return nullptr;
            }
        }

        template<typename T> static bool Release(T* object) noexcept
        {
            return AliveObjects<T>().erase(object) == 1;
        }
    };

    using Lifetime = PtrLifetime<>;
    using ConcurrentLifetime = PtrLifetime<NovelRT::Threading::ConcurrentSharedPtr>;
}

#endif // NOVELRT_INTEROP_LIFETIMEEXTENDER_H
