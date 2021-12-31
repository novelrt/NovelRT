// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT::Maths;

class LeadingZeroCount64Test : public testing::Test
{
public:
    uint64_t testValue = 0;

protected:

    void SetUp() override
    {
        testValue = 0;
    }
};

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenNoBitsSet)
{
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 64);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit0Set)
{
    testValue ^= 1;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 63);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit1Set)
{
    testValue ^= (1ULL << 1ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 62);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit2Set)
{
    testValue ^= (1ULL << 2ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 61);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit3Set)
{
    testValue ^= (1ULL << 3ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 60);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit4Set)
{
    testValue ^= (1ULL << 4ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 59);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit5Set)
{
    testValue ^= (1ULL << 5ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 58);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit6Set)
{
    testValue ^= (1ULL << 6ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 57);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit7Set)
{
    testValue ^= (1ULL << 7ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 56);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit8Set)
{
    testValue ^= (1ULL << 8ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 55);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit9Set)
{
    testValue ^= (1ULL << 9ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 54);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit10Set)
{
    testValue ^= (1ULL << 10ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 53);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit11Set)
{
    testValue ^= (1ULL << 11ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 52);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit12Set)
{
    testValue ^= (1ULL << 12ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 51);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit13Set)
{
    testValue ^= (1ULL << 13ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 50);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit14Set)
{
    testValue ^= (1ULL << 14ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 49);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit15Set)
{
    testValue ^= (1ULL << 15ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 48);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit16Set)
{
    testValue ^= (1ULL << 16ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 47);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit17Set)
{
    testValue ^= (1ULL << 17ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 46);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit18Set)
{
    testValue ^= (1ULL << 18ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 45);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit19Set)
{
    testValue ^= (1ULL << 19ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 44);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit20Set)
{
    testValue ^= (1ULL << 20ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 43);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit21Set)
{
    testValue ^= (1ULL << 21ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 42);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit22Set)
{
    testValue ^= (1ULL << 22ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 41);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit23Set)
{
    testValue ^= (1ULL << 23ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 40);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit24Set)
{
    testValue ^= (1ULL << 24ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 39);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit25Set)
{
    testValue ^= (1ULL << 25ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 38);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit26Set)
{
    testValue ^= (1ULL << 26ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 37);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit27Set)
{
    testValue ^= (1ULL << 27ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 36);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit28Set)
{
    testValue ^= (1ULL << 28ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 35);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit29Set)
{
    testValue ^= (1ULL << 29ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 34);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit30Set)
{
    testValue ^= (1ULL << 30ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 33);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit31Set)
{
    testValue ^= (1ULL << 31ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 32);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit32Set)
{
    testValue ^= (1ULL << 32ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 31);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit33Set)
{
    testValue ^= (1ULL << 33ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 30);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit34Set)
{
    testValue ^= (1ULL << 34ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 29);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit35Set)
{
    testValue ^= (1ULL << 35ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 28);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit36Set)
{
    testValue ^= (1ULL << 36ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 27);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit37Set)
{
    testValue ^= (1ULL << 37ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 26);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit38Set)
{
    testValue ^= (1ULL << 38ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 25);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit39Set)
{
    testValue ^= (1ULL << 39ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 24);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit40Set)
{
    testValue ^= (1ULL << 40ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 23);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit41Set)
{
    testValue ^= (1ULL << 41ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 22);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit42Set)
{
    testValue ^= (1ULL << 42ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 21);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit43Set)
{
    testValue ^= (1ULL << 43ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 20);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit44Set)
{
    testValue ^= (1ULL << 44ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 19);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit45Set)
{
    testValue ^= (1ULL << 45ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 18);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit46Set)
{
    testValue ^= (1ULL << 46ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 17);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit47Set)
{
    testValue ^= (1ULL << 47ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 16);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit48Set)
{
    testValue ^= (1ULL << 48ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 15);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit49Set)
{
    testValue ^= (1ULL << 49ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 14);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit50Set)
{
    testValue ^= (1ULL << 50ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 13);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit51Set)
{
    testValue ^= (1ULL << 51ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 12);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit52Set)
{
    testValue ^= (1ULL << 52ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 11);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit53Set)
{
    testValue ^= (1ULL << 53ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 10);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit54Set)
{
    testValue ^= (1ULL << 54ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 9);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit55Set)
{
    testValue ^= (1ULL << 55ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 8);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit56Set)
{
    testValue ^= (1ULL << 56ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 7);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit57Set)
{
    testValue ^= (1ULL << 57ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 6);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit58Set)
{
    testValue ^= (1ULL << 58ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 5);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit59Set)
{
    testValue ^= (1ULL << 59ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 4);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit60Set)
{
    testValue ^= (1ULL << 60ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 3);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit61Set)
{
    testValue ^= (1ULL << 61ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 2);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit62Set)
{
    testValue ^= (1ULL << 62ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 1);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit63Set)
{
    testValue ^= (1ULL << 63ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenAllBitsSet)
{
    testValue = std::numeric_limits<uint64_t>::max();
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}


TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit0SetInverse)
{
    testValue ^= 1;
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit1SetInverse)
{
    testValue ^= (1ULL << 1ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit2SetInverse)
{
    testValue ^= (1ULL << 2ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit3SetInverse)
{
    testValue ^= (1ULL << 3ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit4SetInverse)
{
    testValue ^= (1ULL << 4ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit5SetInverse)
{
    testValue ^= (1ULL << 5ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit6SetInverse)
{
    testValue ^= (1ULL << 6ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit7SetInverse)
{
    testValue ^= (1ULL << 7ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit8SetInverse)
{
    testValue ^= (1ULL << 8ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit9SetInverse)
{
    testValue ^= (1ULL << 9ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit10SetInverse)
{
    testValue ^= (1ULL << 10ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit11SetInverse)
{
    testValue ^= (1ULL << 11ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit12SetInverse)
{
    testValue ^= (1ULL << 12ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit13SetInverse)
{
    testValue ^= (1ULL << 13ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit14SetInverse)
{
    testValue ^= (1ULL << 14ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit15SetInverse)
{
    testValue ^= (1ULL << 15ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit16SetInverse)
{
    testValue ^= (1ULL << 16ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit17SetInverse)
{
    testValue ^= (1ULL << 17ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit18SetInverse)
{
    testValue ^= (1ULL << 18ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit19SetInverse)
{
    testValue ^= (1ULL << 19ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit20SetInverse)
{
    testValue ^= (1ULL << 20ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit21SetInverse)
{
    testValue ^= (1ULL << 21ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit22SetInverse)
{
    testValue ^= (1ULL << 22ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit23SetInverse)
{
    testValue ^= (1ULL << 23ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit24SetInverse)
{
    testValue ^= (1ULL << 24ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit25SetInverse)
{
    testValue ^= (1ULL << 25ULL);
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 38);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit26SetInverse)
{
    testValue ^= (1ULL << 26ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit27SetInverse)
{
    testValue ^= (1ULL << 27ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit28SetInverse)
{
    testValue ^= (1ULL << 28ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit29SetInverse)
{
    testValue ^= (1ULL << 29ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit30SetInverse)
{
    testValue ^= (1ULL << 30ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit31SetInverse)
{
    testValue ^= (1ULL << 31ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit32SetInverse)
{
    testValue ^= (1ULL << 32ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit33SetInverse)
{
    testValue ^= (1ULL << 33ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit34SetInverse)
{
    testValue ^= (1ULL << 34ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit35SetInverse)
{
    testValue ^= (1ULL << 35ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit36SetInverse)
{
    testValue ^= (1ULL << 36ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit37SetInverse)
{
    testValue ^= (1ULL << 37ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit38SetInverse)
{
    testValue ^= (1ULL << 38ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit39SetInverse)
{
    testValue ^= (1ULL << 39ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit40SetInverse)
{
    testValue ^= (1ULL << 40ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit41SetInverse)
{
    testValue ^= (1ULL << 41ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit42SetInverse)
{
    testValue ^= (1ULL << 42ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit43SetInverse)
{
    testValue ^= (1ULL << 43ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit44SetInverse)
{
    testValue ^= (1ULL << 44ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit45SetInverse)
{
    testValue ^= (1ULL << 45ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit46SetInverse)
{
    testValue ^= (1ULL << 46ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit47SetInverse)
{
    testValue ^= (1ULL << 47ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit48SetInverse)
{
    testValue ^= (1ULL << 48ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit49SetInverse)
{
    testValue ^= (1ULL << 49ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit50SetInverse)
{
    testValue ^= (1ULL << 50ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit51SetInverse)
{
    testValue ^= (1ULL << 51ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit52SetInverse)
{
    testValue ^= (1ULL << 52ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit53SetInverse)
{
    testValue ^= (1ULL << 53ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit54SetInverse)
{
    testValue ^= (1ULL << 54ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit55SetInverse)
{
    testValue ^= (1ULL << 55ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit56SetInverse)
{
    testValue ^= (1ULL << 56ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit57SetInverse)
{
    testValue ^= (1ULL << 57ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit58SetInverse)
{
    testValue ^= (1ULL << 58ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit59SetInverse)
{
    testValue ^= (1ULL << 59ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit60SetInverse)
{
    testValue ^= (1ULL << 60ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit61SetInverse)
{
    testValue ^= (1ULL << 61ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit62SetInverse)
{
    testValue ^= (1ULL << 62ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 0);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenBit63SetInverse)
{
    testValue ^= (1ULL << 63ULL);
    testValue = ~testValue;
    auto result = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(result, 1);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenAlternatingBitsSet)
{
    testValue = 0b1010101010101010101010101010101010101010101010101010101010101010;
    auto resultOfPattern = Utilities::LeadingZeroCount64(testValue);
    ASSERT_EQ(resultOfPattern, 0);
    testValue = ~testValue;
    auto resultOfPatternInverse = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(resultOfPatternInverse, 1);
}

TEST_F(LeadingZeroCount64Test, LeadingZeroCount64ReturnsCorrectCountWhenRandomBitsSet)
{
    testValue = 0b1010010001010101101010101010101010101010101010101010101010101010;
    auto resultOfPattern = Utilities::LeadingZeroCount64(testValue);
    EXPECT_EQ(resultOfPattern, 0);
}