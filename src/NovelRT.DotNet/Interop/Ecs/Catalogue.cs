// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NovelRT.Interop.Ecs
{
    public class Catalogue : ShimObject
    {
        public Catalogue(nuint poolId, ComponentCache componentCache, EntityCache entityCache)
        {
            Create(poolId, componentCache.internalHandle, entityCache.internalHandle);
        }
        public Catalogue(nuint poolId, IntPtr componentCache, EntityCache entityCache){
            Create(poolId, componentCache, entityCache.internalHandle);
        }
        public Catalogue(nuint poolId, ComponentCache componentCache, IntPtr entityCache)
        {
            Create(poolId, componentCache.internalHandle, entityCache);
        }
        public Catalogue(nuint poolId, IntPtr componentCache, IntPtr entityCache)
        {
            Create(poolId, componentCache, entityCache);
        }
        public void Create(nuint poolId, IntPtr componentCache, IntPtr entityCache)
        {
            internalHandle = NovelRT.Nrt_Catalogue_Create(poolId, componentCache, entityCache);
        }
        //fix capitalization, related: https://github.com/novelrt/NovelRT/issues/293
        nuint CreateEntity()
        {
            return NovelRT.Nrt_catalogue_CreateEntity(internalHandle);
        }
        public unsafe UnsafeComponentView GetUnsafeComponentViewByID(nuint componentID)
        {
            IntPtr returnedView = new(0);
            NrtResult result = NovelRT.Nrt_Catalogue_GetComponentViewById(internalHandle, componentID, &returnedView);
            if (result == NrtResult.NRT_SUCCESS)
            {
                return new UnsafeComponentView(returnedView);
            }
            throw new ArgumentOutOfRangeException();
        }
        //Stathis: backwards compatibility until (safe) ComponentView is implemented.
        UnsafeComponentView GetComponentViewByID(nuint componentId)
        {
            return GetUnsafeComponentViewByID(componentId);
        }
    }
}
