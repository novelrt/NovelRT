// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/SceneGraph/NrtScene.h>
#include <NovelRT/NovelRT.h>

using namespace NovelRT;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtSceneHandle Nrt_Scene_create()
    {
        return reinterpret_cast<NrtSceneHandle>(new SceneGraph::Scene());
    }

    NrtResult Nrt_Scene_getNodes(NrtSceneHandle scene, NrtSceneNodeSetHandle* outputSet)
    {
        if (scene == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputSet == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppScene = reinterpret_cast<SceneGraph::Scene*>(&scene);
        std::set<std::shared_ptr<SceneGraph::SceneNode>>* nodeSet =
            new std::set<std::shared_ptr<SceneGraph::SceneNode>>();
        *nodeSet = cppScene->getNodes();

        *outputSet = reinterpret_cast<NrtSceneNodeSetHandle>(nodeSet);
        return NRT_SUCCESS;
    }

    NrtBool Nrt_Scene_insert(NrtSceneHandle scene, NrtSceneNodeHandle nodeToInsert)
    {
        auto cppScene = reinterpret_cast<SceneGraph::Scene*>(&scene);
        auto cppNode = reinterpret_cast<SceneGraph::SceneNode*>(nodeToInsert)->shared_from_this();
        return static_cast<int32_t>(cppScene->insert(cppNode));
    }

    NrtBool Nrt_Scene_remove(NrtSceneHandle scene, NrtSceneNodeHandle nodeToRemove)
    {
        auto cppScene = reinterpret_cast<SceneGraph::Scene*>(&scene);
        auto cppNode = reinterpret_cast<SceneGraph::SceneNode*>(nodeToRemove)->shared_from_this();
        return static_cast<int32_t>(cppScene->remove(cppNode));
    }

    NrtResult Nrt_Scene_Destroy(NrtSceneHandle scene)
    {
        if (scene == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto cppScene = reinterpret_cast<SceneGraph::Scene*>(&scene);
        try
        {
            delete cppScene; // TODO: This can throw?????
        }
        catch (const std::exception& ex)
        {
            const char* message = ex.what();
            char* target = new char[strlen(message) + 1];

            // strcpy should be "safe" there since we called strlen earlier
            strcpy(target, message);

            Nrt_SetErrMsgCustomInternal(target);
            return NRT_FAILURE_UNKNOWN;
        }

        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
