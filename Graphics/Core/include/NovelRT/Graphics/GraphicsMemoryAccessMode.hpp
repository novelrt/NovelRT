#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>

namespace NovelRT::Graphics
{
    enum class GraphicsMemoryAccessMode : uint32_t
    {
        None = 0,
        IndirectCommandRead = 1 << 0,
        IndexRead = 1 << 1,
        VertexAttributeRead = 1 << 2,
        UniformRead = 1 << 3,
        InputAttachmentRead = 1 << 4,
        ShaderRead = 1 << 5,
        ShaderWrite = 1 << 6,
        ColorAttachmentRead = 1 << 7,
        ColorAttachmentWrite = 1 << 8,
        DepthStencilAttachmentRead = 1 << 9,
        DepthStencilAttachmentWrite = 1 << 10,
        TransferRead = 1 << 11,
        TransferWrite = 1 << 12,
        HostRead = 1 << 13,
        HostWrite = 1 << 14,
        MemoryRead = 1 << 15,
        MemoryWrite = 1 << 16,
        All = IndirectCommandRead | IndexRead | VertexAttributeRead | UniformRead | InputAttachmentRead | ShaderRead |
              ShaderWrite | ColorAttachmentRead | ColorAttachmentWrite | DepthStencilAttachmentRead |
              DepthStencilAttachmentWrite | TransferRead | TransferWrite | HostRead | HostWrite | MemoryRead |
              MemoryWrite
    };
}
