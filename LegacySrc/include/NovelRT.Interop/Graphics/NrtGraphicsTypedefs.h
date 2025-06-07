// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_GRAPHICS_NRTGRAPHICSTYPEDEFS_H
#define NOVELRT_INTEROP_GRAPHICS_NRTGRAPHICSTYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    } NrtRGBAColour;

    typedef struct NrtGraphicsProvider* NrtGraphicsProviderHandle;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_GRAPHICS_NRTGRAPHICSTYPEDEFS_H
