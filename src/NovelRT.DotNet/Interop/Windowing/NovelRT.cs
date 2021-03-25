// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtWindowingService")]
        public static extern IntPtr Nrt_WindowingService_create();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_WindowingService_initialiseWindow([NativeTypeName("NrtWindowingService")] IntPtr service, [NativeTypeName("int32_t")] int displayNumber, [NativeTypeName("const char *")] sbyte* windowTitle, [NativeTypeName("NrtWindowMode")] uint windowMode, [NativeTypeName("int32_t")] int transparencyEnabled);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_WindowingService_tearDown([NativeTypeName("NrtWindowingService")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_WindowingService_getWindowTitle([NativeTypeName("NrtWindowingService")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_WindowingService_setWindowTitle([NativeTypeName("NrtWindowingService")] IntPtr service, [NativeTypeName("const char *")] sbyte* value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_WindowingService_setWindowSize([NativeTypeName("NrtWindowingService")] IntPtr service, NrtGeoVector2F value);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtGeoVector2F Nrt_WindowingService_getWindowSize([NativeTypeName("NrtWindowingService")] IntPtr service);
    }
}
