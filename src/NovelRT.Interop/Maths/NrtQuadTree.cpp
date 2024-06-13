// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtQuadTree.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/NovelRT.h>

#include <cmath>
#include <list>

std::list<std::shared_ptr<NovelRT::Maths::QuadTree>> _treeCollection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtQuadTreeHandle Nrt_QuadTree_Create(NrtGeoBounds bounds)
    {
        _treeCollection.push_back(
            std::make_shared<Maths::QuadTree>(*reinterpret_cast<const Maths::GeoBounds*>(&bounds)));
        return reinterpret_cast<NrtQuadTreeHandle>(_treeCollection.back().get());
    }

    NrtResult Nrt_QuadTree_GetParent(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputParentTree)
    {
        if (tree == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputParentTree == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        auto parentTree = treePointer->GetParent();
        *outputParentTree = reinterpret_cast<NrtQuadTreeHandle&>(parentTree);

        return NRT_SUCCESS;
    }

    NrtGeoBounds Nrt_QuadTree_GetBounds(const NrtQuadTreeHandle tree)
    {
        Maths::GeoBounds bounds = Maths::GeoBounds({0, 0}, {0, 0}, 0);
        bounds = reinterpret_cast<Maths::QuadTree*>(tree)->GetBounds();
        return *reinterpret_cast<NrtGeoBounds*>(&bounds);
    }

    NrtResult Nrt_QuadTree_GetPoint(const NrtQuadTreeHandle tree, size_t index, NrtQuadTreePointHandle* outputPoint)
    {
        if (tree == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputPoint == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        auto point = treePointer->GetPoint(index).get();
        *outputPoint = reinterpret_cast<NrtQuadTreePointHandle&>(point);

        return NRT_SUCCESS;
    }

    size_t Nrt_QuadTree_GetPointCount(const NrtQuadTreeHandle tree)
    {
        return reinterpret_cast<Maths::QuadTree*>(tree)->GetPointCount();
    }

    NrtResult Nrt_QuadTree_GetTopLeft(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree)
    {
        if (tree == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputCornerTree == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        *outputCornerTree = reinterpret_cast<NrtQuadTreeHandle>(treePointer->GetTopLeft().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTree_GetTopRight(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree)
    {
        if (tree == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputCornerTree == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        *outputCornerTree = reinterpret_cast<NrtQuadTreeHandle>(treePointer->GetTopRight().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTree_GetBottomLeft(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree)
    {
        if (tree == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputCornerTree == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        *outputCornerTree = reinterpret_cast<NrtQuadTreeHandle>(treePointer->GetBottomLeft().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTree_GetBottomRight(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree)
    {
        if (tree == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputCornerTree == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        *outputCornerTree = reinterpret_cast<NrtQuadTreeHandle>(treePointer->GetBottomRight().get());

        return NRT_SUCCESS;
    }

    NrtBool Nrt_QuadTree_TryInsert(const NrtQuadTreeHandle tree, NrtQuadTreePointHandle point)
    {
        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        return static_cast<int32_t>(
            treePointer->TryInsert(reinterpret_cast<Maths::QuadTreePoint*>(point)->shared_from_this()));
    }

    NrtBool Nrt_QuadTree_TryRemove(const NrtQuadTreeHandle tree, NrtQuadTreePointHandle point)
    {
        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        return static_cast<int32_t>(
            treePointer->TryRemove(reinterpret_cast<Maths::QuadTreePoint*>(point)->shared_from_this()));
    }

    NrtResult Nrt_QuadTree_GetIntersectingPoints(const NrtQuadTreeHandle tree,
                                                 NrtGeoBounds bounds,
                                                 NrtPointVectorHandle* outputResultVector)
    {
        if (tree == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResultVector == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        std::vector<std::shared_ptr<Maths::QuadTreePoint>>* points =
            new std::vector<std::shared_ptr<Maths::QuadTreePoint>>();

        try
        {
            *points = reinterpret_cast<Maths::QuadTree*>(tree)->GetIntersectingPoints(
                *reinterpret_cast<const Maths::GeoBounds*>(&bounds));
        }
        catch (const Exceptions::NotSupportedException)
        {
            Nrt_SetErrMsgIsNotSupportedInternal();
            return NRT_FAILURE_NOT_SUPPORTED;
        }

        *outputResultVector = reinterpret_cast<NrtPointVectorHandle>(points);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_PointVector_Destroy(NrtPointVectorHandle vector)
    {
        if (vector == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(vector);

        return NRT_SUCCESS;
    }

    size_t Nrt_PointVector_GetSize(const NrtPointVectorHandle vector)
    {
        return reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(vector)->size();
    }

    NrtResult Nrt_PointVector_GetPointFromIndex(const NrtPointVectorHandle vector,
                                                size_t index,
                                                NrtQuadTreePointHandle* outputPoint)
    {
        if (vector == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputPoint == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        try
        {
            *outputPoint = reinterpret_cast<NrtQuadTreePointHandle>(
                reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(vector)->at(index).get());
        }
        catch (const std::out_of_range)
        { // todo: handle error message
            Nrt_SetErrMsgIsArgumentOutOfRangeInternal();
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTree_Destroy(NrtQuadTreeHandle tree)
    {
        if (tree == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto ptr = reinterpret_cast<Maths::QuadTree*>(tree)->shared_from_this();

        if (std::find(_treeCollection.begin(), _treeCollection.end(), ptr) == _treeCollection.end())
        {
            Nrt_SetErrMsgIsAlreadyDeletedOrRemovedInternal();
            return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
        }

        _treeCollection.remove(ptr);

        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
