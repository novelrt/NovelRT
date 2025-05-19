// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_MATHS_MATHSTYPEDEFS_H
#define NOVELRT_INTEROP_MATHS_MATHSTYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtPointVector* NrtPointVectorHandle;
    typedef struct NrtQuadTree* NrtQuadTreeHandle;
    typedef struct NrtQuadTreePoint* NrtQuadTreePointHandle;

    typedef struct
    {
        float x;
        float y;
    } NrtGeoVector2F;

    typedef struct
    {
        float x;
        float y;
        float z;
    } NrtGeoVector3F;

    typedef struct
    {
        float x;
        float y;
        float z;
        float w;
    } NrtGeoVector4F;

    typedef struct
    {
        NrtGeoVector4F x;
        NrtGeoVector4F y;
        NrtGeoVector4F z;
        NrtGeoVector4F w;
    } NrtGeoMatrix4x4F;

    typedef struct
    {
        NrtGeoVector2F position;
        NrtGeoVector2F size;
        float rotation;
    } NrtGeoBounds;

    typedef struct
    {
        NrtGeoVector2F position;
        NrtGeoVector2F scale;
        float rotation;
    } NrtTransform;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_MATHS_MATHSTYPEDEFS_H
