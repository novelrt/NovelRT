// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Vulkan/Graphics.Vulkan.h>
#include <NovelRT/Experimental/Graphics/Vulkan/VulkanGraphicsDevice.h>

namespace NovelRT::Experimental::Graphics::Vulkan
{
    VulkanGraphicsDevice::VulkanGraphicsDevice(std::shared_ptr<VulkanGraphicsAdapter> adapter,
                                               std::shared_ptr<IGraphicsSurface> surface,
                                               int32_t contextCount)
        : GraphicsDevice(std::move(adapter), std::move(surface)),
          _fence(VulkanGraphicsFence(std::dynamic_pointer_cast<VulkanGraphicsDevice>(shared_from_this()))),
          _contexts(CreateGraphicsContexts(contextCount)),
          _contextPtrs{},
          _logger(LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_GFX)),
          _device(VK_NULL_HANDLE),
          _graphicsQueue(VK_NULL_HANDLE),
          _presentQueue(VK_NULL_HANDLE),
          _surface(VK_NULL_HANDLE),
          _swapChain(VK_NULL_HANDLE),
          _swapChainImages(std::vector<VkImage>{}),
          _contextIndex(0),
          _vulkanSwapChainFormat(VkFormat{}),
          _swapChainExtent(VkExtent2D{}),
          _renderPass([&]() { return CreateRenderPass(); }),
          _indicesData{},
          _state()
    {
        _contextPtrs.reserve(_contexts.size());

        for (auto&& context : _contexts)
        {
            _contextPtrs.emplace_back(context.shared_from_this());
        }

        Initialise();
        static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
    }

    std::vector<VulkanGraphicsContext> VulkanGraphicsDevice::CreateGraphicsContexts(int32_t contextCount) const
    {
        std::vector<VulkanGraphicsContext> contexts(contextCount);

        for (int32_t i = 0; i < contextCount; i++)
        {
            contexts[i] = VulkanGraphicsContext(std::dynamic_pointer_cast<VulkanGraphicsDevice>(shared_from_this()), i);
        }

        return contexts;
    }

    std::vector<std::string> VulkanGraphicsDevice::GetFinalPhysicalDeviceExtensionSet() const
    {
        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(GetAdapter()->GetVulkanPhysicalDevice(), nullptr, &extensionCount,
                                             nullptr);
        std::vector<VkExtensionProperties> extensionProperties(extensionCount);
        vkEnumerateDeviceExtensionProperties(GetAdapter()->GetVulkanPhysicalDevice(), nullptr, &extensionCount,
                                             extensionProperties.data());

        _logger.logInfoLine("Found the following available physical device extensions:");

        for (auto&& extensionProperty : extensionProperties)
        {
            _logger.logInfoLine("  Extension Name: " + std::string(extensionProperty.extensionName) +
                                "  Spec Version: " + std::to_string(extensionProperty.specVersion));
        }

        for (auto&& requestedRequiredExt : EngineConfig::RequiredVulkanPhysicalDeviceExtensions())
        {
            auto result =
                std::find_if(extensionProperties.begin(), extensionProperties.end(),
                             [&](auto& x) { return strcmp(requestedRequiredExt.c_str(), x.extensionName) == 0; });

            if (result == extensionProperties.end())
            {
                throw Exceptions::InitialisationFailureException(
                    "The required Vulkan extension " + requestedRequiredExt + " is not available on this device.");
            }
        }

        std::vector<std::string> finalOptionalExtensions{};

        for (auto&& requestedOptionalExt : EngineConfig::OptionalVulkanPhysicalDeviceExtensions())
        {
            auto result =
                std::find_if(extensionProperties.begin(), extensionProperties.end(),
                             [&](auto& x) { return strcmp(requestedOptionalExt.c_str(), x.extensionName) == 0; });

            if (result == extensionProperties.end())
            {
                _logger.logWarningLine("The optional Vulkan extension " + requestedOptionalExt +
                                       " is not available on this device. Vulkan may not behave as you expect.");
                continue;
            }

            finalOptionalExtensions.emplace_back(requestedOptionalExt);
        }

        std::vector<std::string> allExtensions = EngineConfig::RequiredVulkanPhysicalDeviceExtensions();
        allExtensions.insert(allExtensions.end(), finalOptionalExtensions.begin(), finalOptionalExtensions.end());
        return allExtensions;
    }

    void VulkanGraphicsDevice::ConfigureOutputSurface(std::shared_ptr<IGraphicsSurface> targetSurface)
    {
        switch (targetSurface->GetKind())
        {
            case GraphicsSurfaceKind::Glfw:
            {
                auto func =
                    reinterpret_cast<VkResult (*)(VkInstance, void*, const VkAllocationCallbacks*, VkSurfaceKHR*)>(
                        targetSurface->GetContextHandle());

                VkResult funcResult = func(GetAdapter()->GetProvider()->GetVulkanInstance(), targetSurface->GetHandle(),
                                           nullptr, &_surface);
                if (funcResult != VK_SUCCESS)
                {
                    throw Exceptions::InitialisationFailureException("Failed to initialise the VkSurfaceKHR.",
                                                                     funcResult);
                }

                _logger.logInfoLine("VkSurfaceKHR successfully created.");
                break;
            }
            case GraphicsSurfaceKind::Unknown:
            case GraphicsSurfaceKind::Android:
            case GraphicsSurfaceKind::Wayland:
            case GraphicsSurfaceKind::Win32:
            case GraphicsSurfaceKind::Xcb:
            case GraphicsSurfaceKind::Xlib:
            default:
                throw Exceptions::NotSupportedException(
                    "The specified graphics surface kind is not supported by this graphics device.");
        }
    }

    QueueFamilyIndices VulkanGraphicsDevice::FindQueueFamilies(VkPhysicalDevice physicalDevice) const noexcept
    {
        QueueFamilyIndices returnObject{};

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        VkBool32 presentSupport = false;

        uint32_t familyIndex = 0;
        for (const auto& queueFamily : queueFamilies)
        {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                returnObject.graphicsFamily = familyIndex;
            }

            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, familyIndex, _surface, &presentSupport);
            if (presentSupport)
            {
                returnObject.presentFamily = familyIndex;
            }

            if (returnObject.IsComplete())
            {
                break;
            }

            ++familyIndex;
        }

        return returnObject;
    }

    bool VulkanGraphicsDevice::CheckPhysicalDeviceRequiredExtensionSupport(
        VkPhysicalDevice physicalDevice) const noexcept
    {
        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensionSet(EngineConfig::RequiredVulkanPhysicalDeviceExtensions().begin(),
                                                   EngineConfig::RequiredVulkanPhysicalDeviceExtensions().end());

        for (const auto& extension : availableExtensions)
        {
            requiredExtensionSet.erase(std::string(extension.extensionName));
        }

        return requiredExtensionSet.empty();
    }

    int32_t VulkanGraphicsDevice::GetPhysicalDeviceOptionalExtensionSupportScore(
        VkPhysicalDevice physicalDevice) const noexcept
    {
        float currentPercentageValue = 0;

        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> optionalExtensionSet(EngineConfig::OptionalVulkanPhysicalDeviceExtensions().begin(),
                                                   EngineConfig::OptionalVulkanPhysicalDeviceExtensions().end());

        float percentageStep = (1.0f / optionalExtensionSet.size()) * 100;

        for (const auto& extension : availableExtensions)
        {

            if (optionalExtensionSet.find(std::string(extension.extensionName)) == optionalExtensionSet.end())
            {
                continue;
            }

            currentPercentageValue += percentageStep;
        }

        return static_cast<int32_t>(currentPercentageValue);
    }

    SwapChainSupportDetails VulkanGraphicsDevice::QuerySwapChainSupport(VkPhysicalDevice physicalDevice) const noexcept
    {
        SwapChainSupportDetails returnDetails;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, _surface, &returnDetails.capabilities);

        uint32_t formatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, _surface, &formatCount, nullptr);

        if (formatCount != 0)
        {
            returnDetails.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, _surface, &formatCount, returnDetails.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, _surface, &presentModeCount, nullptr);

        if (presentModeCount != 0)
        {
            returnDetails.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, _surface, &presentModeCount,
                                                      returnDetails.presentModes.data());
        }

        return returnDetails;
    }

    int32_t VulkanGraphicsDevice::RateDeviceSuitability(VkPhysicalDevice physicalDevice) const noexcept
    {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
        vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

        int32_t score = 0;

        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            score += 1000;
        }

        score += deviceProperties.limits.maxImageDimension2D;
        score += GetPhysicalDeviceOptionalExtensionSupportScore(physicalDevice);

        SwapChainSupportDetails supportDetails = QuerySwapChainSupport(physicalDevice);

        QueueFamilyIndices indices = FindQueueFamilies(physicalDevice);
        if (deviceFeatures.geometryShader == VK_FALSE || !indices.IsComplete() ||
            !CheckPhysicalDeviceRequiredExtensionSupport(physicalDevice) || supportDetails.formats.empty() ||
            supportDetails.presentModes.empty())
        {
            score = -1;
        }

        return score;
    }

    void VulkanGraphicsDevice::CreateLogicalDevice()
    {
        _indicesData = FindQueueFamilies(GetAdapter()->GetVulkanPhysicalDevice());

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

        auto physicalDeviceExtensions = GetFinalPhysicalDeviceExtensionSet();
        auto physicalDeviceExtensionPtrs =
            NovelRT::Utilities::Misc::GetStringSpanAsCharPtrVector(physicalDeviceExtensions);

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(physicalDeviceExtensionPtrs.size());
        createInfo.ppEnabledExtensionNames = physicalDeviceExtensionPtrs.data();

        if (GetAdapter()->GetProvider()->GetDebugModeEnabled())
        {
            auto validationLayers = GetAdapter()->GetProvider()->GetValidationLayers();
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            std::vector<const char*> allValidationLayerPtrs =
                NovelRT::Utilities::Misc::GetStringSpanAsCharPtrVector(validationLayers);
            createInfo.ppEnabledLayerNames = allValidationLayerPtrs.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        VkResult deviceResult = vkCreateDevice(GetAdapter()->GetVulkanPhysicalDevice(), &createInfo, nullptr, &_device);

        if (deviceResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to initialise the VkDevice.", deviceResult);
        }

        vkGetDeviceQueue(_device, _indicesData.graphicsFamily.value(), 0, &_graphicsQueue);
        vkGetDeviceQueue(_device, _indicesData.presentFamily.value(), 0, &_presentQueue);

        _logger.logInfoLine("VkDevice successfully created.");
    }

    VkSurfaceFormatKHR VulkanGraphicsDevice::ChooseSwapSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR>& availableFormats) const noexcept
    {
        VkSurfaceFormatKHR returnFormat{};
        returnFormat.format = VK_FORMAT_UNDEFINED;

        for (const auto& availableFormat : availableFormats)
        {
            if (availableFormat.format == VK_FORMAT_R8G8B8A8_UNORM ||
                availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM)
            {
                if (returnFormat.format != VK_FORMAT_R8G8B8A8_UINT)
                {
                    returnFormat = availableFormat;
                }
            }
        }

        if (returnFormat.format == VK_FORMAT_UNDEFINED)
        {
            _logger.logWarningLine(
                "Vulkan was unable to detect one of the preferred VkFormats for the specified surface. The first "
                "format found is now being used. This may result in unexpected behaviour.");

            returnFormat = availableFormats[0];
        }
        else
        {
            _logger.logInfo("Preferred VkFormat detected.");
        }

        return returnFormat;
    }

    // TODO: freesync and gsync support will go here in a later PR.
    VkPresentModeKHR VulkanGraphicsDevice::ChooseSwapPresentMode(
        const std::vector<VkPresentModeKHR>& /*availablePresentModes*/) const noexcept
    {
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D VulkanGraphicsDevice::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const noexcept
    {
        if (capabilities.currentExtent.width != UINT32_MAX)
        {
            return capabilities.currentExtent;
        }

        auto localSize = GetSurface()->GetSize();

        VkExtent2D actualExtent = {static_cast<uint32_t>(localSize.x), static_cast<uint32_t>(localSize.y)};

        actualExtent.width = std::max(capabilities.minImageExtent.width,
                                      std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height,
                                       std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }

    void VulkanGraphicsDevice::CreateSwapChain()
    {
        SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(GetAdapter()->GetVulkanPhysicalDevice());

        VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);
        uint32_t imageCount = swapChainSupport.capabilities.minImageCount +
                              1; // this variable gets re-used for the actual image count later

        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
        {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = _surface;
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = FindQueueFamilies(GetAdapter()->GetVulkanPhysicalDevice());
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        if (indices.graphicsFamily != indices.presentFamily)
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0;
            createInfo.pQueueFamilyIndices = nullptr;
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        VkResult swapChainResult = vkCreateSwapchainKHR(_device, &createInfo, nullptr, &_swapChain);
        if (swapChainResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create the VkSwapchainKHR.", swapChainResult);
        }

        _logger.logInfoLine("VkSwapchainKHR successfully created. Retrieving VkImages...");

        VkResult imagesKHRQuery = vkGetSwapchainImagesKHR(_device, _swapChain, &imageCount, nullptr);

        if (imagesKHRQuery != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to retrieve the VkImages from the VkSwapchainKHR.",
                                                             imagesKHRQuery);
        }

        _swapChainImages.resize(imageCount);
        imagesKHRQuery = vkGetSwapchainImagesKHR(_device, _swapChain, &imageCount, _swapChainImages.data());

        if (imagesKHRQuery != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to retrieve the VkImages from the VkSwapchainKHR.",
                                                             imagesKHRQuery);
        }

        _vulkanSwapChainFormat = surfaceFormat.format;
        _swapChainExtent = extent;

        _logger.logInfoLine("VkImages successfully retrieved.");
    }

    void VulkanGraphicsDevice::Initialise()
    {
        ConfigureOutputSurface(GetSurface());

        CreateLogicalDevice();
        CreateSwapChain();

        _logger.logInfoLine("Vulkan logical device version 1.2 has been successfully initialised.");
    }

    void VulkanGraphicsDevice::TearDown()
    {
        vkDestroySwapchainKHR(_device, _swapChain, nullptr);
        vkDestroySurfaceKHR(GetAdapter()->GetProvider()->GetVulkanInstance(), _surface, nullptr);
        vkDestroyDevice(_device, nullptr);

        _logger.logInfoLine("Vulkan logical device version 1.2 successfully torn down.");
    }

    std::shared_ptr<ShaderProgram> VulkanGraphicsDevice::CreateShaderProgram(std::string entryPointName,
                                                                             ShaderProgramKind kind,
                                                                             gsl::span<uint8_t> byteData)
    {
        return std::shared_ptr<ShaderProgram>(
            new VulkanShaderProgram(std::static_pointer_cast<VulkanGraphicsDevice>(shared_from_this()),
                                    std::move(entryPointName), kind, byteData));
    }

    VulkanGraphicsDevice::~VulkanGraphicsDevice()
    {
        TearDown();
    }

    std::shared_ptr<GraphicsPipeline> VulkanGraphicsDevice::CreatePipeline(
        std::shared_ptr<GraphicsPipelineSignature> signature,
        std::shared_ptr<ShaderProgram> vertexShader,
        std::shared_ptr<ShaderProgram> pixelShader)
    {
        return std::make_shared<GraphicsPipeline>(shared_from_this(), signature, vertexShader, pixelShader);
    }

    std::shared_ptr<GraphicsPipelineSignature> VulkanGraphicsDevice::CreatePipelineSignature(
        gsl::span<GraphicsPipelineInput> inputs,
        gsl::span<GraphicsPipelineResource> resources)
    {
        return std::make_shared<GraphicsPipelineSignature>(shared_from_this(), inputs, resources);
    }

    VkRenderPass VulkanGraphicsDevice::CreateRenderPass()
    {
        VkRenderPass returnRenderPass;

        VkAttachmentDescription attachmentDescription{};
        attachmentDescription.format = _vulkanSwapChainFormat;
        attachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
        attachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colourAttachmentReference{};
        colourAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colourAttachmentReference;

        VkRenderPassCreateInfo renderPassCreateInfo{};
        renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassCreateInfo.attachmentCount = 1;
        renderPassCreateInfo.pAttachments = &attachmentDescription;
        renderPassCreateInfo.subpassCount = 1;
        renderPassCreateInfo.pSubpasses = &subpass;

        VkResult renderPassResult = vkCreateRenderPass(_device, &renderPassCreateInfo, nullptr, &returnRenderPass);

        if (renderPassResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create the VkRenderPass.", renderPassResult);
        }

        _logger.logInfoLine("Successfully created the VkRenderPass.");
        return returnRenderPass;
    }

    size_t VulkanGraphicsDevice::GetContextIndex() const noexcept
    {
        return _contextIndex;
    }

    std::shared_ptr<GraphicsPrimitive> VulkanGraphicsDevice::CreatePrimitive(
        std::shared_ptr<GraphicsPipeline> pipeline,
        GraphicsMemoryRegion<GraphicsResource>& vertexBufferRegion,
        uint32_t vertexBufferStride,
        GraphicsMemoryRegion<GraphicsResource>& indexBufferRegion,
        uint32_t indexBufferStride,
        gsl::span<const GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions)
    {
        return std::static_pointer_cast<GraphicsPrimitive>(
            CreateVulkanPrimitive(std::dynamic_pointer_cast<VulkanGraphicsPipeline>(pipeline), vertexBufferRegion,
                                  vertexBufferStride, indexBufferRegion, indexBufferStride, inputResourceRegions));
    }

    std::shared_ptr<VulkanGraphicsPrimitive> VulkanGraphicsDevice::CreateVulkanPrimitive(
        std::shared_ptr<VulkanGraphicsPipeline> pipeline,
        GraphicsMemoryRegion<GraphicsResource>& vertexBufferRegion,
        uint32_t vertexBufferStride,
        GraphicsMemoryRegion<GraphicsResource>& indexBufferRegion,
        uint32_t indexBufferStride,
        gsl::span<const GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions)
    {
        return std::make_shared<VulkanGraphicsPrimitive>(
            std::dynamic_pointer_cast<VulkanGraphicsDevice>(shared_from_this()), pipeline, vertexBufferRegion,
            vertexBufferStride, indexBufferRegion, vertexBufferStride, inputResourceRegions);
    }

    void VulkanGraphicsDevice::PresentFrame()
    {
        uint32_t contextIndex = static_cast<uint32_t>(GetContextIndex());
        VkSwapchainKHR vulkanSwapchain = GetVulkanSwapchain();

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &vulkanSwapchain;
        presentInfo.pImageIndices = &contextIndex;

        VkResult presentResult = vkQueuePresentKHR(GetVulkanPresentQueue(), &presentInfo);

        if (presentResult != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to present the data within the present queue!");
        }

        Signal(GetCurrentContext()->GetFence());

        auto presentCompletionGraphicsFence = GetPresentCompletionFence();
        VkResult acquireNextImageResult =
            vkAcquireNextImageKHR(GetVulkanDevice(), vulkanSwapchain, std::numeric_limits<uint64_t>::max(),
                                  VK_NULL_HANDLE, presentCompletionGraphicsFence->GetVulkanFence(), &contextIndex);
        presentCompletionGraphicsFence->Wait();
        presentCompletionGraphicsFence->Reset();

        _contextIndex = contextIndex;
    }

    void VulkanGraphicsDevice::Signal(std::shared_ptr<GraphicsFence> fence)
    {
        SignalVulkan(std::dynamic_pointer_cast<VulkanGraphicsFence>(fence));
    }

    void VulkanGraphicsDevice::WaitForIdle()
    {
        VkResult waitForIdleResult = vkDeviceWaitIdle(_device);

        if (waitForIdleResult != VK_SUCCESS)
        {
            throw std::runtime_error("The VkDevice did not idle correctly! Reason: " +
                                     std::to_string(waitForIdleResult));
        }
    }

    VulkanGraphicsMemoryAllocator* VulkanGraphicsDevice::GetMemoryAllocatorInternal()
    {
        return &_memoryAllocator.getActual();
    }
} // namespace NovelRT::Experimental::Graphics::Vulkan
