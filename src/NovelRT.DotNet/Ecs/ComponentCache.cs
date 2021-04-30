// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static NovelRT.Interop.NovelRT;
using NovelRT.Interop;
namespace NovelRT.Ecs
{
    public class ComponentCache : ShimObject
    {
            public override void Dispose(bool isDisposing)
        {
            if (internalHandle != IntPtr.Zero)
            {
                NrtResult result = Nrt_ComponentCache_Destroy(internalHandle);
                if (result != NrtResult.NRT_SUCCESS)
                {
                    throw new ObjectDisposedException(GetType().FullName);
                }
            }
        }
    }
}
