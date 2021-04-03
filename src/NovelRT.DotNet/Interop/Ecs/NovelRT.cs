// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtCatalogueHandle")]
        public static extern IntPtr Nrt_Catalogue_Create([NativeTypeName("size_t")] nuint poolId, [NativeTypeName("NrtComponentCacheHandle")] IntPtr componentCache, [NativeTypeName("NrtEntityCacheHandle")] IntPtr entityCache);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Catalogue_GetComponentViewById([NativeTypeName("NrtCatalogueHandle")] IntPtr catalogue, [NativeTypeName("NrtComponentTypeId")] nuint componentId, [NativeTypeName("NrtUnsafeComponentViewHandle *")] IntPtr* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtUnsafeComponentViewHandle")]
        public static extern IntPtr Nrt_Catalogue_GetComponentViewByIdUnsafe([NativeTypeName("NrtCatalogueHandle")] IntPtr catalogue, [NativeTypeName("NrtComponentTypeId")] nuint componentId);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtEntityId")]
        public static extern nuint Nrt_catalogue_CreateEntity([NativeTypeName("NrtCatalogueHandle")] IntPtr catalogue);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Catalogue_DeleteEntity([NativeTypeName("NrtCatalogueHandle")] IntPtr catalogue, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Catalogue_Destroy([NativeTypeName("NrtCatalogueHandle")] IntPtr catalogue);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtComponentBufferMemoryContainerHandle")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_Create([NativeTypeName("size_t")] nuint poolSize, void* deleteInstructionState, [NativeTypeName("size_t")] nuint sizeOfDataTypeInBytes, [NativeTypeName("NrtComponentUpdateFnPtr")] delegate* unmanaged<IntPtr, IntPtr, nuint, void> fnPtr);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container, [NativeTypeName("NrtEntityIdVectorHandle")] IntPtr entitiesToDelete);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataViewHandle")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_GetDeleteInstructionState([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint poolId, [NativeTypeName("NrtEntityId")] nuint entity, [NativeTypeName("const void *")] void* componentData);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ComponentBufferMemoryContainer_GetComponent([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container, [NativeTypeName("NrtEntityId")] nuint entity, [NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataViewHandle *")] IntPtr* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataViewHandle")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_GetComponentUnsafe([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_ComponentBufferMemoryContainer_HasComponent([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("size_t")]
        public static extern nuint Nrt_ComponentBufferMemoryContainer_GetImmutableDataLength([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_begin([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_end([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ComponentBufferMemoryContainer_Destroy([NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("const void *")]
        public static extern void* Nrt_ComponentBufferMemoryContainer_ImmutableDataView_GetDataHandle([NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataViewHandle")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ComponentBufferMemoryContainer_ImmutableDataView_Destroy([NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataViewHandle")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtComponentCacheHandle")]
        public static extern IntPtr Nrt_ComponentCache_Create([NativeTypeName("size_t")] nuint poolSize);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ComponentCache_RegisterComponentTypeUnsafe([NativeTypeName("NrtComponentCacheHandle")] IntPtr componentCache, [NativeTypeName("size_t")] nuint sizeOfDataType, [NativeTypeName("const void *")] void* deleteInstructionState, [NativeTypeName("NrtComponentUpdateFnPtr")] delegate* unmanaged<IntPtr, IntPtr, nuint, void> updateFnPtr, [NativeTypeName("NrtComponentTypeId *")] nuint* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ComponentCache_GetComponentBufferById([NativeTypeName("NrtComponentCacheHandle")] IntPtr componentCache, [NativeTypeName("NrtComponentTypeId")] nuint id, [NativeTypeName("NrtComponentBufferMemoryContainerHandle *")] IntPtr* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_ComponentCache_PrepAllBuffersForNextFrame([NativeTypeName("NrtComponentCacheHandle")] IntPtr componentCache, [NativeTypeName("NrtEntityIdVectorHandle")] IntPtr entitiesToDelete);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_ComponentCache_Destroy([NativeTypeName("NrtComponentCacheHandle")] IntPtr componentCache);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtEntityCacheHandle")]
        public static extern IntPtr Nrt_EntityCache_Create([NativeTypeName("size_t")] nuint poolSize);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtEntityIdVectorHandle")]
        public static extern IntPtr Nrt_EntityCache_GetEntitiesToRemoveThisFrame([NativeTypeName("NrtEntityCacheHandle")] IntPtr entityCache);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_EntityCache_RemoveEntity([NativeTypeName("NrtEntityCacheHandle")] IntPtr entityCache, [NativeTypeName("size_t")] nuint poolId, [NativeTypeName("NrtEntityId")] nuint entityToRemove);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_EntityCache_ProcessEntityDeletionRequestsFromThreads([NativeTypeName("NrtEntityCacheHandle")] IntPtr entityCache);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_EntityCache_Destroy([NativeTypeName("NrtEntityCacheHandle")] IntPtr entityCache);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtEntityIdVectorHandle")]
        public static extern IntPtr Nrt_EntityIdVector_Create();

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_EntityIdVector_Insert([NativeTypeName("NrtEntityIdVectorHandle")] IntPtr vector, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_EntityIdVector_Remove([NativeTypeName("NrtEntityIdVectorHandle")] IntPtr vector, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_EntityIdVector_Delete([NativeTypeName("NrtEntityIdVectorHandle")] IntPtr vector);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainerHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_Create([NativeTypeName("size_t")] nuint sizeOfDataTypeInBytes);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_Insert([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint key, [NativeTypeName("const void *")] void* value);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_TryInsert([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint key, [NativeTypeName("const void *")] void* value);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_Remove([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint key);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_TryRemove([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint key);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_Clear([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_ContainsKey([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint key);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndex([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint denseIndex, [NativeTypeName("size_t *")] nuint* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("size_t")]
        public static extern nuint Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndexUnsafe([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint denseIndex);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_GetByteIteratorViewBasedOnDenseIndex([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint denseIndex, [NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle *")] IntPtr* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_GetByteIteratorViewBasedOnDenseIndexUnsafe([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint denseIndex);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndex([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint denseIndex, [NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle *")] IntPtr* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndexUnsafe([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint index);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("size_t")]
        public static extern nuint Nrt_SparseSetMemoryContainer_Length([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_Indexer([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint key);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_ConstIndexer([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint key);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_begin([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_end([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_cbegin([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_cend([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_Destroy([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_ByteIteratorView_IsValid([NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_ByteIteratorView_CopyFromLocation([NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle")] IntPtr view, void* outputLocation);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_ByteIteratorView_WriteToLocation([NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle")] IntPtr view, void* data);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void* Nrt_SparseSetMemoryContainer_ByteIteratorView_GetDataHandle([NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy([NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_ConstByteIteratorView_IsValid([NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_ConstByteIteratorView_CopyFromLocation([NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle")] IntPtr view, void* outputLocation);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("const void *")]
        public static extern void* Nrt_SparseSetMemoryContainer_ConstByteIteratorView_GetDataHandle([NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_ConstByteIteratorView_Destroy([NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_Iterator_MoveNext([NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_Iterator_Equal([NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")] IntPtr lhs, [NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")] IntPtr rhs);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_Iterator_NotEqual([NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")] IntPtr lhs, [NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")] IntPtr rhs);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_Iterator_GetValuePair([NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")] IntPtr iterator, [NativeTypeName("size_t *")] nuint* outputId, [NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle *")] IntPtr* outputView);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_Iterator_Destroy([NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_ConstIterator_MoveNext([NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_ConstIterator_Equal([NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")] IntPtr lhs, [NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")] IntPtr rhs);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_ConstIterator_NotEqual([NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")] IntPtr lhs, [NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")] IntPtr rhs);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_ConstIterator_GetValuePair([NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")] IntPtr iterator, [NativeTypeName("size_t *")] nuint* outputId, [NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle *")] IntPtr* outputView);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_ConstIterator_Destroy([NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSystemSchedulerHandle")]
        public static extern IntPtr Nrt_SystemScheduler_CreateWithDefaultThreadCount();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSystemSchedulerHandle")]
        public static extern IntPtr Nrt_SystemScheduler_Create([NativeTypeName("uint32_t")] uint maximumThreadCount);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SystemScheduler_RegisterSystem([NativeTypeName("NrtSystemSchedulerHandle")] IntPtr scheduler, [NativeTypeName("NrtSystemUpdateFnPtr")] delegate* unmanaged<ulong, IntPtr, void> systemUpdatePtr);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("uint32_t")]
        public static extern uint Nrt_SystemScheduler_GetWorkerThreadCount([NativeTypeName("NrtSystemSchedulerHandle")] IntPtr systemScheduler);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtEntityCacheHandle")]
        public static extern IntPtr Nrt_SystemScheduler_GetEntityCache([NativeTypeName("NrtSystemSchedulerHandle")] IntPtr systemScheduler);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtComponentCacheHandle")]
        public static extern IntPtr Nrt_SystemScheduler_GetComponentCache([NativeTypeName("NrtSystemSchedulerHandle")] IntPtr systemScheduler);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SystemScheduler_SpinThreads([NativeTypeName("NrtSystemSchedulerHandle")] IntPtr systemScheduler);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SystemScheduler_ExecuteIteration([NativeTypeName("NrtSystemSchedulerHandle")] IntPtr systemScheduler, [NativeTypeName("NrtTimestamp")] ulong delta);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SystemScheduler_Destroy([NativeTypeName("NrtSystemSchedulerHandle")] IntPtr systemScheduler);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtUnsafeComponentViewHandle")]
        public static extern IntPtr Nrt_UnsafeComponentView_Create([NativeTypeName("size_t")] nuint poolId, [NativeTypeName("NrtComponentBufferMemoryContainerHandle")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_UnsafeComponentView_PushComponentUpdateInstruction([NativeTypeName("NrtUnsafeComponentViewHandle")] IntPtr componentView, [NativeTypeName("NrtEntityId")] nuint entity, void* instructionData);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_UnsafeComponentView_RemoveComponent([NativeTypeName("NrtUnsafeComponentViewHandle")] IntPtr componentView, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_UnsafeComponentView_GetComponent([NativeTypeName("NrtUnsafeComponentViewHandle")] IntPtr componentView, [NativeTypeName("NrtEntityId")] nuint entity, [NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataViewHandle *")] IntPtr* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataViewHandle")]
        public static extern IntPtr Nrt_UnsafeComponentView_GetComponentUnsafe([NativeTypeName("NrtUnsafeComponentViewHandle")] IntPtr componentView, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("size_t")]
        public static extern nuint Nrt_UnsafeComponentView_GetImmutableDataLength([NativeTypeName("NrtUnsafeComponentViewHandle")] IntPtr componentView);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")]
        public static extern IntPtr Nrt_UnsafeComponentView_begin([NativeTypeName("NrtUnsafeComponentViewHandle")] IntPtr componentView);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")]
        public static extern IntPtr Nrt_UnsafeComponentView_end([NativeTypeName("NrtUnsafeComponentViewHandle")] IntPtr componentView);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_UnsafeComponentView_Destroy([NativeTypeName("NrtUnsafeComponentViewHandle")] IntPtr componentView);
    }
}
