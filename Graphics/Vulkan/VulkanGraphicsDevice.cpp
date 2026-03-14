// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>

#include <NovelRT/Graphics/Vulkan/Utilities/Support.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsCmdList.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipeline.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderPass.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderTarget.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp>
#include <NovelRT/Logging/BuiltInLogSections.hpp>
#include <NovelRT/Utilities/Macros.hpp>
#include <NovelRT/Utilities/Span.hpp>
#include <NovelRT/Utilities/Strings.hpp>

#include <algorithm>
#include <set>
#include <vulkan/vulkan_core.h>

namespace NovelRT::Graphics
{
    using VulkanGraphicsAdapter = GraphicsAdapter<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsBuffer = GraphicsBuffer<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsContext = GraphicsContext<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDescriptorSet = GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsFence = GraphicsFence<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsPipeline = GraphicsPipeline<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsPipelineSignature = GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsRenderPass = GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>;
    template<template<typename> typename TResource>
    using VulkanGraphicsResourceMemoryRegion = GraphicsResourceMemoryRegion<TResource, Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsSurfaceContext = GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsSwapchain = GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsTexture = GraphicsTexture<Vulkan::VulkanGraphicsBackend>;
    using VulkanShaderProgram = ShaderProgram<Vulkan::VulkanGraphicsBackend>;

    void VulkanGraphicsDevice::OnGraphicsSurfaceSizeChanged(NovelRT::Maths::GeoVector2F /*newSize*/)
    {
        if (_vulkanSwapchain.HasValue())
        {
            _vulkanSwapchain.Get()->RecreateSwapchain();
        }
    }

