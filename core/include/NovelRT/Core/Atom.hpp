#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <atomic>
#include <cstddef>
#include <limits>
#include <string>

namespace NovelRT
{
    class Atom
    {
    private:
        uintptr_t _value;

    public:
        constexpr Atom() noexcept : Atom(0)
        {
        }

        constexpr Atom(uintptr_t value) noexcept : _value(value)
        {
        }

        bool operator==(Atom other) const noexcept
        {
            return _value == other._value;
        }

        bool operator==(uintptr_t other) const noexcept
        {
            return _value == other;
        }

        bool operator!=(Atom other) const noexcept
        {
            return _value != other._value;
        }

        bool operator!=(uintptr_t other) const noexcept
        {
            return _value != other;
        }

        bool operator<(Atom other) const noexcept
        {
            return _value < other._value;
        }

        bool operator<=(Atom other) const noexcept
        {
            return _value <= other._value;
        }

        bool operator>(Atom other) const noexcept
        {
            return _value > other._value;
        }

        bool operator>=(Atom other) const noexcept
        {
            return _value >= other._value;
        }

        operator uintptr_t() const noexcept
        {
            return _value;
        }

        static Atom GetNextEcsPrimitiveInfoConfigurationId() noexcept;
    };

    class AtomFactory
    {
    private:
        std::atomic_uintptr_t _currentValue;
        bool _moved;

    public:
        AtomFactory() noexcept;
        explicit AtomFactory(Atom startingValue) noexcept;
        AtomFactory(const AtomFactory& other) noexcept;
        AtomFactory(AtomFactory&& other) noexcept;
        AtomFactory& operator=(const AtomFactory& other) noexcept;
        AtomFactory& operator=(AtomFactory&& other) noexcept;
        ~AtomFactory() = default;

        [[nodiscard]] Atom GetNext();

        void SetToValue(Atom newValue);
    };

    class AtomFactoryDatabase
    {
    public:
        [[nodiscard]] static AtomFactory& GetFactory(const std::string& factoryName) noexcept;
    };
}
