#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/GraphicsBufferKind.hpp>
#include <NovelRT/Graphics/GraphicsMemoryRegionAllocationFlags.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <cstdint>


namespace NovelRT::Graphics
{
    struct GraphicsBufferCreateInfo
    {
        GraphicsBufferKind bufferKind;
        GraphicsResourceAccess cpuAccessKind;
        GraphicsResourceAccess gpuAccessKind;
        size_t size;
        GraphicsMemoryRegionAllocationFlags allocationFlags;
    };
}