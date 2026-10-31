#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>
#include <cstring>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <variant>

#include <NovelRT/Ecs/Animation/Easing.hpp>
#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EcsUtils.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Maths/Utilities.hpp>

namespace NovelRT::Ecs::Animation
{
    /**
     * @brief Requests a finite number of complete tween cycles.
     * @details A Repeat cycle contains one forward pass. A PingPong cycle contains an outward and a return pass.
     */
    struct TweenCycles
    {
        /**
         * @brief The total number of cycles to execute, including the first cycle.
         * @details Must be greater than zero. Validation occurs when the tween is scheduled.
         */
        uint32_t count;
    };

    /**
     * @brief Requests repetition without a cycle limit.
     * @details The job continues until cancelled or until the target component is absent from the committed state.
     */
    struct TweenForever
    {
    };

    /**
     * @brief Determines how the tween proceeds between animation passes.
     */
    enum class TweenLoopMode
    {
        /**
         * @brief Repeats forward movement for each cycle.
         * @details ToTarget restarts from its captured starting value; ByOffset advances both endpoints by the offset.
         */
        Repeat,
        /**
         * @brief Alternates outward and return passes between the captured endpoints.
         * @details One complete cycle includes both directions and takes twice the supplied duration.
         */
        PingPong
    };

    /**
     * @brief Configures the number of cycles and the behaviour between passes of a tween.
     * @details The default configuration executes one forward pass without repetition.
     */
    struct TweenOptions
    {
        /**
         * @brief A finite total cycle count or an instruction to repeat indefinitely.
         * @details Defaults to one cycle. A finite count of zero is rejected when the tween is scheduled.
         */
        std::variant<TweenCycles, TweenForever> repetition = TweenCycles{1};
        /**
         * @brief The behaviour used between passes, defaulting to forward repetition.
         */
        TweenLoopMode loopMode = TweenLoopMode::Repeat;
    };

    /**
     * @brief Requires a type whose object representation can be copied as bytes.
     * @details Trivial copyability does not guarantee that zeroed bytes represent a valid, neutral ECS instruction.
     * @tparam T The type to inspect.
     */
    template<typename T>
    concept IsTriviallyCopyable = std::is_trivially_copyable_v<T>; // TODO: We should probably move this out of here and
                                                                   // update other parts of the ECS - Matt J.

    /**
     * @brief Extracts the component and value types from a pointer to a component data member.
     * @tparam T The pointer-to-member type. Types that do not match the specialisation have no definition.
     */
    template<typename T>
    struct MemberPointerTraits;

    /**
     * @brief Describes the types associated with a component data-member pointer.
     * @tparam TComponent The component type containing the member.
     * @tparam TValue The type of the selected member.
     */
    template<typename TComponent, typename TValue>
    struct MemberPointerTraits<TValue TComponent::*>
    {
        /** @brief The component type containing the member. */
        using ComponentType = TComponent;
        /** @brief The type of the selected member value. */
        using ValueType = TValue;
    };

    /**
     * @brief Prepares component instructions by zeroing their entire object representation.
     *
     * @details The current component argument is ignored. The tween assigns the selected member's calculated
     * difference after this factory returns.
     *
     * @warning All-zero bytes must represent a valid instruction that leaves unrelated members unchanged under
     * the component's merge rules. Trivial copyability alone does not establish this property. Supply a custom
     * instruction factory when the component requires another neutral representation or has replacement fields.
     */
    struct ZeroedInstructionFactory
    {
        /**
         * @brief Creates a zeroed instruction independently of the supplied current component.
         * @tparam TComponent A default-constructible, trivially copyable component with a zero-neutral representation.
         * @return A component instruction with all bytes set to zero.
         */
        template<IsTriviallyCopyable TComponent>
        [[nodiscard]] TComponent operator()(const TComponent& /*unused*/) const noexcept
        {

            TComponent instruction{};
            std::memset(static_cast<void*>(&instruction), 0, sizeof(instruction));

            return instruction;
        }
    };

