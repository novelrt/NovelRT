// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtAudioServiceHandle")]
        public static extern IntPtr Nrt_AudioService_create();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_destroy([NativeTypeName("NrtAudioServiceHandle")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_AudioService_initialiseAudio([NativeTypeName("NrtAudioServiceHandle")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_loadMusic([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("char *")] sbyte* input, [NativeTypeName("NrtAudioServiceIteratorHandle *")] IntPtr* output);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_setSoundVolume([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("unsigned int")] uint source, float val);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_setSoundPosition([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("unsigned int")] uint source, float posX, float posY);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_resumeMusic([NativeTypeName("NrtAudioServiceHandle")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_playMusic([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("NrtAudioServiceIteratorHandle")] IntPtr handle, [NativeTypeName("int32_t")] int loops);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_pauseMusic([NativeTypeName("NrtAudioServiceHandle")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_stopMusic([NativeTypeName("NrtAudioServiceHandle")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_setMusicVolume([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, float value);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_checkSources([NativeTypeName("NrtAudioServiceHandle")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_loadSound([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("char *")] sbyte* input, [NativeTypeName("unsigned int *")] uint* output);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_unload([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("unsigned int")] uint handle);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_playSound([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("unsigned int")] uint handle, int loops);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_stopSound([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("unsigned int")] uint handle);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_tearDown([NativeTypeName("NrtAudioServiceHandle")] IntPtr service);
    }
}
