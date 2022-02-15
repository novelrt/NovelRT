// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/Graphics/NrtVertexInfo.h>
#include <NovelRT/Ecs/Ecs.h>

#ifdef __cplusplus
extern "C"
{
    using namespace NovelRT::Ecs::Graphics;
#endif

    NrtBool Nrt_VertexInfo_Equals_Operator(NrtVertexInfo lhs, NrtVertexInfo rhs)
    {
        return *reinterpret_cast<const VertexInfo*>(&lhs) == *reinterpret_cast<const VertexInfo*>(&rhs);
    }

#ifdef __cplusplus
}
#endif