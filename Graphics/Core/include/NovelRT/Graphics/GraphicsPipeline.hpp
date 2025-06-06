#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsDescriptorSet.hpp>

namespace NovelRT::Graphics
{
    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsPipeline : public GraphicsDeviceObject<TBackend>
    {
    public:
        using BackendPipelineType = typename GraphicsBackendTraits<TBackend>::PipelineType;

    private:
        std::shared_ptr<BackendPipelineType> _implementation;
        std::shared_ptr<GraphicsPipelineSignature<TBackend>> _signature;
        std::shared_ptr<ShaderProgram<TBackend>> _vertexShader;
        std::shared_ptr<ShaderProgram<TBackend>> _pixelShader;

    public:
        GraphicsPipeline(std::shared_ptr<BackendPipelineType> implementation,
                         std::shared_ptr<GraphicsDevice<TBackend>> device,
                         std::shared_ptr<GraphicsPipelineSignature<TBackend>> signature,
                         std::shared_ptr<ShaderProgram<TBackend>> vertexShader,
                         std::shared_ptr<ShaderProgram<TBackend>> pixelShader) noexcept
            : GraphicsDeviceObject<TBackend>(device),
              _implementation(implementation),
              _signature(signature),
              _vertexShader(vertexShader),
              _pixelShader(pixelShader)
        {
        }

        virtual ~GraphicsPipeline() override = default;

        [[nodiscard]] std::shared_ptr<BackendPipelineType> GetImplementation() const noexcept
        {
            return _implementation;
        }

        bool HasVertexShader() const noexcept
        {
            return _vertexShader != nullptr;
        }

        bool HasPixelShader() const noexcept
        {
            return _pixelShader != nullptr;
        }

        [[nodiscard]] std::shared_ptr<ShaderProgram<TBackend>> GetVertexShader() const noexcept
        {
            return _vertexShader;
        }

        [[nodiscard]] std::shared_ptr<ShaderProgram<TBackend>> GetPixelShader() const noexcept
        {
            return _pixelShader;
        }

        [[nodiscard]] std::shared_ptr<GraphicsPipelineSignature<TBackend>> GetSignature() const noexcept
        {
            return _signature;
        }

        [[nodiscard]] std::shared_ptr<GraphicsDescriptorSet<TBackend>> CreateDescriptorSet()
        {
            return std::make_shared<GraphicsDescriptorSet<TBackend>>(_implementation->CreateDescriptorSet(), std::static_pointer_cast<GraphicsPipeline<TBackend>>(GraphicsDeviceObject<TBackend>::shared_from_this()));
        }
    };
}
