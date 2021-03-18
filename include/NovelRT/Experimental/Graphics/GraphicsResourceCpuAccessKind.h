// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICSRESOURCECPUACCESSKIND_H
#define NOVELRT_EXPERIMENTAL_GRAPHICSRESOURCECPUACCESSKIND_H

#include <cstdint>

namespace NovelRT::Experimental::Graphics
{
    enum class GraphicsResourceCpuAccessKind : uint32_t
    {
        None = 1 << 0,
        GpuOnly = None,
        Read = 1 << 1,
        GpuToCpu = Read,
        Write = 1 << 2,
        CpuToGpu = Write,
        ReadWrite = Read | Write,
        GpuToCpuToGpu = ReadWrite
    };
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICSRESOURCECPUACCESSKIND_H
