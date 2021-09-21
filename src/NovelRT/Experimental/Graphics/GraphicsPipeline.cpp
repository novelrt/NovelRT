// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Graphics.h>
#include <NovelRT/Experimental/Graphics/GraphicsPipeline.h>

namespace NovelRT::Experimental::Graphics
{
    GraphicsPipeline::GraphicsPipeline(const std::shared_ptr<GraphicsDevice>& device,
                                       std::shared_ptr<GraphicsPipelineSignature> signature,
                                       std::shared_ptr<ShaderProgram> vertexShader,
                                       std::shared_ptr<ShaderProgram> pixelShader) noexcept
        : GraphicsDeviceObject(std::weak_ptr<GraphicsDevice>(device)),
          _signature(signature),
          _vertexShader(vertexShader),
          _pixelShader(pixelShader)
    {
    }

    bool GraphicsPipeline::HasVertexShader() const noexcept
    {
        return _vertexShader != nullptr;
    }

    bool GraphicsPipeline::HasPixelShader() const noexcept
    {
        return _pixelShader != nullptr;
    }

    std::shared_ptr<ShaderProgram> GraphicsPipeline::GetVertexShader() const noexcept
    {
        return _vertexShader;
    }

    std::shared_ptr<ShaderProgram> GraphicsPipeline::GetPixelShader() const noexcept
    {
        return _pixelShader;
    }

    std::shared_ptr<GraphicsPipelineSignature> GraphicsPipeline::GetSignature() const noexcept
    {
        return _signature;
    }
} // namespace NovelRT::Experimental::Graphics