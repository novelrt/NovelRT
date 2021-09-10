// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_VULKANGRAPHICSPRIMITIVE_H
#define NOVELRT_VULKANGRAPHICSPRIMITIVE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsPrimitive final : public GraphicsPrimitive
    {
    private:
        Threading::VolatileState _state;

    public:
        VulkanGraphicsPrimitive(std::shared_ptr<VulkanGraphicsDevice> device,
                                std::shared_ptr<VulkanGraphicsPipeline> pipeline,
                                GraphicsMemoryRegion<GraphicsResource> vertexBufferView,
                                uint32_t vertexBufferStride,
                                GraphicsMemoryRegion<GraphicsResource> indexBufferView,
                                uint32_t indexBufferStride,
                                gsl::span<const GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions = {})
            : GraphicsPrimitive(std::move(device),
                                std::move(pipeline),
                                std::move(vertexBufferView),
                                vertexBufferStride,
                                std::move(indexBufferView),
                                indexBufferStride,
                                inputResourceRegions),
              _state()
        {
            static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsDevice> GetDevice() const
        {
            return std::dynamic_pointer_cast<VulkanGraphicsDevice>(GraphicsPrimitive::GetDevice());
        }

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsPipeline> GetPipeline() const noexcept
        {
            return std::dynamic_pointer_cast<VulkanGraphicsPipeline>(GraphicsPrimitive::GetPipeline());
        }

        //TODO: potential bug later...?
        ~VulkanGraphicsPrimitive() final
        {
            for (auto&& inputResourceRegion : GetInputResourceRegions())
            {
                inputResourceRegion.GetCollection()->Free(inputResourceRegion);
            }
        }
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // NOVELRT_VULKANGRAPHICSPRIMITIVE_H
