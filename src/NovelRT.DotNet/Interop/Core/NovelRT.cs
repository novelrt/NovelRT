// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_DebugService_create([NativeTypeName("NrtUtilitiesEventHandle")] IntPtr sceneConstructionEvent, [NativeTypeName("NrtRenderingServiceHandle")] IntPtr renderingService, [NativeTypeName("NrtDebugServiceHandle *")] IntPtr* outputService);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_DebugService_getIsFpsCounterVisible([NativeTypeName("NrtDebugServiceHandle")] IntPtr service);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_DebugService_setIsFpsCounterVisible([NativeTypeName("NrtDebugServiceHandle")] IntPtr service, [NativeTypeName("int32_t")] int value);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("uint32_t")]
        public static extern uint Nrt_DebugService_getFramesPerSecond([NativeTypeName("NrtDebugServiceHandle")] IntPtr service);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_DebugService_setFramesPerSecond([NativeTypeName("NrtDebugServiceHandle")] IntPtr service, [NativeTypeName("uint32_t")] uint value);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_getLastError();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("const char *")]
        public static extern sbyte* Nrt_getLastErrorInternal();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsNullptrInternal();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsNaNInternal();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsDivideByZeroInternal();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsNotSupportedInternal();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsInitialisationFailureInternal();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsFunctionNotFoundInternal();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsNotInitialisedInternal();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsArgumentOutOfRangeInternal();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsInvalidOperationInternal();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsCharacterNotFoundInternal();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgIsOutOfMemoryInternal();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_setErrMsgCustomInternal([NativeTypeName("const char *")] sbyte* message);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtLoggingServiceHandle")]
        public static extern IntPtr Nrt_LoggingService_create();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtLoggingServiceHandle")]
        public static extern IntPtr Nrt_LoggingService_createCustomTitle([NativeTypeName("const char *")] sbyte* core);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtLoggingServiceHandle")]
        public static extern IntPtr Nrt_LoggingService_createCustomTitleAndLevel([NativeTypeName("const char *")] sbyte* core, NrtLogLevel level);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_LoggingService_log([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("const char *")] sbyte* message, NrtLogLevel level);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_LoggingService_logInfoLine([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("const char *")] sbyte* message);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_LoggingService_logErrorLine([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("const char *")] sbyte* message);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_LoggingService_logWarningLine([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("const char *")] sbyte* message);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_LoggingService_logDebugLine([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("const char *")] sbyte* message);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_LoggingService_logInternal([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("const char *")] sbyte* message, NrtLogLevel level);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_LoggingService_setLogLevel([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, NrtLogLevel level);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_LoggingService_throwIfNullPtr([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, void* @object, [NativeTypeName("const char *")] sbyte* exceptionMessage);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_LoggingService_throwIfNotZero([NativeTypeName("NrtLoggingServiceHandle")] IntPtr service, [NativeTypeName("int32_t")] int error, [NativeTypeName("const char *")] sbyte* exceptionMessage);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtNovelRunnerHandle")]
        public static extern IntPtr Nrt_NovelRunner_create([NativeTypeName("int32_t")] int displayNumber);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtNovelRunnerHandle")]
        public static extern IntPtr Nrt_NovelRunner_createCustom([NativeTypeName("int32_t")] int displayNumber, [NativeTypeName("const char *")] sbyte* windowTitle, NrtWindowMode windowMode, [NativeTypeName("uint32_t")] uint targetFrameRate);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_NovelRunner_runNovel([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_NovelRunner_destroy([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_NovelRunner_getAudioService([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtAudioServiceHandle *")] IntPtr* outputService);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_NovelRunner_getInteractionService([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtInteractionServiceHandle *")] IntPtr* outputService);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_NovelRunner_getWindowingService([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtWindowingServiceHandle *")] IntPtr* outputService);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_NovelRunner_getRenderer([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtRenderingServiceHandle *")] IntPtr* outputService);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_NovelRunner_getDebugService([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtDebugServiceHandle *")] IntPtr* outputService);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_NovelRunner_SubscribeToUpdate([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("void (*)(NrtTimestamp, void *)")] delegate* unmanaged<ulong, void*, void> func, void* context, [NativeTypeName("NrtAtom *")] nuint* eventHandlerId);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_NovelRunner_UnsubscribeFromUpdate([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtAtom")] nuint eventHandlerId);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_NovelRunner_SubscribeToSceneConstructionRequested([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("void (*)(void *)")] delegate* unmanaged<void*, void> func, void* context, [NativeTypeName("NrtAtom *")] nuint* eventHandlerId);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_NovelRunner_UnsubscribeFromSceneConstructionRequested([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtAtom")] nuint eventHandlerId);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_NovelRunner_getUpdateEvent([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtUtilitiesEventWithTimestampHandle *")] IntPtr* outputEvent);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_NovelRunner_getSceneConstructionEvent([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtUtilitiesEventHandle *")] IntPtr* outputEvent);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoBounds Nrt_Transform_getAABB([NativeTypeName("const NrtTransform")] NrtTransform transform);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtGeoBounds Nrt_Transform_getBounds([NativeTypeName("const NrtTransform")] NrtTransform transform);
    }
}
