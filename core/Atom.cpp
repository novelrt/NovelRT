// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <mutex>
#include <unordered_map>

#include <NovelRT/Core/Atom.hpp>
#include <NovelRT/Core/Exceptions/InvalidOperationException.hpp>

namespace NovelRT
{
    Atom Atom::GetNextEcsPrimitiveInfoConfigurationId() noexcept
    {
        static std::atomic_uintptr_t _nextEcsPrimitiveInfoConfigurationId(0);
        auto value = ++_nextEcsPrimitiveInfoConfigurationId;
        return Atom(value);
    }

    AtomFactory::AtomFactory() noexcept : AtomFactory(0)
    {
    }

    AtomFactory::AtomFactory(Atom startingValue) noexcept : _currentValue(startingValue), _moved(false)
    {
    }

    AtomFactory::AtomFactory(const AtomFactory& other) noexcept
    {
        *this = other;
    }

    AtomFactory::AtomFactory(AtomFactory&& other) noexcept
    {
        *this = std::move(other);
    }

    AtomFactory& AtomFactory::operator=(const AtomFactory& other) noexcept
    {
        _currentValue = other._currentValue.load();
        return *this;
    }

    AtomFactory& AtomFactory::operator=(AtomFactory&& other) noexcept
    {
        other._moved = true;
        _currentValue = other._currentValue.load();
        return *this;
    }

    Atom AtomFactory::GetNext()
    {
        if (_moved)
        {
            throw Exceptions::InvalidOperationException("AtomFactory object has been moved. It is invalid to get the "
                                                        "next atomic value from a factory in this state.");
        }

        auto value = ++_currentValue;
        return value;
    }

    void AtomFactory::SetToValue(Atom value)
    {
        if (_moved)
        {
            throw Exceptions::InvalidOperationException("AtomFactory object has been moved. It is invalid to directly "
                                                        "set the current atomic value from a factory in this state.");
        }

        _currentValue = value;
    }

    AtomFactory& AtomFactoryDatabase::GetFactory(const std::string& factoryName) noexcept
    {
        //static tbb::mutex _mutex;
        static std::unordered_map<std::string, AtomFactory> _factories;
        //std::scoped_lock lock(_mutex);
        auto it = _factories.find(factoryName);

        if (it == _factories.end())
        {
            _factories[factoryName] = AtomFactory(0);
        }

        return _factories[factoryName];
    }
}
