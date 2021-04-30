// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;
using NovelRT.Interop;
using static NovelRT.Interop.NovelRT;
namespace NovelRT.Ecs
{
    public class Catalogue : ShimObject, IDisposable
    {
        public Catalogue(nuint poolId, ComponentCache componentCache, EntityCache entityCache)
        {
            internalHandle = Nrt_Catalogue_Create(poolId, componentCache.internalHandle, entityCache.internalHandle);
        }
        public Catalogue(IntPtr handle)
        {
            internalHandle = handle;
        }
        //TODO: fix capitalization, related: https://github.com/novelrt/NovelRT/issues/293
        public nuint CreateEntity()
        {
            return Nrt_catalogue_CreateEntity(internalHandle);
        }
        public unsafe UnsafeComponentView GetUnsafeComponentViewByID(nuint componentID)
        {
            IntPtr returnedView = new(0);
            NrtResult result = Nrt_Catalogue_GetComponentViewById(internalHandle, componentID, &returnedView);
            if (result == NrtResult.NRT_SUCCESS)
            {
                return new UnsafeComponentView(returnedView);
            }
            throw new ArgumentOutOfRangeException();
        }
        //Stathis: backwards compatibility until (safe) ComponentView is implemented.
        public UnsafeComponentView GetComponentViewByID(nuint componentId)
        {
            return GetUnsafeComponentViewByID(componentId);
        }
        public void DeleteEntity(nuint entity)
        {
            NrtResult result = Nrt_Catalogue_DeleteEntity(this.internalHandle, entity);
            if (result == NrtResult.NRT_FAILURE_NULLPTR_PROVIDED)
                throw new ObjectDisposedException(GetType().FullName);
        }
        ~Catalogue()
        {
            Dispose(isDisposing: false);
        }

        public override void Dispose(bool isDisposing)
        {
            if (internalHandle != IntPtr.Zero)
            {
                NrtResult result = Nrt_Catalogue_Destroy(internalHandle);
                if (result != NrtResult.NRT_SUCCESS)
                {
                    throw new ObjectDisposedException(GetType().FullName);
                }
            }
        }
    }
}
