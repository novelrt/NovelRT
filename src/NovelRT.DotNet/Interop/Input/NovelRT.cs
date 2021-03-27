// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_executeObjectBehaviour([NativeTypeName("NrtBasicInteractionRect")] IntPtr @object);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_getTransform([NativeTypeName("NrtBasicInteractionRect")] IntPtr @object, [NativeTypeName("NrtTransform *")] NrtTransform* outputTransform);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_setTransform([NativeTypeName("NrtBasicInteractionRect")] IntPtr @object, NrtTransform transform);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_Input_BasicInteractionRect_getLayer([NativeTypeName("NrtBasicInteractionRect")] IntPtr @object);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_setLayer([NativeTypeName("NrtBasicInteractionRect")] IntPtr @object, [NativeTypeName("int32_t")] int value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_Input_BasicInteractionRect_getActive([NativeTypeName("NrtBasicInteractionRect")] IntPtr @object);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_setActive([NativeTypeName("NrtBasicInteractionRect")] IntPtr @object, [NativeTypeName("int32_t")] int value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_validateInteractionPrimeter([NativeTypeName("NrtBasicInteractionRect")] IntPtr @object, [NativeTypeName("const NrtGeoVector2F")] NrtGeoVector2F mousePosition);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtKeyCodeKind Nrt_Input_BasicInteractionRect_getSubscribedKey([NativeTypeName("NrtBasicInteractionRect")] IntPtr @object);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_setSubscribedKey([NativeTypeName("NrtBasicInteractionRect")] IntPtr @object, NrtKeyCodeKind value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_addInteraction([NativeTypeName("NrtBasicInteractionRect")] IntPtr @object, [NativeTypeName("void (*)()")] delegate* unmanaged<void> ptr);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtKeyState")]
        public static extern int Nrt_KeyStateFrameChangeLog_getCurrentState([NativeTypeName("NrtKeyStateFrameChangeLog")] IntPtr changeLog);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("uint32_t")]
        public static extern uint Nrt_KeyStateFrameChangeLog_getChangeCount([NativeTypeName("NrtKeyStateFrameChangeLog")] IntPtr changeLog);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_KeyStateFrameChangeLog_compareChangeLog([NativeTypeName("NrtKeyStateFrameChangeLog")] IntPtr lhs, [NativeTypeName("NrtKeyState")] int rhs);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_KeyStateFrameChangeLog_compareKeyState([NativeTypeName("NrtKeyState")] int lhs, [NativeTypeName("NrtKeyStateFrameChangeLog")] IntPtr rhs);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtInteractionService")]
        public static extern IntPtr Nrt_InteractionService_create([NativeTypeName("const NrtWindowingService")] IntPtr windowingService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_InteractionService_consumePlayerInput([NativeTypeName("const NrtInteractionService")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_InteractionService_createBasicInteractionRect([NativeTypeName("const NrtInteractionService")] IntPtr service, [NativeTypeName("const NrtTransform")] NrtTransform transform, [NativeTypeName("int32_t")] int layer, [NativeTypeName("NrtBasicInteractionRect *")] IntPtr* outputRect);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_InteractionService_executeClickedInteractable([NativeTypeName("const NrtInteractionService")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_InteractionService_setScreenSize([NativeTypeName("const NrtInteractionService")] IntPtr service, NrtGeoVector2F value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_InteractionService_getKeyState([NativeTypeName("const NrtInteractionService")] IntPtr service, [NativeTypeName("NrtKeyCode")] int value, [NativeTypeName("NrtKeyStateFrameChangeLog *")] IntPtr* output);
    }
}
