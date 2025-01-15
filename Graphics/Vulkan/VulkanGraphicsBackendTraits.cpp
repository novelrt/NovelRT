#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/GraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>

template class NovelRT::Graphics::GraphicsProvider<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::GraphicsAdapter<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
template class NovelRT::Graphics::GraphicsSurfaceContext<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
