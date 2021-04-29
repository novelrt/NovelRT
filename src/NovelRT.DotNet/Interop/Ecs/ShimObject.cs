// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NovelRT.Interop.Ecs
{
    public abstract class ShimObject
    {
        private IntPtr _internalHandle;
        private bool _disposedValue;

        /// <summary>
        /// The unique handle of the ShimObject.
        /// </summary>
        public IntPtr internalHandle { get; internal set; }

    }
}
