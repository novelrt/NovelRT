// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/GraphicsPipeline.hpp>
#include <NovelRT/Graphics/GraphicsPipelineSignature.hpp>

namespace NovelRT::Graphics
{
    GraphicsDescriptorSet::GraphicsDescriptorSet(std::shared_ptr<GraphicsPipeline> targetPipeline) noexcept
        : _pipeline(targetPipeline)
    {
    }

    std::shared_ptr<GraphicsPipeline> GraphicsDescriptorSet::GetPipeline() const noexcept
    {
        return _pipeline;
    }

    void GraphicsDescriptorSet::AddBuffers(NovelRT::Utilities::Misc::Span<const std::shared_ptr<GraphicsBuffer>> buffers)
    {
        auto signature = GetPipeline()->GetSignature();

        signature->GetInputs()
    }
}