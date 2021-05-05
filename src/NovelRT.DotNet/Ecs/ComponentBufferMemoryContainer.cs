// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static NovelRT.Interop.NovelRT;
using NovelRT.Interop;
using NovelRT.Utilities;

namespace NovelRT.Ecs
{
    public class ComponentBufferMemoryContainer : ShimObject
    {
        public unsafe ComponentBufferMemoryContainer(nuint poolSize, void* deleteInstructionState, nuint sizeOfDataTypeInBytes, delegate* unmanaged<IntPtr, IntPtr, nuint, void> function)
        {
            Nrt_ComponentBufferMemoryContainer_Create(poolSize, deleteInstructionState, sizeOfDataTypeInBytes, function);
        }
        void PrepContainerForFrame(EntityIdVector entitiesToDelete)
        {
            Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame(internalHandle, entitiesToDelete.internalHandle);
        }
        IntPtr GetDeleteInstructionState()
        {
            return Nrt_ComponentBufferMemoryContainer_GetDeleteInstructionState(internalHandle);
        }
        public unsafe void PushComponentUpdateInstruction<T>(nuint poolId, nuint entity, in T componentData) where T : unmanaged
        {
            NrtResult result;
            fixed (void* ptr = &componentData)
            {
                result = Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(internalHandle, poolId, entity, ptr);
            }
            NrtUtilities.ThrowExceptionIfFailed(result, this);
        }
        public unsafe T GetComponent<T>(nuint entity) where T : unmanaged
        {
            T result;
            NrtResult nrtResult = Nrt_ComponentBufferMemoryContainer_GetComponent(this.internalHandle, entity, (IntPtr*)&result);
            NrtUtilities.ThrowExceptionIfFailed(nrtResult, this);
            return result;
        }
        public bool HasComponent(nuint entity){
            NrtBool result=Nrt_ComponentBufferMemoryContainer_HasComponent(this.internalHandle,entity);
            return NrtUtilities.NrtBoolToBool(result);
        }
        public nuint GetImmutableDataLength(){
            return Nrt_ComponentBufferMemoryContainer_GetImmutableDataLength(this.internalHandle);
        }
        
        /*
        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataViewHandle")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_GetComponentUnsafe([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container, [NativeTypeName("NrtEntityId")] nuint entity);
        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_begin([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_end([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("const void *")]
        public static extern void* Nrt_ComponentBufferMemoryContainer_ImmutableDataView_GetDataHandle([NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataViewHandle")] IntPtr view);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ComponentBufferMemoryContainer_ImmutableDataView_Destroy([NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataViewHandle")] IntPtr view);
        */
        public override void Dispose(bool isDisposing)
        {
            if (internalHandle != IntPtr.Zero)
            {
                NrtResult result = Nrt_ComponentBufferMemoryContainer_Destroy(internalHandle);
                if (result != NrtResult.NRT_SUCCESS)
                {
                    throw new ObjectDisposedException(GetType().FullName);
                }
            }
        }
    }
}
