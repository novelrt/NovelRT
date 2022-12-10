// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/GlfwVulkanUIProvider/UI.GlfwVulkan.h>

namespace NovelRT::UI::GlfwVulkan
{
    GlfwVulkanUIProvider::GlfwVulkanUIProvider() noexcept
        : _isInitialised(false),
        _initInfo(),
        _graphicsDevice(nullptr)
    {
    }

    void GlfwVulkanUIProvider::Initialise(std::shared_ptr<NovelRT::Graphics::GraphicsDevice> gfxDevice,
        std::shared_ptr<NovelRT::Windowing::IWindowingDevice> windowingDevice,
        void* gfxProvider,
        std::shared_ptr<NovelRT::Graphics::GraphicsPipeline> pipeline)
    {
        _logger.logDebugLine("Initialising Dear ImGui UI service with GLFW and Vulkan...");
        if(gfxDevice == nullptr)
        {
            _logger.logErrorLine("Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as GraphicsDevice!");
            throw NovelRT::Exceptions::NullPointerException("Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as GraphicsDevice!");
        }
        if(windowingDevice == nullptr)
        {
            _logger.logErrorLine("Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as IWindowingDevice!");
            throw NovelRT::Exceptions::NullPointerException("Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as IWindowingDevice!");
        }
        if(gfxDevice == nullptr)
        {
            _logger.logErrorLine("Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as IGraphicsPluginProvider!");
            throw NovelRT::Exceptions::NullPointerException("Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as IGraphicsPluginProvider!");
        }
        if(pipeline == nullptr)
        {
            _logger.logErrorLine("Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as GraphicsPipeline!");
            throw NovelRT::Exceptions::NullPointerException("Could not initialise Dear ImGui with GLFW and Vulkan - null pointer provided as GraphicsPipeline!");
        }

        auto vulkanProvider = reinterpret_cast<NovelRT::Graphics::Vulkan::VulkanGraphicsProvider*>(gfxProvider);
        auto vulkanDevice = reinterpret_cast<NovelRT::Graphics::Vulkan::VulkanGraphicsDevice*>(gfxDevice.get());
        _graphicsDevice = std::shared_ptr<NovelRT::Graphics::Vulkan::VulkanGraphicsDevice>(vulkanDevice);
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
        VkCommandBuffer buffer = vulkanDevice->GetCurrentContext()->CreateVulkanCommandBuffer();

        vkBeginCommandBuffer(buffer, &commandBufferBeginInfo);
        ImGui_ImplVulkan_CreateFontsTexture(buffer);
        vkEndCommandBuffer(buffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &buffer;
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
        UIEvent += [&](auto sys)
        {
            unused(sys);
            ImGui::ShowDemoWindow();
            _logger.logDebugLine("Custom UI Event hit.");
        };
    }

    void GlfwVulkanUIProvider::Begin()
    {
        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void GlfwVulkanUIProvider::End()
    {
        ImGuiIO& io = ImGui::GetIO();
        unused(io);
        ImGui::Render();
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), _graphicsDevice->GetCurrentContext()->GetVulkanCommandBuffer());
    }

    GlfwVulkanUIProvider::~GlfwVulkanUIProvider()
    {
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}
