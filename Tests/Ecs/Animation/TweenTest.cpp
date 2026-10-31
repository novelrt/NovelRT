// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Animation/Tween.hpp>
#include <NovelRT/Ecs/Components/TransformComponent.hpp>
#include <NovelRT/Ecs/SystemScheduler.hpp>
#include <gtest/gtest.h>

#include <chrono>
#include <limits>
#include <vector>

using namespace NovelRT;
using namespace NovelRT::Ecs;
using namespace NovelRT::Ecs::Animation;
using namespace NovelRT::Timing;
using namespace std::chrono_literals;

namespace
{
    struct TweenTestComponent
    {
        float value;
        float otherValue;
        const int* pointer;

        TweenTestComponent& operator+=(const TweenTestComponent& other)
        {
            value += other.value;
            otherValue += other.otherValue;
            pointer = other.pointer;
            return *this;
        }

        bool operator==(const TweenTestComponent&) const = default;
    };

    struct TweenTestInstructionFactory
    {
        int* invocationCount = nullptr;
        float otherValueDelta = 0.0f;

        TweenTestComponent operator()(const TweenTestComponent& current) const
        {
            if (invocationCount)
            {
                ++*invocationCount;
            }

            return TweenTestComponent{.value = 0.0f, .otherValue = otherValueDelta, .pointer = current.pointer};
        }
    };

    struct MidpointInterpolator
    {
        float operator()(float start, float target, float /*progress*/) const
        {
            return (start + target) * 0.5f;
        }
    };
}

// Exercise both public entry points through the same scheduler fixture.
// false selects ToTarget; true selects ByOffset.
class TweenTest : public testing::TestWithParam<bool>
{
public:
    SystemScheduler systemScheduler{1};
    Catalogue catalogue{0, systemScheduler};
    ComponentCache& componentCache = systemScheduler.GetComponentCache();
    EntityId entity = 0;
    int payload = 123;
    int invocationCount = 0;

protected:
    void SetUp() override
    {
        componentCache.RegisterComponentType(TweenTestComponent{std::numeric_limits<float>::lowest(), 0.0f, nullptr},
                                             "TWEEN_TEST_COMPONENT");

        entity = catalogue.CreateEntity();
        catalogue.GetComponentView<TweenTestComponent>().AddComponent(entity,
                                                                      TweenTestComponent{10.0f, 7.0f, &payload});
        CommitComponents();
        systemScheduler.GetEntityCache().ProcessEntityRegistrationRequestsFromThreads();

        // Jobs execute at scheduling-layer boundaries.
        static_cast<void>(systemScheduler.RegisterSystem([](Timestamp, Catalogue) {}));
    }

    void CommitComponents()
    {
        componentCache.PrepAllBuffersForNextFrame(std::vector<EntityId>{});
    }

    TweenTestComponent GetComponent()
    {
        return catalogue.GetComponentView<TweenTestComponent>().GetComponent(entity);
    }

    void SetValue(float value)
    {
        const auto current = GetComponent();
        catalogue.GetComponentView<TweenTestComponent>().PushComponentUpdateInstruction(
            entity, TweenTestComponent{value - current.value, 0.0f, current.pointer});
        CommitComponents();
    }

    float Advance(GameClock::duration delta)
    {
        systemScheduler.ExecuteIteration(Timestamp{delta});
        return GetComponent().value;
    }

    template<typename TEasing = Easing::Linear, typename TInterpolator = DefaultTweenInterpolator<float>>
    SystemId ScheduleTween(float value = 100.0f,
                           GameClock::duration duration = 1s,
                           TweenOptions options = {},
                           float otherValueDelta = 0.0f)
    {
        using TweenType = Tween<&TweenTestComponent::value, TEasing, TweenTestInstructionFactory, TInterpolator>;
        const TweenTestInstructionFactory factory{&invocationCount, otherValueDelta};

        if (GetParam())
        {
            return TweenType::ByOffset(catalogue, entity, value, duration, options, factory);
        }

        return TweenType::ToTarget(catalogue, entity, value, duration, options, factory);
    }
};

TEST_P(TweenTest, RegistrationDefersComponentAccessAndInstructionCreation)
{
    static_cast<void>(ScheduleTween());

    EXPECT_FLOAT_EQ(GetComponent().value, 10.0f);
    EXPECT_EQ(invocationCount, 0);

    // The starting value is captured when the job runs, rather than at registration.
    SetValue(20.0f);
    EXPECT_FLOAT_EQ(Advance(500ms), GetParam() ? 70.0f : 60.0f);
}

