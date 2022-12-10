// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/GlfwVulkanUIProvider/UI.GlfwVulkan.h>

namespace NovelRT::UI::GlfwVulkan
{
    GlfwVulkanUIProvider::GlfwVulkanUIProvider() noexcept
        : _isInitialised(false),
        _initInfo()
    {
    }

    void GlfwVulkanUIProvider::Initialise(std::shared_ptr<NovelRT::Graphics::GraphicsDevice> gfxDevice, std::shared_ptr<NovelRT::Windowing::IWindowingDevice> windowingDevice, std::shared_ptr<NovelRT::PluginManagement::IGraphicsPluginProvider> gfxProvider, std::shared_ptr<NovelRT::Graphics::GraphicsPipeline> pipeline)
    {
        _logger.logDebugLine("Initialising Dear ImGui UI service with GLFW and Vulkan...");
        if(gfxDevice == nullptr)
        {
            _logger.logErrorLine("Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided to gfxDevice!");
            throw NovelRT::Exceptions::NullPointerException("Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided to gfxDevice!");
        }
        if(windowingDevice == nullptr)
        {
            _logger.logErrorLine("Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided to windowingDevice!");
            throw NovelRT::Exceptions::NullPointerException("Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided to windowingDevice!");
        }
        if(gfxDevice == nullptr)
        {
            _logger.logErrorLine("Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided to gfxProvider!");
            throw NovelRT::Exceptions::NullPointerException("Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided to gfxProvider!");
        }

        auto vulkanProvider = reinterpret_cast<NovelRT::Graphics::Vulkan::VulkanGraphicsProvider*>(gfxProvider.get());
        auto vulkanDevice = reinterpret_cast<NovelRT::Graphics::Vulkan::VulkanGraphicsDevice*>(gfxDevice.get());
        auto vulkanPipeline = reinterpret_cast<NovelRT::Graphics::Vulkan::VulkanGraphicsPipeline*>(pipeline.get());

        //Init Dear ImGui Context
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        unused(io);

        //GLFW Specific Init
        ImGui_ImplGlfw_InitForVulkan(reinterpret_cast<GLFWwindow*>(windowingDevice->GetHandle()), true);

        //Vulkan Specific Init
        _initInfo.Instance = vulkanProvider->GetVulkanInstance();
        _initInfo.PhysicalDevice = vulkanDevice->GetAdapter()->GetVulkanPhysicalDevice();
        _initInfo.Device = vulkanDevice->GetVulkanDevice();
        _initInfo.QueueFamily = static_cast<uint32_t>(-1);
        _initInfo.Queue = vulkanDevice->GetVulkanGraphicsQueue();
        _initInfo.PipelineCache = nullptr;
        _initInfo.DescriptorPool = vulkanPipeline->GetSignature()->GetVulkanDescriptorPool();
        _initInfo.Subpass = 0;
        _initInfo.MinImageCount = 2;
        _initInfo.ImageCount = static_cast<uint32_t>(vulkanDevice->GetVulkanSwapChainImages().size());
        _initInfo.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
        _initInfo.Allocator = nullptr;
        _initInfo.CheckVkResultFn = [](VkResult err){
            if (err == 0) return;
            spdlog::error("Vulkan Error: VkResult = {}", err);
            if (err < 0)
            {
                std::runtime_error("Vulkan check failed! Reason: " + std::to_string(err));
            }
        };
        ImGui_ImplVulkan_Init(&_initInfo, vulkanDevice->GetVulkanRenderPass());

        //Fonts init
        _logger.logDebugLine("Dear ImGui - uploading default fonts...");
        VkCommandBufferBeginInfo commandBufferBeginInfo{};
        commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        VkCommandBuffer* buffer = nullptr;
        *buffer = vulkanDevice->GetCurrentContext()->GetVulkanCommandBuffer();

        vkBeginCommandBuffer(*buffer, &commandBufferBeginInfo);
        ImGui_ImplVulkan_CreateFontsTexture(*buffer);
        vkEndCommandBuffer(*buffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &*buffer;
        auto executeGraphicsFence = vulkanDevice->GetCurrentContext()->GetWaitForExecuteCompletionFence();

        VkResult queueSubmitResult = vkQueueSubmit(vulkanDevice->GetVulkanGraphicsQueue(), 1, &submitInfo,
                                                   executeGraphicsFence->GetVulkanFence());

        if (queueSubmitResult != VK_SUCCESS)
        {
            throw std::runtime_error("vkQueueSubmit failed! Reason: " + std::to_string(queueSubmitResult));
        }

        executeGraphicsFence->Wait();
        executeGraphicsFence->Reset();

        _isInitialised = true;
        _logger.logDebugLine("Initialised Dear ImGui UI service with GLFW and Vulkan successfully.");
    }


}
