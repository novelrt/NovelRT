// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ATOM_H
#define NOVELRT_ATOM_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT
{
class Atom
{
  private:
    uintptr_t _value;

  public:
    explicit Atom() : Atom(0)
    {
    }

    explicit Atom(uintptr_t value) : _value(value)
    {
    }

    bool operator==(Atom other) const
    {
        return _value == other._value;
    }

    bool operator!=(Atom other) const
    {
        return _value != other._value;
    }

    bool operator<(Atom other) const
    {
        return _value < other._value;
    }

    bool operator<=(Atom other) const
    {
        return _value <= other._value;
    }

    bool operator>(Atom other) const
    {
        return _value > other._value;
    }

    bool operator>=(Atom other) const
    {
        return _value >= other._value;
    }

    // TODO: These should be internal to NovelRT

    static Atom getNextEventHandlerId()
    {
        static std::atomic_uintptr_t _nextEventHandlerId(0);
        auto value = ++_nextEventHandlerId;
        return Atom(value);
    }

    static Atom getNextFontSetId()
    {
        static std::atomic_uintptr_t _nextFontSetId(0);
        auto value = ++_nextFontSetId;
        return Atom(value);
    }

    static Atom getNextTextureId()
    {
        static std::atomic_uintptr_t _nextTextureId(0);
        auto value = ++_nextTextureId;
        return Atom(value);
    }
};
} // namespace NovelRT

#endif // NOVELRT_ATOM_H
