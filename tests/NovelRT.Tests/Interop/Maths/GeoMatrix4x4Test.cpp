// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtGeoMatrix4x4F.h>
#include <NovelRT/NovelRT.h>

#include <cmath>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(InteropGeoMatrix4x4FTest, GetDefaultIdentityReturnsCorrectIdentityMatrix)
{
    NrtGeoMatrix4x4F mat4 = Nrt_GeoMatrix4x4F_GetDefaultIdentity();
    EXPECT_EQ(Maths::GeoMatrix4x4F::GetDefaultIdentity(), reinterpret_cast<Maths::GeoMatrix4x4F&>(mat4));
}

TEST(InteropGeoMatrix4x4FTest, IsNaNReturnsTrueWhenGivenNaNMatrix)
{
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_IsNaN(NrtGeoMatrix4x4F{Nrt_GeoVector4F_Uniform(NAN), Nrt_GeoVector4F_Uniform(NAN),
                                                         Nrt_GeoVector4F_Uniform(NAN), Nrt_GeoVector4F_Uniform(NAN)}));
}

TEST(InteropGeoMatrix4x4FTest, IsNaNReturnsFalseWhenGivenValidMatrix)
{
    EXPECT_FALSE(Nrt_GeoMatrix4x4F_IsNaN(Nrt_GeoMatrix4x4F_GetDefaultIdentity()));
}

TEST(InteropGeoMatrix4x4FTest, EqualsOperatorReturnsTrueWhenMatricesAreEqual)
{
    EXPECT_TRUE(
        Nrt_GeoMatrix4x4F_Equal(Nrt_GeoMatrix4x4F_GetDefaultIdentity(), Nrt_GeoMatrix4x4F_GetDefaultIdentity()));
}

TEST(InteropGeoMatrix4x4FTest, EqualsOperatorReturnsFalseWhenMatricesAreDifferent)
{
    EXPECT_FALSE(Nrt_GeoMatrix4x4F_Equal(Nrt_GeoMatrix4x4F_GetDefaultIdentity(), NrtGeoMatrix4x4F{
                                                                                     Nrt_GeoVector4F_Zero(),
                                                                                     Nrt_GeoVector4F_Zero(),
                                                                                     Nrt_GeoVector4F_Zero(),
                                                                                     Nrt_GeoVector4F_Zero(),
                                                                                 }));
}

TEST(InteropGeoMatrix4x4FTest, NotEqualsOperatorReturnsTrueWhenMatricesAreDifferent)
{
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_NotEqual(Nrt_GeoMatrix4x4F_GetDefaultIdentity(), NrtGeoMatrix4x4F{
                                                                                       Nrt_GeoVector4F_Zero(),
                                                                                       Nrt_GeoVector4F_Zero(),
                                                                                       Nrt_GeoVector4F_Zero(),
                                                                                       Nrt_GeoVector4F_Zero(),
                                                                                   }));
}

TEST(InteropGeoMatrix4x4FTest, NotEqualsOperatorReturnsFalseWhenMatricesAreEqual)
{
    EXPECT_FALSE(
        Nrt_GeoMatrix4x4F_NotEqual(Nrt_GeoMatrix4x4F_GetDefaultIdentity(), Nrt_GeoMatrix4x4F_GetDefaultIdentity()));
}

TEST(InteropGeoMatrix4x4FTest, AddMatrixAddsMatricesTogetherCorrectly)
{
    Maths::GeoMatrix4x4F expectedMatrix =
        Maths::GeoMatrix4x4F::GetDefaultIdentity() + Maths::GeoMatrix4x4F::GetDefaultIdentity();
    NrtGeoMatrix4x4F actualMatrix =
        Nrt_GeoMatrix4x4F_AddMatrix(Nrt_GeoMatrix4x4F_GetDefaultIdentity(), Nrt_GeoMatrix4x4F_GetDefaultIdentity());
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_Equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, SubtractMatrixSubtractsMatricesTogetherCorrectly)
{
    Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::Zero(), Maths::GeoVector4F::Zero(),
                                                               Maths::GeoVector4F::Zero(), Maths::GeoVector4F::Zero());
    NrtGeoMatrix4x4F actualMatrix = Nrt_GeoMatrix4x4F_SubtractMatrix(Nrt_GeoMatrix4x4F_GetDefaultIdentity(),
                                                                     Nrt_GeoMatrix4x4F_GetDefaultIdentity());
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_Equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, MultiplyMatrixMultipliesMatricesTogetherCorrectly)
{
    Maths::GeoMatrix4x4F inputMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f),
                             Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f));
    Maths::GeoMatrix4x4F expectedMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(16.0f), Maths::GeoVector4F::Uniform(16.0f),
                             Maths::GeoVector4F::Uniform(16.0f), Maths::GeoVector4F::Uniform(16.0f));
    NrtGeoMatrix4x4F resultMatrix = Nrt_GeoMatrix4x4F_MultiplyMatrix(
        *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix), *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix));
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_Equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), resultMatrix));
}

