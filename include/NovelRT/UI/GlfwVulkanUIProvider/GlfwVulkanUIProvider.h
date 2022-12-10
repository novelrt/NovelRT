// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_GLFWVULKAN_GLFWVULKANUIPROVIDER_H
#define NOVELRT_UI_GLFWVULKAN_GLFWVULKANUIPROVIDER_H

#ifndef NOVELRT_UI_GLFWVULKAN_H
#error NovelRT does not support including types explicitly by default. Please include UI.GlfwVulkan.h instead for the UI::GlfwVulkan namespace subset.
#endif

namespace NovelRT::UI::GlfwVulkan
{
    class GlfwVulkanUIProvider final : public UI::UIProvider
    {
    protected:
        bool _isInitialised;
        ImGui_ImplVulkan_InitInfo _initInfo;
        std::shared_ptr<NovelRT::Graphics::Vulkan::VulkanGraphicsDevice> _graphicsDevice;

    public:
        GlfwVulkanUIProvider() noexcept;
        ~GlfwVulkanUIProvider() final;
        void Initialise(std::shared_ptr<NovelRT::Graphics::GraphicsDevice> gfxDevice,
            std::shared_ptr<NovelRT::Windowing::IWindowingDevice> windowingDevice,
            void* gfxProvider,
            std::shared_ptr<NovelRT::Graphics::GraphicsPipeline> pipeline);

        void Begin();
        void End();
    };
}


#endif // NOVELRT_UI_GLFWVULKAN_GLFWVULKANUIPROVIDER_H
