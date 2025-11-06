module;

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <atomic>
#include <string>

#ifndef __TBB_PREVIEW_MUTEXES
#define __TBB_PREVIEW_MUTEXES 1
#endif

#include <mutex>
#include <oneapi/tbb/mutex.h>
#include <unordered_map>

export module NovelRT.Utilities:Atom;

import NovelRT.Exceptions;

namespace NovelRT
{
    export using Atom = uintptr_t;

    export class AtomFactory
    {
    private:
        std::atomic_uintptr_t _currentValue;
        bool _moved;

    public:
        AtomFactory() noexcept : AtomFactory(0)
        {
        }

        explicit AtomFactory(Atom startingValue) noexcept : _currentValue(startingValue), _moved(false)
        {
        }

        AtomFactory(const AtomFactory& other) noexcept
        {
            *this = other;
        }

        AtomFactory(AtomFactory&& other) noexcept
        {
            *this = std::move(other);
        }

        AtomFactory& operator=(const AtomFactory& other) noexcept
        {
            _currentValue = other._currentValue.load();
            return *this;
        }

        AtomFactory& operator=(AtomFactory&& other) noexcept
        {
            other._moved = true;
            _currentValue = other._currentValue.load();
            return *this;
        }


        ~AtomFactory() = default;

        [[nodiscard]] Atom GetNext()
        {
            if (_moved)
            {
                throw Exceptions::InvalidOperationException("AtomFactory object has been moved. It is invalid to get the "
                "next atomic value from a factory in this state.");
            }

            auto value = ++_currentValue;
            return value;
        }

        void SetToValue(Atom newValue)
        {
            if (_moved)
            {
                throw Exceptions::InvalidOperationException("AtomFactory object has been moved. It is invalid to directly "
                "set the current atomic value from a factory in this state.");
            }

            _currentValue = newValue;
        }
    };

    export class AtomFactoryDatabase
    {
    public:
        [[nodiscard]] static AtomFactory& GetFactory(const std::string& factoryName) noexcept
        {
            static tbb::mutex _mutex;
            static std::unordered_map<std::string, AtomFactory> _factories;
            std::scoped_lock lock(_mutex);
            auto it = _factories.find(factoryName);

            if (it == _factories.end())
            {
                _factories[factoryName] = AtomFactory(0);
            }

            return _factories[factoryName];
        }
    };
}
