// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtRuntimeService")]
        public static extern IntPtr Nrt_RuntimeService_create();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RuntimeService_destroy([NativeTypeName("NrtRuntimeService")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RuntimeService_initialise([NativeTypeName("NrtRuntimeService")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RuntimeService_tearDown([NativeTypeName("NrtRuntimeService")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RuntimeService_freeObject([NativeTypeName("NrtRuntimeService")] IntPtr service, [NativeTypeName("intptr_t")] nint obj);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RuntimeService_freeString([NativeTypeName("NrtRuntimeService")] IntPtr service, [NativeTypeName("const char *")] sbyte* str);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RuntimeService_getInkService([NativeTypeName("NrtRuntimeService")] IntPtr service, [NativeTypeName("NrtInkService *")] IntPtr* outputInkService);
    }
}
