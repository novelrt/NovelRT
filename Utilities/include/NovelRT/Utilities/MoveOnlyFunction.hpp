#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

namespace NovelRT::Utilities
{
    template<typename...>
    class MoveOnlyFunction;

    template <typename R, typename... Args>
    class MoveOnlyFunction<R(Args...)>
    {
    private:
        struct Callable
        {
            virtual ~Callable() = default;
            virtual R call(Args...) = 0;
            virtual const void* target() = 0;
        };
        template <typename F>
        struct SpecificCallable : Callable
        {
            template <typename T, typename = std::enable_if_t<!std::is_same_v<std::decay_t<T>, SpecificCallable>>>
            explicit SpecificCallable(T&& func) : func(std::forward<T>(func)) {};
        R call(Args... args) override
            {
                if constexpr(std::is_void_v<R>)
                { std::invoke(func, std::forward<Args>(args)...); }
                else
                { return std::invoke(func, std::forward<Args>(args)...); }
            }
            
            const void* target() override
            {
                return std::addressof(func);
            }
            F func;
        };

        std::unique_ptr<Callable> _ptr = nullptr;

    public:
        MoveOnlyFunction() = default;
        MoveOnlyFunction(const MoveOnlyFunction& other) = delete;
        MoveOnlyFunction& operator=(const MoveOnlyFunction& other) = delete;
        MoveOnlyFunction(MoveOnlyFunction&& other) noexcept = default;
        MoveOnlyFunction& operator=(MoveOnlyFunction&& other) noexcept = default;

        ~MoveOnlyFunction() = default;

        template <typename F, typename = std::enable_if_t<!std::is_same_v<std::decay_t<F>, MoveOnlyFunction> && std::is_invocable_r_v<R, F&, Args...>>>
        MoveOnlyFunction(F&& func) : _ptr(std::make_unique<SpecificCallable<std::decay_t<F>>>(std::forward<F>(func))) { }

        R operator()(Args... args) 
        {
            return _ptr->call(std::forward<Args>(args)...);
            
        }; 

        template <typename F>
        F* target() noexcept
        {
            return reinterpret_cast<F*>(const_cast<void*>(_ptr->target()));
        };

    };
}