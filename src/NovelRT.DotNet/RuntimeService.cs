// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;

namespace NovelRT.DotNet
{
    public static class RuntimeService
    {
        public static void Initialize()
        {
            Console.WriteLine($"Hello from .NET v{Environment.Version}!");
        }
    }
}
