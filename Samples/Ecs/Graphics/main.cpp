// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>
#include <NovelRT/Ecs/EcsDefaultsBuilder.hpp>

#include <NovelRT/Ecs/Components/EntityGraphComponent.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>

#include <NovelRT/Ecs/Graphics/EcsGraphicsBuilder.hpp>
#include <NovelRT/Ecs/Graphics/RenderPassManager.hpp>
#include <NovelRT/Ecs/Graphics/RenderOrchestratorSystem.hpp>
#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>

#include <NovelRT/Graphics/GraphicsPipelineInput.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElement.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElementKind.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResourceKind.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResource.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapterSelector.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderTarget.hpp>

#include <NovelRT/ResourceManagement/Desktop/DesktopResourceLoader.hpp>

#include <NovelRT/Timing/StepTimer.hpp>

#include <NovelRT/Windowing/Glfw/GlfwWindowProvider.hpp>

#include <NovelRT/Utilities/Macros.hpp>

#include <optional>

using namespace NovelRT::Ecs;
using namespace NovelRT::Ecs::Components;
using namespace NovelRT::Ecs::Graphics;
using namespace NovelRT::Ecs::Graphics::Components;
using namespace NovelRT::Logging;
using namespace NovelRT::Graphics;
using namespace NovelRT::Graphics::Vulkan;
using namespace NovelRT::Timing;
using namespace NovelRT::Windowing;
using namespace NovelRT::Utilities;
using namespace NovelRT::ResourceManagement::Desktop;
using namespace NovelRT::Timing;

struct PtrNonsense
{
    std::shared_ptr<GraphicsRenderPass<VulkanGraphicsBackend>> trianglePass;
    std::shared_ptr<IGraphicsSurface> sampleSurface;
    std::shared_ptr<GraphicsMemoryAllocator<VulkanGraphicsBackend>> memoryAllocator;
    std::shared_ptr<GraphicsDevice<VulkanGraphicsBackend>> gfxDevice;
    RenderPassId triangleRenderPassId;
};


PtrNonsense& GetPtrNonsenseStruct()
{
    static PtrNonsense storage{};
    return storage;
}

struct TexturedVertex
{
    NovelRT::Maths::GeoVector3F Position;
    NovelRT::Maths::GeoVector2F UV;
};

template<typename TBackend>
struct RenderingData
{
    std::shared_ptr<GraphicsBuffer<TBackend>> VertexBuffer;
    std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>> VertexBufferRegion;
    std::shared_ptr<GraphicsPipeline<TBackend>> RenderPipeline;
    std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsTexture, TBackend>> TextureRegion;
    std::shared_ptr<GraphicsContext<TBackend>> GraphicsContext;
};


int main()
{
    auto wndProvider = std::make_shared<WindowProvider<Glfw::GlfwWindowingBackend>>(
        NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(400, 400));

    auto gfxProvider = wndProvider->CreateGraphicsProvider<VulkanGraphicsBackend>(true);
    auto gfxSurfaceContext = std::make_shared<GraphicsSurfaceContext<VulkanGraphicsBackend>>(wndProvider, gfxProvider);
    GetPtrNonsenseStruct().sampleSurface = gfxSurfaceContext->GetSurface();

    VulkanGraphicsAdapterSelector selector{};
    auto gfxAdapter = selector.GetDefaultRecommendedAdapter(gfxProvider, gfxSurfaceContext);
    GetPtrNonsenseStruct().gfxDevice = gfxAdapter->CreateDevice(gfxSurfaceContext);
    GetPtrNonsenseStruct().memoryAllocator = std::make_shared<GraphicsMemoryAllocator<VulkanGraphicsBackend>>(GetPtrNonsenseStruct().gfxDevice, gfxProvider);

    SystemSchedulerBuilder builder{};
    AddDefaults(builder);
    AddGraphics<Vulkan::VulkanGraphicsBackend>(builder)
        .WithGraphicsDevice(GetPtrNonsenseStruct().gfxDevice)
        .WithSurfaceContext(gfxSurfaceContext)
        .ConfigureRenderPasses(
            [](RenderPassManager<VulkanGraphicsBackend>& renderPassManager)
            {
                GraphicsRenderPassDescription passDesc{};
                GraphicsAttachmentDescription attachmentDesc{};

                auto vulkanFormat = GetPtrNonsenseStruct().gfxDevice->GetSwapchain()->GetVulkanFormat();
                if (vulkanFormat == VK_FORMAT_R8G8B8A8_UNORM)
                {
                    attachmentDesc.texelFormat = TexelFormat::R8G8B8A8_UNORM;
                }
                else if (vulkanFormat == VK_FORMAT_B8G8R8A8_UNORM)
                {
                    attachmentDesc.texelFormat = TexelFormat::B8G8R8A8_UNORM;
                }
                else
                {
                    throw NovelRT::Exceptions::InitialisationFailureException("How did you get here?");
                }

                attachmentDesc.loadOp = LoadOp::Clear;
                attachmentDesc.storeOp = StoreOp::Store;
                attachmentDesc.initialLayout = ImageLayout::Undefined;
                attachmentDesc.finalLayout = ImageLayout::Present;

                passDesc.attachmentDescriptions.push_back(attachmentDesc);
                GetPtrNonsenseStruct().trianglePass = GetPtrNonsenseStruct().gfxDevice->CreateRenderPass(passDesc);
                GetPtrNonsenseStruct().triangleRenderPassId = renderPassManager.RegisterRenderPass(GetPtrNonsenseStruct().trianglePass);
            })
        .WithDefaultOrchestrator();

    SystemScheduler scheduler = builder.Build();
    StepTimer timer{};
    Event<Timestamp::duration> TimerCallback{};

    TimerCallback += [&timer,&scheduler](auto /* delta */) { scheduler.ExecuteIteration(timer.getTotalTime()); };

    while (!wndProvider->ShouldClose())
    {
        wndProvider->ProcessAllMessages();
        timer.Tick(TimerCallback);
    }

    return 0;
}
