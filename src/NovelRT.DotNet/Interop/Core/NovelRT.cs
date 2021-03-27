// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_getLastError();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtGeoBounds Nrt_Transform_getAABB([NativeTypeName("const NrtTransform")] NrtTransform transform);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtGeoBounds Nrt_Transform_getBounds([NativeTypeName("const NrtTransform")] NrtTransform transform);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtLoggingService")]
        public static extern IntPtr Nrt_LoggingService_create();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtLoggingService")]
        public static extern IntPtr Nrt_LoggingService_createCustomTitle([NativeTypeName("const char *")] sbyte* core);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtLoggingService")]
        public static extern IntPtr Nrt_LoggingService_createCustomTitleAndLevel([NativeTypeName("const char *")] sbyte* core, NrtLogLevel level);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_log([NativeTypeName("NrtLoggingService")] IntPtr service, [NativeTypeName("const char *")] sbyte* message, NrtLogLevel level);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_logInfoLine([NativeTypeName("NrtLoggingService")] IntPtr service, [NativeTypeName("const char *")] sbyte* message);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_logErrorLine([NativeTypeName("NrtLoggingService")] IntPtr service, [NativeTypeName("const char *")] sbyte* message);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_logWarningLine([NativeTypeName("NrtLoggingService")] IntPtr service, [NativeTypeName("const char *")] sbyte* message);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_logDebugLine([NativeTypeName("NrtLoggingService")] IntPtr service, [NativeTypeName("const char *")] sbyte* message);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_logInternal([NativeTypeName("NrtLoggingService")] IntPtr service, [NativeTypeName("const char *")] sbyte* message, NrtLogLevel level);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_setLogLevel([NativeTypeName("NrtLoggingService")] IntPtr service, NrtLogLevel level);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_throwIfNullPtr([NativeTypeName("NrtLoggingService")] IntPtr service, [NativeTypeName("void *")] void* @object, [NativeTypeName("const char *")] sbyte* exceptionMessage);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_throwIfNotZero([NativeTypeName("NrtLoggingService")] IntPtr service, [NativeTypeName("int32_t")] int error, [NativeTypeName("const char *")] sbyte* exceptionMessage);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_DebugService_create([NativeTypeName("NrtUtilitiesEvent")] IntPtr sceneConstructionEvent, [NativeTypeName("NrtRenderingService")] IntPtr renderingService, [NativeTypeName("NrtDebugService *")] IntPtr* outputService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_DebugService_getIsFpsCounterVisible([NativeTypeName("NrtDebugService")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_DebugService_setIsFpsCounterVisible([NativeTypeName("NrtDebugService")] IntPtr service, [NativeTypeName("int32_t")] int value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("uint32_t")]
        public static extern uint Nrt_DebugService_getFramesPerSecond([NativeTypeName("NrtDebugService")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_DebugService_setFramesPerSecond([NativeTypeName("NrtDebugService")] IntPtr service, [NativeTypeName("uint32_t")] uint value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtNovelRunner")]
        public static extern IntPtr Nrt_NovelRunner_create([NativeTypeName("int32_t")] int displayNumber);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtNovelRunner")]
        public static extern IntPtr Nrt_NovelRunner_createCustom([NativeTypeName("int32_t")] int displayNumber, [NativeTypeName("const char *")] sbyte* windowTitle, [NativeTypeName("NrtWindowMode")] uint windowMode, [NativeTypeName("uint32_t")] uint targetFrameRate);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_runNovel([NativeTypeName("NrtNovelRunner")] IntPtr runner);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_destroy([NativeTypeName("NrtNovelRunner")] IntPtr runner);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getAudioService([NativeTypeName("NrtNovelRunner")] IntPtr runner, [NativeTypeName("NrtAudioService *")] IntPtr* outputService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getInteractionService([NativeTypeName("NrtNovelRunner")] IntPtr runner, [NativeTypeName("NrtInteractionService *")] IntPtr* outputService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getWindowingService([NativeTypeName("NrtNovelRunner")] IntPtr runner, [NativeTypeName("NrtWindowingService *")] IntPtr* outputService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getRuntimeService([NativeTypeName("NrtNovelRunner")] IntPtr runner, [NativeTypeName("NrtRuntimeService *")] IntPtr* outputService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getRenderer([NativeTypeName("NrtNovelRunner")] IntPtr runner, [NativeTypeName("NrtRenderingService *")] IntPtr* outputService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getDebugService([NativeTypeName("NrtNovelRunner")] IntPtr runner, [NativeTypeName("NrtDebugService *")] IntPtr* outputService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_addUpdate([NativeTypeName("NrtNovelRunner")] IntPtr runner, [NativeTypeName("void (*)(NrtTimestamp)")] delegate* unmanaged<ulong, void> func);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_addSceneConstructionRequested([NativeTypeName("NrtNovelRunner")] IntPtr runner, [NativeTypeName("void (*)()")] delegate* unmanaged<void> func);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getUpdateEvent([NativeTypeName("NrtNovelRunner")] IntPtr runner, [NativeTypeName("NrtUtilitiesEventWithTimestamp *")] IntPtr* outputEvent);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getSceneConstructionEvent([NativeTypeName("NrtNovelRunner")] IntPtr runner, [NativeTypeName("NrtUtilitiesEvent *")] IntPtr* outputEvent);
    }
}
