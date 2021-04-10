// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_WINDOWING_WINDOWINGTYPEDEFS_H
#define NOVELRT_INTEROP_WINDOWING_WINDOWINGTYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtWindowingService* NrtWindowingServiceHandle;

    typedef enum
    {
        NRT_WINDOW_MODE_WINDOWED = 0,
        NRT_WINDOW_MODE_BORDERLESS = 1,
        NRT_WINDOW_MODE_FULLSCREEN = 2
    } NrtWindowModeKind;

    typedef int32_t NrtWindowMode;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_WINDOWING_WINDOWINGTYPEDEFS_H
