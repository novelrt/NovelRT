#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/NotSupportedException.hpp>
#include <NovelRT/Graphics/GraphicsPipelineVisibility.hpp>

#include <algorithm>
#include <array>
#include <utility>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan::Utilities
{
    [[nodiscard]] inline VkPipelineStageFlags GetVulkanPipelineStageFlags(
        Graphics::GraphicsPipelineVisibility stageFlag)
    {
        using Stage = Graphics::GraphicsPipelineVisibility;

        static constexpr auto stageFlags = std::to_array<std::pair<Stage, VkPipelineStageFlags>>({
            {Stage::None, 0},
            {Stage::TopOfPipe, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT},
            {Stage::DrawIndirect, VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT},
            {Stage::VertexInput, VK_PIPELINE_STAGE_VERTEX_INPUT_BIT},
            {Stage::VertexShader, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT},
            {Stage::TesselationControlShader, VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT},
            {Stage::TesselationEvaluationShader, VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT},
            {Stage::GeometryShader, VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT},
            {Stage::FragmentShader, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT},
            {Stage::EarlyFragmentTests, VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT},
            {Stage::LateFragmentTests, VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT},
            {Stage::ColorAttachmentOutput, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT},
            {Stage::ComputeShader, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT},
            {Stage::Transfer, VK_PIPELINE_STAGE_TRANSFER_BIT},
            {Stage::BottomOfPipe, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT},
            {Stage::Host, VK_PIPELINE_STAGE_HOST_BIT},
            {Stage::AllGraphics, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT},
            {Stage::AllCommands, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT},
        });

        static_assert(std::ranges::all_of(stageFlags,
                                          [](const auto& flag)
                                          { return static_cast<VkPipelineStageFlags>(flag.first) == flag.second; }),
                      "Graphics pipeline stages must match Vulkan pipeline stage flags.");

        if (stageFlag == Stage::None)
        {
            throw Exceptions::NotSupportedException("Vulkan pipeline barrier stage flags cannot be None.");
        }

        return static_cast<VkPipelineStageFlags>(stageFlag);
    }
}