TEST_P(TweenTest, InterpolatesAndSubmitsExactEndpointBeforeFinishing)
{
    static_cast<void>(ScheduleTween());

    EXPECT_FLOAT_EQ(Advance(250ms), GetParam() ? 35.0f : 32.5f);
    EXPECT_FLOAT_EQ(Advance(1s), GetParam() ? 110.0f : 100.0f);
    EXPECT_EQ(invocationCount, 2);

    SetValue(50.0f);
    EXPECT_FLOAT_EQ(Advance(1s), 50.0f);
    EXPECT_EQ(invocationCount, 2);
}

TEST_P(TweenTest, RepeatsWithCorrectEndpointsAndStopsAfterConfiguredCycles)
{
    static_cast<void>(ScheduleTween(100.0f, 1s, TweenOptions{.repetition = TweenCycles{3}}));

    EXPECT_FLOAT_EQ(Advance(1s), GetParam() ? 110.0f : 100.0f);
    EXPECT_FLOAT_EQ(Advance(500ms), GetParam() ? 160.0f : 55.0f);
    EXPECT_FLOAT_EQ(Advance(10s), GetParam() ? 310.0f : 100.0f);

    SetValue(50.0f);
    EXPECT_FLOAT_EQ(Advance(1s), 50.0f);
    EXPECT_EQ(invocationCount, 3);
}

TEST_P(TweenTest, CarriesElapsedTimeAcrossMultipleRepeatBoundaries)
{
    static_cast<void>(ScheduleTween(100.0f, 1s, TweenOptions{.repetition = TweenForever{}}));

    EXPECT_FLOAT_EQ(Advance(900ms), GetParam() ? 100.0f : 91.0f);
    EXPECT_FLOAT_EQ(Advance(300ms), GetParam() ? 130.0f : 28.0f);
    EXPECT_FLOAT_EQ(Advance(3300ms), GetParam() ? 460.0f : 55.0f);
    EXPECT_EQ(invocationCount, 3);
}

TEST_P(TweenTest, PingPongCycleIncludesOutwardAndReturnPasses)
{
    static_cast<void>(ScheduleTween(100.0f, 1s, TweenOptions{.loopMode = TweenLoopMode::PingPong}));

    EXPECT_FLOAT_EQ(Advance(1s), GetParam() ? 110.0f : 100.0f);
    EXPECT_FLOAT_EQ(Advance(500ms), GetParam() ? 60.0f : 55.0f);
    EXPECT_FLOAT_EQ(Advance(500ms), 10.0f);

    SetValue(50.0f);
    EXPECT_FLOAT_EQ(Advance(1s), 50.0f);
    EXPECT_EQ(invocationCount, 3);
}

TEST_P(TweenTest, CarriesElapsedTimeAcrossMultiplePingPongBoundaries)
{
    static_cast<void>(
        ScheduleTween(100.0f, 1s, TweenOptions{.repetition = TweenForever{}, .loopMode = TweenLoopMode::PingPong}));

    EXPECT_FLOAT_EQ(Advance(1200ms), GetParam() ? 90.0f : 82.0f);
    EXPECT_FLOAT_EQ(Advance(800ms), 10.0f);
    EXPECT_FLOAT_EQ(Advance(3500ms), GetParam() ? 60.0f : 55.0f);
}

TEST_P(TweenTest, LargeDeltaStopsAtFinalPingPongEndpoint)
{
    static_cast<void>(
        ScheduleTween(100.0f, 1s, TweenOptions{.repetition = TweenCycles{3}, .loopMode = TweenLoopMode::PingPong}));

    EXPECT_FLOAT_EQ(Advance(4500ms), GetParam() ? 60.0f : 55.0f);
    EXPECT_FLOAT_EQ(Advance(2s), 10.0f);

    SetValue(50.0f);
    EXPECT_FLOAT_EQ(Advance(1s), 50.0f);
    EXPECT_EQ(invocationCount, 2);
}

TEST_P(TweenTest, ZeroDeltaDoesNotAdvanceProgressOrConsumeCycles)
{
    static_cast<void>(ScheduleTween());

    EXPECT_FLOAT_EQ(Advance(0ms), 10.0f);
    EXPECT_FLOAT_EQ(Advance(500ms), GetParam() ? 60.0f : 55.0f);
    EXPECT_FLOAT_EQ(Advance(0ms), GetParam() ? 60.0f : 55.0f);
    EXPECT_FLOAT_EQ(Advance(500ms), GetParam() ? 110.0f : 100.0f);
}

