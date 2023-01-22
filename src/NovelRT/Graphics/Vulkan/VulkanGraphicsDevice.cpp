// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Graphics/Vulkan/Graphics.Vulkan.h"

namespace NovelRT::Graphics::Vulkan
{
    VulkanGraphicsDevice::VulkanGraphicsDevice(const std::shared_ptr<VulkanGraphicsAdapter>& adapter,
                                               const std::shared_ptr<VulkanGraphicsSurfaceContext>& surfaceContext,
                                               int32_t contextCount)
        : GraphicsDevice(adapter, std::static_pointer_cast<GraphicsSurfaceContext>(surfaceContext)),
          _presentCompletionFence([&]() {
              return std::make_shared<VulkanGraphicsFence>(
                  std::dynamic_pointer_cast<VulkanGraphicsDevice>(shared_from_this()), /* isSignaled*/ false);
          }),
          _contextCount(contextCount),
          _contexts([&]() { return CreateGraphicsContexts(_contextCount); }),
          _contextPtrs([&]() { return CreateGraphicsContextPointers(); }),
          _logger(LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_GFX)),
          _surface(GetSurfaceContext()->GetVulkanSurfaceContextHandle()),
          _device([&]() { return CreateLogicalDevice(); }),
          _graphicsQueue(VK_NULL_HANDLE),
          _presentQueue(VK_NULL_HANDLE),
          _contextIndex(0),
          _vulkanSwapChainFormat(VkFormat{}),
          _swapChainExtent(VkExtent2D{}),
          _isAttachedToResizeEvent(false),
          _vulkanSwapchain([&]() { return CreateSwapChain(); }),
          _swapChainImages([&]() { return GetSwapChainImages(); }),
          _renderPass([&]() { return CreateRenderPass(); }),
          _memoryAllocator([&]() { return CreateMemoryAllocator(); }),
          _indicesData{},
          _state()
    {
        _logger.logInfoLine("Provided GPU device: " + GetAdapter()->GetName());
        static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
        auto countFfs = GetSurface()->SizeChanged.getHandlerCount();
        unused(countFfs);
    }

    std::vector<std::shared_ptr<GraphicsContext>> VulkanGraphicsDevice::CreateGraphicsContextPointers()
    {
        std::vector<std::shared_ptr<GraphicsContext>> ptrs{};
        ptrs.reserve(_contexts.getActual().size());

        for (auto&& context : _contexts.getActual())
        {
            ptrs.emplace_back(std::dynamic_pointer_cast<VulkanGraphicsContext>(context->shared_from_this()));
        }

        return ptrs;
    }

    std::vector<std::shared_ptr<VulkanGraphicsContext>> VulkanGraphicsDevice::CreateGraphicsContexts(
        uint32_t contextCount)
    {
        std::vector<std::shared_ptr<VulkanGraphicsContext>> contexts(contextCount);

        for (uint32_t i = 0; i < contextCount; i++)
        {
            contexts[i] = std::make_shared<VulkanGraphicsContext>(
                std::dynamic_pointer_cast<VulkanGraphicsDevice>(shared_from_this()), i);
        }

        return contexts;
    }

    std::shared_ptr<VulkanGraphicsMemoryAllocator> VulkanGraphicsDevice::CreateMemoryAllocator()
    {
        GraphicsMemoryAllocatorSettings allocatorSettings{};
        return std::make_shared<VulkanGraphicsMemoryAllocator>(
            std::dynamic_pointer_cast<VulkanGraphicsDevice>(shared_from_this()), allocatorSettings);
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
            auto result = std::find_if(extensionProperties.begin(), extensionProperties.end(), [&](auto& x) {
                return strcmp(requestedRequiredExt.c_str(), x.extensionName) == 0;
            });

            if (result == extensionProperties.end())
            {
                throw Exceptions::InitialisationFailureException(
                    "The required Vulkan extension " + requestedRequiredExt + " is not available on this device.");
            }
        }

        std::vector<std::string> finalOptionalExtensions{};

        for (auto&& requestedOptionalExt : EngineConfig::OptionalVulkanPhysicalDeviceExtensions())
        {
            auto result = std::find_if(extensionProperties.begin(), extensionProperties.end(), [&](auto& x) {
                return strcmp(requestedOptionalExt.c_str(), x.extensionName) == 0;
            });

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

    VkDevice VulkanGraphicsDevice::CreateLogicalDevice()
    {
        VkDevice device;

        _indicesData = Utilities::FindQueueFamilies(GetAdapter()->GetVulkanPhysicalDevice(), _surface);

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

        VkResult deviceResult = vkCreateDevice(GetAdapter()->GetVulkanPhysicalDevice(), &createInfo, nullptr, &device);

        if (deviceResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to initialise the VkDevice.", deviceResult);
        }

        vkGetDeviceQueue(device, _indicesData.graphicsFamily.value(), 0, &_graphicsQueue);
        vkGetDeviceQueue(device, _indicesData.presentFamily.value(), 0, &_presentQueue);

        _logger.logInfoLine("VkDevice successfully created.");
        return device;
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

    VkSwapchainKHR VulkanGraphicsDevice::CreateSwapChain(VkSwapchainKHR oldSwapchain)
    {
        VkSwapchainKHR vulkanSwapchain;

        SwapChainSupportDetails swapChainSupport = Utilities::QuerySwapChainSupport(
            GetAdapter()->GetVulkanPhysicalDevice(), GetSurfaceContext()->GetVulkanSurfaceContextHandle());

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
        createInfo.imageUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = Utilities::FindQueueFamilies(GetAdapter()->GetVulkanPhysicalDevice(), _surface);
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
        createInfo.oldSwapchain = oldSwapchain;

        VkResult swapChainResult = vkCreateSwapchainKHR(GetVulkanDevice(), &createInfo, nullptr, &vulkanSwapchain);
        if (swapChainResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create the VkSwapchainKHR.", swapChainResult);
        }

        if (oldSwapchain != VK_NULL_HANDLE)
        {
            vkDestroySwapchainKHR(GetVulkanDevice(), oldSwapchain, nullptr);
        }

        _vulkanSwapChainFormat = surfaceFormat.format;
        _swapChainExtent = extent;

        _logger.logInfoLine("VkSwapchainKHR successfully created.");
        return vulkanSwapchain;
    }

    std::vector<VkImage> VulkanGraphicsDevice::GetSwapChainImages()
    {
        VkDevice device = GetVulkanDevice();
        VkSwapchainKHR vulkanSwapchain = GetVulkanSwapchain();

        uint32_t imageCount;
        VkResult imagesKHRQuery = vkGetSwapchainImagesKHR(device, vulkanSwapchain, &imageCount, nullptr);

        if (imagesKHRQuery != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to retrieve the VkImages from the VkSwapchainKHR.",
                                                             imagesKHRQuery);
        }

        ResizeGraphicsContexts(imageCount);

        std::vector<VkImage> swapChainImages = std::vector<VkImage>(imageCount);
        imagesKHRQuery = vkGetSwapchainImagesKHR(device, vulkanSwapchain, &imageCount, swapChainImages.data());

        if (imagesKHRQuery != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to retrieve the VkImages from the VkSwapchainKHR.",
                                                             imagesKHRQuery);
        }

        auto presentCompletionGraphicsFence = GetPresentCompletionFence();

        uint32_t contextIndex = 0;
        VkResult acquireNextImageResult =
            vkAcquireNextImageKHR(GetVulkanDevice(), vulkanSwapchain, std::numeric_limits<uint64_t>::max(),
                                  VK_NULL_HANDLE, presentCompletionGraphicsFence->GetVulkanFence(), &contextIndex);

        if (acquireNextImageResult != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to acquire next VkImage! Reason: " +
                                     std::to_string(acquireNextImageResult));
        }
        presentCompletionGraphicsFence->Wait();

        if (!_isAttachedToResizeEvent)
        {
            _isAttachedToResizeEvent = true;
            GetSurface()->SizeChanged += [&](auto args) { OnGraphicsSurfaceSizeChanged(args); };
        }

        _contextIndex = contextIndex;

        _logger.logInfoLine("VkImages successfully retrieved.");
        return swapChainImages;
    }

    void VulkanGraphicsDevice::TearDown()
    {
        if (_vulkanSwapchain.isCreated())
        {
            vkDestroySwapchainKHR(GetVulkanDevice(), GetVulkanSwapchain(), nullptr);
            _vulkanSwapchain.reset();
        }

        if (_device.isCreated())
        {
            vkDestroyDevice(GetVulkanDevice(), nullptr);
            _device.reset();
        }

        _logger.logInfoLine("Vulkan logical device version 1.2 successfully torn down.");
    }

    std::shared_ptr<ShaderProgram> VulkanGraphicsDevice::CreateShaderProgram(
        std::string entryPointName,
        ShaderProgramKind kind,
        NovelRT::Utilities::Misc::Span<uint8_t> byteData)
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
        return std::static_pointer_cast<GraphicsPipeline>(std::make_shared<VulkanGraphicsPipeline>(
            std::dynamic_pointer_cast<VulkanGraphicsDevice>(shared_from_this()),
            std::dynamic_pointer_cast<VulkanGraphicsPipelineSignature>(signature),
            std::dynamic_pointer_cast<VulkanShaderProgram>(vertexShader),
            std::dynamic_pointer_cast<VulkanShaderProgram>(pixelShader)));
    }

    std::shared_ptr<GraphicsPipelineSignature> VulkanGraphicsDevice::CreatePipelineSignature(
        GraphicsPipelineBlendFactor srcBlendFactor,
        GraphicsPipelineBlendFactor dstBlendFactor,
        NovelRT::Utilities::Misc::Span<GraphicsPipelineInput> inputs,
        NovelRT::Utilities::Misc::Span<GraphicsPipelineResource> resources)
    {
        return std::static_pointer_cast<GraphicsPipelineSignature>(std::make_shared<VulkanGraphicsPipelineSignature>(
            std::dynamic_pointer_cast<VulkanGraphicsDevice>(shared_from_this()), srcBlendFactor, dstBlendFactor, inputs,
            resources));
    }

    VkRenderPass VulkanGraphicsDevice::CreateRenderPass()
    {
        VkRenderPass returnRenderPass;

        // The swap chain needs to be created first to ensure we know the format
        auto vulkanSwapchain = GetVulkanSwapchain();
        unused(vulkanSwapchain);

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

        VkResult renderPassResult =
            vkCreateRenderPass(GetVulkanDevice(), &renderPassCreateInfo, nullptr, &returnRenderPass);

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
        NovelRT::Utilities::Misc::Span<const GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions)
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
        NovelRT::Utilities::Misc::Span<const GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions)
    {
        return std::make_shared<VulkanGraphicsPrimitive>(
            std::dynamic_pointer_cast<VulkanGraphicsDevice>(shared_from_this()), pipeline, vertexBufferRegion,
            vertexBufferStride, indexBufferRegion, indexBufferStride, inputResourceRegions);
    }

    void VulkanGraphicsDevice::PresentFrame()
    {
        auto presentCompletionGraphicsFence = GetPresentCompletionFence();
        presentCompletionGraphicsFence->Wait();
        presentCompletionGraphicsFence->Reset();

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

        VkResult acquireNextImageResult =
            vkAcquireNextImageKHR(GetVulkanDevice(), vulkanSwapchain, std::numeric_limits<uint64_t>::max(),
                                  VK_NULL_HANDLE, presentCompletionGraphicsFence->GetVulkanFence(), &contextIndex);

        if (acquireNextImageResult != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to acquire next VkImage! Reason: " +
                                     std::to_string(acquireNextImageResult));
        }
        presentCompletionGraphicsFence->Wait();

        _contextIndex = contextIndex;
    }

    void VulkanGraphicsDevice::Signal(std::shared_ptr<GraphicsFence> fence)
    {
        SignalVulkan(std::dynamic_pointer_cast<VulkanGraphicsFence>(fence));
    }

    void VulkanGraphicsDevice::WaitForIdle()
    {
        VkResult waitForIdleResult = vkDeviceWaitIdle(GetVulkanDevice());

        if (waitForIdleResult != VK_SUCCESS)
        {
            throw std::runtime_error("The VkDevice did not idle correctly! Reason: " +
                                     std::to_string(waitForIdleResult));
        }
    }

    VulkanGraphicsMemoryAllocator* VulkanGraphicsDevice::GetMemoryAllocatorInternal()
    {
        return _memoryAllocator.getActual().get();
    }

    void VulkanGraphicsDevice::OnGraphicsSurfaceSizeChanged(NovelRT::Maths::GeoVector2F newSize)
    {
        auto presentCompletionGraphicsFence = GetPresentCompletionFence();
        presentCompletionGraphicsFence->Wait();
        presentCompletionGraphicsFence->Reset();

        if (_vulkanSwapchain.isCreated())
        {
            _vulkanSwapchain.reset(CreateSwapChain(_vulkanSwapchain.getActual()));
        }
        else
        {
            _vulkanSwapchain.reset(CreateSwapChain());
        }

        _swapChainImages.reset(GetSwapChainImages());

        for (auto&& context : _contexts.getActual())
        {
            context->OnGraphicsSurfaceSizeChanged(newSize);
        }
    }

    void VulkanGraphicsDevice::SignalVulkan(const std::shared_ptr<VulkanGraphicsFence>& fence) const
    {
        VkResult result = vkQueueSubmit(GetVulkanGraphicsQueue(), 0, nullptr, fence->GetVulkanFence());

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to signal VkQueue PresentQueue! Reason: " + std::to_string(result));
        }
    }

    void VulkanGraphicsDevice::ResizeGraphicsContexts(uint32_t newContextCount)
    {
        _contextCount = newContextCount;
        auto& contexts = _contexts.getActual();
        if (contexts.size() == newContextCount)
        {
            return;
        }

        size_t oldSize = contexts.size();
        contexts.resize(newContextCount);

        for (size_t i = oldSize; i < newContextCount; i++)
        {
            contexts[i] = std::make_shared<VulkanGraphicsContext>(
                std::dynamic_pointer_cast<VulkanGraphicsDevice>(shared_from_this()), i);
        }

        _contextPtrs.reset();
    }
} // namespace NovelRT::Graphics::Vulkan
