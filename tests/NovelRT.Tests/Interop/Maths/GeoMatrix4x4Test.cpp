// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtGeoMatrix4x4F.h>
#include <NovelRT/NovelRT.h>

#include <cmath>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(InteropGeoMatrix4x4FTest, getDefaultIdentityReturnsCorrectIdentityMatrix)
{
    NrtGeoMatrix4x4F mat4 = Nrt_GeoMatrix4x4F_getDefaultIdentity();
    EXPECT_EQ(Maths::GeoMatrix4x4F::GetDefaultIdentity(), reinterpret_cast<Maths::GeoMatrix4x4F&>(mat4));
}

TEST(InteropGeoMatrix4x4FTest, isNaNReturnsTrueWhenGivenNaNMatrix)
{
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_isNaN(NrtGeoMatrix4x4F{Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN),
                                                         Nrt_GeoVector4F_uniform(NAN), Nrt_GeoVector4F_uniform(NAN)}));
}

TEST(InteropGeoMatrix4x4FTest, isNaNReturnsFalseWhenGivenValidMatrix)
{
    EXPECT_FALSE(Nrt_GeoMatrix4x4F_isNaN(Nrt_GeoMatrix4x4F_getDefaultIdentity()));
}

TEST(InteropGeoMatrix4x4FTest, equalsOperatorReturnsTrueWhenMatricesAreEqual)
{
    EXPECT_TRUE(
        Nrt_GeoMatrix4x4F_equal(Nrt_GeoMatrix4x4F_getDefaultIdentity(), Nrt_GeoMatrix4x4F_getDefaultIdentity()));
}

TEST(InteropGeoMatrix4x4FTest, equalsOperatorReturnsFalseWhenMatricesAreDifferent)
{
    EXPECT_FALSE(Nrt_GeoMatrix4x4F_equal(Nrt_GeoMatrix4x4F_getDefaultIdentity(), NrtGeoMatrix4x4F{
                                                                                     Nrt_GeoVector4F_zero(),
                                                                                     Nrt_GeoVector4F_zero(),
                                                                                     Nrt_GeoVector4F_zero(),
                                                                                     Nrt_GeoVector4F_zero(),
                                                                                 }));
}

TEST(InteropGeoMatrix4x4FTest, notEqualsOperatorReturnsTrueWhenMatricesAreDifferent)
{
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_notEqual(Nrt_GeoMatrix4x4F_getDefaultIdentity(), NrtGeoMatrix4x4F{
                                                                                       Nrt_GeoVector4F_zero(),
                                                                                       Nrt_GeoVector4F_zero(),
                                                                                       Nrt_GeoVector4F_zero(),
                                                                                       Nrt_GeoVector4F_zero(),
                                                                                   }));
}

TEST(InteropGeoMatrix4x4FTest, notEqualsOperatorReturnsFalseWhenMatricesAreEqual)
{
    EXPECT_FALSE(
        Nrt_GeoMatrix4x4F_notEqual(Nrt_GeoMatrix4x4F_getDefaultIdentity(), Nrt_GeoMatrix4x4F_getDefaultIdentity()));
}

TEST(InteropGeoMatrix4x4FTest, addMatrixAddsMatricesTogetherCorrectly)
{
    Maths::GeoMatrix4x4F expectedMatrix =
        Maths::GeoMatrix4x4F::GetDefaultIdentity() + Maths::GeoMatrix4x4F::GetDefaultIdentity();
    NrtGeoMatrix4x4F actualMatrix =
        Nrt_GeoMatrix4x4F_addMatrix(Nrt_GeoMatrix4x4F_getDefaultIdentity(), Nrt_GeoMatrix4x4F_getDefaultIdentity());
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, subtractMatrixSubtractsMatricesTogetherCorrectly)
{
    Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::Zero(), Maths::GeoVector4F::Zero(),
                                                               Maths::GeoVector4F::Zero(), Maths::GeoVector4F::Zero());
    NrtGeoMatrix4x4F actualMatrix = Nrt_GeoMatrix4x4F_subtractMatrix(Nrt_GeoMatrix4x4F_getDefaultIdentity(),
                                                                     Nrt_GeoMatrix4x4F_getDefaultIdentity());
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, multiplyMatrixMultipliesMatricesTogetherCorrectly)
{
    Maths::GeoMatrix4x4F inputMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f),
                             Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f));
    Maths::GeoMatrix4x4F expectedMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(16.0f), Maths::GeoVector4F::Uniform(16.0f),
                             Maths::GeoVector4F::Uniform(16.0f), Maths::GeoVector4F::Uniform(16.0f));
    NrtGeoMatrix4x4F resultMatrix = Nrt_GeoMatrix4x4F_multiplyMatrix(
        *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix), *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix));
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), resultMatrix));
}

