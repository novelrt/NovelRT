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

    public:
        GlfwVulkanUIProvider() noexcept;
        ~GlfwVulkanUIProvider() final;
        void Initialise(std::shared_ptr<NovelRT::Graphics::GraphicsDevice> gfxDevice,
            std::shared_ptr<NovelRT::Windowing::IWindowingDevice> windowingDevice,
            std::shared_ptr<NovelRT::Graphics::GraphicsProvider> gfxProvider,
            std::shared_ptr<NovelRT::Graphics::GraphicsPipeline> pipeline);

        void Begin();
        void End(std::shared_ptr<NovelRT::Graphics::GraphicsContext> context);
    };
}


#endif // NOVELRT_UI_GLFWVULKAN_GLFWVULKANUIPROVIDER_H
