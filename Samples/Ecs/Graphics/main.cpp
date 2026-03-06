// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsAdapter.hpp>
#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/GraphicsContext.hpp>
#include <NovelRT/Graphics/GraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsFence.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/GraphicsPipeline.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInput.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElement.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElementKind.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResource.hpp>
#include <NovelRT/Graphics/GraphicsRenderPass.hpp>
#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapterSelector.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderTarget.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchainImage.hpp>

#include <NovelRT/Windowing/Glfw/GlfwWindowProvider.hpp>

using namespace NovelRT::Logging;
using namespace NovelRT::Windowing::Glfw;
using namespace NovelRT::Windowing;
using namespace NovelRT::Graphics::Vulkan;
using namespace NovelRT::Graphics;

int main()
{
    LoggingService logger{};
    logger.setLogLevel(LogLevel::Info);

    auto wndProvider = std::make_shared<WindowProvider<Glfw::GlfwWindowingBackend>>(
        NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(400, 400));

    auto gfxProvider = wndProvider->CreateGraphicsProvider<VulkanGraphicsBackend>(true);
    auto gfxSurfaceContext = std::make_shared<GraphicsSurfaceContext<VulkanGraphicsBackend>>(wndProvider, gfxProvider);

    VulkanGraphicsAdapterSelector selector{};
    auto gfxAdapter = selector.GetDefaultRecommendedAdapter(gfxProvider, gfxSurfaceContext);
    auto gfxDevice = gfxAdapter->CreateDevice(gfxSurfaceContext);
    auto memoryAllocator = std::make_shared<GraphicsMemoryAllocator<VulkanGraphicsBackend>>(gfxDevice, gfxProvider);

    //auto renderingData = SetupSample(gfxDevice, memoryAllocator);

    //std::vector<std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, VulkanGraphicsBackend>>>
    //inputResourceRegions{renderingData.TextureRegion};

    while (!wndProvider->ShouldClose())
    {
        wndProvider->ProcessAllMessages();
        if (wndProvider->IsVisible())
        {
            //Render(renderingData, gfxDevice, inputResourceRegions);
        }
    }

    return 0;
}
