// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimator_create([NativeTypeName("NrtNovelRunnerHandle")] IntPtr runner, [NativeTypeName("NrtImageRectHandle")] IntPtr rect, [NativeTypeName("NrtSpriteAnimatorHandle *")] IntPtr* outputAnimator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimator_play([NativeTypeName("NrtSpriteAnimatorHandle")] IntPtr animator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimator_pause([NativeTypeName("NrtSpriteAnimatorHandle")] IntPtr animator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimator_stop([NativeTypeName("NrtSpriteAnimatorHandle")] IntPtr animator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtAnimatorPlayState")]
        public static extern int Nrt_SpriteAnimator_getCurrentPlayState([NativeTypeName("NrtSpriteAnimatorHandle")] IntPtr animator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimator_insertNewState([NativeTypeName("NrtSpriteAnimatorHandle")] IntPtr animator, [NativeTypeName("NrtSpriteAnimatorStateHandle")] IntPtr state);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSpriteAnimatorFrameHandle")]
        public static extern IntPtr Nrt_SpriteAnimatorFrame_create();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrame_getTexture([NativeTypeName("NrtSpriteAnimatorFrameHandle")] IntPtr frame, [NativeTypeName("NrtTextureHandle *")] IntPtr* outputTexture);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrame_setTexture([NativeTypeName("NrtSpriteAnimatorFrameHandle")] IntPtr frame, [NativeTypeName("NrtTextureHandle")] IntPtr texture);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtTimestamp")]
        public static extern ulong Nrt_SpriteAnimatorFrame_getDuration([NativeTypeName("NrtSpriteAnimatorFrameHandle")] IntPtr frame);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrame_setDuration([NativeTypeName("NrtSpriteAnimatorFrameHandle")] IntPtr frame, [NativeTypeName("NrtTimestamp")] ulong timestamp);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrame_addFrameEnter([NativeTypeName("NrtSpriteAnimatorFrameHandle")] IntPtr frame, [NativeTypeName("void (*)()")] delegate* unmanaged<void> func);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrame_addFrameExit([NativeTypeName("NrtSpriteAnimatorFrameHandle")] IntPtr frame, [NativeTypeName("void (*)()")] delegate* unmanaged<void> func);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSpriteAnimatorStateHandle")]
        public static extern IntPtr Nrt_SpriteAnimatorState_create();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorState_insertNewState([NativeTypeName("NrtSpriteAnimatorStateHandle")] IntPtr state, [NativeTypeName("NrtSpriteAnimatorStateHandle")] IntPtr stateTarget, [NativeTypeName("NrtSpriteAnimatorStateConditionFunctionsHandle")] IntPtr vector);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorState_removeStateAtIndex([NativeTypeName("NrtSpriteAnimatorStateHandle")] IntPtr state, [NativeTypeName("size_t")] nuint index);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_SpriteAnimatorState_getShouldLoop([NativeTypeName("NrtSpriteAnimatorStateHandle")] IntPtr state);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorState_setShouldLoop([NativeTypeName("NrtSpriteAnimatorStateHandle")] IntPtr state, [NativeTypeName("int32_t")] int loop);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorState_getFrames([NativeTypeName("NrtSpriteAnimatorStateHandle")] IntPtr state, [NativeTypeName("NrtSpriteAnimatorFrameVectorHandle *")] IntPtr* outputFramess);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorState_setFrames([NativeTypeName("NrtSpriteAnimatorStateHandle")] IntPtr state, [NativeTypeName("NrtSpriteAnimatorFrameVectorHandle")] IntPtr frames);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorState_tryFindValidTransition([NativeTypeName("NrtSpriteAnimatorStateHandle")] IntPtr state, [NativeTypeName("NrtSpriteAnimatorStateHandle *")] IntPtr* outputTransitionState);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSpriteAnimatorFrameVectorHandle")]
        public static extern IntPtr Nrt_SpriteAnimatorFrameVector_create();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrameVector_addFrame([NativeTypeName("NrtSpriteAnimatorFrameVectorHandle")] IntPtr vector, [NativeTypeName("NrtSpriteAnimatorFrameHandle")] IntPtr frame);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrameVector_getFrameAtIndex([NativeTypeName("NrtSpriteAnimatorFrameVectorHandle")] IntPtr vector, [NativeTypeName("int32_t")] int index, [NativeTypeName("NrtSpriteAnimatorFrameHandle *")] IntPtr* outputFrame);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrameVector_removeFrameAtIndex([NativeTypeName("NrtSpriteAnimatorFrameVectorHandle")] IntPtr vector, [NativeTypeName("int32_t")] int index);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrameVector_delete([NativeTypeName("NrtSpriteAnimatorFrameVectorHandle")] IntPtr vector);
    }
}