    /**
     * @brief Adapts the clamped maths lerp function to the tween interpolation policy interface.
     * @tparam TValue A value type satisfying Maths::Utilities::LinearlyInterpolatable.
     */
    template<typename TValue>
    struct DefaultTweenInterpolator
    {
        /**
         * @brief Interpolates between the supplied endpoints using clamped progress.
         * @param start The starting value for this pass.
         * @param target The destination value for this pass.
         * @param progress The eased progress, clamped to [0, 1] by Maths::Utilities::Lerp.
         * @return The interpolated value, or the exact corresponding endpoint outside the interpolation interval.
         * @note Easing values outside [0, 1] do not produce overshoot with this default interpolator.
         */
        [[nodiscard]] TValue operator()(const TValue& start, const TValue& target, float progress) const
        {
            return Maths::Utilities::Lerp(start, target, progress);
        }
    };

    /**
     * @brief Schedules additive animations of one component data member as ECS system jobs.
     *
     * @details Member selects the component type and field at compile time; the entity supplied to ToTarget or
     * ByOffset selects the component instance. Tween itself is stateless. Each scheduled job owns its captured
     * endpoints, policy objects and timing state, and captures the starting value on its first execution.
     *
     * For the current pass, let \f$s\f$ and \f$e\f$ be its endpoints, \f$t\f$ its normalised elapsed time,
     * \f$E\f$ the easing policy and \f$I\f$ the interpolation policy. The requested member value is:
     * \f[
     *     v = I(s, e, E(t)).
     * \f]
     * If \f$c\f$ is the member value in the committed snapshot, the job assigns \f$v-c\f$ to that member in
     * an instruction prepared by TInstructionFactory. Instructions follow normal ECS buffering and merge rules.
     * Concurrent writers can affect the resulting component value; coordinating those writers is the caller's
     * responsibility. Values use the selected member's coordinate space without parent or world-space conversion.
     *
     * The job finishes if the component is absent when an invocation reads the committed state. The returned SystemId
     * can be passed to Catalogue::CancelSystemJob to stop future invocations. Cancellation does not retract instructions
     * that have already been submitted, reset the value, or force the final endpoint.
     *
     * @code{.cpp}
     * using PositionTween = Tween<&Components::TransformComponent::position, Easing::InOutCubic>;
     * auto jobId = PositionTween::ToTarget(
     *     catalogue, entity, Maths::GeoVector2F{100.0f, 0.0f}, std::chrono::milliseconds{500});
     * @endcode
     *
     * @tparam Member A pointer to a writable data member of a registered, trivially copyable ECS component.
     * The member must support additive updates, subtraction and multiplication by a float scalar.
     * @tparam TEasing A default-constructible, copy-constructible policy callable on a const instance with float
     * progress, returning a float-compatible value. Defaults to Easing::Linear.
     * @tparam TInstructionFactory A copy-constructible callable accepting the current component and returning a
     * component instruction that preserves unrelated members under its merge rules. A factory instance can be supplied
     * when scheduling; otherwise it is default-constructed. Defaults to ZeroedInstructionFactory.
     * @tparam TInterpolator A default-constructible, copy-constructible policy callable on a const instance with the
     * start value, target value and eased float progress, returning a ValueType-compatible value. Defaults to clamped
     * linear interpolation through DefaultTweenInterpolator.
     */
    template<auto Member,
             typename TEasing = Easing::Linear,
             typename TInstructionFactory = ZeroedInstructionFactory,
             typename TInterpolator =
                 DefaultTweenInterpolator<typename MemberPointerTraits<decltype(Member)>::ValueType>>
    class Tween
    {
    public:
        /** @brief The component type containing the selected member. */
        using ComponentType = typename MemberPointerTraits<decltype(Member)>::ComponentType;
        /** @brief The type of the selected member being animated. */
        using ValueType = typename MemberPointerTraits<decltype(Member)>::ValueType;

    private:
        using TickCount = Timing::GameClock::rep;

        // TODO: I don't know if there's an argument to maybe make an interface to jobs looking at how much state we're
        // tracking, or maybe this is just me being unsure how to store it in the ECS. - Matt J.
        struct TweenJob
        {
            EntityId entity;
            ValueType target;
            TickCount durationTicks;
            bool pingPong;
            bool forever;
            uint64_t remainingLegs;