    std::vector<std::string> VulkanGraphicsDevice::GetFinalPhysicalDeviceExtensionSet(
        std::vector<std::string> requiredDeviceExtensions,
        std::vector<std::string> optionalDeviceExtensions) const
    {
        uint32_t extensionCount = 0;
        auto adapter = GetAdapter();
        vkEnumerateDeviceExtensionProperties(adapter->GetPhysicalDevice(), nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensionProperties(extensionCount);
        vkEnumerateDeviceExtensionProperties(adapter->GetPhysicalDevice(), nullptr, &extensionCount,
                                             extensionProperties.data());

        _logger.logInfoLine("Found the following available physical device extensions:");

        for (auto&& extensionProperty : extensionProperties)
        {
            _logger.logInfoLine("  Extension Name: " + std::string(extensionProperty.extensionName) +
                                "  Spec Version: " + std::to_string(extensionProperty.specVersion));
        }

        // TODO: EngineConfig was here
        for (auto&& requestedRequiredExt : requiredDeviceExtensions)
        {
            auto result = std::find_if(extensionProperties.begin(), extensionProperties.end(), [&](auto& x)
                                       { return strcmp(requestedRequiredExt.c_str(), x.extensionName) == 0; });

            if (result == extensionProperties.end())
            {
                throw Exceptions::InitialisationFailureException(
                    "The required Vulkan extension " + requestedRequiredExt + " is not available on this device.");
            }
        }

        std::vector<std::string> finalOptionalExtensions{};

        // TODO: EngineConfig was here
        for (auto&& requestedOptionalExt : optionalDeviceExtensions)
        {
            auto result = std::find_if(extensionProperties.begin(), extensionProperties.end(), [&](auto& x)
                                       { return strcmp(requestedOptionalExt.c_str(), x.extensionName) == 0; });

            if (result == extensionProperties.end())
            {
                _logger.logWarningLine("The optional Vulkan extension " + requestedOptionalExt +
                                       " is not available on this device. Vulkan may not behave as you expect.");
                continue;
            }

            finalOptionalExtensions.emplace_back(requestedOptionalExt);
        }

        // TODO: EngineConfig was here
        std::vector<std::string> allExtensions{requiredDeviceExtensions};
        allExtensions.insert(allExtensions.end(), finalOptionalExtensions.begin(), finalOptionalExtensions.end());
        return allExtensions;
    }

    VkDevice VulkanGraphicsDevice::CreateLogicalDevice(std::vector<std::string> requiredDeviceExtensions,
                                                       std::vector<std::string> optionalDeviceExtensions)
    {
        _indicesData = Vulkan::Utilities::FindQueueFamilies(_adapter->GetPhysicalDevice(), _surface);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};
        std::set<uint32_t> uniqueQueueFamilies{_indicesData.graphicsFamily.value(), _indicesData.presentFamily.value()};

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        auto physicalDeviceExtensions =
            GetFinalPhysicalDeviceExtensionSet(requiredDeviceExtensions, optionalDeviceExtensions);
        auto physicalDeviceExtensionPtrs = NovelRT::Utilities::GetStringSpanAsCharPtrVector(physicalDeviceExtensions);

        VkPhysicalDeviceFeatures deviceFeatures{};
        VkPhysicalDeviceNestedCommandBufferFeaturesEXT nestedCommandBuffer{};
        VkPhysicalDeviceMaintenance7FeaturesKHR maintenance7{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(physicalDeviceExtensionPtrs.size());
        createInfo.ppEnabledExtensionNames = physicalDeviceExtensionPtrs.data();

        if (std::find(physicalDeviceExtensions.begin(), physicalDeviceExtensions.end(),
                      VK_KHR_MAINTENANCE_7_EXTENSION_NAME) != physicalDeviceExtensions.end())
        {
            createInfo.pNext = &maintenance7;
            maintenance7.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_7_FEATURES_KHR;
            maintenance7.maintenance7 = true;
        }
        else
        {
            createInfo.pNext = &nestedCommandBuffer;
            nestedCommandBuffer.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_NESTED_COMMAND_BUFFER_FEATURES_EXT;
            nestedCommandBuffer.nestedCommandBuffer = true;
        }

        std::vector<const char*> allValidationLayerPtrs{};

        auto provider = _adapter->GetProvider();
        if (provider->GetDebugModeEnabled())
        {
            auto validationLayers = provider->GetValidationLayers();
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            allValidationLayerPtrs = NovelRT::Utilities::GetStringSpanAsCharPtrVector(validationLayers);
            createInfo.ppEnabledLayerNames = allValidationLayerPtrs.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        VkDevice device = VK_NULL_HANDLE;
        VkResult deviceResult = vkCreateDevice(_adapter->GetPhysicalDevice(), &createInfo, nullptr, &device);

        if (deviceResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to initialise the VkDevice.", deviceResult);
        }

        vkGetDeviceQueue(device, _indicesData.graphicsFamily.value(), 0, &_graphicsQueue);
        vkGetDeviceQueue(device, _indicesData.presentFamily.value(), 0, &_presentQueue);

        _logger.logInfoLine("VkDevice successfully created.");
        return device;
    }

    VulkanGraphicsDevice::GraphicsDevice(std::shared_ptr<VulkanGraphicsAdapter> adapter,
                                         std::shared_ptr<VulkanGraphicsSurfaceContext> surfaceContext,
                                         std::vector<std::string> requiredDeviceExtensions,
                                         std::vector<std::string> optionalDeviceExtensions)
        : _adapter(std::move(adapter)),
          _surfaceContext(std::move(surfaceContext)),
          _presentCompletionFence(
              [this]() { return std::make_shared<VulkanGraphicsFence>(shared_from_this(), /* isSignaled*/ false); }),
          _logger(NovelRT::Logging::CONSOLE_LOG_GFX),
          _surface(_surfaceContext->GetSurfaceContextHandle()),
          _device([this, requiredDeviceExtensions, optionalDeviceExtensions]()
                  { return CreateLogicalDevice(requiredDeviceExtensions, optionalDeviceExtensions); }),
          _graphicsQueue(VK_NULL_HANDLE),
          _presentQueue(VK_NULL_HANDLE),
          _vulkanSwapchain(
              [this]()
              { return std::make_shared<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>>(shared_from_this()); }),
          _indicesData{}
    {
        _logger.logInfoLine("Provided GPU device: " + _adapter->GetName());
        unused(_state.Transition(Threading::VolatileState::Initialised));

        _surfaceContext->GetSurface()->SizeChanged += [this](auto arg) { OnGraphicsSurfaceSizeChanged(arg); };
    }

    VulkanGraphicsDevice::~GraphicsDevice()
    {
        if (_vulkanSwapchain.HasValue())
        {
            _vulkanSwapchain.Reset();
        }

        if (_device.HasValue())
        {
            vkDestroyDevice(GetVulkanDevice(), nullptr);
            _device.Reset();
        }

        _logger.logInfoLine("Vulkan logical device successfully torn down.");
    }

    [[nodiscard]] std::shared_ptr<VulkanGraphicsAdapter> VulkanGraphicsDevice::GetAdapter() const
    {
        return _adapter;
    }

    [[nodiscard]] std::shared_ptr<VulkanGraphicsSwapchain> VulkanGraphicsDevice::GetSwapchain() const
    {
        return _vulkanSwapchain.Get();
    }

    std::shared_ptr<IGraphicsSurface> VulkanGraphicsDevice::GetSurface() const noexcept
    {
        return _surfaceContext->GetSurface();
    }

    std::shared_ptr<VulkanGraphicsSurfaceContext> VulkanGraphicsDevice::GetSurfaceContext() const noexcept
    {
        return _surfaceContext;
    }

    std::shared_ptr<VulkanShaderProgram> VulkanGraphicsDevice::CreateShaderProgram(
        std::string entryPointName,
        ShaderProgramKind kind,
        NovelRT::Utilities::Span<uint8_t> byteData)
    {
        return std::make_shared<VulkanShaderProgram>(shared_from_this(), std::move(entryPointName), kind, byteData);
    }

    std::shared_ptr<VulkanGraphicsPipeline> VulkanGraphicsDevice::CreatePipeline(
        std::shared_ptr<VulkanGraphicsPipelineSignature> signature,
        std::shared_ptr<VulkanShaderProgram> vertexShader,
        std::shared_ptr<VulkanShaderProgram> pixelShader,
        std::shared_ptr<VulkanGraphicsRenderPass> renderPass,
        bool imguiRenderMode)
    {
        return std::make_shared<VulkanGraphicsPipeline>(shared_from_this(), signature, std::move(vertexShader),
                                                        std::move(pixelShader), renderPass, imguiRenderMode);
    }

    std::shared_ptr<VulkanGraphicsPipelineSignature> VulkanGraphicsDevice::CreatePipelineSignature(
        GraphicsPipelineBlendFactor srcBlendFactor,
        GraphicsPipelineBlendFactor dstBlendFactor,
        NovelRT::Utilities::Span<GraphicsPipelineInput> inputs,
        NovelRT::Utilities::Span<GraphicsPipelineResource> resources,
        NovelRT::Utilities::Span<GraphicsPushConstantRange> pushConstantRanges)
    {
        return std::make_shared<VulkanGraphicsPipelineSignature>(shared_from_this(), srcBlendFactor, dstBlendFactor,
                                                                 inputs, resources, pushConstantRanges);
    }

    std::shared_ptr<VulkanGraphicsContext> VulkanGraphicsDevice::CreateGraphicsContext()
    {
        return std::make_shared<VulkanGraphicsContext>(shared_from_this());
    }

    std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>> VulkanGraphicsDevice::BeginFrame()
    {
        auto swapchain = _vulkanSwapchain.Get();
        auto image = swapchain->AcquireNextImage();

        while (image == nullptr)
        {
            swapchain->RecreateSwapchain();
            image = swapchain->AcquireNextImage();
        }

        return image;
    }

    void VulkanGraphicsDevice::QueueSubmit(std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>> cmdList)
    {
        std::vector<VkCommandBuffer> buffers;
        buffers.emplace_back(cmdList->GetVkCommandBuffer());

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = static_cast<uint32_t>(buffers.size());
        submitInfo.pCommandBuffers = buffers.data();

        // TODO: submit to the correct queue if it's just transfers somehow?
        const VkResult queueSubmitResult = vkQueueSubmit(GetVulkanGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
        //
        if (queueSubmitResult != VK_SUCCESS)
        {
            throw std::runtime_error("vkQueueSubmit failed! Reason: " + std::to_string(queueSubmitResult));
        }
    }

    void VulkanGraphicsDevice::PresentFrame()
    {
        auto swapchain = _vulkanSwapchain.Get();

        if (!swapchain->Present())
        {
            swapchain->RecreateSwapchain();
        }
    }

    void VulkanGraphicsDevice::WaitForIdle()
    {
        const VkResult waitForIdleResult = vkDeviceWaitIdle(GetVulkanDevice());

        if (waitForIdleResult != VK_SUCCESS)
        {
            throw std::runtime_error("The VkDevice did not idle correctly! Reason: " +
                                     std::to_string(waitForIdleResult));
        }
    }

    VkQueue VulkanGraphicsDevice::GetVulkanPresentQueue() const noexcept
    {
        return _presentQueue;
    }

    VkQueue VulkanGraphicsDevice::GetVulkanGraphicsQueue() const noexcept
    {
        return _graphicsQueue;
    }

    VkDevice VulkanGraphicsDevice::GetVulkanDevice() const
    {
        return _device.Get();
    }

    const Vulkan::QueueFamilyIndices& VulkanGraphicsDevice::GetIndicesData() const noexcept
    {
        return _indicesData;
    }

    std::shared_ptr<VulkanGraphicsFence> VulkanGraphicsDevice::GetPresentCompletionFence() const
    {
        return _presentCompletionFence.Get();
    }

    std::shared_ptr<VulkanGraphicsRenderPass> VulkanGraphicsDevice::CreateRenderPass(
        const GraphicsRenderPassDescription& description)
    {
        return std::make_shared<VulkanGraphicsRenderPass>(shared_from_this(), description);
    }
}
