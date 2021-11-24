// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtAudioServiceHandle")]
        public static extern IntPtr Nrt_AudioService_Create();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_Destroy([NativeTypeName("NrtAudioServiceHandle")] IntPtr service);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_AudioService_InitialiseAudio([NativeTypeName("NrtAudioServiceHandle")] IntPtr service);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_LoadMusic([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("char *")] sbyte* input, [NativeTypeName("NrtAudioServiceIteratorHandle *")] IntPtr* output);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_SetSoundVolume([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("unsigned int")] uint source, float val);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_SetSoundPosition([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("unsigned int")] uint source, float posX, float posY);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_ResumeMusic([NativeTypeName("NrtAudioServiceHandle")] IntPtr service);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_PlayMusic([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("NrtAudioServiceIteratorHandle")] IntPtr handle, [NativeTypeName("int32_t")] int loops);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_PauseMusic([NativeTypeName("NrtAudioServiceHandle")] IntPtr service);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_StopMusic([NativeTypeName("NrtAudioServiceHandle")] IntPtr service);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_SetMusicVolume([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, float value);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_CheckSources([NativeTypeName("NrtAudioServiceHandle")] IntPtr service);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_LoadSound([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("char *")] sbyte* input, [NativeTypeName("unsigned int *")] uint* output);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_Unload([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("unsigned int")] uint handle);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_PlaySound([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("unsigned int")] uint handle, int loops);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_StopSound([NativeTypeName("NrtAudioServiceHandle")] IntPtr service, [NativeTypeName("unsigned int")] uint handle);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_AudioService_TearDown([NativeTypeName("NrtAudioServiceHandle")] IntPtr service);
    }
}
