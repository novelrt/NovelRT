// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_InkService_initialise([NativeTypeName("NrtInkServiceHandle")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_InkService_tearDown([NativeTypeName("NrtInkServiceHandle")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_InkService_createStory([NativeTypeName("NrtInkServiceHandle")] IntPtr service, [NativeTypeName("const char *")] sbyte* jsonString, [NativeTypeName("NrtStoryHandle *")] IntPtr* outputStory);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_InkService_getRuntimeService([NativeTypeName("NrtInkServiceHandle")] IntPtr service, [NativeTypeName("NrtRuntimeServiceHandle *")] IntPtr* outputRuntimeService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_Story_canContinue([NativeTypeName("NrtStoryHandle")] IntPtr story);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_Story_chooseChoiceIndex([NativeTypeName("NrtStoryHandle")] IntPtr story, [NativeTypeName("int32_t")] int choiceIdx);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_Story_continue([NativeTypeName("NrtStoryHandle")] IntPtr story);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_Story_continueMaximally([NativeTypeName("NrtStoryHandle")] IntPtr story);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_Story_resetState([NativeTypeName("NrtStoryHandle")] IntPtr story);
    }
}
