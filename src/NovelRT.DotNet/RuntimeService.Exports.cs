// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace NovelRT.DotNet
{
    public static unsafe partial class RuntimeService
    {
        public struct Exports
        {
            public delegate* unmanaged<void> Initialise;
            public delegate* unmanaged<void> Teardown;
            public delegate* unmanaged<IntPtr, void> FreeObject;
            public delegate* unmanaged<byte*, void> FreeString;
            public delegate* unmanaged<InkService.Exports*, void> GetInkServiceExports;
        }
    }
}
