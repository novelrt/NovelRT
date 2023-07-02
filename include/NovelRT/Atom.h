// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <atomic>
#include <cstddef>
#include <limits>
#include <string>

#ifndef NOVELRT_ATOM_H
#define NOVELRT_ATOM_H

namespace NovelRT
{
    using Atom = uintptr_t;

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

#endif // NOVELRT_ATOM_H