            TInstructionFactory instructionFactory;
            // Empty for ToTarget; populated for ByOffset.
            std::optional<ValueType> offset;
            TEasing easing{};
            TInterpolator interpolator{};

            std::optional<ValueType> start{};
            TickCount elapsedTicks = 0;
            bool returning = false;

            // Advances within the current leg and returns the number
            // of leg boundaries crossed AKA where one one start-to-end animation pass finishes, and another begins.
            TickCount AdvanceTime(Timing::GameClock::duration delta)
            {
                const TickCount deltaTicks = delta.count();

                TickCount crossedLegs = deltaTicks / durationTicks;
                const TickCount leftoverTicks = deltaTicks % durationTicks;

                const TickCount ticksUntilEndpoint = durationTicks - elapsedTicks;

                if (leftoverTicks >= ticksUntilEndpoint)
                {
                    ++crossedLegs;
                    elapsedTicks = leftoverTicks - ticksUntilEndpoint;
                }
                else
                {
                    elapsedTicks += leftoverTicks;
                }

                return crossedLegs;
            }

            void AdvanceOffsetEndpoints(TickCount crossedLegs, bool finished)
            {
                if (!offset.has_value() || pingPong)
                {
                    return;
                }

                // On completion, stop at the final permitted pass.
                const uint64_t passesToAdvance = finished ? remainingLegs - 1 : crossedLegs;

                if (passesToAdvance == 0)
                {
                    return;
                }

                const ValueType displacement = offset.value() * static_cast<float>(passesToAdvance);

                start = start.value() + displacement;
                target = target + displacement;
            }

            ValueType CalculateDesiredValue(bool finished, bool crossedBoundary) const
            {
                if (finished)
                {
                    return pingPong ? start.value() : target;
                }

                if (crossedBoundary && elapsedTicks == 0)
                {
                    const bool reachedStart = (pingPong && !returning) || (!pingPong && offset.has_value());

                    return reachedStart ? start.value() : target;
                }

                const auto progress =
                    static_cast<float>(static_cast<double>(elapsedTicks) / static_cast<double>(durationTicks));

                const auto& from = returning ? target : start.value();
                const auto& to = returning ? start.value() : target;

                return interpolator(from, to, easing(progress));
            }

            bool operator()(Timing::Timestamp delta, Catalogue context)
            {
                auto view = context.GetComponentView<ComponentType>();

                ComponentType current{};

                if (!view.TryGetComponent(entity, current))
                {
                    return true;
                }

                if (!start.has_value())
                {
                    start.emplace(current.*Member);

                    if (offset.has_value())
                    {
                        target = start.value() + offset.value();
                    }
                }

                const TickCount crossedLegs = AdvanceTime(delta.time_since_epoch());

                const bool finished = !forever && crossedLegs >= remainingLegs;

                AdvanceOffsetEndpoints(crossedLegs, finished);

                if (!finished)
                {
                    if (!forever)
                    {
                        remainingLegs -= crossedLegs;
                    }

                    // this branch is what enables the ping pong logic to work by swapping the from and to states over.
                    if (pingPong && crossedLegs % 2 != 0)
                    {
                        returning = !returning;
                    }
                }

                const ValueType desired = CalculateDesiredValue(finished, crossedLegs > 0);

                auto instruction = instructionFactory(current);
                instruction.*Member = desired - current.*Member;

                view.PushComponentUpdateInstruction(entity, instruction);

                return finished;
            }
        };

        static SystemId Schedule(Catalogue& catalogue,
                                 EntityId entity,
                                 ValueType target,
                                 bool byOffset,
                                 Timing::GameClock::duration duration,
                                 TweenOptions options,
                                 TInstructionFactory instructionFactory)
        {

            const TickCount durationTicks = duration.count();

            if (durationTicks == 0)
            {
                throw std::invalid_argument("Tween duration must be greater than zero.");
            }

            const auto* cycles = std::get_if<TweenCycles>(&options.repetition);

            if (cycles && cycles->count == 0)
            {
                throw std::invalid_argument("Tween cycle count must be greater than zero.");
            }

            const bool pingPong = options.loopMode == TweenLoopMode::PingPong;

            // A ping-pong cycle contains two legs.
            const uint64_t remainingLegs = cycles ? uint64_t{cycles->count} * (pingPong ? 2u : 1u) : 0;

            std::optional<ValueType> offset;

            if (byOffset)
            {
                offset.emplace(target);
            }

            return catalogue.ScheduleSystemJob(TweenJob{.entity = entity,
                                                        .target = std::move(target),
                                                        .durationTicks = durationTicks,
                                                        .pingPong = pingPong,
                                                        .forever = cycles == nullptr,
                                                        .remainingLegs = remainingLegs,
                                                        .instructionFactory = std::move(instructionFactory),
                                                        .offset = std::move(offset)});
        }

