// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_CORE_ATOM_H
#define NOVELRT_CORE_ATOM_H

namespace NovelRT::Core
{
    class Atom
    {
        friend class AtomHashFunction;

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

    class AtomHashFunction
    {
    public:
        size_t operator()(Atom atom) const noexcept
        {
            return static_cast<size_t>(atom._value);
        }
    };
}

namespace std
{
    template<> class numeric_limits<NovelRT::Core::Atom> : public numeric_limits<uintptr_t>
    {
    };
}

#endif // NOVELRT_CORE_ATOM_H
