// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace NovelRT.DotNet
{
    public static unsafe partial class RuntimeService
    {
        private static HashSet<GCHandle> _gcHandles = new HashSet<GCHandle>();

        [UnmanagedCallersOnly]
        public static void GetExports(Exports* exports)
        {
            exports->Initialise = &Initialise;
            exports->Teardown = &Teardown;
            exports->FreeObject = &FreeObject;
            exports->FreeString = &FreeString;
            exports->GetInkServiceExports = &InkService.GetExports;
        }

        internal static IntPtr AllocateHandle<T>(T obj)
            where T : class
        {
            var gcHandle = GCHandle.Alloc(obj);
            _gcHandles.Add(gcHandle);
            return GCHandle.ToIntPtr(gcHandle);
        }

        internal static string PointerToString(byte* str)
        {
            return Marshal.PtrToStringUTF8((IntPtr)str);
        }

        internal static T ResolveHandle<T>(IntPtr handle)
            where T : class
        {
            var gcHandle = GCHandle.FromIntPtr(handle);
            return (T)gcHandle.Target;
        }

        internal static byte* StringToPointer(string str)
        {
            return (byte*)Marshal.StringToHGlobalAnsi(str);
        }

        [UnmanagedCallersOnly]
        private static void Initialise()
        {
            #if DEBUG
            Console.WriteLine("Initialising the .NET runtime service...");
            #endif
        }

        [UnmanagedCallersOnly]
        private static void FreeObject(IntPtr handle)
        {
            var gcHandle = GCHandle.FromIntPtr(handle);
            _gcHandles.Remove(gcHandle);
            gcHandle.Free();
        }

        [UnmanagedCallersOnly]
        private static void FreeString(byte* handle)
        {
            Marshal.FreeHGlobal((IntPtr)handle);
        }

        [UnmanagedCallersOnly]
        private static void Teardown()
        {
            #if DEBUG
            Console.WriteLine("Tearing down the .NET runtime service...");
            #endif
        }
    }
}