TEST_P(TweenTest, CancellationStopsFurtherInstructionsWithoutResettingValue)
{
    const auto jobId = ScheduleTween(100.0f, 1s, TweenOptions{.repetition = TweenForever{}});
    const float value = Advance(250ms);

    catalogue.CancelSystemJob(jobId);

    EXPECT_FLOAT_EQ(Advance(1s), value);
    EXPECT_EQ(invocationCount, 1);
}

TEST_P(TweenTest, MissingComponentOnFirstExecutionEndsJobWithoutRecreatingIt)
{
    static_cast<void>(ScheduleTween());
    auto view = catalogue.GetComponentView<TweenTestComponent>();
    view.RemoveComponent(entity);
    CommitComponents();

    systemScheduler.ExecuteIteration(Timestamp{100ms});
    EXPECT_FALSE(view.HasComponent(entity));
    EXPECT_EQ(invocationCount, 0);

    view.AddComponent(entity, TweenTestComponent{70.0f, 7.0f, &payload});
    CommitComponents();
    EXPECT_FLOAT_EQ(Advance(1s), 70.0f);
    EXPECT_EQ(invocationCount, 0);
}

TEST_P(TweenTest, ComponentRemovalDuringAnimationEndsJob)
{
    static_cast<void>(ScheduleTween());
    static_cast<void>(Advance(250ms));
    auto view = catalogue.GetComponentView<TweenTestComponent>();
    view.RemoveComponent(entity);
    CommitComponents();

    systemScheduler.ExecuteIteration(Timestamp{100ms});
    EXPECT_FALSE(view.HasComponent(entity));

    view.AddComponent(entity, TweenTestComponent{70.0f, 7.0f, &payload});
    CommitComponents();
    EXPECT_FLOAT_EQ(Advance(1s), 70.0f);
    EXPECT_EQ(invocationCount, 1);
}

TEST_P(TweenTest, RejectsZeroDurationBeforeRegisteringJob)
{
    EXPECT_THROW(static_cast<void>(ScheduleTween(100.0f, 0ms)), std::invalid_argument);

    EXPECT_FLOAT_EQ(Advance(1s), 10.0f);
    EXPECT_EQ(invocationCount, 0);
}

TEST_P(TweenTest, RejectsZeroCyclesBeforeRegisteringJob)
{
    EXPECT_THROW(static_cast<void>(ScheduleTween(100.0f, 1s, TweenOptions{.repetition = TweenCycles{0}})),
                 std::invalid_argument);

    EXPECT_FLOAT_EQ(Advance(1s), 10.0f);
    EXPECT_EQ(invocationCount, 0);
}

TEST_P(TweenTest, FactoryPreservesReplacementFieldsAndUnrelatedAdditiveFields)
{
    static_cast<void>(ScheduleTween());
    static_cast<void>(Advance(500ms));
    static_cast<void>(Advance(500ms));

    const auto component = GetComponent();
    EXPECT_FLOAT_EQ(component.otherValue, 7.0f);
    EXPECT_EQ(component.pointer, &payload);
}

TEST_P(TweenTest, StoresConfiguredFactoryInstanceAcrossInvocations)
{
    static_cast<void>(ScheduleTween(100.0f, 1s, {}, 2.0f));
    static_cast<void>(Advance(500ms));
    static_cast<void>(Advance(500ms));

    EXPECT_FLOAT_EQ(GetComponent().otherValue, 11.0f);
    EXPECT_EQ(invocationCount, 2);
}

TEST_P(TweenTest, AppliesEasingAfreshInEachPingPongDirection)
{
    static_cast<void>(
        ScheduleTween<Easing::InQuadratic>(100.0f, 1s, TweenOptions{.loopMode = TweenLoopMode::PingPong}));

    EXPECT_FLOAT_EQ(Advance(500ms), GetParam() ? 35.0f : 32.5f);
    EXPECT_FLOAT_EQ(Advance(500ms), GetParam() ? 110.0f : 100.0f);
    EXPECT_FLOAT_EQ(Advance(500ms), GetParam() ? 85.0f : 77.5f);
    EXPECT_FLOAT_EQ(Advance(500ms), 10.0f);
}

