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


namespace NovelRT::Graphics
{
    template<>
    struct GraphicsBackendTraits<Vulkan::VulkanGraphicsBackend>
    {
        using ProviderType = Vulkan::VulkanGraphicsProvider;
        using AdapterType = Vulkan::VulkanGraphicsAdapter;
        using DeviceType = Vulkan::VulkanGraphicsDevice;
        using SurfaceContextType = Vulkan::VulkanGraphicsSurfaceContext;
        using ContextType = Vulkan::VulkanGraphicsSurfaceContext;
        using ResourceType = Vulkan::VulkanGraphicsResource;
        using ResourceMemoryRegionType = Vulkan::VulkanGraphicsResourceMemoryRegion; 
        using MemoryAllocatorType = Vulkan::VulkanGraphicsMemoryAllocator;
        using BufferType = Vulkan::VulkanGraphicsBuffer;
        using TextureType = Vulkan::VulkanGraphicsTexture;
    };
}