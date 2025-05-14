#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsCmdList.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipeline.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderPass.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp>

#include <NovelRT/Graphics/GraphicsAdapter.hpp>
#include <NovelRT/Graphics/GraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/GraphicsContext.hpp>
#include <NovelRT/Graphics/GraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsFence.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/GraphicsPipeline.hpp>
#include <NovelRT/Graphics/GraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/GraphicsProvider.hpp>
#include <NovelRT/Graphics/GraphicsRenderPass.hpp>
#include <NovelRT/Graphics/GraphicsResource.hpp>
#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Graphics/GraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>
#include <NovelRT/Graphics/ShaderProgram.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>

template class NovelRT::Graphics::GraphicsAdapter<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::GraphicsBuffer<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::GraphicsCmdList<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::GraphicsContext<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::GraphicsDescriptorSet<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::GraphicsDevice<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::GraphicsFence<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::GraphicsMemoryAllocator<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::GraphicsPipeline<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::GraphicsPipelineSignature<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::GraphicsProvider<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::GraphicsRenderPass<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
//template class NovelRT::Graphics::GraphicsResource<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
//template class NovelRT::Graphics::GraphicsResourceMemoryRegion<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::GraphicsSurfaceContext<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::GraphicsTexture<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::ShaderProgram<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
