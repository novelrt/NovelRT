// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Graphics/GraphicsAdapter.hpp>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsPipeline.hpp>
#include <NovelRT/Graphics/GraphicsProvider.hpp>
#include <NovelRT/Graphics/GraphicsRenderPass.hpp>
#include <NovelRT/Graphics/ShaderProgram.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Support.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipeline.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp>
#include <NovelRT/Logging/BuiltInLogSections.hpp>
#include <NovelRT/Utilities/Macros.hpp>
#include <NovelRT/Utilities/Strings.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <set>

namespace NovelRT::Graphics::Vulkan
{
    VulkanGraphicsDevice::VulkanGraphicsDevice(VulkanGraphicsAdapter* adapter,
                                               VulkanGraphicsSurfaceContext* surfaceContext,
                                               int32_t contextCount)
        : _adapter(adapter)
        , _surfaceContext(surfaceContext)
        , _presentCompletionFence([&]() { return new VulkanGraphicsFence{this, /* isSignaled*/ false}; })
        , _contextCount(contextCount)
        , _contexts([this]() { return CreateInitialGraphicsContexts(_contextCount); })
        , _logger(LoggingService(NovelRT::Logging::CONSOLE_LOG_GFX))
        , _surface(GetSurfaceContext()->GetVulkanSurfaceContextHandle())
        , _device([&]() { return CreateLogicalDevice(); })
        , _graphicsQueue(VK_NULL_HANDLE)
        , _presentQueue(VK_NULL_HANDLE)
        , _contextIndex(0)
        , _vulkanSwapChainFormat(VkFormat{})
        , _swapChainExtent(VkExtent2D{})
        , _isAttachedToResizeEvent(false)
        , _vulkanSwapchain([&]() { return CreateSwapChain(); })
        , _swapChainImages([&]() { return GetSwapChainImages(); })
        , _renderPass([&]() { return new VulkanGraphicsRenderPass{CreateRenderPass()}; })
        , _indicesData{}
    {
        _logger.logInfoLine("Provided GPU device: " + GetAdapter()->GetName());
        unused(_state.Transition(Threading::VolatileState::Initialised));
        auto countFfs = GetSurface()->SizeChanged.getHandlerCount();
        unused(countFfs);
    }

