// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtQuadTreePoint.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/NovelRT.h>

#include <algorithm>
#include <list>

std::list<std::shared_ptr<NovelRT::Maths::QuadTreePoint>> _pointCollection; // TODO: Why a list? - Ruby

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtQuadTreePointHandle Nrt_QuadTreePoint_Create(NrtGeoVector2F position)
    {
        _pointCollection.push_back(
            std::make_shared<Maths::QuadTreePoint>(reinterpret_cast<Maths::GeoVector2F&>(position)));
        return reinterpret_cast<NrtQuadTreePointHandle>(_pointCollection.back().get());
    }

    NrtQuadTreePointHandle Nrt_QuadTreePoint_CreateFromFloat(float x, float y)
    {
        _pointCollection.push_back(std::make_shared<Maths::QuadTreePoint>(Maths::GeoVector2F(x, y)));
        return reinterpret_cast<NrtQuadTreePointHandle>(_pointCollection.back().get());
    }

    NrtGeoVector2F Nrt_QuadTreePoint_GetPosition(const NrtQuadTreePointHandle point)
    {
        Maths::GeoVector2F pos = reinterpret_cast<const std::shared_ptr<Maths::QuadTreePoint>&>(point)->GetPosition();
        NrtGeoVector2F returnValue = reinterpret_cast<const NrtGeoVector2F&>(pos);
        return returnValue;
    }

    NrtResult Nrt_QuadTreePoint_Destroy(NrtQuadTreePointHandle point)
    {
        if (point == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto ptr = reinterpret_cast<Maths::QuadTreePoint*>(point)->shared_from_this();

        if (std::find(_pointCollection.begin(), _pointCollection.end(), ptr) == _pointCollection.end())
        { // TODO: This may prove to be a bottleneck later
            Nrt_SetErrMsgIsAlreadyDeletedOrRemovedInternal();
            return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
        }

        _pointCollection.remove(reinterpret_cast<Maths::QuadTreePoint*>(point)->shared_from_this());
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
