// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EcsDefaultsBuilder.hpp>
#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>

#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/Components/EntityGraphComponent.hpp>

#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>
#include <NovelRT/Ecs/Graphics/Components/Camera.hpp>
#include <NovelRT/Ecs/Graphics/Components/Viewport.hpp>
#include <NovelRT/Ecs/Graphics/EcsGraphicsBuilder.hpp>
#include <NovelRT/Ecs/Graphics/RenderOrchestratorSystem.hpp>
#include <NovelRT/Ecs/Graphics/RenderPassManager.hpp>
#include <NovelRT/Ecs/Graphics/SpriteRendererSystem.hpp>

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>

#include <NovelRT/Graphics/GraphicsPipeline.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInput.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElement.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElementKind.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResource.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResourceKind.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapterSelector.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderTarget.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>

#include <NovelRT/Maths/GeoMatrix4x4F.hpp>
#include <NovelRT/Maths/GeoVector2F.hpp>
#include <NovelRT/Maths/GeoVector3F.hpp>
#include <NovelRT/Maths/GeoVector4F.hpp>

#include <NovelRT/ResourceManagement/Desktop/DesktopResourceLoader.hpp>

#include <NovelRT/Timing/StepTimer.hpp>

#include <NovelRT/Windowing/Glfw/GlfwWindowProvider.hpp>

#include <NovelRT/Utilities/Macros.hpp>

#include <memory>
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
using namespace NovelRT::Maths;

class SpriteSetupSystem : public IEcsSystem
{
private:
    std::optional<EntityId> _spriteEntity;
    std::optional<EntityId> _cameraViewportEntity;
    std::shared_ptr<DesktopResourceLoader> _resourceLoader;
    GeoVector2F _viewportSize;

public:
    explicit SpriteSetupSystem(std::shared_ptr<DesktopResourceLoader> resourceLoader, GeoVector2F viewportSize)
        : _resourceLoader(std::move(resourceLoader)), _viewportSize(viewportSize)
    {
    }

    void Update(NovelRT::Timing::Timestamp /*delta*/, Catalogue catalogue) final
    {
        if (_spriteEntity.has_value() && _cameraViewportEntity.has_value())
        {
            return;
        }

        auto [spriteView, transformView, graphView, cameraView, viewportView] = catalogue.GetComponentViews<
            NovelRT::Ecs::Graphics::Components::Sprite, NovelRT::Ecs::Components::TransformComponent,
            NovelRT::Ecs::Components::EntityGraphComponent, NovelRT::Ecs::Graphics::Components::Camera,
            NovelRT::Ecs::Graphics::Components::Viewport>();

        auto spriteEntity = catalogue.CreateEntity();
        _spriteEntity = spriteEntity;

        auto assetId = _resourceLoader->TryGetAssetIdBasedOnFilePath("Images/novel-chan.png").value();

        NovelRT::Ecs::Graphics::Components::Sprite sprite{};
        sprite.assetId = assetId;
        spriteView.AddComponent(spriteEntity, sprite);

        NovelRT::Ecs::Components::TransformComponent transform{};
        transform.position = NovelRT::Maths::GeoVector2F(0.0f, 0.0f);
        transform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
        transform.rotationInRadians = 0.0f;
        transformView.AddComponent(spriteEntity, transform);

        EntityGraphComponent graphComp{};
        graphComp.parent = std::numeric_limits<EntityId>::max();
        graphComp.childrenStartNode = std::numeric_limits<EntityId>::max();
        graphView.AddComponent(spriteEntity, graphComp);

        auto cameraViewportEntity = catalogue.CreateEntity();
        _cameraViewportEntity = cameraViewportEntity;

        NovelRT::Ecs::Components::TransformComponent viewportTransform{};
        viewportTransform.position = NovelRT::Maths::GeoVector2F(0.0f, 0.0f);
        viewportTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
        viewportTransform.rotationInRadians = 0.0f;
        transformView.AddComponent(cameraViewportEntity, viewportTransform);

        auto size = _viewportSize;

        NovelRT::Ecs::Graphics::Components::Camera camera{};
        camera.left = -1.0f;
        camera.right = 1.0f;
        camera.top = -1.0f;
        camera.bottom = 1.0f;
        camera.nearPlane = 0.0f;
        camera.farPlane = 1.0f;
        camera.referenceResolutionWidth = 1920;
        camera.referenceResolutionHeight = 1080;

        cameraView.AddComponent(cameraViewportEntity, camera);

        NovelRT::Ecs::Graphics::Components::Viewport viewport{};
        viewport.width = size.x;
        viewport.height = size.y;

        viewportView.AddComponent(cameraViewportEntity, viewport);
    }
};

int main()
{
    auto resourceLoader = std::make_shared<DesktopResourceLoader>();
    resourceLoader
        ->InitAssetDatabase(); // TODO: Hack because this was originally called by the legacy plugin provider stuff.

    auto wndProvider = std::make_shared<WindowProvider<Glfw::GlfwWindowingBackend>>(
        NovelRT::Windowing::WindowMode::Windowed, NovelRT::Maths::GeoVector2F(1920.0f, 1080.0f) / 2.0f);

    auto gfxProvider = wndProvider->CreateGraphicsProvider<VulkanGraphicsBackend>(true);
    auto gfxSurfaceContext = std::make_shared<GraphicsSurfaceContext<VulkanGraphicsBackend>>(wndProvider, gfxProvider);

    VulkanGraphicsAdapterSelector selector{};
    auto gfxAdapter = selector.GetDefaultRecommendedAdapter(gfxProvider, gfxSurfaceContext);
    auto gfxDevice = gfxAdapter->CreateDevice(gfxSurfaceContext);
    auto memoryAllocator = std::make_shared<GraphicsMemoryAllocator<VulkanGraphicsBackend>>(gfxDevice, gfxProvider);

    SystemSchedulerBuilder builder{};


    AddDefaults(builder);
    AddGraphics<Vulkan::VulkanGraphicsBackend>(builder)
        .WithGraphicsDevice(gfxDevice)
        .WithSurfaceContext(gfxSurfaceContext)
        .WithResourceLoader(resourceLoader)
        .WithMemoryAllocator(memoryAllocator)
        .WithDefaultSpriteRendering()
        .WithDefaultOrchestrator();

    auto setupSystem = std::make_shared<SpriteSetupSystem>(resourceLoader, GeoVector2F(1920.0f, 1080.0f) / 2.0f);

    builder.Configure([setupSystem](SystemScheduler& scheduler) { unused(scheduler.RegisterSystem(setupSystem)); });

    SystemScheduler scheduler = builder.Build();
    StepTimer timer{};
    Event<Timestamp::duration> TimerCallback{};

    TimerCallback += [&timer, &scheduler](auto /* delta */) { scheduler.ExecuteIteration(timer.getTotalTime()); };

    while (!wndProvider->ShouldClose())
    {
        wndProvider->ProcessAllMessages();
        timer.Tick(TimerCallback);
    }

    gfxDevice->WaitForIdle();

    return 0;
}
