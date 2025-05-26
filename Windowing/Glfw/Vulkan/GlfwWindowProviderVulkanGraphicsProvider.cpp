#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Windowing/Glfw/GlfwWindowProvider.hpp>

#include <vector>
#include <string>

namespace NovelRT::Windowing
{
    using GlfwWindowProvider = WindowProvider<Glfw::GlfwWindowingBackend>;

    template <>
    std::shared_ptr<Graphics::GraphicsProvider<Graphics::Vulkan::VulkanGraphicsBackend>> GlfwWindowProvider::CreateGraphicsProvider()
    {
        if (glfwVulkanSupported() == GLFW_FALSE)
        {
            //throw Exceptions::InvalidOperationException("Vulkan is not supported on this platform.");
            return nullptr;
        }

        uint32_t extensionCount = 0;
        auto extensions = glfwGetRequiredInstanceExtensions(&extensionCount);
        if (extensionCount == 0)
        {
            const char* output = nullptr;
            glfwGetError(&output);
            if (output != nullptr)
            {
                throw Exceptions::InitialisationFailureException("GLFW3 failed to initialise Vulkan.", std::string(output));
            }
            else
            {
                throw Exceptions::InitialisationFailureException(
                    "GLFW3 failed to initialise Vulkan.",
                    "Attempting to fetch the required Vulkan extensions failed with a count of zero.");
            }
        }

        // TODO: EngineConfig was here
        auto requiredExtensions = std::vector<std::string>(); //EngineConfig::RequiredVulkanInstanceExtensions();

        for (size_t i = 0; i < extensionCount; i++)
        {
            requiredExtensions.emplace_back(extensions[i]);
        }

#ifdef __APPLE__
        requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

        return std::make_shared<Graphics::GraphicsProvider<Graphics::Vulkan::VulkanGraphicsBackend>>(requiredExtensions, std::vector<std::string>{}, std::vector<std::string>{}, std::vector<std::string>{});
    }
}
