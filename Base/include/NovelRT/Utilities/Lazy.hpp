#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <functional>
#include <memory>
#include <optional>

namespace NovelRT::Utilities
{
    template<typename T>
    class Lazy
    {
    private:
        std::function<T()> _delegate;
        mutable std::optional<T> _actual;

    public:
        Lazy(std::function<T()> delegate) : _delegate(std::move(delegate)), _actual()
        {
        }

        template<typename U = std::remove_cv_t<T>>
        Lazy(U&& eagerStartValue, std::function<T()> delegate)
            : _delegate(std::move(delegate)), _actual(std::forward(eagerStartValue))
        {
        }

        constexpr T& Get() &
        {
            if (!HasValue())
            {
                std::optional<T>(std::move(_delegate())).swap(_actual);
            }

            return _actual.value();
        }

        constexpr const T& Get() const&
        {
            if (!HasValue())
            {
                std::optional<T>(std::move(_delegate())).swap(_actual);
            }

            return _actual.value();
        }

        constexpr T&& Get() &&
        {
            if (!HasValue())
            {
                std::optional<T>(std::move(_delegate())).swap(_actual);
            }

            return std::move(_actual.value());
        }

        constexpr const T&& Get() const&&
        {
            if (!HasValue())
            {
                std::optional<T>(std::move(_delegate())).swap(_actual);
            }

            return std::move(_actual.value());
        }

        void Reset() noexcept
        {
            _actual.reset();
        }

        void Reset(T newExplicitValue) noexcept
        {
            _actual = newExplicitValue;
        }

        [[nodiscard]] bool HasValue() const noexcept
        {
            return _actual.has_value();
        }
    };
}
