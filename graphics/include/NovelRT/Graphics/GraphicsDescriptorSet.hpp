#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Utilities/Misc.h>
#include <memory>
#include <vector>

namespace NovelRT::Graphics
{
    class GraphicsBuffer;
    class GraphicsPipeline;
    class GraphicsTexture;

    class GraphicsDescriptorSet
    {
    private:
        std::shared_ptr<GraphicsPipeline> _pipeline;

    public:
        explicit GraphicsDescriptorSet(std::shared_ptr<GraphicsPipeline> targetPipeline) noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsPipeline> GetPipeline() const noexcept;

        void AddBuffers(NovelRT::Utilities::Misc::Span<const std::shared_ptr<GraphicsBuffer>> buffers);        

        void AddTextures(NovelRT::Utilities::Misc::Span<const std::shared_ptr<GraphicsTexture>> textures);

        virtual ~GraphicsDescriptorSet() = default;
    };
}