// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_TYPEDEFS_H
#define NOVELRT_INTEROP_GRAPHICS_TYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtGraphicsProviderPtr* NrtGraphicsProviderPtrHandle;
    typedef struct NrtGraphicsAdapterPtr* NrtGraphicsAdapterPtrHandle;
    typedef struct NrtGraphicsSurfaceContextPtr* NrtGraphicsSurfaceContextPtrHandle;
    typedef struct NrtIGraphicsSurfacePtr* NrtIGraphicsSurfacePtrHandle;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_GRAPHICS_TYPEDEFS_H