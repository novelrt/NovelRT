// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NovelRT.Interop.Ecs
{
    public class Catalogue
    {
        IntPtr pointer;
        public Catalogue(nuint poolId, IntPtr componentCache,IntPtr entityCache)
        {
            pointer=NovelRT.Nrt_Catalogue_Create(poolId, componentCache, entityCache);
        }

    }
}
