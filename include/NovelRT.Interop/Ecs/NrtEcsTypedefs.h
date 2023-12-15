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
    typedef NrtBool (*NrtComponentComparatorFnPtr)(const void*, const void*, void*);

    typedef void (*NrtSystemUpdateFnPtr)(NrtTimestamp, NrtCatalogueHandle, void*);

    typedef NrtAtom NrtEntityId;
    typedef NrtAtom NrtComponentTypeId;

    // Default components, equivalents in C structs
    // When a component is modified in DefaultComponentTypes.h,
    // it must also be updated there.

    // Note that we do not use the NrtBool type,
    // as it doesn't have the same as a standard C/C++ bool.

    typedef struct
    {
        NrtGeoVector3F positionAndLayer;
        NrtGeoVector2F scale;
        float rotationInRadians;
    } NrtTransformComponent;

    typedef struct
    {
        bool isValid;
        NrtEntityId parent;
        NrtEntityId childrenStartNode;
    } NrtEntityGraphComponent;

    typedef struct
    {
        bool isValid;
        NrtEntityId parent;
        NrtEntityId childrenStartNode;
    } NrtLinkedEntityListNodeComponent;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_ECSTYPEDEFS_H
