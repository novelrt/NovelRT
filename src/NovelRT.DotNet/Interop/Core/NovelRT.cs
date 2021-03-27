// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_DebugService_create([NativeTypeName("NrtUtilitiesEventHandle")] IntPtr sceneConstructionEvent, [NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService, [NativeTypeName("NrtDebugServiceHandle *")] IntPtr* outputService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_DebugService_getIsFpsCounterVisible([NativeTypeName("NrtDebugServiceHandle")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_DebugService_setIsFpsCounterVisible([NativeTypeName("NrtDebugServiceHandle")] IntPtr service, [NativeTypeName("int32_t")] int value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("uint32_t")]
        public static extern uint Nrt_DebugService_getFramesPerSecond([NativeTypeName("NrtDebugServiceHandle")] IntPtr service);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_DebugService_setFramesPerSecond([NativeTypeName("NrtDebugServiceHandle")] IntPtr service, [NativeTypeName("uint32_t")] uint value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_getLastError();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_getLastErrorInternal();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsNullptrInternal();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsNaNInternal();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsDivideByZeroInternal();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsNotSupportedInternal();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsInitialisationFailureInternal();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsFunctionNotFoundInternal();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsNotInitialisedInternal();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsArgumentOutOfRangeInternal();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsInvalidOperationInternal();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsCharacterNotFoundInternal();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsOutOfMemoryInternal();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgCustomInternal([NativeTypeName("const char *")] sbyte* message);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtLoggingServiceHandle")]
        public static extern IntPtr Nrt_LoggingService_create();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtLoggingServiceHandle")]
        public static extern IntPtr Nrt_LoggingService_createCustomTitle([NativeTypeName("const char *")] sbyte* core);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtLoggingServiceHandle")]
        public static extern IntPtr Nrt_LoggingService_createCustomTitleAndLevel([NativeTypeName("const char *")] sbyte* core, [NativeTypeName("NrtLogLevel")] int level);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_log([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("const char *")] sbyte* message, [NativeTypeName("NrtLogLevel")] int level);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_logInfoLine([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("const char *")] sbyte* message);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_logErrorLine([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("const char *")] sbyte* message);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_logWarningLine([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("const char *")] sbyte* message);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_logDebugLine([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("const char *")] sbyte* message);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_logInternal([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("const char *")] sbyte* message, [NativeTypeName("NrtLogLevel")] int level);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_setLogLevel([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("NrtLogLevel")] int level);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_throwIfNullPtr([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("void *")] void* @object, [NativeTypeName("const char *")] sbyte* exceptionMessage);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_LoggingService_throwIfNotZero([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("int32_t")] int error, [NativeTypeName("const char *")] sbyte* exceptionMessage);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtNovelRunnerHandle")]
        public static extern IntPtr Nrt_NovelRunner_create([NativeTypeName("int32_t")] int displayNumber);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtNovelRunnerHandle")]
        public static extern IntPtr Nrt_NovelRunner_createCustom([NativeTypeName("int32_t")] int displayNumber, [NativeTypeName("const char *")] sbyte* windowTitle, [NativeTypeName("NrtWindowMode")] int windowMode, [NativeTypeName("uint32_t")] uint targetFrameRate);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_runNovel([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_destroy([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getAudioService([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtAudioServiceHandle *")] IntPtr* outputService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getInteractionService([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtInteractionServiceHandle *")] IntPtr* outputService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getWindowingService([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtWindowingServiceHandle *")] IntPtr* outputService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getRuntimeService([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtRuntimeServiceHandle *")] IntPtr* outputService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getRenderer([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtRenderingServiceHandle *")] IntPtr* outputService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getDebugService([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtDebugServiceHandle *")] IntPtr* outputService);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_addUpdate([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("void (*)(NrtTimestamp)")] delegate* unmanaged<ulong, void> func);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_addSceneConstructionRequested([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("void (*)()")] delegate* unmanaged<void> func);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getUpdateEvent([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtUtilitiesEventWithTimestampHandle *")] IntPtr* outputEvent);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_NovelRunner_getSceneConstructionEvent([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtUtilitiesEventHandle *")] IntPtr* outputEvent);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtGeoBounds Nrt_Transform_getAABB([NativeTypeName("const NrtTransform")] NrtTransform transform);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtGeoBounds Nrt_Transform_getBounds([NativeTypeName("const NrtTransform")] NrtTransform transform);
    }
}
