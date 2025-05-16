#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBufferKind.hpp>
#include <NovelRT/Graphics/GraphicsMemoryRegionAllocationFlags.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>

#include <cstdint>


namespace NovelRT::Graphics
{
    struct GraphicsBufferCreateInfo
    {
        GraphicsBufferKind bufferKind = GraphicsBufferKind::Default;
        GraphicsResourceAccess cpuAccessKind = GraphicsResourceAccess::None;
        GraphicsResourceAccess gpuAccessKind = GraphicsResourceAccess::None;
        size_t size = 0;
        GraphicsMemoryRegionAllocationFlags allocationFlags = GraphicsMemoryRegionAllocationFlags::None;
    };
}
