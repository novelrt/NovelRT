#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsDescriptorSet.hpp>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsPipeline : public GraphicsDeviceObject<TBackend>
    {
    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsPipeline<TBackend>> shared_from_this();

        GraphicsPipeline() = delete;
        virtual ~GraphicsPipeline() override = default;

        bool HasVertexShader() const noexcept;
        bool HasPixelShader() const noexcept;

        [[nodiscard]] std::shared_ptr<ShaderProgram<TBackend>> GetVertexShader() const noexcept;
        [[nodiscard]] std::shared_ptr<ShaderProgram<TBackend>> GetPixelShader() const noexcept;
        [[nodiscard]] std::shared_ptr<GraphicsPipelineSignature<TBackend>> GetSignature() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsDescriptorSet<TBackend>> CreateDescriptorSet();
    };
}
