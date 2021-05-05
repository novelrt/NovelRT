// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoBounds Nrt_GeoBounds_zero();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoBounds Nrt_GeoBounds_GetAABBFromTransform(NrtTransform transform);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoBounds Nrt_GeoBounds_FromTransform(NrtTransform transform);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_GeoBounds_getCornerInLocalSpace(NrtGeoBounds bounds, [NativeTypeName("int32_t")] int index);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_GeoBounds_getCornerInWorldSpace(NrtGeoBounds bounds, [NativeTypeName("int32_t")] int index);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoBounds_pointIsWithinBounds(NrtGeoBounds bounds, NrtGeoVector2F point);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_GeoBounds_getExtents(NrtGeoBounds bounds);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_GeoBounds_intersectsWith(NrtGeoBounds first, NrtGeoBounds other, NrtBool* outputResult);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoBounds_equal(NrtGeoBounds lhs, NrtGeoBounds rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoBounds_notEqual(NrtGeoBounds lhs, NrtGeoBounds rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector2F_isNaN(NrtGeoVector2F vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_GeoVector2F_uniform(float value);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_GeoVector2F_zero();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_GeoVector2F_one();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector2F_rotateToAngleAroundPoint(NrtGeoVector2F* vector, float angleRotationValue, NrtGeoVector2F point);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector2F_epsilonEquals(NrtGeoVector2F vector, NrtGeoVector2F other, NrtGeoVector2F epsilonValue);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_GeoVector2F_getNormalised(NrtGeoVector2F vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern float Nrt_GeoVector2F_getLength(NrtGeoVector2F vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern float Nrt_GeoVector2F_getMagnitude(NrtGeoVector2F vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector2F_equal(NrtGeoVector2F lhs, NrtGeoVector2F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector2F_notEqual(NrtGeoVector2F lhs, NrtGeoVector2F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector2F_lessThan(NrtGeoVector2F lhs, NrtGeoVector2F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector2F_lessThanOrEqualTo(NrtGeoVector2F lhs, NrtGeoVector2F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector2F_greaterThan(NrtGeoVector2F lhs, NrtGeoVector2F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector2F_greaterThanOrEqualTo(NrtGeoVector2F lhs, NrtGeoVector2F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_GeoVector2F_addVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_GeoVector2F_subtractVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_GeoVector2F_multiplyVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_GeoVector2F_divideVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_GeoVector2F_addFloat(NrtGeoVector2F lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_GeoVector2F_subtractFloat(NrtGeoVector2F lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_GeoVector2F_multiplyFloat(NrtGeoVector2F lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_GeoVector2F_divideFloat(NrtGeoVector2F lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector2F_addAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector2F_subtractAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector2F_multiplyAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector2F_divideAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector2F_addAssignFloat(NrtGeoVector2F* lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector2F_subtractAssignFloat(NrtGeoVector2F* lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector2F_multiplyAssignFloat(NrtGeoVector2F* lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector2F_divideAssignFloat(NrtGeoVector2F* lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector3F Nrt_GeoVector3F_createFromGeoVector2F(NrtGeoVector2F vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector3F_isNaN(NrtGeoVector3F vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector3F Nrt_GeoVector3F_uniform(float value);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector3F Nrt_GeoVector3F_zero();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector3F Nrt_GeoVector3F_one();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector3F_rotateToAngleAroundPoint(NrtGeoVector3F* vector, float angleRotationValue, NrtGeoVector3F point);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector3F_epsilonEquals(NrtGeoVector3F vector, NrtGeoVector3F other, NrtGeoVector3F epsilonValue);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector3F Nrt_GeoVector3F_getNormalised(NrtGeoVector3F vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern float Nrt_GeoVector3F_getLength(NrtGeoVector3F vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern float Nrt_GeoVector3F_getMagnitude(NrtGeoVector3F vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector3F_equal(NrtGeoVector3F lhs, NrtGeoVector3F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector3F_notEqual(NrtGeoVector3F lhs, NrtGeoVector3F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector3F_lessThan(NrtGeoVector3F lhs, NrtGeoVector3F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector3F_lessThanOrEqualTo(NrtGeoVector3F lhs, NrtGeoVector3F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector3F_greaterThan(NrtGeoVector3F lhs, NrtGeoVector3F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector3F_greaterThanOrEqualTo(NrtGeoVector3F lhs, NrtGeoVector3F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector3F Nrt_GeoVector3F_addVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector3F Nrt_GeoVector3F_subtractVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector3F Nrt_GeoVector3F_multiplyVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector3F Nrt_GeoVector3F_divideVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector3F Nrt_GeoVector3F_addFloat(NrtGeoVector3F lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector3F Nrt_GeoVector3F_subtractFloat(NrtGeoVector3F lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector3F Nrt_GeoVector3F_multiplyFloat(NrtGeoVector3F lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector3F Nrt_GeoVector3F_divideFloat(NrtGeoVector3F lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector3F_addAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector3F_subtractAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector3F_multiplyAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector3F_divideAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector3F_addAssignFloat(NrtGeoVector3F* lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector3F_subtractAssignFloat(NrtGeoVector3F* lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector3F_multiplyAssignFloat(NrtGeoVector3F* lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector3F_divideAssignFloat(NrtGeoVector3F* lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector4F Nrt_GeoVector4F_createFromGeoVector2F(NrtGeoVector2F vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector4F Nrt_GeoVector4F_createFromGeoVector3F(NrtGeoVector3F vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector4F_isNaN(NrtGeoVector4F vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector4F Nrt_GeoVector4F_uniform(float value);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector4F Nrt_GeoVector4F_zero();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector4F Nrt_GeoVector4F_one();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector4F_rotateToAngleAroundPoint([NativeTypeName("NrtGeoVector4F *const")] NrtGeoVector4F* vector, float angleRotationValue, NrtGeoVector3F point);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector4F_epsilonEquals(NrtGeoVector4F vector, NrtGeoVector4F other, NrtGeoVector4F epsilonValue);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector4F Nrt_GeoVector4F_getNormalised(NrtGeoVector4F vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern float Nrt_GeoVector4F_getLength(NrtGeoVector4F vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern float Nrt_GeoVector4F_getMagnitude(NrtGeoVector4F vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector4F_equal(NrtGeoVector4F lhs, NrtGeoVector4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector4F_notEqual(NrtGeoVector4F lhs, NrtGeoVector4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector4F_lessThan(NrtGeoVector4F lhs, NrtGeoVector4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector4F_lessThanOrEqualTo(NrtGeoVector4F lhs, NrtGeoVector4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector4F_greaterThan(NrtGeoVector4F lhs, NrtGeoVector4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoVector4F_greaterThanOrEqualTo(NrtGeoVector4F lhs, NrtGeoVector4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector4F Nrt_GeoVector4F_addVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector4F Nrt_GeoVector4F_subtractVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector4F Nrt_GeoVector4F_multiplyVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector4F Nrt_GeoVector4F_divideVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector4F Nrt_GeoVector4F_addFloat(NrtGeoVector4F lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector4F Nrt_GeoVector4F_subtractFloat(NrtGeoVector4F lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector4F Nrt_GeoVector4F_multiplyFloat(NrtGeoVector4F lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector4F Nrt_GeoVector4F_divideFloat(NrtGeoVector4F lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector4F_addAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector4F_subtractAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector4F_multiplyAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector4F_divideAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector4F_addAssignFloat(NrtGeoVector4F* lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector4F_subtractAssignFloat(NrtGeoVector4F* lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector4F_multiplyAssignFloat(NrtGeoVector4F* lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoVector4F_divideAssignFloat(NrtGeoVector4F* lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoMatrix4x4F_isNaN(NrtGeoMatrix4x4F matrix);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_getDefaultIdentity();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoMatrix4x4F_equal(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_GeoMatrix4x4F_notEqual(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_addMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_subtractMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_multiplyMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoMatrix4x4F_addAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoMatrix4x4F_subtractAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoMatrix4x4F_multiplyAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_addFloat(NrtGeoMatrix4x4F lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_subtractFloat(NrtGeoMatrix4x4F lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_multiplyFloat(NrtGeoMatrix4x4F lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoMatrix4x4F_addAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoMatrix4x4F_subtractAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_GeoMatrix4x4F_multiplyAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtQuadTreeHandle")]
        public static extern IntPtr Nrt_QuadTree_create(NrtGeoBounds bounds);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTree_getParent([NativeTypeName("const NrtQuadTreeHandle")] IntPtr tree, [NativeTypeName("NrtQuadTreeHandle *")] IntPtr* outputParentTree);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoBounds Nrt_QuadTree_getBounds([NativeTypeName("const NrtQuadTreeHandle")] IntPtr tree);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTree_getPoint([NativeTypeName("const NrtQuadTreeHandle")] IntPtr tree, [NativeTypeName("size_t")] nuint index, [NativeTypeName("NrtQuadTreePointHandle *")] IntPtr* outputPoint);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("size_t")]
        public static extern nuint Nrt_QuadTree_getPointCount([NativeTypeName("const NrtQuadTreeHandle")] IntPtr tree);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTree_getTopLeft([NativeTypeName("const NrtQuadTreeHandle")] IntPtr tree, [NativeTypeName("NrtQuadTreeHandle *")] IntPtr* outputCornerTree);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTree_getTopRight([NativeTypeName("const NrtQuadTreeHandle")] IntPtr tree, [NativeTypeName("NrtQuadTreeHandle *")] IntPtr* outputCornerTree);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTree_getBottomLeft([NativeTypeName("const NrtQuadTreeHandle")] IntPtr tree, [NativeTypeName("NrtQuadTreeHandle *")] IntPtr* outputCornerTree);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTree_getBottomRight([NativeTypeName("const NrtQuadTreeHandle")] IntPtr tree, [NativeTypeName("NrtQuadTreeHandle *")] IntPtr* outputCornerTree);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_QuadTree_tryInsert([NativeTypeName("NrtQuadTreeHandle")] IntPtr tree, [NativeTypeName("NrtQuadTreePointHandle")] IntPtr point);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_QuadTree_tryRemove([NativeTypeName("const NrtQuadTreeHandle")] IntPtr tree, [NativeTypeName("NrtQuadTreePointHandle")] IntPtr point);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTree_getIntersectingPoints([NativeTypeName("const NrtQuadTreeHandle")] IntPtr tree, NrtGeoBounds bounds, [NativeTypeName("NrtPointVectorHandle *")] IntPtr* outputResultVector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_PointVector_delete([NativeTypeName("NrtPointVectorHandle")] IntPtr vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("size_t")]
        public static extern nuint Nrt_PointVector_getSize([NativeTypeName("const NrtPointVectorHandle")] IntPtr vector);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_PointVector_getPointFromIndex([NativeTypeName("const NrtPointVectorHandle")] IntPtr vector, [NativeTypeName("size_t")] nuint index, [NativeTypeName("NrtQuadTreePointHandle *")] IntPtr* outputPoint);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTree_delete([NativeTypeName("NrtQuadTreeHandle")] IntPtr tree);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtQuadTreePointHandle")]
        public static extern IntPtr Nrt_QuadTreePoint_create(NrtGeoVector2F position);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtQuadTreePointHandle")]
        public static extern IntPtr Nrt_QuadTreePoint_createFromFloat(float x, float y);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_QuadTreePoint_getPosition([NativeTypeName("const NrtQuadTreePointHandle")] IntPtr point);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTreePoint_delete([NativeTypeName("NrtQuadTreePointHandle")] IntPtr point);
    }
}
