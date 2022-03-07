// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/Graphics/NrtTextureInfo.h>
#include <NovelRT/Ecs/Ecs.h>

#ifdef __cplusplus
extern "C"
{
    using namespace NovelRT::Ecs::Graphics;
#endif

    NrtBool Nrt_TextureInfo_Equal(NrtTextureInfo lhs, NrtTextureInfo rhs)
    {
        return *reinterpret_cast<const TextureInfo*>(&lhs) == *reinterpret_cast<const TextureInfo*>(&rhs);
    }

#ifdef __cplusplus
}
#endif
