// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <atomic>
#include <cstddef>

#ifndef NOVELRT_ATOM_H
#define NOVELRT_ATOM_H

namespace NovelRT {
  class Atom {
    friend class AtomHashFunction;
  private:
    uintptr_t _value;

  public:
    explicit Atom() noexcept : Atom(0) {
    }

    Atom(uintptr_t value) noexcept :
      _value(value) {
    }

    bool operator==(Atom other) const noexcept {
      return _value == other._value;
    }

    bool operator!=(Atom other) const noexcept {
      return _value != other._value;
    }

    bool operator<(Atom other) const noexcept {
      return _value < other._value;
    }

    bool operator<=(Atom other) const noexcept {
      return _value <= other._value;
    }

    bool operator>(Atom other) const noexcept {
      return _value > other._value;
    }

    bool operator>=(Atom other) const noexcept {
      return _value >= other._value;
    }

    operator uintptr_t() noexcept {
      return _value;
    }

    // TODO: These should be internal to NovelRT

    static Atom getNextEventHandlerId() noexcept {
      static std::atomic_uintptr_t _nextEventHandlerId(0);
      auto value = ++_nextEventHandlerId;
      return Atom(value);
    }

    static Atom getNextFontSetId() noexcept {
      static std::atomic_uintptr_t _nextFontSetId(0);
      auto value = ++_nextFontSetId;
      return Atom(value);
    }

    static Atom getNextTextureId() noexcept {
      static std::atomic_uintptr_t _nextTextureId(0);
      auto value = ++_nextTextureId;
      return Atom(value);
    }
    
    static Atom getNextComponentTypeId() noexcept {
      static std::atomic_uintptr_t _nextComponentTypeId(0);
      auto value = ++_nextComponentTypeId;
      return Atom(value);
    }

    static Atom getNextEntityId() noexcept {
      static std::atomic_uintptr_t _nextEntityId(0);
      auto value = ++ _nextEntityId;
      return Atom(value);
    }

    static Atom getNextSystemId() noexcept {
      static std::atomic_uintptr_t _nextSystemId(0);
      auto value = ++ _nextSystemId;
      return Atom(value);
    }
  };

  class AtomHashFunction {
    public:
    size_t operator()(Atom atom) const noexcept {
      return static_cast<size_t>(atom._value);
    }
  };
}

#endif // NOVELRT_ATOM_H
