// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtRuntimeServiceHandle")]
        public static extern IntPtr Nrt_RuntimeService_create();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RuntimeService_destroy([NativeTypeName("NrtRuntimeServiceHandle")] IntPtr service);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RuntimeService_initialise([NativeTypeName("NrtRuntimeServiceHandle")] IntPtr service);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RuntimeService_tearDown([NativeTypeName("NrtRuntimeServiceHandle")] IntPtr service);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RuntimeService_freeObject([NativeTypeName("NrtRuntimeServiceHandle")] IntPtr service, [NativeTypeName("intptr_t")] nint obj);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RuntimeService_freeString([NativeTypeName("NrtRuntimeServiceHandle")] IntPtr service, [NativeTypeName("const char *")] sbyte* str);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RuntimeService_getInkService([NativeTypeName("NrtRuntimeServiceHandle")] IntPtr service, [NativeTypeName("NrtInkServiceHandle *")] IntPtr* outputInkService);
    }
}
