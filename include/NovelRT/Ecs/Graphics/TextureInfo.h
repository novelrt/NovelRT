// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_GRAPHICS_TEXTUREINFO_H
#define NOVELRT_ECS_GRAPHICS_TEXTUREINFO_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Graphics
{
    struct TextureInfo
    {
        NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource> gpuTextureRegion = {};
        std::string textureName;
        uint32_t width = 0;
        uint32_t height = 0;
        NovelRT::Core::Atom ecsId = 0;
        std::vector<uint8_t> textureData;
        uuids::uuid textureAssetDataHandle;

        bool operator==(const TextureInfo& other) const noexcept
        {
            return (gpuTextureRegion == other.gpuTextureRegion) && (textureName == other.textureName) &&
                   (ecsId == other.ecsId) && (textureAssetDataHandle == other.textureAssetDataHandle);
        }
    };
}

#endif // NOVELRT_ECS_GRAPHICS_TEXTUREINFO_H
