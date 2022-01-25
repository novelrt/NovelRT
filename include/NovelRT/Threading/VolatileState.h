// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_VOLATILESTATE_H
#define NOVELRT_VOLATILESTATE_H

#ifndef NOVELRT_THREADING_H
#error NovelRT does not support including types explicitly by default. Please include Threading.h instead for the Threading namespace subset.
#endif

namespace NovelRT::Threading
{
    class VolatileState
    {
    private:
        std::atomic_uint32_t _value;
        inline void Swap(const VolatileState& swapTarget)
        {
            uint32_t value = swapTarget._value;
            _value = value;
        }

    public:
        static inline const uint32_t Uninitialised = 0;
        static inline const uint32_t Initialised = 1;

        VolatileState() noexcept;
        VolatileState(const VolatileState& other) noexcept;

        [[nodiscard]] inline bool IsInitialised() const noexcept
        {
            return _value == Initialised;
        }

        [[nodiscard]] inline uint32_t Transition(uint32_t to) noexcept
        {
            return _value.exchange(to);
        }

        void Transition(uint32_t from, uint32_t to);

        [[nodiscard]] bool TryTransition(uint32_t from,
                                         uint32_t to,
                                         uint32_t* outOptionalOriginalState = nullptr) noexcept;

        [[nodiscard]] inline operator uint32_t() const noexcept
        {
            return _value;
        }

        inline VolatileState& operator=(const VolatileState& other) noexcept
        {
            Swap(other);
            return *this;
        }
    };
}

#endif // !NOVELRT_VOLATILESTATE_H
