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
        GraphicsTextureAddressMode addressMode = GraphicsTextureAddressMode::Repeat;
        GraphicsTextureKind textureKind = GraphicsTextureKind::TwoDimensional;
        GraphicsResourceAccess cpuAccessKind = GraphicsResourceAccess::None;
        GraphicsResourceAccess gpuAccessKind = GraphicsResourceAccess::None;
        uint32_t width = 0;
        uint32_t height = 0;
        uint32_t depth = 0;
        GraphicsMemoryRegionAllocationFlags allocationFlags = GraphicsMemoryRegionAllocationFlags::None;
        TexelFormat texelFormat = TexelFormat::R8G8B8A8_UNORM;
    };
}