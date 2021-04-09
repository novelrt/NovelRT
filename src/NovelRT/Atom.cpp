// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>

namespace NovelRT
{
    Atom Atom::getNextEventHandlerId() noexcept
    {
        static std::atomic_uintptr_t _nextEventHandlerId(0);
        auto value = ++_nextEventHandlerId;
        return Atom(value);
    }

    Atom Atom::getNextFontSetId() noexcept
    {
        static std::atomic_uintptr_t _nextFontSetId(0);
        auto value = ++_nextFontSetId;
        return Atom(value);
    }

    Atom Atom::getNextTextureId() noexcept
    {
        static std::atomic_uintptr_t _nextTextureId(0);
        auto value = ++_nextTextureId;
        return Atom(value);
    }

    Atom Atom::getNextComponentTypeId() noexcept
    {
        static std::atomic_uintptr_t _nextComponentTypeId(0);
        auto value = ++_nextComponentTypeId;
        return Atom(value);
    }

    Atom Atom::getNextEntityId() noexcept
    {
        static std::atomic_uintptr_t _nextEntityId(0);
        auto value = ++_nextEntityId;
        return Atom(value);
    }

    Atom Atom::getNextSystemId() noexcept
    {
        static std::atomic_uintptr_t _nextSystemId(0);
        auto value = ++_nextSystemId;
        return Atom(value);
    }
} // namespace NovelRT
