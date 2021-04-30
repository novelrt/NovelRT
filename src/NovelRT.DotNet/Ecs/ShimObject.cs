// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NovelRT.Interop;

namespace NovelRT.Ecs
{
    public abstract class ShimObject : IDisposable
    {
        internal IntPtr _internalHandle;
        internal bool _disposedValue;

        /// <summary>
        /// The unique handle of the ShimObject.
        /// </summary>
        public IntPtr internalHandle { get; internal set; }

        public abstract void Dispose(bool isDisposing);

        public void Dispose()
        {
            Dispose(isDisposing: true);
            GC.SuppressFinalize(this);
        }
        
    }
}
