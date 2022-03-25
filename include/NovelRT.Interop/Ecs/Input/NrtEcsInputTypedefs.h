// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_INPUT_TYPEDEFS_H
#define NOVELRT_INTEROP_ECS_INPUT_TYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtInputSystem* NrtInputSystemHandle;

    typedef struct{
        NrtAtom actionId;
        NrtKeyState state;
        float mousePositionX;
        float mousePositionY;
    } NrtInputEventComponent;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_GRAPHICS_TYPEDEFS_H
