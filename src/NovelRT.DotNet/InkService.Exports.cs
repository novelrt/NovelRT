// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace NovelRT.DotNet
{
    public static unsafe partial class InkService
    {
        public struct Exports
        {
            public delegate* unmanaged<void> Initialise;
            public delegate* unmanaged<void> Teardown;
            public delegate* unmanaged<StoryExports*, void> GetStoryExports;
        }

        public struct StoryExports
        {
            public delegate* unmanaged<byte*, IntPtr> CreateFromJsonString;
            public delegate* unmanaged<IntPtr, int, void> ChooseChoiceIndex;
            public delegate* unmanaged<IntPtr, byte*> Continue;
            public delegate* unmanaged<IntPtr, byte*> ContinueMaximally;
            public delegate* unmanaged<IntPtr, byte> GetCanContinue;
            public delegate* unmanaged<IntPtr, void> ResetState;
        }
    }
}
