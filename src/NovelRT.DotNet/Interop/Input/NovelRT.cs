// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_executeObjectBehaviour([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_getTransform([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object, [NativeTypeName("NrtTransform *")] NrtTransform* outputTransform);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_setTransform([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object, NrtTransform transform);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_Input_BasicInteractionRect_getLayer([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_setLayer([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object, [NativeTypeName("int32_t")] int value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_Input_BasicInteractionRect_getActive([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_setActive([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object, [NativeTypeName("int32_t")] int value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_validateInteractionPrimeter([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object, [NativeTypeName("const NrtGeoVector2F")] NrtGeoVector2F mousePosition);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtKeyCode")]
        public static extern int Nrt_Input_BasicInteractionRect_getSubscribedKey([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_setSubscribedKey([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object, [NativeTypeName("NrtKeyCode")] int value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Input_BasicInteractionRect_addInteraction([NativeTypeName("NrtBasicInteractionRectHandle")] IntPtr @object, [NativeTypeName("void (*)()")] delegate* unmanaged<void> ptr);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtInteractionServiceHandle")]
        public static extern IntPtr Nrt_InteractionService_create([NativeTypeName("const NrtWindowingServiceHandle")] IntPtr windowingService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_InteractionService_consumePlayerInput([NativeTypeName("const NrtInteractionServiceHandle")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_InteractionService_createBasicInteractionRect([NativeTypeName("const NrtInteractionServiceHandle")] IntPtr service, [NativeTypeName("const NrtTransform")] NrtTransform transform, [NativeTypeName("int32_t")] int layer, [NativeTypeName("NrtBasicInteractionRectHandle *")] IntPtr* outputRect);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_InteractionService_executeClickedInteractable([NativeTypeName("const NrtInteractionServiceHandle")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_InteractionService_setScreenSize([NativeTypeName("const NrtInteractionServiceHandle")] IntPtr service, NrtGeoVector2F value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_InteractionService_getKeyState([NativeTypeName("const NrtInteractionServiceHandle")] IntPtr service, [NativeTypeName("NrtKeyCode")] int value, [NativeTypeName("NrtKeyStateFrameChangeLogHandle *")] IntPtr* output);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtKeyState")]
        public static extern int Nrt_KeyStateFrameChangeLog_getCurrentState([NativeTypeName("NrtKeyStateFrameChangeLogHandle")] IntPtr changeLog);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("uint32_t")]
        public static extern uint Nrt_KeyStateFrameChangeLog_getChangeCount([NativeTypeName("NrtKeyStateFrameChangeLogHandle")] IntPtr changeLog);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_KeyStateFrameChangeLog_compareChangeLog([NativeTypeName("NrtKeyStateFrameChangeLogHandle")] IntPtr lhs, [NativeTypeName("NrtKeyState")] int rhs);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_KeyStateFrameChangeLog_compareKeyState([NativeTypeName("NrtKeyState")] int lhs, [NativeTypeName("NrtKeyStateFrameChangeLogHandle")] IntPtr rhs);
    }
}
