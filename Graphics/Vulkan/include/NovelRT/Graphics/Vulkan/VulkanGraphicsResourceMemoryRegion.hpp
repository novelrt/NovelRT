#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Vma.hpp>

#include <type_traits>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template<>
    class GraphicsResourceMemoryRegion<GraphicsResource, Vulkan::VulkanGraphicsBackend>
        : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
    private:
        std::weak_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;
        std::shared_ptr<GraphicsResource<Vulkan::VulkanGraphicsBackend>> _owningResource;
        VmaVirtualAllocation _virtualAllocation;
        VmaVirtualAllocationInfo _virtualAllocationInfo;

    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, Vulkan::VulkanGraphicsBackend>> shared_from_this();
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<const GraphicsResourceMemoryRegion<GraphicsResource, Vulkan::VulkanGraphicsBackend>> shared_from_this() const;

        GraphicsResourceMemoryRegion(
            std::weak_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> graphicsDevice,
            std::shared_ptr<GraphicsResource<Vulkan::VulkanGraphicsBackend>> owningResource,
            VmaVirtualAllocation virtualAllocation,
            VmaVirtualAllocationInfo virtualAllocationInfo);

        virtual ~GraphicsResourceMemoryRegion();

        [[nodiscard]] std::weak_ptr<GraphicsResource<Vulkan::VulkanGraphicsBackend>> GetOwningResource() const noexcept;

        [[nodiscard]] size_t GetOffset() const noexcept;
        [[nodiscard]] size_t GetSize() const noexcept;

        [[nodiscard]] Utilities::Span<uint8_t> MapBytes();

        [[nodiscard]] Utilities::Span<const uint8_t> MapBytesForRead();

        void UnmapBytes();

        void UnmapBytesAndWrite();

        template<typename T> [[nodiscard]] Utilities::Span<T> Map();

        template<typename T> [[nodiscard]] Utilities::Span<const T> MapForRead();

        [[nodiscard]] VmaVirtualAllocation GetVirtualAllocation() const noexcept;
        [[nodiscard]] VmaVirtualAllocationInfo GetVirtualAllocationInfo() const noexcept;
    };

    template<template <typename> typename TResource>
    class GraphicsResourceMemoryRegion<TResource, Vulkan::VulkanGraphicsBackend>
        : public GraphicsResourceMemoryRegion<GraphicsResource, Vulkan::VulkanGraphicsBackend>
    {
        static_assert(std::is_base_of_v<GraphicsResource<Vulkan::VulkanGraphicsBackend>, TResource<Vulkan::VulkanGraphicsBackend>>, "TResource must inherit VulkanGraphicsResource");

    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsResourceMemoryRegion<TResource, Vulkan::VulkanGraphicsBackend>> shared_from_this()
        {
            return std::static_pointer_cast<GraphicsResourceMemoryRegion<TResource, Vulkan::VulkanGraphicsBackend>>(GraphicsDeviceObject::shared_from_this());
        }

        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<const GraphicsResourceMemoryRegion<TResource, Vulkan::VulkanGraphicsBackend>> shared_from_this() const
        {
            return std::static_pointer_cast<const GraphicsResourceMemoryRegion<TResource, Vulkan::VulkanGraphicsBackend>>(GraphicsDeviceObject::shared_from_this());
        }

        GraphicsResourceMemoryRegion(
            std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> graphicsDevice,
            std::shared_ptr<TResource<Vulkan::VulkanGraphicsBackend>> owningResource,
            VmaVirtualAllocation virtualAllocation,
            VmaVirtualAllocationInfo virtualAllocationInfo)
            : GraphicsResourceMemoryRegion<GraphicsResource, Vulkan::VulkanGraphicsBackend>(
                graphicsDevice, owningResource, virtualAllocation, virtualAllocationInfo)
        { }

        virtual ~GraphicsResourceMemoryRegion() override = default;

        [[nodiscard]] std::weak_ptr<TResource<Vulkan::VulkanGraphicsBackend>> GetOwningResource() const noexcept
        {
            auto original = GraphicsResourceMemoryRegion<GraphicsResource, Vulkan::VulkanGraphicsBackend>::GetOwningResource();
            return std::static_pointer_cast<TResource<Vulkan::VulkanGraphicsBackend>>(std::shared_ptr<GraphicsResource<Vulkan::VulkanGraphicsBackend>>(original));
        }
    };
}
