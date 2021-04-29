// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NovelRT.Interop.Ecs
{
    public class UnsafeComponentView : ShimObject
    {
        public UnsafeComponentView(nuint poolId, ComponentBufferMemoryContainer container)
        {
            internalHandle = NovelRT.Nrt_UnsafeComponentView_Create(poolId, container.internalHandle);
        }
        public UnsafeComponentView(nuint poolId){ throw new NotImplementedException(); }
        public UnsafeComponentView(ComponentBufferMemoryContainer container) { throw new NotImplementedException();  }
        public UnsafeComponentView(IntPtr viewId){ throw new NotImplementedException(); }
    }
}
