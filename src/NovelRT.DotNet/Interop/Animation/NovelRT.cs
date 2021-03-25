// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSpriteAnimatorFrame")]
        public static extern IntPtr Nrt_SpriteAnimatorFrame_create();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrame_getTexture([NativeTypeName("NrtSpriteAnimatorFrame")] IntPtr frame, [NativeTypeName("NrtTexture *")] IntPtr* outputTexture);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrame_setTexture([NativeTypeName("NrtSpriteAnimatorFrame")] IntPtr frame, [NativeTypeName("NrtTexture")] IntPtr texture);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtTimestamp")]
        public static extern ulong Nrt_SpriteAnimatorFrame_getDuration([NativeTypeName("NrtSpriteAnimatorFrame")] IntPtr frame);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrame_setDuration([NativeTypeName("NrtSpriteAnimatorFrame")] IntPtr frame, [NativeTypeName("NrtTimestamp")] ulong timestamp);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrame_addFrameEnter([NativeTypeName("NrtSpriteAnimatorFrame")] IntPtr frame, [NativeTypeName("void (*)()")] delegate* unmanaged<void> func);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrame_addFrameExit([NativeTypeName("NrtSpriteAnimatorFrame")] IntPtr frame, [NativeTypeName("void (*)()")] delegate* unmanaged<void> func);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSpriteAnimatorState")]
        public static extern IntPtr Nrt_SpriteAnimatorState_create();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorState_insertNewState([NativeTypeName("NrtSpriteAnimatorState")] IntPtr state, [NativeTypeName("NrtSpriteAnimatorState")] IntPtr stateTarget, [NativeTypeName("NrtSpriteAnimatorStateConditionFunctions")] IntPtr vector);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorState_removeStateAtIndex([NativeTypeName("NrtSpriteAnimatorState")] IntPtr state, [NativeTypeName("size_t")] nuint index);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_SpriteAnimatorState_getShouldLoop([NativeTypeName("NrtSpriteAnimatorState")] IntPtr state);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorState_setShouldLoop([NativeTypeName("NrtSpriteAnimatorState")] IntPtr state, [NativeTypeName("int32_t")] int loop);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorState_getFrames([NativeTypeName("NrtSpriteAnimatorState")] IntPtr state, [NativeTypeName("NrtSpriteAnimatorFrameVector *")] IntPtr* outputFramess);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorState_setFrames([NativeTypeName("NrtSpriteAnimatorState")] IntPtr state, [NativeTypeName("NrtSpriteAnimatorFrameVector")] IntPtr frames);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorState_tryFindValidTransition([NativeTypeName("NrtSpriteAnimatorState")] IntPtr state, [NativeTypeName("NrtSpriteAnimatorState *")] IntPtr* outputTransitionState);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSpriteAnimatorFrameVector")]
        public static extern IntPtr Nrt_SpriteAnimatorFrameVector_create();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrameVector_addFrame([NativeTypeName("NrtSpriteAnimatorFrameVector")] IntPtr vector, [NativeTypeName("NrtSpriteAnimatorFrame")] IntPtr frame);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrameVector_getFrameAtIndex([NativeTypeName("NrtSpriteAnimatorFrameVector")] IntPtr vector, [NativeTypeName("int32_t")] int index, [NativeTypeName("NrtSpriteAnimatorFrame *")] IntPtr* outputFrame);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrameVector_removeFrameAtIndex([NativeTypeName("NrtSpriteAnimatorFrameVector")] IntPtr vector, [NativeTypeName("int32_t")] int index);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimatorFrameVector_delete([NativeTypeName("NrtSpriteAnimatorFrameVector")] IntPtr vector);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimator_create([NativeTypeName("NrtNovelRunner")] IntPtr runner, [NativeTypeName("NrtImageRect")] IntPtr rect, [NativeTypeName("NrtSpriteAnimator *")] IntPtr* outputAnimator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimator_play([NativeTypeName("NrtSpriteAnimator")] IntPtr animator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimator_pause([NativeTypeName("NrtSpriteAnimator")] IntPtr animator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimator_stop([NativeTypeName("NrtSpriteAnimator")] IntPtr animator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtAnimatorPlayState")]
        public static extern int Nrt_SpriteAnimator_getCurrentPlayState([NativeTypeName("NrtSpriteAnimator")] IntPtr animator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SpriteAnimator_insertNewState([NativeTypeName("NrtSpriteAnimator")] IntPtr animator, [NativeTypeName("NrtSpriteAnimatorState")] IntPtr state);
    }
}
