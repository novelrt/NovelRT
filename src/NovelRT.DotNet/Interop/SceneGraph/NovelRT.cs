// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using System;
using System.Runtime.InteropServices;

namespace NovelRT.Interop
{
    public static unsafe partial class NovelRT
    {
        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtSceneNode")]
        public static extern IntPtr Nrt_SceneNode_create();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SceneNode_getChildren([NativeTypeName("NrtSceneNode")] IntPtr node, [NativeTypeName("NrtSceneNodeSet *")] IntPtr* outputSet);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SceneNode_getParents([NativeTypeName("NrtSceneNode")] IntPtr node, [NativeTypeName("NrtSceneNodeSet *")] IntPtr* outputSet);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SceneNode_insert([NativeTypeName("NrtSceneNode")] IntPtr node, [NativeTypeName("NrtSceneNode")] IntPtr nodeToInsert);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SceneNode_remove([NativeTypeName("NrtSceneNode")] IntPtr node, [NativeTypeName("NrtSceneNode")] IntPtr nodeToRemove);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SceneNode_isAdjacent([NativeTypeName("NrtSceneNode")] IntPtr firstNode, [NativeTypeName("NrtSceneNode")] IntPtr secondNode);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SceneNode_traverseBreadthFirst([NativeTypeName("NrtSceneNode")] IntPtr node, [NativeTypeName("void (*)(NrtSceneNode)")] delegate* unmanaged<IntPtr, void> action);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SceneNode_traverseBreadthFirstWithIterator([NativeTypeName("NrtSceneNode")] IntPtr node, [NativeTypeName("int32_t (*)(NrtSceneNode)")] delegate* unmanaged<IntPtr, int> action, [NativeTypeName("NrtSceneNodeBreadthFirstIterator *")] IntPtr* outputIterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SceneNode_traverseDepthFirst([NativeTypeName("NrtSceneNode")] IntPtr node, [NativeTypeName("void (*)(NrtSceneNode)")] delegate* unmanaged<IntPtr, void> action);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SceneNode_traverseDepthFirstWithIterator([NativeTypeName("NrtSceneNode")] IntPtr node, [NativeTypeName("int32_t (*)(NrtSceneNode)")] delegate* unmanaged<IntPtr, int> action, [NativeTypeName("NrtSceneNodeDepthFirstIterator *")] IntPtr* outputIterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SceneNode_canReach([NativeTypeName("NrtSceneNode")] IntPtr firstNode, [NativeTypeName("NrtSceneNode")] IntPtr secondNode);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SceneNode_delete([NativeTypeName("NrtSceneNode")] IntPtr node);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SceneNodeSet_delete([NativeTypeName("NrtSceneNodeSet")] IntPtr nodeSet);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("size_t")]
        public static extern nuint Nrt_SceneNodeSet_getSize([NativeTypeName("const NrtSceneNodeSet")] IntPtr nodeSet);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SceneNodeSet_getSceneNodeFromIndex([NativeTypeName("const NrtSceneNodeSet")] IntPtr nodeSet, [NativeTypeName("size_t")] nuint index, [NativeTypeName("NrtSceneNode *")] IntPtr* outputSceneNode);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SceneNodeBreadthFirstIterator_create([NativeTypeName("NrtSceneNode")] IntPtr node, [NativeTypeName("int32_t (*)(NrtSceneNode)")] delegate* unmanaged<IntPtr, int> func, [NativeTypeName("NrtSceneNodeBreadthFirstIterator *")] IntPtr* outputIterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SceneNodeBreadthFirstIterator_increment([NativeTypeName("NrtSceneNodeBreadthFirstIterator")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SceneNodeBreadthFirstIterator_postFixIncrement([NativeTypeName("NrtSceneNodeBreadthFirstIterator")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SceneNodeBreadthFirstIterator_isEnd([NativeTypeName("NrtSceneNodeBreadthFirstIterator")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_SceneNodeBreadthFirstIterator_runFunction([NativeTypeName("NrtSceneNodeBreadthFirstIterator")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SceneNodeBreadthFirstIterator_isEqual([NativeTypeName("NrtSceneNodeBreadthFirstIterator")] IntPtr iterator, [NativeTypeName("NrtSceneNodeBreadthFirstIterator")] IntPtr other);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SceneNodeBreadthFirstIterator_isNotEqual([NativeTypeName("NrtSceneNodeBreadthFirstIterator")] IntPtr iterator, [NativeTypeName("NrtSceneNodeBreadthFirstIterator")] IntPtr other);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SceneNodeDepthFirstIterator_create([NativeTypeName("NrtSceneNode")] IntPtr node, [NativeTypeName("int32_t (*)(NrtSceneNode)")] delegate* unmanaged<IntPtr, int> func, [NativeTypeName("NrtSceneNodeDepthFirstIterator *")] IntPtr* outputIterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SceneNodeDepthFirstIterator_increment([NativeTypeName("NrtSceneNodeDepthFirstIterator")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_SceneNodeDepthFirstIterator_postFixIncrement([NativeTypeName("NrtSceneNodeDepthFirstIterator")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SceneNodeDepthFirstIterator_isEnd([NativeTypeName("NrtSceneNodeDepthFirstIterator")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("int32_t")]
        public static extern int Nrt_SceneNodeDepthFirstIterator_runFunction([NativeTypeName("NrtSceneNodeDepthFirstIterator")] IntPtr iterator);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SceneNodeDepthFirstIterator_isEqual([NativeTypeName("NrtSceneNodeDepthFirstIterator")] IntPtr iterator, [NativeTypeName("NrtSceneNodeDepthFirstIterator")] IntPtr other);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_SceneNodeDepthFirstIterator_isNotEqual([NativeTypeName("NrtSceneNodeDepthFirstIterator")] IntPtr iterator, [NativeTypeName("NrtSceneNodeDepthFirstIterator")] IntPtr other);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderObjectNode_create([NativeTypeName("NrtRenderObject")] IntPtr @object, [NativeTypeName("NovelRTRenderObjectNode *")] IntPtr* outputNode);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderObjectNode_getRenderObject([NativeTypeName("NovelRTRenderObjectNode")] IntPtr node, [NativeTypeName("NrtRenderObject *")] IntPtr* outputObject);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_RenderObjectNode_delete([NativeTypeName("NovelRTRenderObjectNode")] IntPtr node);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_QuadTreeScenePoint_createVector(NrtGeoVector2F position, [NativeTypeName("NrtSceneNode")] IntPtr node, [NativeTypeName("NrtQuadTreeScenePoint *")] IntPtr* outputPoint);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_QuadTreeScenePoint_createFloat(float x, float y, [NativeTypeName("NrtSceneNode")] IntPtr node, [NativeTypeName("NrtQuadTreeScenePoint *")] IntPtr* outputPoint);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_QuadTreeScenePoint_getSceneNode([NativeTypeName("NrtQuadTreeScenePoint")] IntPtr point, [NativeTypeName("NrtSceneNode *")] IntPtr* outputNode);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_QuadTreeNode_create([NativeTypeName("NrtQuadTreeScenePointArray")] IntPtr points, [NativeTypeName("NrtQuadTreeNode *")] IntPtr* outputPoint);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_QuadTreeNode_getTopLeft([NativeTypeName("NrtQuadTreeNode")] IntPtr node, [NativeTypeName("NrtQuadTreeScenePoint *")] IntPtr* outputPoint);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_QuadTreeNode_getTopRight([NativeTypeName("NrtQuadTreeNode")] IntPtr node, [NativeTypeName("NrtQuadTreeScenePoint *")] IntPtr* outputPoint);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_QuadTreeNode_getBottomLeft([NativeTypeName("NrtQuadTreeNode")] IntPtr node, [NativeTypeName("NrtQuadTreeScenePoint *")] IntPtr* outputPoint);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_QuadTreeNode_getBottomRight([NativeTypeName("NrtQuadTreeNode")] IntPtr node, [NativeTypeName("NrtQuadTreeScenePoint *")] IntPtr* outputPoint);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_QuadTreeScenePointArray_create([NativeTypeName("NrtQuadTreeScenePoint")] IntPtr pointOne, [NativeTypeName("NrtQuadTreeScenePoint")] IntPtr pointTwo, [NativeTypeName("NrtQuadTreeScenePoint")] IntPtr pointThree, [NativeTypeName("NrtQuadTreeScenePoint")] IntPtr pointFour, [NativeTypeName("NrtQuadTreeScenePointArray *")] IntPtr* outputArray);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtScene")]
        public static extern IntPtr Nrt_Scene_create();

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Scene_getNodes([NativeTypeName("NrtScene")] IntPtr scene, [NativeTypeName("NrtSceneNodeSet *")] IntPtr* outputSet);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_Scene_insert([NativeTypeName("NrtScene")] IntPtr scene, [NativeTypeName("NrtSceneNode")] IntPtr nodeToInsert);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtBool")]
        public static extern int Nrt_Scene_remove([NativeTypeName("NrtScene")] IntPtr scene, [NativeTypeName("NrtSceneNode")] IntPtr nodeToRemove);

        [DllImport("Interop", ExactSpelling = true)]
        [return: NativeTypeName("NrtResult")]
        public static extern int Nrt_Scene_delete([NativeTypeName("NrtScene")] IntPtr scene);
    }
}