    public:
        /**
         * @brief Creates and schedules a new tween, based on an absolute target, and applies it to the Member on the
         * given entity.
         *
         * @details The starting value is captured when the job first executes. Using vectors as an example, if the
         * member starts at (0, 0) and the target is (0, 10), it will animate to (0, 10). With ordinary repetition,
         * each subsequent cycle restarts from the captured starting value and animates to the same target.
         * Changes made to the member by other code do not change these captured endpoints.
         *
         * With ping-pong enabled, the tween animates between the captured starting value and the target,
         * returning to the starting value to complete each cycle.
         *
         * @param catalogue The ECS context used to schedule the job.
         * @param entity The entity whose component member will be animated.
         * @param target The destination value.
         * @param duration The duration of one directional pass. A complete ping-pong cycle takes twice this duration.
         * @param options The repetition and looping configuration values. These determine how many cycles execute
         * and whether the tween uses ordinary repetition or ping-pong.
         * @param instructionFactory The factory used to prepare component instructions before the member's
         * calculated difference is assigned. It must preserve unrelated members under the component's merge rules.
         * @return The SystemId that represents the scheduled job. This can be used to cancel the tween from another
         * Catalogue belonging to the same SystemScheduler.
         * @throws std::invalid_argument If duration or the finite cycle count is zero.
         */
        [[nodiscard]] static SystemId ToTarget(Catalogue& catalogue,
                                               EntityId entity,
                                               ValueType target,
                                               Timing::GameClock::duration duration,
                                               TweenOptions options = {},
                                               TInstructionFactory instructionFactory = {})
        {
            return Schedule(catalogue, entity, std::move(target), false, duration, options,
                            std::move(instructionFactory));
        }

        /**
         * @brief Creates and schedules a new tween, based on a relative offset, and applies it to the Member on the
         * given entity.
         *
         * @details The starting value is captured when the job first executes. Using vectors as an example, if the
         * member starts at (0, 0) and the offset is (0, 10), it will animate to (0, 10). With ordinary repetition,
         * subsequent cycles animate from (0, 10) to (0, 20), then from (0, 20) to (0, 30), and so on.
         *
         * With ping-pong enabled, the tween animates between the captured starting value and that value plus the
         * offset, returning to the starting value to complete each cycle.
         *
         * @param catalogue The ECS context used to schedule the job.
         * @param entity The entity whose component member will be animated.
         * @param offset The displacement applied by each forward cycle, or by the outward pass of a ping-pong cycle.
         * @param duration The duration of one directional pass. A complete ping-pong cycle takes twice this duration.
         * @param options The repetition and looping configuration values. These determine how many cycles execute
         * and whether the tween uses ordinary repetition or ping-pong.
         * @param instructionFactory The factory used to prepare component instructions before the member's
         * calculated difference is assigned. It must preserve unrelated members under the component's merge rules.
         * @return The SystemId that represents the scheduled job. This can be used to cancel the tween from another
         * Catalogue belonging to the same SystemScheduler.
         * @throws std::invalid_argument If duration or the finite cycle count is zero.
         */
        [[nodiscard]] static SystemId ByOffset(Catalogue& catalogue,
                                               EntityId entity,
                                               ValueType offset,
                                               Timing::GameClock::duration duration,
                                               TweenOptions options = {},
                                               TInstructionFactory instructionFactory = {})
        {
            return Schedule(catalogue, entity, std::move(offset), true, duration, options,
                            std::move(instructionFactory));
        }
    };
}
