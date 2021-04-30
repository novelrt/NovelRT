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
    public class ComponentBufferMemoryContainer : ShimObject
    {
        public unsafe ComponentBufferMemoryContainer(nuint poolSize, void* deleteInstructionState, nuint sizeOfDataTypeInBytes, delegate* unmanaged<IntPtr,IntPtr, nuint,void> function){
            
            //internalHandle=Nrt_ComponentBufferMemoryContainer_Create
            Nrt_ComponentBufferMemoryContainer_Create(poolSize, deleteInstructionState,sizeOfDataTypeInBytes,function);
        }
        void PrepContainerForFrame(EntityIdVector entitiesToDelete)
        {
            Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame(internalHandle, entitiesToDelete.internalHandle);
        }
        IntPtr GetDeleteInstructionState(){
            return Nrt_ComponentBufferMemoryContainer_GetDeleteInstructionState(internalHandle);
        }
        void PushComponentUpdateInstruction(nuint poolId){
            //NrtResult result= Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(internalHandle, poolId, [NativeTypeName("NrtEntityId")] nuint entity, [NativeTypeName("const void *")] void* componentData);
        }
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
        /*
        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint poolId, [NativeTypeName("NrtEntityId")] nuint entity, [NativeTypeName("const void *")] void* componentData);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ComponentBufferMemoryContainer_GetComponent([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container, [NativeTypeName("NrtEntityId")] nuint entity, [NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataViewHandle *")] IntPtr* outputResult);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataViewHandle")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_GetComponentUnsafe([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_ComponentBufferMemoryContainer_HasComponent([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("size_t")]
        public static extern nuint Nrt_ComponentBufferMemoryContainer_GetImmutableDataLength([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_begin([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_end([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ComponentBufferMemoryContainer_Destroy([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("const void *")]
        public static extern void* Nrt_ComponentBufferMemoryContainer_ImmutableDataView_GetDataHandle([NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataViewHandle")] IntPtr view);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ComponentBufferMemoryContainer_ImmutableDataView_Destroy([NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataViewHandle")] IntPtr view);
        */
    }
}
