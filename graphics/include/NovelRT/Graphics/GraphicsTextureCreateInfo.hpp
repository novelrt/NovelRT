#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsMemoryRegionAllocationFlags.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/GraphicsTextureAddressMode.hpp>
#include <NovelRT/Graphics/GraphicsTextureKind.hpp>
#include <NovelRT/Graphics/TexelFormat.hpp>
#include <cstdint>

namespace NovelRT::Graphics
{
    struct GraphicsTextureCreateInfo
    {
        GraphicsTextureAddressMode addressMode;
        GraphicsTextureKind textureKind;
        GraphicsResourceAccess cpuAccessKind;
        GraphicsResourceAccess gpuAccessKind;
        uint32_t width;
        uint32_t height;
        uint32_t depth;
        GraphicsMemoryRegionAllocationFlags allocationFlags;
        TexelFormat texelFormat;
    };
}