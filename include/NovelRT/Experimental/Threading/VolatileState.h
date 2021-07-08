// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_VOLATILESTATE_H
#define NOVELRT_EXPERIMENTAL_VOLATILESTATE_H

#ifndef NOVELRT_EXPERIMENTAL_THREADING_H
#error NovelRT does not support including types explicitly by default. Please include Threading.h instead for the Threading namespace subset.
#endif

namespace NovelRT::Experimental::Threading
{
    class VolatileState
    {
    private:
        std::atomic_uint32_t _value;

    public:
        static inline const uint32_t Uninitialised = 0;
        static inline const uint32_t Initialised = 1;

        VolatileState() noexcept;

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
    };
} // namespace NovelRT::Experimental::Threading

#endif // !NOVELRT_EXPERIMENTAL_VOLATILESTATE_H
