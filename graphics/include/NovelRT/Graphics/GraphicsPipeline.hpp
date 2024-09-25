#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>

namespace NovelRT::Graphics
{
    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsPipeline : public GraphicsDeviceObject<TBackend>
    {
    private:
        std::shared_ptr<GraphicsPipelineSignature<TBackend>> _signature;
        std::shared_ptr<ShaderProgram<TBackend>> _vertexShader;
        std::shared_ptr<ShaderProgram<TBackend>> _pixelShader;

    public:
        GraphicsPipeline(std::shared_ptr<GraphicsDevice<TBackend>> device,
                                           std::shared_ptr<GraphicsPipelineSignature<TBackend>> signature,
                                           std::shared_ptr<ShaderProgram<TBackend>> vertexShader,
                                           std::shared_ptr<ShaderProgram<TBackend>> pixelShader) noexcept
            : GraphicsDeviceObject(device),
              _signature(signature),
              _vertexShader(vertexShader),
              _pixelShader(pixelShader)
        {
        }

        virtual ~GraphicsPipeline() override = default;

        bool HasVertexShader() const noexcept
        {
            return _vertexShader != nullptr;
        }

        bool HasPixelShader() const noexcept
        {
            return _pixelShader != nullptr;
        }

        std::shared_ptr<ShaderProgram<TBackend>> GetVertexShader() const noexcept
        {
            return _vertexShader;
        }

        std::shared_ptr<ShaderProgram<TBackend>> GetPixelShader() const noexcept
        {
            return _pixelShader;
        }

        std::shared_ptr<GraphicsPipelineSignature<TBackend>> GetSignature() const noexcept
        {
            return _signature;
        }
    };
}
