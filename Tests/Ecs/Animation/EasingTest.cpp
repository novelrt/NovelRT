// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Animation/Easing.hpp>
#include <gtest/gtest.h>

#include <array>
#include <string>

using namespace NovelRT::Ecs::Animation;

namespace
{
    template<typename TPolicy>
    float EvaluateEasing(float progress)
    {
        return TPolicy{}(progress);
    }

    struct EasingTestCase
    {
        std::string name;
        float (*evaluate)(float);
        float quarter;
        float half;
        float threeQuarters;
    };

    const std::array<EasingTestCase, 10> EasingTestCases = {{
        {"Linear", EvaluateEasing<Easing::Linear>, 0.25f, 0.5f, 0.75f},
        {"InQuadratic", EvaluateEasing<Easing::InQuadratic>, 0.0625f, 0.25f, 0.5625f},
        {"OutQuadratic", EvaluateEasing<Easing::OutQuadratic>, 0.4375f, 0.75f, 0.9375f},
        {"InOutQuadratic", EvaluateEasing<Easing::InOutQuadratic>, 0.125f, 0.5f, 0.875f},
        {"InCubic", EvaluateEasing<Easing::InCubic>, 0.015625f, 0.125f, 0.421875f},
        {"OutCubic", EvaluateEasing<Easing::OutCubic>, 0.578125f, 0.875f, 0.984375f},
        {"InOutCubic", EvaluateEasing<Easing::InOutCubic>, 0.0625f, 0.5f, 0.9375f},
        {"InSine", EvaluateEasing<Easing::InSine>, 0.07612047f, 0.29289322f, 0.61731657f},
        {"OutSine", EvaluateEasing<Easing::OutSine>, 0.38268343f, 0.70710678f, 0.92387953f},
        {"InOutSine", EvaluateEasing<Easing::InOutSine>, 0.14644661f, 0.5f, 0.85355339f},
    }};

    static_assert(Easing::InQuadratic{}(0.5f) == 0.25f);
    static_assert(Easing::OutQuadratic{}(0.5f) == 0.75f);
    static_assert(Easing::InOutQuadratic{}(0.5f) == 0.5f);
    static_assert(Easing::InCubic{}(0.5f) == 0.125f);
    static_assert(Easing::OutCubic{}(0.5f) == 0.875f);
    static_assert(Easing::InOutCubic{}(0.5f) == 0.5f);
}

class EasingTest : public testing::TestWithParam<EasingTestCase>
{
};

TEST_P(EasingTest, ProducesExpectedProgressAtEndpointsAndIntermediateTimes)
{
    const auto& testCase = GetParam();

    EXPECT_NEAR(testCase.evaluate(0.0f), 0.0f, 0.000001f);
    EXPECT_NEAR(testCase.evaluate(0.25f), testCase.quarter, 0.000001f);
    EXPECT_NEAR(testCase.evaluate(0.5f), testCase.half, 0.000001f);
    EXPECT_NEAR(testCase.evaluate(0.75f), testCase.threeQuarters, 0.000001f);
    EXPECT_NEAR(testCase.evaluate(1.0f), 1.0f, 0.000001f);
}

TEST_P(EasingTest, ProgressRemainsMonotonicAndWithinUnitInterval)
{
    const auto& testCase = GetParam();
    float previous = testCase.evaluate(0.0f);

    for (int i = 1; i <= 100; ++i)
    {
        const float progress = static_cast<float>(i) / 100.0f;
        const float value = testCase.evaluate(progress);
        SCOPED_TRACE(progress);

        EXPECT_GE(value, previous);
        EXPECT_GE(value, 0.0f);
        EXPECT_LE(value, 1.0f);
        previous = value;
    }
}

INSTANTIATE_TEST_SUITE_P(Easing,
                         EasingTest,
                         testing::ValuesIn(EasingTestCases),
                         [](const testing::TestParamInfo<EasingTestCase>& info) { return info.param.name; });
