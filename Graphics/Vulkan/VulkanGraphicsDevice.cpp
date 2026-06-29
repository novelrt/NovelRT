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
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSemaphore.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp>
#include <NovelRT/Logging/BuiltInLogSections.hpp>
#include <NovelRT/Utilities/Macros.hpp>
#include <NovelRT/Utilities/Span.hpp>
#include <NovelRT/Utilities/Strings.hpp>

#include <algorithm>
#include <ranges>
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
    using VulkanGraphicsSemaphore = GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>;
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
        std::vector<FeatureProviderExtensionGroup> requiredDeviceExtensions,
        std::vector<FeatureProviderExtensionGroup> optionalDeviceExtensions) const
    {
        uint32_t extensionCount = 0;
        auto adapter = GetAdapter();
        vkEnumerateDeviceExtensionProperties(adapter->GetPhysicalDevice(), nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensionProperties(extensionCount);
        vkEnumerateDeviceExtensionProperties(adapter->GetPhysicalDevice(), nullptr, &extensionCount,
                                             extensionProperties.data());

        _logger.logInfoLine("Found the following available physical device extensions as part of VkDevice setup:");

        for (auto&& extensionProperty : extensionProperties)
        {
            _logger.logInfoLine("  Extension Name: " + std::string(extensionProperty.extensionName) +
                                "  Spec Version: " + std::to_string(extensionProperty.specVersion));
        }

        std::vector<std::string> cppNames{};

        std::ranges::transform(extensionProperties, std::back_inserter(cppNames),
                               [&](const auto& x) -> std::string { return std::string(x.extensionName); });

        size_t groupCounter = 0ULL;

        std::vector<std::string> finalRequiredDeviceExtensions{};

        // TODO: EngineConfig was here
        for (auto&& requestedRequiredExt : requiredDeviceExtensions)
        {
            auto result = requestedRequiredExt.FindFirstAvailableExtension(cppNames);

            if (!result.has_value())
            {
                std::string missingExtensions{};

                bool firstRun = true;

                for (const auto& extStr : requestedRequiredExt.extensionNames)
                {
                    if (!firstRun)
                    {
                        missingExtensions += "OR ";
                        firstRun = false;
                    }

                    missingExtensions += extStr;
                }

                throw Exceptions::InitialisationFailureException(
                    "None of the required Vulkan extensions in group " + std::to_string(groupCounter) +
                    " are available on this device. Extensions missing:\n" + missingExtensions);
            }

            finalRequiredDeviceExtensions.emplace_back(*result);

            groupCounter += 1ULL;
        }

        size_t groupCounterOptionals = 0ULL;

        std::vector<std::string> finalOptionalExtensions{};

        // TODO: EngineConfig was here
        for (auto&& requestedOptionalExt : optionalDeviceExtensions)
        {

            auto result = requestedOptionalExt.FindFirstAvailableExtension(cppNames);

            if (!result.has_value())
            {
                std::string missingExtensions{};

                bool firstRun = true;

                for (const auto& extStr : requestedOptionalExt.extensionNames)
                {
                    if (!firstRun)
                    {
                        missingExtensions += "OR ";
                        firstRun = false;
                    }

                    missingExtensions += extStr;
                }

                _logger.logWarningLine("The optional Vulkan extensions in group " +
                                       std::to_string(groupCounterOptionals) +
                                       " are not available on this device. Vulkan may not behave as you expect. "
                                       "Optionally requested was one of the following:");

                _logger.logWarningLine(missingExtensions);
                continue;
            }

            finalOptionalExtensions.emplace_back(*result);

            groupCounter += 1ULL;
        }

        // TODO: EngineConfig was here}
        std::vector<std::string> allExtensions{finalRequiredDeviceExtensions};
        allExtensions.insert(allExtensions.end(), finalOptionalExtensions.begin(), finalOptionalExtensions.end());
        return allExtensions;
    }

    VkDevice VulkanGraphicsDevice::CreateLogicalDevice(
        std::vector<FeatureProviderExtensionGroup> requiredDeviceExtensions,
        std::vector<FeatureProviderExtensionGroup> optionalDeviceExtensions)
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
        VkPhysicalDeviceTimelineSemaphoreFeaturesKHR timelineSemaphore{};
        timelineSemaphore.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES_KHR;
        timelineSemaphore.timelineSemaphore = true;

        VkPhysicalDeviceNestedCommandBufferFeaturesEXT nestedCommandBuffer{};
        VkPhysicalDeviceMaintenance7FeaturesKHR maintenance7{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pNext = &timelineSemaphore;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(physicalDeviceExtensionPtrs.size());
        createInfo.ppEnabledExtensionNames = physicalDeviceExtensionPtrs.data();

        if (std::find(physicalDeviceExtensions.begin(), physicalDeviceExtensions.end(),
                      VK_KHR_MAINTENANCE_7_EXTENSION_NAME) != physicalDeviceExtensions.end())
        {
            timelineSemaphore.pNext = &maintenance7;
            maintenance7.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_7_FEATURES_KHR;
            maintenance7.maintenance7 = true;
        }
        else
        {
            timelineSemaphore.pNext = &nestedCommandBuffer;
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
        vkGetDeviceQueue(device, _indicesData.transferFamily.value(), 0, &_transferQueue);

        _logger.logInfoLine("VkDevice successfully created.");
        return device;
    }

    VulkanGraphicsDevice::GraphicsDevice(std::shared_ptr<VulkanGraphicsAdapter> adapter,
                                         std::shared_ptr<VulkanGraphicsSurfaceContext> surfaceContext,
                                         std::vector<FeatureProviderExtensionGroup> requiredDeviceExtensions,
                                         std::vector<FeatureProviderExtensionGroup> optionalDeviceExtensions)
        : _adapter(std::move(adapter)),
          _surfaceContext(std::move(surfaceContext)),
          _logger(NovelRT::Logging::CONSOLE_LOG_GFX),
          _surface(_surfaceContext->GetSurfaceContextHandle()),
          _device([this, requiredDeviceExtensions, optionalDeviceExtensions]()
                  { return CreateLogicalDevice(requiredDeviceExtensions, optionalDeviceExtensions); }),
          _graphicsQueue(VK_NULL_HANDLE),
          _presentQueue(VK_NULL_HANDLE),
          _transferQueue(VK_NULL_HANDLE),
          _vulkanSwapchain(
              [this]()
              { return std::make_shared<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>>(shared_from_this()); }),
          _indicesData{},
          _queueSubmitMutex(std::make_unique<tbb::mutex>())
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

    std::shared_ptr<VulkanGraphicsSemaphore> VulkanGraphicsDevice::CreateSemaphore(uint64_t initialValue)
    {
        return std::make_shared<VulkanGraphicsSemaphore>(shared_from_this(), initialValue);
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

    void VulkanGraphicsDevice::EndFrame()
    {
        auto swapchain = _vulkanSwapchain.Get();

        if (!swapchain->Present())
        {
            swapchain->RecreateSwapchain();
        }
    }

    void VulkanGraphicsDevice::QueueSubmit(
        NovelRT::Utilities::Span<std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>> cmdLists)
    {
        QueueSubmit({}, cmdLists, {});
    }

    void VulkanGraphicsDevice::QueueSubmit(
        NovelRT::Utilities::Span<std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>> cmdLists,
        NovelRT::Utilities::Span<std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t>>
            semaphoresToSignal)
    {
        QueueSubmit({}, cmdLists, semaphoresToSignal);
    }

    void VulkanGraphicsDevice::QueueSubmit(
        NovelRT::Utilities::Span<std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t>>
            semaphoresToWait,
        NovelRT::Utilities::Span<std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>> cmdLists,
        NovelRT::Utilities::Span<std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t>>
            semaphoresToSignal)
    {
        std::lock_guard guard(*_queueSubmitMutex);

        std::vector<VkCommandBuffer> buffers(cmdLists.size());
        std::vector<VkSemaphore> waitSemaphores(semaphoresToWait.size());
        std::vector<uint64_t> waitSemaphoreValues(semaphoresToWait.size());
        std::vector<VkSemaphore> signalSemaphores(semaphoresToSignal.size());
        std::vector<uint64_t> signalSemaphoreValues(semaphoresToSignal.size());
        std::transform(cmdLists.begin(), cmdLists.end(), buffers.begin(),
                       [](const auto& cmdList) { return cmdList->GetVkCommandBuffer(); });
        std::transform(semaphoresToWait.begin(), semaphoresToWait.end(), waitSemaphores.begin(),
                       [](const auto& semaphore) { return semaphore.first->GetVulkanSemaphore(); });
        std::transform(semaphoresToWait.begin(), semaphoresToWait.end(), waitSemaphoreValues.begin(),
                       [](const auto& semaphore) { return semaphore.second; });
        std::transform(semaphoresToSignal.begin(), semaphoresToSignal.end(), signalSemaphores.begin(),
                       [](const auto& semaphore) { return semaphore.first->GetVulkanSemaphore(); });
        std::transform(semaphoresToSignal.begin(), semaphoresToSignal.end(), signalSemaphoreValues.begin(),
                       [](const auto& semaphore) { return semaphore.second; });

        std::vector<VkPipelineStageFlags> waitDstStageMasks(waitSemaphores.size(), VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

        VkTimelineSemaphoreSubmitInfo semaphoreSubmitInfo{};
        semaphoreSubmitInfo.sType = VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO;
        semaphoreSubmitInfo.waitSemaphoreValueCount = static_cast<uint32_t>(waitSemaphoreValues.size());
        semaphoreSubmitInfo.pWaitSemaphoreValues = waitSemaphoreValues.data();
        semaphoreSubmitInfo.signalSemaphoreValueCount = static_cast<uint32_t>(signalSemaphoreValues.size());
        semaphoreSubmitInfo.pSignalSemaphoreValues = signalSemaphoreValues.data();

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.pNext = &semaphoreSubmitInfo;
        submitInfo.commandBufferCount = static_cast<uint32_t>(buffers.size());
        submitInfo.pCommandBuffers = buffers.data();
        submitInfo.signalSemaphoreCount = static_cast<uint32_t>(signalSemaphores.size());
        submitInfo.pSignalSemaphores = signalSemaphores.data();
        submitInfo.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size());
        submitInfo.pWaitSemaphores = waitSemaphores.data();
        submitInfo.pWaitDstStageMask = waitDstStageMasks.data();

        const VkResult queueSubmitResult = vkQueueSubmit(GetVulkanTransferQueue(), 1, &submitInfo, VK_NULL_HANDLE);
        if (queueSubmitResult != VK_SUCCESS)
        {
            throw std::runtime_error("vkQueueSubmit failed! Reason: " + std::to_string(queueSubmitResult));
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

    VkQueue VulkanGraphicsDevice::GetVulkanTransferQueue() const noexcept
    {
        return _transferQueue;
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

    std::shared_ptr<VulkanGraphicsRenderPass> VulkanGraphicsDevice::CreateRenderPass(
        const GraphicsRenderPassDescription& description)
    {
        return std::make_shared<VulkanGraphicsRenderPass>(shared_from_this(), description);
    }
}
