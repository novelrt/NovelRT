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
        std::unique_ptr<BackendPipelineType> _implementation;
        std::shared_ptr<GraphicsPipelineSignature<TBackend>> _signature;
        std::shared_ptr<ShaderProgram<TBackend>> _vertexShader;
        std::shared_ptr<ShaderProgram<TBackend>> _pixelShader;

    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsPipeline<TBackend>> shared_from_this()
        {
            return std::static_pointer_cast<GraphicsPipeline<TBackend>>(GraphicsDeviceObject<TBackend>::shared_from_this());
        }

        GraphicsPipeline(std::unique_ptr<BackendPipelineType> implementation,
                         std::weak_ptr<GraphicsDevice<TBackend>> device,
                         std::shared_ptr<GraphicsPipelineSignature<TBackend>> signature,
                         std::shared_ptr<ShaderProgram<TBackend>> vertexShader,
                         std::shared_ptr<ShaderProgram<TBackend>> pixelShader) noexcept
            : GraphicsDeviceObject<TBackend>(std::move(device))
            , _implementation(std::move(implementation))
            , _signature(std::move(signature))
            , _vertexShader(std::move(vertexShader))
            , _pixelShader(std::move(pixelShader))
        {
        }

        virtual ~GraphicsPipeline() override = default;

        [[nodiscard]] BackendPipelineType* GetImplementation() const noexcept
        {
            return _implementation.get();
        }

        bool HasVertexShader() const noexcept
        {
            return _vertexShader != nullptr;
        }

        bool HasPixelShader() const noexcept
        {
            return _pixelShader != nullptr;
        }

        [[nodiscard]] ShaderProgram<TBackend>* GetVertexShader() const noexcept
        {
            return _vertexShader.get();
        }

        [[nodiscard]] ShaderProgram<TBackend>* GetPixelShader() const noexcept
        {
            return _pixelShader.get();
        }

        [[nodiscard]] GraphicsPipelineSignature<TBackend>* GetSignature() const noexcept
        {
            return _signature.get();
        }

        [[nodiscard]] std::shared_ptr<GraphicsDescriptorSet<TBackend>> CreateDescriptorSet()
        {
            return std::make_shared<GraphicsDescriptorSet<TBackend>>(
                _implementation->CreateDescriptorSet(),
                this->shared_from_this());
        }
    };
}