TEST_P(TweenTest, SupportsCustomInterpolatorAndStillSubmitsExactFinalEndpoint)
{
    static_cast<void>(ScheduleTween<Easing::Linear, MidpointInterpolator>());

    EXPECT_FLOAT_EQ(Advance(250ms), GetParam() ? 60.0f : 55.0f);
    EXPECT_FLOAT_EQ(Advance(1s), GetParam() ? 110.0f : 100.0f);
}

TEST_P(TweenTest, CorrectsAgainstCommittedValueWithoutRecapturingEndpoints)
{
    static_cast<void>(ScheduleTween());
    static_cast<void>(Advance(500ms));
    SetValue(200.0f);

    EXPECT_FLOAT_EQ(Advance(250ms), GetParam() ? 85.0f : 77.5f);
}

TEST_P(TweenTest, JobsForDifferentEntitiesKeepIndependentTimingAndEndpoints)
{
    using TweenType = Tween<&TweenTestComponent::value, Easing::Linear, TweenTestInstructionFactory>;

    const EntityId otherEntity = catalogue.CreateEntity();
    auto view = catalogue.GetComponentView<TweenTestComponent>();
    view.AddComponent(otherEntity, TweenTestComponent{100.0f, 9.0f, &payload});
    CommitComponents();

    const auto firstJob = ScheduleTween();
    SystemId secondJob;

    if (GetParam())
    {
        secondJob = TweenType::ByOffset(catalogue, otherEntity, 100.0f, 2s);
    }
    else
    {
        secondJob = TweenType::ToTarget(catalogue, otherEntity, 200.0f, 2s);
    }

    EXPECT_NE(firstJob, secondJob);
    EXPECT_FLOAT_EQ(Advance(500ms), GetParam() ? 60.0f : 55.0f);
    EXPECT_FLOAT_EQ(view.GetComponent(otherEntity).value, 125.0f);

    EXPECT_FLOAT_EQ(Advance(500ms), GetParam() ? 110.0f : 100.0f);
    EXPECT_FLOAT_EQ(view.GetComponent(otherEntity).value, 150.0f);

    SetValue(50.0f);
    EXPECT_FLOAT_EQ(Advance(1s), 50.0f);
    EXPECT_FLOAT_EQ(view.GetComponent(otherEntity).value, 200.0f);
    EXPECT_FLOAT_EQ(view.GetComponent(otherEntity).otherValue, 9.0f);
    EXPECT_EQ(view.GetComponent(otherEntity).pointer, &payload);
}

TEST_P(TweenTest, ZeroedFactoryChangesVectorPositionWithoutChangingScaleOrRotation)
{
    using Transform = Components::TransformComponent;
    using PositionTween = Tween<&Transform::position>;

    componentCache.RegisterComponentType(
        Transform{.position = {-999.0f, -999.0f}, .scale = {-999.0f, -999.0f}, .rotationInRadians = -999.0f},
        "TWEEN_TEST_TRANSFORM");
    auto view = catalogue.GetComponentView<Transform>();
    view.AddComponent(entity, Transform{.position = {10.0f, 20.0f}, .scale = {2.0f, 3.0f}, .rotationInRadians = 0.5f});
    CommitComponents();

    if (GetParam())
    {
        static_cast<void>(PositionTween::ByOffset(catalogue, entity, {100.0f, 200.0f}, 1s,
                                                  TweenOptions{.repetition = TweenCycles{3}}));
    }
    else
    {
        static_cast<void>(PositionTween::ToTarget(catalogue, entity, {100.0f, 200.0f}, 1s));
    }

    systemScheduler.ExecuteIteration(Timestamp{1500ms});
    const auto transform = view.GetComponent(entity);

    EXPECT_FLOAT_EQ(transform.position.x, GetParam() ? 160.0f : 100.0f);
    EXPECT_FLOAT_EQ(transform.position.y, GetParam() ? 320.0f : 200.0f);
    EXPECT_EQ(transform.scale, Maths::GeoVector2F(2.0f, 3.0f));
    EXPECT_FLOAT_EQ(transform.rotationInRadians, 0.5f);
}

INSTANTIATE_TEST_SUITE_P(Tween,
                         TweenTest,
                         testing::Values(false, true),
                         [](const testing::TestParamInfo<bool>& info) { return info.param ? "ByOffset" : "ToTarget"; });