TEST(InteropGeoMatrix4x4FTest, AddAssignMatrixAddsMatricesTogetherCorrectly)
{
    NrtGeoMatrix4x4F inputMatrix = Nrt_GeoMatrix4x4F_GetDefaultIdentity();
    Maths::GeoMatrix4x4F expectedMatrix =
        Maths::GeoMatrix4x4F::GetDefaultIdentity() + Maths::GeoMatrix4x4F::GetDefaultIdentity();
    Nrt_GeoMatrix4x4F_AddAssignMatrix(reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix),
                                      *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix));
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_Equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, SubtractAssignMatrixSubtractsMatricesTogetherCorrectly)
{
    NrtGeoMatrix4x4F inputMatrix = Nrt_GeoMatrix4x4F_GetDefaultIdentity();
    NrtGeoMatrix4x4F expectedMatrix = NrtGeoMatrix4x4F{Nrt_GeoVector4F_Zero(), Nrt_GeoVector4F_Zero(),
                                                       Nrt_GeoVector4F_Zero(), Nrt_GeoVector4F_Zero()};
    Nrt_GeoMatrix4x4F_SubtractAssignMatrix(&inputMatrix, inputMatrix);
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_Equal(expectedMatrix, inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, MultiplyAssignMatrixMultipliesMatricesTogetherCorrectly)
{
    Maths::GeoMatrix4x4F inputMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f),
                             Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f));
    Maths::GeoMatrix4x4F expectedMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(16.0f), Maths::GeoVector4F::Uniform(16.0f),
                             Maths::GeoVector4F::Uniform(16.0f), Maths::GeoVector4F::Uniform(16.0f));
    Nrt_GeoMatrix4x4F_MultiplyAssignMatrix(reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix),
                                           *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix));
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_Equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix),
                                        *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix)));
}

TEST(InteropGeoMatrix4x4FTest, AddFloatAddsMatrixAndFloatTogetherCorrectly)
{
    Maths::GeoMatrix4x4F expectedMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f),
                             Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f));
    NrtGeoMatrix4x4F actualMatrix = Nrt_GeoMatrix4x4F_AddFloat(
        NrtGeoMatrix4x4F{Nrt_GeoVector4F_One(), Nrt_GeoVector4F_One(), Nrt_GeoVector4F_One(), Nrt_GeoVector4F_One()},
        1.0f);
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_Equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, SubtractFloatSubtractsMatricxAndFloatTogetherCorrectly)
{
    Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::Zero(), Maths::GeoVector4F::Zero(),
                                                               Maths::GeoVector4F::Zero(), Maths::GeoVector4F::Zero());
    NrtGeoMatrix4x4F actualMatrix = Nrt_GeoMatrix4x4F_SubtractFloat(
        NrtGeoMatrix4x4F{Nrt_GeoVector4F_One(), Nrt_GeoVector4F_One(), Nrt_GeoVector4F_One(), Nrt_GeoVector4F_One()},
        1.0f);
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_Equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, MultiplyFloatMultipliesMatrixAndFloatTogetherCorrectly)
{
    Maths::GeoMatrix4x4F inputMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f),
                             Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f));
    Maths::GeoMatrix4x4F expectedMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(4.0f), Maths::GeoVector4F::Uniform(4.0f),
                             Maths::GeoVector4F::Uniform(4.0f), Maths::GeoVector4F::Uniform(4.0f));
    NrtGeoMatrix4x4F resultMatrix =
        Nrt_GeoMatrix4x4F_MultiplyFloat(*reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix), 2.0f);
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_Equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), resultMatrix));
}

TEST(InteropGeoMatrix4x4FTest, AddAssignFloatAddsMatrixAndFloatTogetherCorrectly)
{
    NrtGeoMatrix4x4F inputMatrix{Nrt_GeoVector4F_Uniform(1.0f), Nrt_GeoVector4F_Uniform(1.0f),
                                 Nrt_GeoVector4F_Uniform(1.0f), Nrt_GeoVector4F_Uniform(1.0f)};
    Maths::GeoMatrix4x4F expectedMatrix =
        *reinterpret_cast<Maths::GeoMatrix4x4F*>(&inputMatrix) + *reinterpret_cast<Maths::GeoMatrix4x4F*>(&inputMatrix);
    Nrt_GeoMatrix4x4F_AddAssignFloat(reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix), 1.0f);
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_Equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, SubtractAssignFloatSubtractsMatrixAndFloatTogetherCorrectly)
{
    NrtGeoMatrix4x4F inputMatrix{Nrt_GeoVector4F_One(), Nrt_GeoVector4F_One(), Nrt_GeoVector4F_One(),
                                 Nrt_GeoVector4F_One()};
    NrtGeoMatrix4x4F expectedMatrix = NrtGeoMatrix4x4F{Nrt_GeoVector4F_Zero(), Nrt_GeoVector4F_Zero(),
                                                       Nrt_GeoVector4F_Zero(), Nrt_GeoVector4F_Zero()};
    Nrt_GeoMatrix4x4F_SubtractAssignFloat(&inputMatrix, 1.0f);
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_Equal(expectedMatrix, inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, MultiplyAssignFloatMultipliesMatrixAndFloatTogetherCorrectly)
{
    Maths::GeoMatrix4x4F inputMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f),
                             Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f));
    Maths::GeoMatrix4x4F expectedMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(4.0f), Maths::GeoVector4F::Uniform(4.0f),
                             Maths::GeoVector4F::Uniform(4.0f), Maths::GeoVector4F::Uniform(4.0f));

    Nrt_GeoMatrix4x4F_MultiplyAssignFloat(reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix), 2.0f);
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_Equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix),
                                        *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix)));
}
