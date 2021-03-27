// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtTimestamp")]
        public static extern ulong Nrt_Timestamp_create([NativeTypeName("uint64_t")] ulong ticks);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_Timestamp_isNaN([NativeTypeName("NrtTimestamp")] ulong timestamp);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern double Nrt_Timestamp_getSecondsDouble([NativeTypeName("NrtTimestamp")] ulong timestamp);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern float Nrt_Timestamp_getSecondsFloat([NativeTypeName("NrtTimestamp")] ulong timestamp);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtTimestamp")]
        public static extern ulong Nrt_Timestamp_zero();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtTimestamp")]
        public static extern ulong Nrt_Timestamp_fromSeconds(double seconds);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtTimestamp")]
        public static extern ulong Nrt_Timestamp_addTimestamp([NativeTypeName("NrtTimestamp")] ulong first, [NativeTypeName("NrtTimestamp")] ulong other);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtTimestamp")]
        public static extern ulong Nrt_Timestamp_subtractTimestamp([NativeTypeName("NrtTimestamp")] ulong first, [NativeTypeName("NrtTimestamp")] ulong other);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtTimestamp")]
        public static extern ulong Nrt_Timestamp_multiplyTimestamp([NativeTypeName("NrtTimestamp")] ulong first, [NativeTypeName("NrtTimestamp")] ulong other);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtTimestamp")]
        public static extern ulong Nrt_Timestamp_divideTimestamp([NativeTypeName("NrtTimestamp")] ulong first, [NativeTypeName("NrtTimestamp")] ulong other);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_Timestamp_addAssignTimestamp([NativeTypeName("NrtTimestamp *")] ulong* first, [NativeTypeName("NrtTimestamp")] ulong other);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_Timestamp_subtractAssignTimestamp([NativeTypeName("NrtTimestamp *")] ulong* first, [NativeTypeName("NrtTimestamp")] ulong other);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_Timestamp_multiplyAssignTimestamp([NativeTypeName("NrtTimestamp *")] ulong* first, [NativeTypeName("NrtTimestamp")] ulong other);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_Timestamp_divideAssignTimestamp([NativeTypeName("NrtTimestamp *")] ulong* first, [NativeTypeName("NrtTimestamp")] ulong other);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_Timestamp_lessThan([NativeTypeName("NrtTimestamp")] ulong lhs, [NativeTypeName("NrtTimestamp")] ulong rhs);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_Timestamp_lessThanOrEqualTo([NativeTypeName("NrtTimestamp")] ulong lhs, [NativeTypeName("NrtTimestamp")] ulong rhs);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_Timestamp_greaterThan([NativeTypeName("NrtTimestamp")] ulong lhs, [NativeTypeName("NrtTimestamp")] ulong rhs);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_Timestamp_greaterThanOrEqualTo([NativeTypeName("NrtTimestamp")] ulong lhs, [NativeTypeName("NrtTimestamp")] ulong rhs);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_Timestamp_equal([NativeTypeName("NrtTimestamp")] ulong lhs, [NativeTypeName("NrtTimestamp")] ulong rhs);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_Timestamp_notEqual([NativeTypeName("NrtTimestamp")] ulong lhs, [NativeTypeName("NrtTimestamp")] ulong rhs);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_StepTimer_create([NativeTypeName("uint32_t")] uint targetFrameRate, double maxSecondDelta, [NativeTypeName("NrtStepTimer *")] IntPtr* output);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("uint64_t")]
        public static extern ulong Nrt_StepTimer_getElapsedTicks([NativeTypeName("NrtStepTimer")] IntPtr timer);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("uint64_t")]
        public static extern ulong Nrt_StepTimer_getTotalTicks([NativeTypeName("NrtStepTimer")] IntPtr timer);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtTimestamp")]
        public static extern ulong Nrt_StepTimer_getElapsedTime([NativeTypeName("NrtStepTimer")] IntPtr timer);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtTimestamp")]
        public static extern ulong Nrt_StepTimer_getTotalTime([NativeTypeName("NrtStepTimer")] IntPtr timer);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("uint64_t")]
        public static extern ulong Nrt_StepTimer_getTargetElapsedTicks([NativeTypeName("NrtStepTimer")] IntPtr timer);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_StepTimer_setTargetElapsedTicks([NativeTypeName("NrtStepTimer")] IntPtr timer, [NativeTypeName("uint64_t")] ulong input);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtTimestamp")]
        public static extern ulong Nrt_StepTimer_getTargetElapsedTime([NativeTypeName("NrtStepTimer")] IntPtr timer);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_StepTimer_setTargetElapsedTime([NativeTypeName("NrtStepTimer")] IntPtr timer, [NativeTypeName("NrtTimestamp")] ulong target);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("uint32_t")]
        public static extern uint Nrt_StepTimer_getFrameCount([NativeTypeName("NrtStepTimer")] IntPtr timer);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("uint32_t")]
        public static extern uint Nrt_StepTimer_getFramesPerSecond([NativeTypeName("NrtStepTimer")] IntPtr timer);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_StepTimer_getIsFixedTimeStep([NativeTypeName("NrtStepTimer")] IntPtr timer);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_StepTimer_setIsFixedTimeStep([NativeTypeName("NrtStepTimer")] IntPtr timer, [NativeTypeName("int32_t")] int input);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_StepTimer_resetElapsedTime([NativeTypeName("NrtStepTimer")] IntPtr timer);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_StepTimer_tick([NativeTypeName("NrtStepTimer")] IntPtr timer, [NativeTypeName("NrtUtilitiesEventWithTimestamp")] IntPtr @event);
    }
}
