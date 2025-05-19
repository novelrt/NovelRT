#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Vma.hpp>

#include <type_traits>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;
    class VulkanGraphicsResource;

    template<typename TResource>
    class VulkanGraphicsResourceMemoryRegion;

    template<>
    class VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>
    {
    private:
        VulkanGraphicsDevice* _device;
        VulkanGraphicsResource* _owningResource;
        VmaVirtualAllocation _virtualAllocation;
        VmaVirtualAllocationInfo _virtualAllocationInfo;

    public:
        VulkanGraphicsResourceMemoryRegion(VulkanGraphicsDevice* graphicsDevice,
                                           VulkanGraphicsResource* owningResource,
                                           VmaVirtualAllocation virtualAllocation,
                                           VmaVirtualAllocationInfo virtualAllocationInfo);

        virtual ~VulkanGraphicsResourceMemoryRegion();

        [[nodiscard]] VulkanGraphicsResource* GetOwningResource() const noexcept
        {
            return _owningResource;
        }


        [[nodiscard]] VulkanGraphicsDevice* GetDevice() const noexcept
        {
            return _device;
        }

        [[nodiscard]] size_t GetOffset() const noexcept;

        [[nodiscard]] size_t GetSize() const noexcept;

        [[nodiscard]] VmaVirtualAllocation GetVirtualAllocation() const noexcept;

        [[nodiscard]] VmaVirtualAllocationInfo GetVirtualAllocationInfo() const noexcept;
    };

    template<typename TResource>
    class VulkanGraphicsResourceMemoryRegion : public VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>
    {
        static_assert(std::is_base_of_v<VulkanGraphicsResource, TResource>, "TResource must inherit VulkanGraphicsResource");

    public:
        VulkanGraphicsResourceMemoryRegion(VulkanGraphicsDevice* graphicsDevice,
                                           TResource* owningResource,
                                           VmaVirtualAllocation virtualAllocation,
                                           VmaVirtualAllocationInfo virtualAllocationInfo)
            : VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>(graphicsDevice, owningResource, virtualAllocation, virtualAllocationInfo)
        { }

        [[nodiscard]] TResource* GetOwningResource() const noexcept
        {
            return static_cast<TResource*>(VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>::GetOwningResource());
        }

        virtual ~VulkanGraphicsResourceMemoryRegion() override = default;
    };
}
