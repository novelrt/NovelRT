// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>
#include <NovelRT/Ecs/EcsDefaultsBuilder.hpp>

#include <NovelRT/Ecs/Graphics/EcsGraphicsBuilder.hpp>
#include <NovelRT/Ecs/Graphics/RenderPassManager.hpp>
#include <NovelRT/Ecs/Graphics/RenderOrchestratorSystem.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapterSelector.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>

#include <NovelRT/Timing/StepTimer.hpp>

#include <NovelRT/Windowing/Glfw/GlfwWindowProvider.hpp>

using namespace NovelRT::Ecs;
using namespace NovelRT::Ecs::Graphics;
using namespace NovelRT::Logging;
using namespace NovelRT::Graphics;
using namespace NovelRT::Graphics::Vulkan;
using namespace NovelRT::Timing;
using namespace NovelRT::Windowing;
using namespace NovelRT::Utilities;

int main()
{
    auto wndProvider = std::make_shared<WindowProvider<Glfw::GlfwWindowingBackend>>(
        NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(400, 400));

    auto gfxProvider = wndProvider->CreateGraphicsProvider<VulkanGraphicsBackend>(true);
    auto gfxSurfaceContext = std::make_shared<GraphicsSurfaceContext<VulkanGraphicsBackend>>(wndProvider, gfxProvider);

    VulkanGraphicsAdapterSelector selector{};
    auto gfxAdapter = selector.GetDefaultRecommendedAdapter(gfxProvider, gfxSurfaceContext);
    auto gfxDevice = gfxAdapter->CreateDevice(gfxSurfaceContext);
    auto memoryAllocator = std::make_shared<GraphicsMemoryAllocator<VulkanGraphicsBackend>>(gfxDevice, gfxProvider);

    SystemSchedulerBuilder builder{};

    // TODO: These variables are here to prevent a segfault. We need to revisit the builder to get rid of these arbitrary variables. - Matt J.
    auto a = AddDefaults(builder);
    auto b = AddGraphics<Vulkan::VulkanGraphicsBackend>(builder);

        b.WithGraphicsDevice(gfxDevice)
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
