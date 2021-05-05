// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTreeNode_create([NativeTypeName("NrtQuadTreeScenePointArrayHandle")] IntPtr points, [NativeTypeName("NrtQuadTreeNodeHandle *")] IntPtr* outputPoint);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTreeNode_getTopLeft([NativeTypeName("NrtQuadTreeNodeHandle")] IntPtr node, [NativeTypeName("NrtQuadTreeScenePointHandle *")] IntPtr* outputPoint);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTreeNode_getTopRight([NativeTypeName("NrtQuadTreeNodeHandle")] IntPtr node, [NativeTypeName("NrtQuadTreeScenePointHandle *")] IntPtr* outputPoint);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTreeNode_getBottomLeft([NativeTypeName("NrtQuadTreeNodeHandle")] IntPtr node, [NativeTypeName("NrtQuadTreeScenePointHandle *")] IntPtr* outputPoint);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTreeNode_getBottomRight([NativeTypeName("NrtQuadTreeNodeHandle")] IntPtr node, [NativeTypeName("NrtQuadTreeScenePointHandle *")] IntPtr* outputPoint);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTreeScenePointArray_create([NativeTypeName("NrtQuadTreeScenePointHandle")] IntPtr pointOne, [NativeTypeName("NrtQuadTreeScenePointHandle")] IntPtr pointTwo, [NativeTypeName("NrtQuadTreeScenePointHandle")] IntPtr pointThree, [NativeTypeName("NrtQuadTreeScenePointHandle")] IntPtr pointFour, [NativeTypeName("NrtQuadTreeScenePointArrayHandle *")] IntPtr* outputArray);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTreeScenePoint_createVector(NrtGeoVector2F position, [NativeTypeName("NrtSceneNodeHandle")] IntPtr node, [NativeTypeName("NrtQuadTreeScenePointHandle *")] IntPtr* outputPoint);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTreeScenePoint_createFloat(float x, float y, [NativeTypeName("NrtSceneNodeHandle")] IntPtr node, [NativeTypeName("NrtQuadTreeScenePointHandle *")] IntPtr* outputPoint);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_QuadTreeScenePoint_getSceneNode([NativeTypeName("NrtQuadTreeScenePointHandle")] IntPtr point, [NativeTypeName("NrtSceneNodeHandle *")] IntPtr* outputNode);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderObjectNode_create([NativeTypeName("NrtRenderObjectHandle")] IntPtr @object, [NativeTypeName("NrtRenderObjectNodeHandle *")] IntPtr* outputNode);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderObjectNode_getRenderObject([NativeTypeName("NrtRenderObjectNodeHandle")] IntPtr node, [NativeTypeName("NrtRenderObjectHandle *")] IntPtr* outputObject);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_RenderObjectNode_delete([NativeTypeName("NrtRenderObjectNodeHandle")] IntPtr node);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSceneHandle")]
        public static extern IntPtr Nrt_Scene_create();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Scene_getNodes([NativeTypeName("NrtSceneHandle")] IntPtr scene, [NativeTypeName("NrtSceneNodeSetHandle *")] IntPtr* outputSet);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_Scene_insert([NativeTypeName("NrtSceneHandle")] IntPtr scene, [NativeTypeName("NrtSceneNodeHandle")] IntPtr nodeToInsert);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_Scene_remove([NativeTypeName("NrtSceneHandle")] IntPtr scene, [NativeTypeName("NrtSceneNodeHandle")] IntPtr nodeToRemove);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_Scene_delete([NativeTypeName("NrtSceneHandle")] IntPtr scene);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSceneNodeHandle")]
        public static extern IntPtr Nrt_SceneNode_create();

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SceneNode_getChildren([NativeTypeName("NrtSceneNodeHandle")] IntPtr node, [NativeTypeName("NrtSceneNodeSetHandle *")] IntPtr* outputSet);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SceneNode_getParents([NativeTypeName("NrtSceneNodeHandle")] IntPtr node, [NativeTypeName("NrtSceneNodeSetHandle *")] IntPtr* outputSet);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SceneNode_insert([NativeTypeName("NrtSceneNodeHandle")] IntPtr node, [NativeTypeName("NrtSceneNodeHandle")] IntPtr nodeToInsert);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SceneNode_remove([NativeTypeName("NrtSceneNodeHandle")] IntPtr node, [NativeTypeName("NrtSceneNodeHandle")] IntPtr nodeToRemove);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SceneNode_isAdjacent([NativeTypeName("NrtSceneNodeHandle")] IntPtr firstNode, [NativeTypeName("NrtSceneNodeHandle")] IntPtr secondNode);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SceneNode_traverseBreadthFirst([NativeTypeName("NrtSceneNodeHandle")] IntPtr node, [NativeTypeName("void (*)(NrtSceneNodeHandle, void *)")] delegate* unmanaged<IntPtr, void*, void> action, void* context);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SceneNode_traverseBreadthFirstWithIterator([NativeTypeName("NrtSceneNodeHandle")] IntPtr node, [NativeTypeName("int32_t (*)(NrtSceneNodeHandle, void *)")] delegate* unmanaged<IntPtr, void*, int> action, void* context, [NativeTypeName("NrtSceneNodeBreadthFirstIteratorHandle *")] IntPtr* outputIterator);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SceneNode_traverseDepthFirst([NativeTypeName("NrtSceneNodeHandle")] IntPtr node, [NativeTypeName("void (*)(NrtSceneNodeHandle, void *)")] delegate* unmanaged<IntPtr, void*, void> action, void* context);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SceneNode_traverseDepthFirstWithIterator([NativeTypeName("NrtSceneNodeHandle")] IntPtr node, [NativeTypeName("int32_t (*)(NrtSceneNodeHandle, void *)")] delegate* unmanaged<IntPtr, void*, int> action, void* context, [NativeTypeName("NrtSceneNodeDepthFirstIteratorHandle *")] IntPtr* outputIterator);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SceneNode_canReach([NativeTypeName("NrtSceneNodeHandle")] IntPtr firstNode, [NativeTypeName("NrtSceneNodeHandle")] IntPtr secondNode);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SceneNode_delete([NativeTypeName("NrtSceneNodeHandle")] IntPtr node);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SceneNodeSet_delete([NativeTypeName("NrtSceneNodeSetHandle")] IntPtr nodeSet);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("size_t")]
        public static extern nuint Nrt_SceneNodeSet_getSize([NativeTypeName("const NrtSceneNodeSetHandle")] IntPtr nodeSet);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SceneNodeSet_getSceneNodeFromIndex([NativeTypeName("const NrtSceneNodeSetHandle")] IntPtr nodeSet, [NativeTypeName("size_t")] nuint index, [NativeTypeName("NrtSceneNodeHandle *")] IntPtr* outputSceneNode);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SceneNodeBreadthFirstIterator_create([NativeTypeName("NrtSceneNodeHandle")] IntPtr node, [NativeTypeName("int32_t (*)(NrtSceneNodeHandle, void *)")] delegate* unmanaged<IntPtr, void*, int> func, void* context, [NativeTypeName("NrtSceneNodeBreadthFirstIteratorHandle *")] IntPtr* outputIterator);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SceneNodeBreadthFirstIterator_increment([NativeTypeName("NrtSceneNodeBreadthFirstIteratorHandle")] IntPtr iterator);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SceneNodeBreadthFirstIterator_postFixIncrement([NativeTypeName("NrtSceneNodeBreadthFirstIteratorHandle")] IntPtr iterator);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SceneNodeBreadthFirstIterator_isEnd([NativeTypeName("NrtSceneNodeBreadthFirstIteratorHandle")] IntPtr iterator);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_SceneNodeBreadthFirstIterator_runFunction([NativeTypeName("NrtSceneNodeBreadthFirstIteratorHandle")] IntPtr iterator);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SceneNodeBreadthFirstIterator_isEqual([NativeTypeName("NrtSceneNodeBreadthFirstIteratorHandle")] IntPtr iterator, [NativeTypeName("NrtSceneNodeBreadthFirstIteratorHandle")] IntPtr other);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SceneNodeBreadthFirstIterator_isNotEqual([NativeTypeName("NrtSceneNodeBreadthFirstIteratorHandle")] IntPtr iterator, [NativeTypeName("NrtSceneNodeBreadthFirstIteratorHandle")] IntPtr other);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SceneNodeDepthFirstIterator_create([NativeTypeName("NrtSceneNodeHandle")] IntPtr node, [NativeTypeName("int32_t (*)(NrtSceneNodeHandle, void *)")] delegate* unmanaged<IntPtr, void*, int> func, void* context, [NativeTypeName("NrtSceneNodeDepthFirstIteratorHandle *")] IntPtr* outputIterator);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SceneNodeDepthFirstIterator_increment([NativeTypeName("NrtSceneNodeDepthFirstIteratorHandle")] IntPtr iterator);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtResult Nrt_SceneNodeDepthFirstIterator_postFixIncrement([NativeTypeName("NrtSceneNodeDepthFirstIteratorHandle")] IntPtr iterator);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SceneNodeDepthFirstIterator_isEnd([NativeTypeName("NrtSceneNodeDepthFirstIteratorHandle")] IntPtr iterator);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_SceneNodeDepthFirstIterator_runFunction([NativeTypeName("NrtSceneNodeDepthFirstIteratorHandle")] IntPtr iterator);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SceneNodeDepthFirstIterator_isEqual([NativeTypeName("NrtSceneNodeDepthFirstIteratorHandle")] IntPtr iterator, [NativeTypeName("NrtSceneNodeDepthFirstIteratorHandle")] IntPtr other);

        [DllImport("NovelRT.Interop", ExactSpelling = true)]
        public static extern NrtBool Nrt_SceneNodeDepthFirstIterator_isNotEqual([NativeTypeName("NrtSceneNodeDepthFirstIteratorHandle")] IntPtr iterator, [NativeTypeName("NrtSceneNodeDepthFirstIteratorHandle")] IntPtr other);
    }
}
