// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;
using Ink.Runtime;

namespace NovelRT.DotNet
{
    public static unsafe partial class InkService
    {
        [UnmanagedCallersOnly]
        public static void GetExports(Exports* exports)
        {
            exports->Initialise = &Initialise;
            exports->Teardown = &Teardown;
            exports->GetStoryExports = &GetStoryExports;
        }

        [UnmanagedCallersOnly]
        private static void Initialise()
        {
            #if DEBUG
            Console.WriteLine("Initialising the .NET ink service...");
            #endif
        }

        [UnmanagedCallersOnly]
        private static void GetStoryExports(StoryExports* exports)
        {
            exports->CreateFromJsonString = &Story_CreateFromJsonString;
            exports->ChooseChoiceIndex = &Story_ChooseChoiceIndex;
            exports->Continue = &Story_Continue;
            exports->ContinueMaximally = &Story_ContinueMaximally;
            exports->GetCanContinue = &Story_GetCanContinue;
            exports->ResetState = &Story_ResetState;
        }

        [UnmanagedCallersOnly]
        private static IntPtr Story_CreateFromJsonString(byte* jsonString)
        {
            var story = new Story(RuntimeService.PointerToString(jsonString));
            return RuntimeService.AllocateHandle(story);
        }

        [UnmanagedCallersOnly]
        private static void Story_ChooseChoiceIndex(IntPtr storyHandle, int choiceIdx)
        {
            var story = RuntimeService.ResolveHandle<Story>(storyHandle);
            story.ChooseChoiceIndex(choiceIdx);
        }

        [UnmanagedCallersOnly]
        private static byte* Story_Continue(IntPtr storyHandle)
        {
            var story = RuntimeService.ResolveHandle<Story>(storyHandle);
            return RuntimeService.StringToPointer(story.Continue());
        }

        [UnmanagedCallersOnly]
        private static byte* Story_ContinueMaximally(IntPtr storyHandle)
        {
            var story = RuntimeService.ResolveHandle<Story>(storyHandle);
            return RuntimeService.StringToPointer(story.ContinueMaximally());
        }

        [UnmanagedCallersOnly]
        private static byte Story_GetCanContinue(IntPtr storyHandle)
        {
            var story = RuntimeService.ResolveHandle<Story>(storyHandle);
            return story.canContinue ? (byte)1 : (byte)0;
        }

        [UnmanagedCallersOnly]
        private static void Story_ResetState(IntPtr storyHandle)
        {
            var story = RuntimeService.ResolveHandle<Story>(storyHandle);
            story.ResetState();
        }

        [UnmanagedCallersOnly]
        private static void Teardown()
        {
            #if DEBUG
            Console.WriteLine("Tearing down the .NET ink service...");
            #endif
        }
    }
}
