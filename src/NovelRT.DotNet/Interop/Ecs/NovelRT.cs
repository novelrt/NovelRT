// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_Create([NativeTypeName("size_t")] nuint sizeOfDataTypeInBytes);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SparseSetMemoryContainer_Insert([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container, [NativeTypeName("size_t")] nuint key, [NativeTypeName("const void *")] void* value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SparseSetMemoryContainer_TryInsert([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container, [NativeTypeName("size_t")] nuint key, [NativeTypeName("const void *")] void* value);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SparseSetMemoryContainer_Remove([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container, [NativeTypeName("size_t")] nuint key);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SparseSetMemoryContainer_TryRemove([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container, [NativeTypeName("size_t")] nuint key);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_Clear([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SparseSetMemoryContainer_ContainsKey([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container, [NativeTypeName("size_t")] nuint key);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndex([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container, [NativeTypeName("size_t")] nuint denseIndex, [NativeTypeName("size_t *")] nuint* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("size_t")]
        public static extern nuint Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndexUnsafe([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container, [NativeTypeName("size_t")] nuint denseIndex);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SparseSetMemoryContainer_GetByteIteratorViewBasedOnDenseIndex([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container, [NativeTypeName("size_t")] nuint denseIndex, [NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorView *")] IntPtr* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorView")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_GetByteIteratorViewBasedOnDenseIndexUnsafe([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container, [NativeTypeName("size_t")] nuint denseIndex);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndex([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container, [NativeTypeName("size_t")] nuint denseIndex, [NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorView *")] IntPtr* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorView")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndexUnsafe([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container, [NativeTypeName("size_t")] nuint index);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("size_t")]
        public static extern nuint Nrt_SparseSetMemoryContainer_Length([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorView")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_Indexer([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container, [NativeTypeName("size_t")] nuint key);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorView")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_ConstIndexer([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container, [NativeTypeName("size_t")] nuint key);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_Iterator")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_begin([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_Iterator")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_end([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIterator")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_cbegin([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIterator")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_cend([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SparseSetMemoryContainer_Destroy([NativeTypeName("NrtSparseSetMemoryContainer")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SparseSetMemoryContainer_ByteIteratorView_IsValid([NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorView")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_ByteIteratorView_CopyFromLocation([NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorView")] IntPtr view, [NativeTypeName("void *")] void* outputLocation);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_ByteIteratorView_WriteToLocation([NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorView")] IntPtr view, [NativeTypeName("void *")] void* data);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("void *")]
        public static extern void* Nrt_SparseSetMemoryContainer_ByteIteratorView_GetDataHandle([NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorView")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy([NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorView")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SparseSetMemoryContainer_ConstByteIteratorView_IsValid([NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorView")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_ConstByteIteratorView_CopyFromLocation([NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorView")] IntPtr view, [NativeTypeName("void *")] void* outputLocation);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("const void *")]
        public static extern void* Nrt_SparseSetMemoryContainer_ConstByteIteratorView_GetDataHandle([NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorView")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SparseSetMemoryContainer_ConstByteIteratorView_Destroy([NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorView")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_Iterator_MoveNext([NativeTypeName("NrtSparseSetMemoryContainer_Iterator")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SparseSetMemoryContainer_Iterator_Equal([NativeTypeName("NrtSparseSetMemoryContainer_Iterator")] IntPtr lhs, [NativeTypeName("NrtSparseSetMemoryContainer_Iterator")] IntPtr rhs);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SparseSetMemoryContainer_Iterator_NotEqual([NativeTypeName("NrtSparseSetMemoryContainer_Iterator")] IntPtr lhs, [NativeTypeName("NrtSparseSetMemoryContainer_Iterator")] IntPtr rhs);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SparseSetMemoryContainer_Iterator_GetValuePair([NativeTypeName("NrtSparseSetMemoryContainer_Iterator")] IntPtr iterator, [NativeTypeName("size_t *")] nuint* outputId, [NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorView *")] IntPtr* outputView);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SparseSetMemoryContainer_Iterator_Destroy([NativeTypeName("NrtSparseSetMemoryContainer_Iterator")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_ConstIterator_MoveNext([NativeTypeName("NrtSparseSetMemoryContainer_ConstIterator")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SparseSetMemoryContainer_ConstIterator_Equal([NativeTypeName("NrtSparseSetMemoryContainer_ConstIterator")] IntPtr lhs, [NativeTypeName("NrtSparseSetMemoryContainer_ConstIterator")] IntPtr rhs);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SparseSetMemoryContainer_ConstIterator_NotEqual([NativeTypeName("NrtSparseSetMemoryContainer_ConstIterator")] IntPtr lhs, [NativeTypeName("NrtSparseSetMemoryContainer_ConstIterator")] IntPtr rhs);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SparseSetMemoryContainer_ConstIterator_GetValuePair([NativeTypeName("NrtSparseSetMemoryContainer_ConstIterator")] IntPtr iterator, [NativeTypeName("size_t *")] nuint* outputId, [NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorView *")] IntPtr* outputView);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SparseSetMemoryContainer_ConstIterator_Destroy([NativeTypeName("NrtSparseSetMemoryContainer_ConstIterator")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtComponentBufferMemoryContainer")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_Create([NativeTypeName("size_t")] nuint poolSize, [NativeTypeName("void *")] void* deleteInstructionState, [NativeTypeName("size_t")] nuint sizeOfDataTypeInBytes, [NativeTypeName("NrtComponentUpdateFnPtr")] delegate* unmanaged<IntPtr, IntPtr, nuint, void> fnPtr);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame([NativeTypeName("NrtComponentBufferMemoryContainer")] IntPtr container, [NativeTypeName("NrtEntityIdVector")] IntPtr entitiesToDelete);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataView")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_GetDeleteInstructionState([NativeTypeName("NrtComponentBufferMemoryContainer")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction([NativeTypeName("NrtComponentBufferMemoryContainer")] IntPtr container, [NativeTypeName("size_t")] nuint poolId, [NativeTypeName("NrtEntityId")] nuint entity, [NativeTypeName("const void *")] void* componentData);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ComponentBufferMemoryContainer_GetComponent([NativeTypeName("NrtComponentBufferMemoryContainer")] IntPtr container, [NativeTypeName("NrtEntityId")] nuint entity, [NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataView *")] IntPtr* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataView")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_GetComponentUnsafe([NativeTypeName("NrtComponentBufferMemoryContainer")] IntPtr container, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_ComponentBufferMemoryContainer_HasComponent([NativeTypeName("NrtComponentBufferMemoryContainer")] IntPtr container, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("size_t")]
        public static extern nuint Nrt_ComponentBufferMemoryContainer_GetImmutableDataLength([NativeTypeName("NrtComponentBufferMemoryContainer")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIterator")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_begin([NativeTypeName("NrtComponentBufferMemoryContainer")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIterator")]
        public static extern IntPtr Nrt_ComponentBufferMemoryContainer_end([NativeTypeName("NrtComponentBufferMemoryContainer")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ComponentBufferMemoryContainer_Destroy([NativeTypeName("NrtComponentBufferMemoryContainer")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("const void *")]
        public static extern void* Nrt_ComponentBufferMemoryContainer_ImmutableDataView_GetDataHandle([NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataView")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ComponentBufferMemoryContainer_ImmutableDataView_Destroy([NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataView")] IntPtr view);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtComponentCache")]
        public static extern IntPtr Nrt_ComponentCache_Create([NativeTypeName("size_t")] nuint poolSize);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ComponentCache_RegisterComponentTypeUnsafe([NativeTypeName("NrtComponentCache")] IntPtr componentCache, [NativeTypeName("size_t")] nuint sizeOfDataType, [NativeTypeName("const void *")] void* deleteInstructionState, [NativeTypeName("NrtComponentUpdateFnPtr")] delegate* unmanaged<IntPtr, IntPtr, nuint, void> updateFnPtr, [NativeTypeName("NrtComponentTypeId *")] nuint* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ComponentCache_GetComponentBufferById([NativeTypeName("NrtComponentCache")] IntPtr componentCache, [NativeTypeName("NrtComponentTypeId")] nuint id, [NativeTypeName("NrtComponentBufferMemoryContainer *")] IntPtr* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_ComponentCache_PrepAllBuffersForNextFrame([NativeTypeName("NrtComponentCache")] IntPtr componentCache, [NativeTypeName("NrtEntityIdVector")] IntPtr entitiesToDelete);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_ComponentCache_Destroy([NativeTypeName("NrtComponentCache")] IntPtr componentCache);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtEntityCache")]
        public static extern IntPtr Nrt_EntityCache_Create([NativeTypeName("size_t")] nuint poolSize);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtEntityIdVector")]
        public static extern IntPtr Nrt_EntityCache_GetEntitiesToRemoveThisFrame([NativeTypeName("NrtEntityCache")] IntPtr entityCache);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_EntityCache_RemoveEntity([NativeTypeName("NrtEntityCache")] IntPtr entityCache, [NativeTypeName("size_t")] nuint poolId, [NativeTypeName("NrtEntityId")] nuint entityToRemove);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_EntityCache_ProcessEntityDeletionRequestsFromThreads([NativeTypeName("NrtEntityCache")] IntPtr entityCache);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_EntityCache_Destroy([NativeTypeName("NrtEntityCache")] IntPtr entityCache);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtUnsafeComponentView")]
        public static extern IntPtr Nrt_UnsafeComponentView_Create([NativeTypeName("size_t")] nuint poolId, [NativeTypeName("NrtComponentBufferMemoryContainer")] IntPtr container);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_UnsafeComponentView_PushComponentUpdateInstruction([NativeTypeName("NrtUnsafeComponentView")] IntPtr componentView, [NativeTypeName("NrtEntityId")] nuint entity, [NativeTypeName("void *")] void* instructionData);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_UnsafeComponentView_RemoveComponent([NativeTypeName("NrtUnsafeComponentView")] IntPtr componentView, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_UnsafeComponentView_GetComponent([NativeTypeName("NrtUnsafeComponentView")] IntPtr componentView, [NativeTypeName("NrtEntityId")] nuint entity, [NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataView *")] IntPtr* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtComponentBufferMemoryContainer_ImmutableDataView")]
        public static extern IntPtr Nrt_UnsafeComponentView_GetComponentUnsafe([NativeTypeName("NrtUnsafeComponentView")] IntPtr componentView, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("size_t")]
        public static extern nuint Nrt_UnsafeComponentView_GetImmutableDataLength([NativeTypeName("NrtUnsafeComponentView")] IntPtr componentView);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIterator")]
        public static extern IntPtr Nrt_UnsafeComponentView_begin([NativeTypeName("NrtUnsafeComponentView")] IntPtr componentView);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIterator")]
        public static extern IntPtr Nrt_UnsafeComponentView_end([NativeTypeName("NrtUnsafeComponentView")] IntPtr componentView);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_UnsafeComponentView_Destroy([NativeTypeName("NrtUnsafeComponentView")] IntPtr componentView);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtCatalogue")]
        public static extern IntPtr Nrt_Catalogue_Create([NativeTypeName("size_t")] nuint poolId, [NativeTypeName("NrtComponentCache")] IntPtr componentCache, [NativeTypeName("NrtEntityCache")] IntPtr entityCache);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Catalogue_GetComponentViewById([NativeTypeName("NrtCatalogue")] IntPtr catalogue, [NativeTypeName("NrtComponentTypeId")] nuint componentId, [NativeTypeName("NrtUnsafeComponentView *")] IntPtr* outputResult);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtUnsafeComponentView")]
        public static extern IntPtr Nrt_Catalogue_GetComponentViewByIdUnsafe([NativeTypeName("NrtCatalogue")] IntPtr catalogue, [NativeTypeName("NrtComponentTypeId")] nuint componentId);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtEntityId")]
        public static extern nuint Nrt_catalogue_CreateEntity([NativeTypeName("NrtCatalogue")] IntPtr catalogue);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Catalogue_DeleteEntity([NativeTypeName("NrtCatalogue")] IntPtr catalogue, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Catalogue_Destroy([NativeTypeName("NrtCatalogue")] IntPtr catalogue);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtEntityIdVector")]
        public static extern IntPtr Nrt_EntityIdVector_Create();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_EntityIdVector_Insert([NativeTypeName("NrtEntityIdVector")] IntPtr vector, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_EntityIdVector_Remove([NativeTypeName("NrtEntityIdVector")] IntPtr vector, [NativeTypeName("NrtEntityId")] nuint entity);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_EntityIdVector_Delete([NativeTypeName("NrtEntityIdVector")] IntPtr vector);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSystemScheduler")]
        public static extern IntPtr Nrt_SystemScheduler_CreateWithDefaultThreadCount();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSystemScheduler")]
        public static extern IntPtr Nrt_SystemScheduler_Create([NativeTypeName("uint32_t")] uint maximumThreadCount);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SystemScheduler_RegisterSystem([NativeTypeName("NrtSystemScheduler")] IntPtr scheduler, [NativeTypeName("NrtSystemUpdatePtr")] delegate* unmanaged<ulong, IntPtr, void> systemUpdatePtr);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("uint32_t")]
        public static extern uint Nrt_SystemScheduler_GetWorkerThreadCount([NativeTypeName("NrtSystemScheduler")] IntPtr systemScheduler);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtEntityCache")]
        public static extern IntPtr Nrt_SystemScheduler_GetEntityCache([NativeTypeName("NrtSystemScheduler")] IntPtr systemScheduler);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtComponentCache")]
        public static extern IntPtr Nrt_SystemScheduler_GetComponentCache([NativeTypeName("NrtSystemScheduler")] IntPtr systemScheduler);

        [DllImport("Interop", ExactSpelling = true)]
        public static extern void Nrt_SystemScheduler_SpinThreads([NativeTypeName("NrtSystemScheduler")] IntPtr systemScheduler);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SystemScheduler_ExecuteIteration([NativeTypeName("NrtSystemScheduler")] IntPtr systemScheduler, [NativeTypeName("NrtTimestamp")] ulong delta);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SystemScheduler_Destroy([NativeTypeName("NrtSystemScheduler")] IntPtr systemScheduler);
    }
}
