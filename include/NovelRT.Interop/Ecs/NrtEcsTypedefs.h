// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_ECSTYPEDEFS_H
#define NOVELRT_INTEROP_ECS_ECSTYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtCatalogue* NrtCatalogueHandle;
    typedef struct NrtConfigurator* NrtConfiguratorHandle;
    typedef struct NrtComponentBufferMemoryContainer* NrtComponentBufferMemoryContainerHandle;
    typedef struct NrtComponentBufferMemoryContainer_ImmutableDataView*
        NrtComponentBufferMemoryContainer_ImmutableDataViewHandle;
    typedef struct NrtComponentCache* NrtComponentCacheHandle;
    typedef struct NrtEntityIdVector* NrtEntityIdVectorHandle;
    typedef struct NrtEntityCache* NrtEntityCacheHandle;
    typedef struct NrtSparseSetMemoryContainer* NrtSparseSetMemoryContainerHandle;
    typedef struct NrtSparseSetMemoryContainer_ByteIteratorView* NrtSparseSetMemoryContainer_ByteIteratorViewHandle;
    typedef struct NrtSparseSetMemoryContainer_ConstByteIteratorView*
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle;
    typedef struct NrtSparseSetMemoryContainer_Iterator* NrtSparseSetMemoryContainer_IteratorHandle;
    typedef struct NrtSparseSetMemoryContainer_ConstIterator* NrtSparseSetMemoryContainer_ConstIteratorHandle;
    typedef struct NrtSystemScheduler* NrtSystemSchedulerHandle;
    typedef struct NrtUnsafeComponentView* NrtUnsafeComponentViewHandle;

    typedef void (*NrtComponentUpdateFnPtr)(void*, const void*, size_t, void*);

    typedef void (*NrtSystemUpdateFnPtr)(NrtTimestamp, NrtCatalogueHandle, void*);

    typedef NrtAtom NrtEntityId;
    typedef NrtAtom NrtComponentTypeId;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_ECSTYPEDEFS_H
