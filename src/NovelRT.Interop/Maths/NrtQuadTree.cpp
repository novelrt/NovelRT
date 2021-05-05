// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtQuadTree.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.h>

#include <cmath>
#include <list>

std::list<std::shared_ptr<NovelRT::Maths::QuadTree>> _treeCollection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtQuadTreeHandle Nrt_QuadTree_create(NrtGeoBounds bounds)
    {
        _treeCollection.push_back(
            std::make_shared<Maths::QuadTree>(*reinterpret_cast<const Maths::GeoBounds*>(&bounds)));
        return reinterpret_cast<NrtQuadTreeHandle>(_treeCollection.back().get());
    }

    NrtResult Nrt_QuadTree_getParent(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputParentTree)
    {
        if (tree == nullptr || outputParentTree == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        auto parentTree = treePointer->getParent();
        *outputParentTree = reinterpret_cast<NrtQuadTreeHandle&>(parentTree);

        return NRT_SUCCESS;
    }

    NrtGeoBounds Nrt_QuadTree_getBounds(const NrtQuadTreeHandle tree)
    {
        Maths::GeoBounds bounds = Maths::GeoBounds({0, 0}, {0, 0}, 0);
        bounds = reinterpret_cast<Maths::QuadTree*>(tree)->getBounds();
        return *reinterpret_cast<NrtGeoBounds*>(&bounds);
    }

    NrtResult Nrt_QuadTree_getPoint(const NrtQuadTreeHandle tree, size_t index, NrtQuadTreePointHandle* outputPoint)
    {
        if (tree == nullptr || outputPoint == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        auto point = treePointer->getPoint(index).get();
        *outputPoint = reinterpret_cast<NrtQuadTreePointHandle&>(point);

        return NRT_SUCCESS;
    }

    size_t Nrt_QuadTree_getPointCount(const NrtQuadTreeHandle tree)
    {
        return reinterpret_cast<Maths::QuadTree*>(tree)->getPointCount();
    }

    NrtResult Nrt_QuadTree_getTopLeft(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree)
    {
        if (tree == nullptr || outputCornerTree == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        *outputCornerTree = reinterpret_cast<NrtQuadTreeHandle>(treePointer->getTopLeft().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTree_getTopRight(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree)
    {
        if (tree == nullptr || outputCornerTree == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        *outputCornerTree = reinterpret_cast<NrtQuadTreeHandle>(treePointer->getTopRight().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTree_getBottomLeft(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree)
    {
        if (tree == nullptr || outputCornerTree == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        *outputCornerTree = reinterpret_cast<NrtQuadTreeHandle>(treePointer->getBottomLeft().get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTree_getBottomRight(const NrtQuadTreeHandle tree, NrtQuadTreeHandle* outputCornerTree)
    {
        if (tree == nullptr || outputCornerTree == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        *outputCornerTree = reinterpret_cast<NrtQuadTreeHandle>(treePointer->getBottomRight().get());

        return NRT_SUCCESS;
    }

    NrtBool Nrt_QuadTree_tryInsert(const NrtQuadTreeHandle tree, NrtQuadTreePointHandle point)
    {
        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        return static_cast<int32_t>(
            treePointer->tryInsert(reinterpret_cast<Maths::QuadTreePoint*>(point)->shared_from_this()));
    }

    NrtBool Nrt_QuadTree_tryRemove(const NrtQuadTreeHandle tree, NrtQuadTreePointHandle point)
    {
        auto treePointer = reinterpret_cast<Maths::QuadTree*>(tree);
        return static_cast<int32_t>(
            treePointer->tryRemove(reinterpret_cast<Maths::QuadTreePoint*>(point)->shared_from_this()));
    }

    NrtResult Nrt_QuadTree_getIntersectingPoints(const NrtQuadTreeHandle tree,
                                                 NrtGeoBounds bounds,
                                                 NrtPointVectorHandle* outputResultVector)
    {
        if (tree == nullptr || outputResultVector == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        std::vector<std::shared_ptr<Maths::QuadTreePoint>>* points =
            new std::vector<std::shared_ptr<Maths::QuadTreePoint>>();

        try
        {
            *points = reinterpret_cast<Maths::QuadTree*>(tree)->getIntersectingPoints(
                *reinterpret_cast<const Maths::GeoBounds*>(&bounds));
        }
        catch (const Exceptions::NotSupportedException)
        {
            Nrt_setErrMsgIsNotSupportedInternal();
            return NRT_FAILURE_NOT_SUPPORTED;
        }

        *outputResultVector = reinterpret_cast<NrtPointVectorHandle>(points);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_PointVector_delete(NrtPointVectorHandle vector)
    {
        if (vector == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        delete reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(vector);

        return NRT_SUCCESS;
    }

    size_t Nrt_PointVector_getSize(const NrtPointVectorHandle vector)
    {
        return reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(vector)->size();
    }

    NrtResult Nrt_PointVector_getPointFromIndex(const NrtPointVectorHandle vector,
                                                size_t index,
                                                NrtQuadTreePointHandle* outputPoint)
    {
        if (vector == nullptr || outputPoint == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        try
        {
            *outputPoint = reinterpret_cast<NrtQuadTreePointHandle>(
                reinterpret_cast<std::vector<std::shared_ptr<Maths::QuadTreePoint>>*>(vector)->at(index).get());
        }
        catch (const std::out_of_range)
        { // todo: handle error message
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_QuadTree_delete(NrtQuadTreeHandle tree)
    {
        if (tree == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto ptr = reinterpret_cast<Maths::QuadTree*>(tree)->shared_from_this();

        if (std::find(_treeCollection.begin(), _treeCollection.end(), ptr) == _treeCollection.end())
        {
            Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
            return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
        }

        _treeCollection.remove(ptr);

        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
