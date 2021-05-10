// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Graphics.h>

namespace NovelRT::Experimental::Graphics
{

    GraphicsPipeline::GraphicsPipeline(std::shared_ptr<ILLGraphicsDevice> device,
                                       std::shared_ptr<GraphicsPipelineSignature> signature,
                                       std::shared_ptr<ShaderProgram> vertexShader,
                                       std::shared_ptr<ShaderProgram> pixelShader) noexcept
        : GraphicsDeviceObject(device), _signature(signature), _vertexShader(vertexShader), _pixelShader(pixelShader)
    {
    }
} // namespace NovelRT::Experimental::Graphics