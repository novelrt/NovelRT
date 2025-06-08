#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Utilities/Operators.hpp>

#include <cstdint>

namespace NovelRT::Graphics
{
    enum class GraphicsPipelineVisibility : uint32_t
    {
        None = 0,
        TopOfPipe = 1 << 0,
        DrawIndirect = 1 << 1,
        VertexInput = 1 << 2,
        VertexShader = 1 << 3,
        TesselationControlShader = 1 << 4,
        TesselationEvaluationShader = 1 << 5,
        GeometryShader = 1 << 6,
        FragmentShader = 1 << 7,
        EarlyFragmentTests = 1 << 8,
        LateFragmentTests = 1 << 9,
        ColorAttachmentOutput = 1 << 10,
        ComputeShader = 1 << 11,
        Transfer = 1 << 12,
        BottomOfPipe = 1 << 13,
        Host = 1 << 14,
        AllGraphics = DrawIndirect | VertexInput | VertexShader | TesselationControlShader |
                      TesselationEvaluationShader | GeometryShader | FragmentShader | EarlyFragmentTests |
                      LateFragmentTests | ColorAttachmentOutput,
        AllCommands = AllGraphics | TopOfPipe | Transfer | BottomOfPipe | Host,
        All = AllCommands
    };
}
