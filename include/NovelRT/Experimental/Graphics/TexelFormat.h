// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_TEXELFORMAT_H
#define NOVELRT_TEXELFORMAT_H

namespace NovelRT::Experimental::Graphics
{
    enum class TexelFormat : uint32_t
    {
        R8G8B8A8_UNORM,
        R16_SINT,
        R16G16UINT,
    };
}

#endif // NOVELRT_TEXELFORMAT_H