    std::vector<VulkanGraphicsContext*> VulkanGraphicsDevice::CreateInitialGraphicsContexts(uint32_t contextCount)
    {
        std::vector<VulkanGraphicsContext*> contexts(contextCount);

        for (uint32_t i = 0; i < contextCount; i++)
        {
            contexts[i] = new VulkanGraphicsContext(this, i);
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

        // TODO: EngineConfig was here
        for (auto&& requestedRequiredExt : std::initializer_list<std::string>{})//EngineConfig::RequiredVulkanPhysicalDeviceExtensions())
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

        // TODO: EngineConfig was here
        for (auto&& requestedOptionalExt : std::initializer_list<std::string>{})// EngineConfig::OptionalVulkanPhysicalDeviceExtensions())
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

        // TODO: EngineConfig was here
        std::vector<std::string> allExtensions = std::vector<std::string>{}; //EngineConfig::RequiredVulkanPhysicalDeviceExtensions();
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
            NovelRT::Utilities::GetStringSpanAsCharPtrVector(physicalDeviceExtensions);

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(physicalDeviceExtensionPtrs.size());
        createInfo.ppEnabledExtensionNames = physicalDeviceExtensionPtrs.data();

        std::vector<const char*> allValidationLayerPtrs{};

        if (GetAdapter()->GetProvider()->GetDebugModeEnabled())
        {
            auto validationLayers = GetAdapter()->GetProvider()->GetValidationLayers();
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            allValidationLayerPtrs = NovelRT::Utilities::GetStringSpanAsCharPtrVector(validationLayers);
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
    //NOLINTNEXTLINE(readability-convert-member-functions-to-static) - this will likely need extra data in the future
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
        std::array<uint32_t, 2> queueFamilyIndices{
            indices.graphicsFamily.value(),
            indices.presentFamily.value()
        };

        if (indices.graphicsFamily != indices.presentFamily)
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices.data();
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

        auto* presentCompletionGraphicsFence = GetPresentCompletionFence();

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
        if (_vulkanSwapchain.HasValue())
        {
            vkDestroySwapchainKHR(GetVulkanDevice(), GetVulkanSwapchain(), nullptr);
            _vulkanSwapchain.Reset();
        }

        if (_device.HasValue())
        {
            vkDestroyDevice(GetVulkanDevice(), nullptr);
            _device.Reset();
        }

        _logger.logInfoLine("Vulkan logical device version 1.2 successfully torn down.");
    }

    std::unique_ptr<VulkanShaderProgram> VulkanGraphicsDevice::CreateShaderProgram(
        std::string entryPointName,
        ShaderProgramKind kind,
        NovelRT::Utilities::Span<uint8_t> byteData)
    {
        return std::make_unique<VulkanShaderProgram>(this, std::move(entryPointName), kind, byteData);
    }

    VulkanGraphicsDevice::~VulkanGraphicsDevice()
    {
        TearDown();
    }

    std::unique_ptr<VulkanGraphicsPipeline> VulkanGraphicsDevice::CreatePipeline(
        VulkanGraphicsPipelineSignature* signature,
        VulkanShaderProgram* vertexShader,
        VulkanShaderProgram* pixelShader,
        bool imguiRenderMode)
    {
        return std::make_unique<VulkanGraphicsPipeline>(this, signature, vertexShader, pixelShader, imguiRenderMode);
    }

    std::unique_ptr<VulkanGraphicsPipelineSignature> VulkanGraphicsDevice::CreatePipelineSignature(
        GraphicsPipelineBlendFactor srcBlendFactor,
        GraphicsPipelineBlendFactor dstBlendFactor,
        NovelRT::Utilities::Span<GraphicsPipelineInput> inputs,
        NovelRT::Utilities::Span<GraphicsPipelineResource> resources,
        NovelRT::Utilities::Span<GraphicsPushConstantRange> pushConstantRanges)
    {
        return std::make_unique<VulkanGraphicsPipelineSignature>(this, srcBlendFactor, dstBlendFactor,
                                                                 inputs, resources, pushConstantRanges);
    }

    VkRenderPass VulkanGraphicsDevice::CreateRenderPass()
    {
        VkRenderPass returnRenderPass;

        // The swap chain needs to be created first to ensure we know the format
        auto* vulkanSwapchain = GetVulkanSwapchain();
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

        VkSubpassDependency dependency = {};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo renderPassCreateInfo{};
        renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassCreateInfo.attachmentCount = 1;
        renderPassCreateInfo.pAttachments = &attachmentDescription;
        renderPassCreateInfo.subpassCount = 1;
        renderPassCreateInfo.pSubpasses = &subpass;
        renderPassCreateInfo.pDependencies = &dependency;
        renderPassCreateInfo.dependencyCount = 1;

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

    void VulkanGraphicsDevice::PresentFrame()
    {
        auto* presentCompletionGraphicsFence = GetPresentCompletionFence();
        presentCompletionGraphicsFence->Reset();

        auto contextIndex = static_cast<uint32_t>(GetContextIndex());
        VkSwapchainKHR vulkanSwapchain = GetVulkanSwapchain();

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &vulkanSwapchain;
        presentInfo.pImageIndices = &contextIndex;

        std::shared_ptr<VulkanGraphicsFence> fence = GetCurrentContext()->GetFence();
        Signal(fence);
        fence->Wait();
        fence->Reset();

        const VkResult presentResult = vkQueuePresentKHR(GetVulkanPresentQueue(), &presentInfo);

        if (presentResult != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to present the data within the present queue!");
        }

        const VkResult acquireNextImageResult = vkAcquireNextImageKHR(GetVulkanDevice(), vulkanSwapchain, std::numeric_limits<uint64_t>::max(),
                                  VK_NULL_HANDLE, presentCompletionGraphicsFence->GetVulkanFence(), &contextIndex);

        if (acquireNextImageResult != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to acquire next VkImage! Reason: " +
                                     std::to_string(acquireNextImageResult));
        }

        presentCompletionGraphicsFence->Wait();
        _contextIndex = contextIndex;
    }

    void VulkanGraphicsDevice::Signal(VulkanGraphicsFence* fence) const
    {
        const VkResult result = vkQueueSubmit(GetVulkanGraphicsQueue(), 0, nullptr, fence->GetVulkanFence());

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to signal VkQueue PresentQueue! Reason: " + std::to_string(result));
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

    std::vector<VulkanGraphicsContext*>::iterator VulkanGraphicsDevice::begin() noexcept
    {
        return _contexts.Get().begin();
    }

    std::vector<VulkanGraphicsContext*>::iterator VulkanGraphicsDevice::end() noexcept
    {
        return _contexts.Get().end();
    }

    VulkanGraphicsContext* VulkanGraphicsDevice::GetCurrentContext()
    {
        return _contexts.Get()[GetContextIndex()];
    }

    IGraphicsSurface* VulkanGraphicsDevice::GetSurface() const noexcept
    {
        return _surfaceContext->GetSurface();
    }

    void VulkanGraphicsDevice::OnGraphicsSurfaceSizeChanged(NovelRT::Maths::GeoVector2F newSize)
    {
        auto* presentCompletionGraphicsFence = GetPresentCompletionFence();
        presentCompletionGraphicsFence->Wait();
        presentCompletionGraphicsFence->Reset();

        if (_vulkanSwapchain.HasValue())
        {
            _vulkanSwapchain.Reset(CreateSwapChain(_vulkanSwapchain.Get()));
        }
        else
        {
            _vulkanSwapchain.Reset(CreateSwapChain());
        }

        _swapChainImages.Reset(GetSwapChainImages());

        for (auto&& context : _contexts.Get())
        {
            context->OnGraphicsSurfaceSizeChanged(newSize);
        }
    }

    void VulkanGraphicsDevice::ResizeGraphicsContexts(uint32_t newContextCount)
    {
        _contextCount = newContextCount;
        auto& contexts = _contexts.Get();
        if (contexts.size() == newContextCount)
        {
            return;
        }

        const size_t oldSize = contexts.size();
        contexts.resize(newContextCount);

        for (size_t i = oldSize; i < newContextCount; i++)
        {
            contexts[i] = new VulkanGraphicsContext(this, i);
        }
    }
} // namespace NovelRT::Graphics::Vulkan

template class NovelRT::Graphics::GraphicsDevice<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
