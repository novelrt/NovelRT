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
    class SparseSetMemoryContainer : ShimObject
    {
        public SparseSetMemoryContainer(nuint sizeOfDataTypeInBytes){
            _internalHandle = Nrt_SparseSetMemoryContainer_Create(sizeOfDataTypeInBytes);
        }
        public override void Dispose(bool isDisposing)
        {
            if (internalHandle != IntPtr.Zero)
            {
                NrtResult result = Nrt_SparseSetMemoryContainer_Destroy(internalHandle);
                NrtUtilities.ThrowExceptionIfFailed(result, this);
            }
        }


        /*
        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_Insert([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint key, [NativeTypeName("const void *")] void* value);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_TryInsert([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint key, [NativeTypeName("const void *")] void* value);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_Remove([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint key);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_TryRemove([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint key);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_Clear([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_ContainsKey([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint key);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndex([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint denseIndex, [NativeTypeName("size_t *")] nuint* outputResult);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("size_t")]
        public static extern nuint Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndexUnsafe([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint denseIndex);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_GetByteIteratorViewBasedOnDenseIndex([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint denseIndex, [NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle *")] IntPtr* outputResult);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_GetByteIteratorViewBasedOnDenseIndexUnsafe([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint denseIndex);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndex([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint denseIndex, [NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle *")] IntPtr* outputResult);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndexUnsafe([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint index);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("size_t")]
        public static extern nuint Nrt_SparseSetMemoryContainer_Length([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_Indexer([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint key);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_ConstIndexer([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container, [NativeTypeName("size_t")] nuint key);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_begin([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_end([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_cbegin([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")]
        public static extern IntPtr Nrt_SparseSetMemoryContainer_cend([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_Destroy([NativeTypeName("NrtSparseSetMemoryContainerHandle")] IntPtr container);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_ByteIteratorView_IsValid([NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle")] IntPtr view);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_ByteIteratorView_CopyFromLocation([NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle")] IntPtr view, void* outputLocation);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_ByteIteratorView_WriteToLocation([NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle")] IntPtr view, void* data);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void* Nrt_SparseSetMemoryContainer_ByteIteratorView_GetDataHandle([NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle")] IntPtr view);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy([NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle")] IntPtr view);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_ConstByteIteratorView_IsValid([NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle")] IntPtr view);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_ConstByteIteratorView_CopyFromLocation([NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle")] IntPtr view, void* outputLocation);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("const void *")]
        public static extern void* Nrt_SparseSetMemoryContainer_ConstByteIteratorView_GetDataHandle([NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle")] IntPtr view);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_ConstByteIteratorView_Destroy([NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle")] IntPtr view);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_Iterator_MoveNext([NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")] IntPtr iterator);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_Iterator_Equal([NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")] IntPtr lhs, [NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")] IntPtr rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_Iterator_NotEqual([NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")] IntPtr lhs, [NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")] IntPtr rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_Iterator_GetValuePair([NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")] IntPtr iterator, [NativeTypeName("size_t *")] nuint* outputId, [NativeTypeName("NrtSparseSetMemoryContainer_ByteIteratorViewHandle *")] IntPtr* outputView);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_Iterator_Destroy([NativeTypeName("NrtSparseSetMemoryContainer_IteratorHandle")] IntPtr iterator);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern void Nrt_SparseSetMemoryContainer_ConstIterator_MoveNext([NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")] IntPtr iterator);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_ConstIterator_Equal([NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")] IntPtr lhs, [NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")] IntPtr rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SparseSetMemoryContainer_ConstIterator_NotEqual([NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")] IntPtr lhs, [NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")] IntPtr rhs);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_ConstIterator_GetValuePair([NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")] IntPtr iterator, [NativeTypeName("size_t *")] nuint* outputId, [NativeTypeName("NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle *")] IntPtr* outputView);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SparseSetMemoryContainer_ConstIterator_Destroy([NativeTypeName("NrtSparseSetMemoryContainer_ConstIteratorHandle")] IntPtr iterator);
*/
    }
}
