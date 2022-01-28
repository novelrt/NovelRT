// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <atomic>
#include <cstddef>
#include <limits>

#ifndef NOVELRT_ATOM_H
#define NOVELRT_ATOM_H

namespace NovelRT
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

        // TODO: These should be internal to NovelRT

        static Atom GetNextEventHandlerId() noexcept;

        static Atom GetNextFontSetId() noexcept;

        static Atom GetNextTextureId() noexcept;

        static Atom GetNextComponentTypeId() noexcept;

        static Atom GetNextEntityId() noexcept;

        static Atom GetNextSystemId() noexcept;

        static Atom GetNextEcsTextureId() noexcept;

        static Atom GetNextEcsVertexDataId() noexcept;

        static Atom GetNextEcsPrimitiveId() noexcept;

        static Atom GetNextEcsGraphicsPipelineId() noexcept;

        static Atom GetNextEcsInputActionId() noexcept;

        static Atom GetNextEcsPrimitiveInfoConfigurationId() noexcept;
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
    template<> class numeric_limits<NovelRT::Atom> : public numeric_limits<uintptr_t>
    {
    };
}

#endif // NOVELRT_ATOM_H