TEST(InteropGeoMatrix4x4FTest, addAssignMatrixAddsMatricesTogetherCorrectly)
{
    NrtGeoMatrix4x4F inputMatrix = Nrt_GeoMatrix4x4F_getDefaultIdentity();
    Maths::GeoMatrix4x4F expectedMatrix =
        Maths::GeoMatrix4x4F::GetDefaultIdentity() + Maths::GeoMatrix4x4F::GetDefaultIdentity();
    Nrt_GeoMatrix4x4F_addAssignMatrix(reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix),
                                      *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix));
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignMatrixSubtractsMatricesTogetherCorrectly)
{
    NrtGeoMatrix4x4F inputMatrix = Nrt_GeoMatrix4x4F_getDefaultIdentity();
    NrtGeoMatrix4x4F expectedMatrix = NrtGeoMatrix4x4F{Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero(),
                                                       Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero()};
    Nrt_GeoMatrix4x4F_subtractAssignMatrix(&inputMatrix, inputMatrix);
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(expectedMatrix, inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignMatrixMultipliesMatricesTogetherCorrectly)
{
    Maths::GeoMatrix4x4F inputMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f),
                             Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f));
    Maths::GeoMatrix4x4F expectedMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(16.0f), Maths::GeoVector4F::Uniform(16.0f),
                             Maths::GeoVector4F::Uniform(16.0f), Maths::GeoVector4F::Uniform(16.0f));
    Nrt_GeoMatrix4x4F_multiplyAssignMatrix(reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix),
                                           *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix));
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix),
                                        *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix)));
}

TEST(InteropGeoMatrix4x4FTest, addFloatAddsMatrixAndFloatTogetherCorrectly)
{
    Maths::GeoMatrix4x4F expectedMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f),
                             Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f));
    NrtGeoMatrix4x4F actualMatrix = Nrt_GeoMatrix4x4F_addFloat(
        NrtGeoMatrix4x4F{Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one()},
        1.0f);
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, subtractFloatSubtractsMatricxAndFloatTogetherCorrectly)
{
    Maths::GeoMatrix4x4F expectedMatrix = Maths::GeoMatrix4x4F(Maths::GeoVector4F::Zero(), Maths::GeoVector4F::Zero(),
                                                               Maths::GeoVector4F::Zero(), Maths::GeoVector4F::Zero());
    NrtGeoMatrix4x4F actualMatrix = Nrt_GeoMatrix4x4F_subtractFloat(
        NrtGeoMatrix4x4F{Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one()},
        1.0f);
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), actualMatrix));
}

TEST(InteropGeoMatrix4x4FTest, multiplyFloatMultipliesMatrixAndFloatTogetherCorrectly)
{
    Maths::GeoMatrix4x4F inputMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f),
                             Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f));
    Maths::GeoMatrix4x4F expectedMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(4.0f), Maths::GeoVector4F::Uniform(4.0f),
                             Maths::GeoVector4F::Uniform(4.0f), Maths::GeoVector4F::Uniform(4.0f));
    NrtGeoMatrix4x4F resultMatrix =
        Nrt_GeoMatrix4x4F_multiplyFloat(*reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix), 2.0f);
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), resultMatrix));
}

TEST(InteropGeoMatrix4x4FTest, addAssignFloatAddsMatrixAndFloatTogetherCorrectly)
{
    NrtGeoMatrix4x4F inputMatrix{Nrt_GeoVector4F_uniform(1.0f), Nrt_GeoVector4F_uniform(1.0f),
                                 Nrt_GeoVector4F_uniform(1.0f), Nrt_GeoVector4F_uniform(1.0f)};
    Maths::GeoMatrix4x4F expectedMatrix =
        *reinterpret_cast<Maths::GeoMatrix4x4F*>(&inputMatrix) + *reinterpret_cast<Maths::GeoMatrix4x4F*>(&inputMatrix);
    Nrt_GeoMatrix4x4F_addAssignFloat(reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix), 1.0f);
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix), inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, subtractAssignFloatSubtractsMatrixAndFloatTogetherCorrectly)
{
    NrtGeoMatrix4x4F inputMatrix{Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one(), Nrt_GeoVector4F_one(),
                                 Nrt_GeoVector4F_one()};
    NrtGeoMatrix4x4F expectedMatrix = NrtGeoMatrix4x4F{Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero(),
                                                       Nrt_GeoVector4F_zero(), Nrt_GeoVector4F_zero()};
    Nrt_GeoMatrix4x4F_subtractAssignFloat(&inputMatrix, 1.0f);
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(expectedMatrix, inputMatrix));
}

TEST(InteropGeoMatrix4x4FTest, multiplyAssignFloatMultipliesMatrixAndFloatTogetherCorrectly)
{
    Maths::GeoMatrix4x4F inputMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f),
                             Maths::GeoVector4F::Uniform(2.0f), Maths::GeoVector4F::Uniform(2.0f));
    Maths::GeoMatrix4x4F expectedMatrix =
        Maths::GeoMatrix4x4F(Maths::GeoVector4F::Uniform(4.0f), Maths::GeoVector4F::Uniform(4.0f),
                             Maths::GeoVector4F::Uniform(4.0f), Maths::GeoVector4F::Uniform(4.0f));

    Nrt_GeoMatrix4x4F_multiplyAssignFloat(reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix), 2.0f);
    EXPECT_TRUE(Nrt_GeoMatrix4x4F_equal(*reinterpret_cast<NrtGeoMatrix4x4F*>(&expectedMatrix),
                                        *reinterpret_cast<NrtGeoMatrix4x4F*>(&inputMatrix)));
}
