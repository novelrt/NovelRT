// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtAudioService")]
        public static extern IntPtr Nrt_AudioService_create();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_AudioService_destroy([NativeTypeName("NrtAudioService")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_AudioService_initialiseAudio([NativeTypeName("NrtAudioService")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_AudioService_loadMusic([NativeTypeName("NrtAudioService")] IntPtr service, [NativeTypeName("char *")] sbyte* input, [NativeTypeName("NrtAudioServiceIterator *")] IntPtr* output);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_AudioService_setSoundVolume([NativeTypeName("NrtAudioService")] IntPtr service, [NativeTypeName("unsigned int")] uint source, float val);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_AudioService_setSoundPosition([NativeTypeName("NrtAudioService")] IntPtr service, [NativeTypeName("unsigned int")] uint source, float posX, float posY);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_AudioService_resumeMusic([NativeTypeName("NrtAudioService")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_AudioService_playMusic([NativeTypeName("NrtAudioService")] IntPtr service, [NativeTypeName("NrtAudioServiceIterator")] IntPtr handle, [NativeTypeName("int32_t")] int loops);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_AudioService_pauseMusic([NativeTypeName("NrtAudioService")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_AudioService_stopMusic([NativeTypeName("NrtAudioService")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_AudioService_setMusicVolume([NativeTypeName("NrtAudioService")] IntPtr service, float value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_AudioService_checkSources([NativeTypeName("NrtAudioService")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_AudioService_loadSound([NativeTypeName("NrtAudioService")] IntPtr service, [NativeTypeName("char *")] sbyte* input, [NativeTypeName("unsigned int *")] uint* output);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_AudioService_unload([NativeTypeName("NrtAudioService")] IntPtr service, [NativeTypeName("unsigned int")] uint handle);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_AudioService_playSound([NativeTypeName("NrtAudioService")] IntPtr service, [NativeTypeName("unsigned int")] uint handle, int loops);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_AudioService_stopSound([NativeTypeName("NrtAudioService")] IntPtr service, [NativeTypeName("unsigned int")] uint handle);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_AudioService_tearDown([NativeTypeName("NrtAudioService")] IntPtr service);
    }
}
