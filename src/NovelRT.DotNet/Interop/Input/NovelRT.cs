// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Input_BasicInteractionRect_executeObjectBehaviour([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Input_BasicInteractionRect_getTransform([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object, NrtTransform* outputTransform);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Input_BasicInteractionRect_setTransform([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object, NrtTransform transform);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_Input_BasicInteractionRect_getLayer([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Input_BasicInteractionRect_setLayer([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object, [NativeTypeName("int32_t")] int value);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_Input_BasicInteractionRect_getActive([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Input_BasicInteractionRect_setActive([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object, [NativeTypeName("int32_t")] int value);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Input_BasicInteractionRect_validateInteractionPrimeter([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object, [NativeTypeName("const NrtGeoVector2F")] NrtGeoVector2F mousePosition);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtKeyCode Nrt_Input_BasicInteractionRect_getSubscribedKey([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Input_BasicInteractionRect_setSubscribedKey([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object, NrtKeyCode value);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Input_BasicInteractionRect_addInteraction([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object, [NativeTypeName("void (*)(void *)")] delegate* unmanaged<void*, void> ptr, void* context);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtInteractionServiceHandle")]
        public static extern IntPtr Nrt_InteractionService_create([NativeTypeName("const NrtWindowingServiceHandle")] IntPtr windowingService);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_InteractionService_consumePlayerInput([NativeTypeName("const NrtInteractionServiceHandle")] IntPtr service);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_InteractionService_createBasicInteractionRect([NativeTypeName("const NrtInteractionServiceHandle")] IntPtr service, [NativeTypeName("const NrtTransform")] NrtTransform transform, [NativeTypeName("int32_t")] int layer, [NativeTypeName("NrtBasicInteractionRectHandle *")] IntPtr* outputRect);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_InteractionService_executeClickedInteractable([NativeTypeName("const NrtInteractionServiceHandle")] IntPtr service);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_InteractionService_setScreenSize([NativeTypeName("const NrtInteractionServiceHandle")] IntPtr service, NrtGeoVector2F value);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_InteractionService_getKeyState([NativeTypeName("const NrtInteractionServiceHandle")] IntPtr service, NrtKeyCode value, [NativeTypeName("NrtKeyStateFrameChangeLogHandle *")] IntPtr* output);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtKeyState Nrt_KeyStateFrameChangeLog_getCurrentState([NativeTypeName("NrtKeyStateFrameChangeLogHandle")] IntPtr changeLog);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("uint32_t")]
        public static extern uint Nrt_KeyStateFrameChangeLog_getChangeCount([NativeTypeName("NrtKeyStateFrameChangeLogHandle")] IntPtr changeLog);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_KeyStateFrameChangeLog_compareChangeLog([NativeTypeName("NrtKeyStateFrameChangeLogHandle")] IntPtr lhs, NrtKeyState rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_KeyStateFrameChangeLog_compareKeyState(NrtKeyState lhs, [NativeTypeName("NrtKeyStateFrameChangeLogHandle")] IntPtr rhs);
    }
}
